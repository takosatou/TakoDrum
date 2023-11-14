/*******************************************************************************

 TakoDrum by Takashi Satou
 takosatou@gmail.com

 licensed under a MIT license https://opensource.org/licenses/MIT

 Based on Bare Conductive work
 This work is licensed under a MIT license https://opensource.org/licenses/MIT

 Copyright (c) 2016, Bare Conductive

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

*******************************************************************************/

#include "Compiler_Errors.h"
#include <MPR121.h>
#include <MPR121_Datastream.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SdFat.h>

const uint32_t BAUD_RATE = 115200;
const uint8_t MPR121_ADDR = 0x5C;
const uint8_t MPR121_INT = 4;

// MIDI constants
SoftwareSerial mySerial(12, 10);  // soft TX on 10, we don't use RX in this code
const uint8_t RESET_MIDI = 8;  // tied to VS1053 Reset line

#define SD_SEL 5
SdFat sd;
SdFile file;

void talkMIDI(byte cmd, byte data1, byte data2) {
  mySerial.write(cmd);
  mySerial.write(data1);
  if ((cmd & 0xF0) <= 0xB0) {
    mySerial.write(data2);
  }
}

void setupMidi() {
  talkMIDI(0xB0, 0x07, 127);
  talkMIDI(0xB0, 0, 0x78); // bank GM1 + GM2
  talkMIDI(0xC0, 0, 0);  // set instrument number 0
}

void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI((0x90 | channel), note, attack_velocity);
}

void setup() {
  Serial.begin(BAUD_RATE);
  mySerial.begin(31250);  // setup soft serial for MIDI control

  // while (!Serial)
  //   ;

  pinMode(PIN_A11, INPUT);

  if (!sd.begin(SD_SEL, SPI_HALF_SPEED)) {
    sd.initErrorHalt();
  }
  if (int8_t(sd.vol()->fatType()) == 0) {
    Serial.println("SD Fail");
  } else {
    Serial.println("SD OK");
  }
  setup_drum_data();

  if (!MPR121.begin(MPR121_ADDR)) {
    Serial.println("err MPR121");
    Serial.println(MPR121.getError(), DEC);
    while (1); // halt
  }

  MPR121.setInterruptPin(MPR121_INT);
  MPR121.setTouchThreshold(40);
  MPR121.setReleaseThreshold(20);

  MPR121.setFFI(FFI_10);
  MPR121.setSFI(SFI_10);
  MPR121.setGlobalCDT(CDT_4US);  // reasonable for larger capacitances

  pinMode(LED_BUILTIN, OUTPUT);
  analogWrite(LED_BUILTIN, 255);  // switch on user LED while auto calibrating electrodes
  delay(1000);
  MPR121.autoSetElectrodes();  // autoset all electrode settings
  analogWrite(LED_BUILTIN, 0);

  // reset MIDI player
  pinMode(RESET_MIDI, OUTPUT);
  digitalWrite(RESET_MIDI, LOW);
  delay(100);
  digitalWrite(RESET_MIDI, HIGH);
  delay(100);

  // initialise MIDI
  setupMidi();
}

/**
27 High Q
28 Slap
29 Scratch Push
30 Scratch Pull
31 Sticks
32 Square Click
33 Metronome Click
34 Metronome Bell
35 Acoustic Bass Drum
36 Bass Drum 1
37 Side Stick
38 Acoustic Snare
39 Hand Clap
40 Snare Drum 2
41 Low Floor Tom
42 Closed Hi-hat
43 High Floor Tom
44 Pedal Hi-hat
45 Low Tom
46 Open Hi-hat
47 Low-Mid Tom
48 High Mid Tom
49 Crash Cymbal 1
50 High Tom
51 Ride Cymbal 1
52 Chinese Cymbal
53 Ride Bell
54 Tambourine
55 Splash Cymbal
56 Cowbell
57 Crash Cymbal 2
58 Vibra Slap
59 Ride Cymbal 2
60 High Bongo
61 Low Bongo
62 Mute High Conga
63 Open High Conga
64 Low Conga
65 High Timbale
66 Low Timbale
67 High Agogo
68 Low Agogo
69 Cabasa
70 Maracas
71 Short Whistle
72 Long Whistle
73 Short Guiro
74 Long Guiro
75 Claves
76 High Wood Block
77 Low Wood Block
78 Mute Cuica
79 Open Cuica
80 Mute Triangle
81 Open Triangle
82 Shaker
83 Jingle Bell
84 Belltree
85 Castanets
86 Mute Surdo
87 Open Surdo
*/

const uint8_t INITIAL_SOUNDS[] = {
  35, // acoustic Bass Drum
  38, // acoustic Snare
  42, // closed Hi-hat
  46, // open Hi-hat
  49, // Crash Cymbal
  55, // Splash Cymbal
  45, // Low floor Tom
  48, // High-Mid Tom
  43, // High floor Tom
  39, // Hand Clap
  56, // Cowbell
};

const uint8_t N_SOUND = 11;
const uint8_t ACCENT = N_SOUND + 1;
const uint16_t ACCENT_BIT = 1 << (ACCENT-1);
enum { STEP16 = 16, STEP12 = 12 } steps = STEP16;
enum { VARIATION_AB = 0, VARIATION_A = 1, VARIATION_B = 2 } variation = VARIATION_A;

struct Bank {
  uint8_t sounds[N_SOUND]; // the MIDI instrument number
  uint16_t data[STEP16 * 2]; // stores bits of step16
};

const uint8_t N_BANK = 6;

Bank banks[N_BANK * 2]; // for step16 and step12
uint8_t bank_number = 0xff;
uint8_t prev_bank_number = 0xff;

uint16_t* data;
uint8_t* sounds;

uint8_t count = 0;
uint16_t record_data;
uint16_t erase_data;
uint16_t tmp_data;

unsigned long t = 0;
unsigned long prev_t = 0;
uint16_t interval = 125;

bool metronome = false;
bool playing = false;
bool prev_playing = false;
bool sound_set = false;
bool record = false;
bool prev_record = false;
bool erase = false;
bool prev_erase = false;

const uint8_t NORMAL_VELOCITY = 0x50;
const uint8_t LED_HI = 0x80;
const uint8_t LED_LO = 0x10;
uint8_t accent = 0;

char filename[] = "takodrum.dat";

uint16_t prev_bank_v;

int diff(int a, int b) {
  return a > b ? a - b : b - a;
}

void get_controls() {
  // char sbuf[64];
  uint16_t v = analogRead(PIN_A0) * 127.0 / 1023;
  talkMIDI(0xB0, 0x07, v); // set volume  max 127

  prev_record = record;
  prev_erase = erase;
  v = analogRead(PIN_A5) + 128;
  record = (v & 0x0100);
  erase = (v & 0x0200);
  // sprintf(sbuf, "v=%d %d %d", v, record, erase);
  // Serial.println(sbuf);

  v = analogRead(PIN_A4) + 32;
  steps = (v & 0x0080) ? STEP12 : STEP16;
  metronome = (v & 0x0200) != 0;
  prev_playing = playing;
  playing = (v & 0x0040) != 0;
  sound_set = (v & 0x100) != 0;
  // sprintf(sbuf, "%d %d %d %d", steps, metronome, playing, sound_set);
  // Serial.println(sbuf);

  // variation A/AB/B
  v = analogRead(PIN_A11);
  // sprintf(sbuf, "%d", v);
  // Serial.println(sbuf);
  variation = v < 10 ? VARIATION_AB : v < 512 ? VARIATION_B : VARIATION_A;

  // read the BANK rotally switch
  v = analogRead(PIN_A3);
  // ignore noisy values
  if (v == prev_bank_v) {
    uint16_t u = (v + 102) / 204;
    if (diff(u * 204, v) < 5) {
      prev_bank_number = bank_number;
      bank_number = u;
    }
  }
  prev_bank_v = v;

  accent = analogRead(PIN_A2) * (127.0 - NORMAL_VELOCITY) / 1023 + NORMAL_VELOCITY;
}

void blink_LED(int i) {
  delay(500);
  while (i > 0) {
    delay(200);
    analogWrite(LED_BUILTIN, 255);
    delay(200);
    analogWrite(LED_BUILTIN, 0);
    i--;
  }
  delay(500);
}

void load_data() {
  get_controls();
  // if you press RECORD button on booting, load the 'takodru{bank_number}.dat' file.
  if (record) {
    filename[7] = bank_number + '1';
    blink_LED(bank_number);
  }

  Serial.println("loading SD");
  Serial.println(filename);
  if (!file.open(filename, O_READ)) {
    Serial.println("OP err");
    return;
  }
  if (file.read((void*)banks, sizeof(banks)) != sizeof(banks)) {
    Serial.println("RD err");
  }
  file.close();
  Serial.println("loaded");
}

void save_data() {
  Serial.println("Saving SD");
  Serial.println(filename);
  if (!file.open(filename, O_WRITE | O_CREAT | O_TRUNC)) {
    Serial.println("OP err");
    return;
  }
  if (file.write((void*)banks, sizeof(banks)) != sizeof(banks)) {
    Serial.println("WR err");
  }
  file.close();
  Serial.println("saved");
}

void setup_drum_data() {
  for (int i = 0; i < N_BANK * 2; i++) {
    memcpy(banks[i].sounds, INITIAL_SOUNDS, N_SOUND);
  }
  load_data();
}

uint8_t last_sound = 0;

void touch_and_sound() {
  uint8_t sound = 0xff;
  uint8_t velocity = MPR121.getTouchData(ACCENT - 1) ?  accent : NORMAL_VELOCITY;
  for (int i = 0; i < N_SOUND; i++) {
    if (MPR121.isNewTouch(i)) {
      noteOn(0, sounds[i], velocity);
      sound = i;
    }
  }
  if (sound != 0xff) {
    last_sound = sound;
  }
}

/**
   If the SOUND-SET switch is ON, you can select sound for the tapped sensor 
   by pressing RECORD and ERASE buttons.
 */
void sound_set_mode() {
  touch_and_sound();

  const uint8_t FIRST_SOUND = 27;
  const uint8_t LAST_SOUND = 87;
  if (record && !prev_record) {
    sounds[last_sound]--;
    if (sounds[last_sound] < FIRST_SOUND) sounds[last_sound] = LAST_SOUND;
    noteOn(0, sounds[last_sound], NORMAL_VELOCITY);
  } else if (erase && !prev_erase) {
    sounds[last_sound]++;
    if (sounds[last_sound] > LAST_SOUND) sounds[last_sound] = FIRST_SOUND;
    noteOn(0, sounds[last_sound], NORMAL_VELOCITY);
  }
  analogWrite(LED_BUILTIN, sounds[last_sound] == FIRST_SOUND ? LED_HI : 0);

  delay(30);
}

void incr_count() {
  count = (count + 1) % (steps * (variation == VARIATION_AB ? 2 : 1));
}

/**
   On PLAY mode, you can write the rhythm by tapping touch sensors in realtime.
   While tapping the RECORD button, the written rhythm is kept and played in the following loop.
   While pressing the ERASE button, the notes of touched instruments will be erased.
 */
void on_play() {
  for (int i = 0; i < ACCENT; i++) {
    uint16_t bit = 1 << i;

    if (MPR121.isNewTouch(i)) {
      tmp_data |= bit;
      if (record) {
        record_data |= bit;
      }
    }
    if (erase && MPR121.getTouchData(i)) {
      erase_data |= bit;
    }
  }

  if (t >= prev_t + interval) {
    prev_t = t;

    uint16_t tempo = analogRead(PIN_A1);
    interval = 33694000 / (tempo + 11484) - 2684;

    data[count] = (data[count] & ~erase_data) | record_data;

    uint8_t velocity = ((data[count] & ACCENT_BIT) || (!erase && (tmp_data & ACCENT_BIT))) ? accent : NORMAL_VELOCITY;

    for (int i = 0; i < N_SOUND; i++) {
      uint16_t bit = 1 << i;
      if ((data[count] & bit) || (!erase && (tmp_data & bit))) {
        noteOn(0, sounds[i], velocity);
      }
    }

    if (count == 0) {
      if (metronome) {
        noteOn(0, 34, 0x40); // Bell
      }
      analogWrite(LED_BUILTIN, LED_HI);
    } else if ((count & 0x03) == 0) {
      if (metronome) {
        noteOn(0, 33, 0x40); // Click
      }
      analogWrite(LED_BUILTIN, LED_LO);
    }
    incr_count();

    tmp_data = erase_data = record_data = 0;
  } else {
    analogWrite(LED_BUILTIN, 0);
  }
}

/**
   On STOP mode, you can write the rhythm step by step using two buttons like DR-55.
   At first, select the sound by tapping a touch sensor, then press the note or rest button.
 */
void on_stop() {
  touch_and_sound();

  if (record && !prev_record) {
    data[count] |= (1 << last_sound);
    noteOn(0, sounds[last_sound], NORMAL_VELOCITY);
    incr_count();
  } else if (erase && !prev_erase) {
    data[count] &= ~(1 << last_sound);
    incr_count();
  }
  if (count == 0) {
    analogWrite(LED_BUILTIN, LED_HI);
  } else if ((count & 0x03) == 0) {
    analogWrite(LED_BUILTIN, LED_LO);
  } else {
    analogWrite(LED_BUILTIN, 0);
  }
  delay(30);
}

void loop() {
  t = millis();
  if (prev_t == 0) {
    prev_t = t;
    return;
  }

  MPR121.updateAll();

  get_controls();

  Bank& cur_bank = banks[(steps == STEP16 ? 0 : 1) * N_BANK + bank_number];
  data = &cur_bank.data[variation == VARIATION_B ? STEP16 : 0];
  sounds = cur_bank.sounds;

  if (prev_bank_number != bank_number && prev_bank_number < N_BANK && bank_number < N_BANK) {
    // char sbuf[16];
    // sprintf(sbuf, "%d->%d", prev_bank_number, bank_number);
    // Serial.println(sbuf);
    Bank& prev_bank = banks[(steps == STEP16 ? 0 : 1) * N_BANK + prev_bank_number];
    int n = variation == VARIATION_AB ? 2 : 1;
    if (erase) { // erase
      memset((void*)data, 0, STEP16 * n * sizeof(uint16_t));
    } else if (record) { // copy
      uint16_t* prev_data = &prev_bank.data[variation == VARIATION_B ? STEP16 : 0];
      memcpy((void*)data, (void*)prev_data, STEP16 * n * sizeof(uint16_t));
      memcpy((void*)sounds, (void*)prev_bank.sounds, N_SOUND * sizeof(uint8_t));
    }
  }

  if (sound_set) {
    sound_set_mode();
  } else if (playing) {
    on_play();
  } else {
    // On switching from PLAY to STOP, save the data to the SD card.
    if (prev_playing) {
      save_data();
      count = 0;
    }
    on_stop();
  }
}


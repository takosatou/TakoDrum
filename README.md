TakoDrum

# 概要
TakoDrumは、Bare Conductive の Touch Board を使ったリズムボックスです。BOSS DR-55 のような操作性で、リズムパターンを打ち込んだり、ルーパーのようにリアルタイムに打ち込みも可能です。

# 各部の説明
![panel](https://github.com/takosatou/TakoDrum/assets/52827488/ffbaf423-6855-4952-863d-ea559199a3aa)

- RESET ... リセットボタン。タッチパッドの感度の自動調整をします。起動時や、タッチパッドの反応が悪い時、タッチパッドの上に紙などを置いて使用するときに押してください。リセットボタンを押すと、数秒間LEDが明滅してから復帰します。
- VOLUME ... 音量を調整します。いちばん左に回すと電源OFFになります。
- TEMPO ... テンポを調整します。一番左が 60bpm、中央が120bpm、一番右が240bpmくらいです。
- LED ... 再生時や打ち込み時に明滅します。
  - 明 ... 起動時、パターンの先頭のステップ
  - 暗 ... 4ステップ間隔
- RECORD ... モードによって次の働きをします。
  - DR-55モード ... 16分音符。その拍で音を出すようにメモリに記録します。
  - ルーパーモード ... RECORDボタンを押しながらタッチしたパターンをメモリに記録します。
  - 音色設定モード ... 音色リストの前の音色を選択します。
- ERASE
  - DR-55モード ... 16分休符。その拍で音を出さないようにメモリを消します。
  - ルーパーモード ... ERASEボタンを押している間、タッチしたパターンをメモリから消します。
  - 音色設定モード ... 音色リストの次の音色を選択します。
- ACCENT ... アクセントの強さを設定します。一番左がアクセントなしです。
- METRONOME ... 右にするとメトロノーム音を出します。パターンの先頭ステップでベルが鳴ります。
- SOUND SET ... 右にすると音色設定モードにします。
- 16/12 ... ステップ数を切り替えます。
  - 16 ... 16ステップ。4拍子用
  - 12 ... 12ステップ。3拍子、6拍子用
- バンク ... 1〜6のバンクを切り替えます。
- A/AB/B ... パターンの前半（A）、全体（AB）、後半（B）のバリエーションを切り替えます。
- STOP/PLAY ... 演奏を停止・再生します。STOPの時はDR-55モードでぱたーんを打ち込めます。
- タッチパッド ... タッチすると11種類の音色を再生します。右下のACCはアクセントを指定し、ACCENTつまみにしたがって、大きな音で再生します。
- LINE OUT ... 標準ジャック（モノラル）。アンプやヘッドホンを接続します。音量はVOLUMEに連動します。差し込むと、内蔵スピーカーからの音声が止まります。
- DC IN 9V ... 外部電源入力ジャック。9V程度のDC電源を接続します。プラグは標準的な外側がアースのものと、エフェクターによく使われるセンターアースの両方に対応しています。
- 内蔵スピーカー ... LINE OUTに接続していないときに音が出ます。

# メモリーの構成
メモリーには、32ないし24ステップのパターンを6バンク記憶できます。バンクは1〜6のロータリースイッチで切り替えます。

A/AB/Bスイッチにより、パターンの前半または後半の16ないし12ステップのみを使うことができます。16ステップと12ビートは別のメモリー空間になっています。（DR1-55では、12ステップは2パターンのみでした）

1バンクごとに音色のセットを設定できます。詳細は、音色設定モードの説明を参照。

# DR-55モード
STOP/PLAYスイッチを左のSTOPにしている時、DR-55と同様に、RECORDボタン(16分音符)とERASEボタン(16分休符)を使ってパターンをステップ入力できます。

設定したい音色をタッチパッドをタップしてから、RECORDボタン(16分音符)またはERASEボタン(16分休符)を押して、1ステップ毎に音を出すか出さないかを指定します。パターンの末尾まで到達すると先頭に戻ります。

4ステップ毎にLEDが光ります。パターンの先頭のステップの時は、LEDが明るく光ります。

間違えて入力してしまった時には、LEDが明るく光るまで、どちらかのボタンを押して先頭に戻り、改めて入力し直してください。

STOP/PLAYスイッチを右のSTARTにすると、入力したパターンを再生します。


https://github.com/takosatou/TakoDrum/assets/52827488/485c4f15-3738-4780-af94-5a3363d04036


# ルーパーモード

STOP/PLAYスイッチを右のSTARTにして再生している時、RECORDボタンまたはERASEボタンを押しながらタッチパッドをタップすると、リアルタイムにパターン入力できます。

RECORDボタンを押しながら入力したタッチパッドをタップすると、メモリーに記録され、次のループで自動再生します。

ERASEボタンを押しながらタッチパッドをタッチすると、タッチしている間、メモリーから消去されて音が出なくなります。特定の音色を消したいときには、ERASEボタンと対象の音色のタッチパッドをループが一巡するまで押し続けます。

RECORDボタンとERASEボタンを同時押ししてタッチパッドをタップすると、タップしたパターンに入れ替えます。


https://github.com/takosatou/TakoDrum/assets/52827488/20e47aa9-2cdc-4470-aa3f-20d8b55de052


# パターンのコピーと消去

RECORDボタンを押しながらバンクを切り替えると、切り替える前のパターンと音色を、切り替えたバンクにコピーします。ルーパーモードで、現在のパターンをコピーして新しいパターンを作るときに便利です。

ERASEボタンを押しながらバンクを切り替えると、切り替えたバンクのパターンを消去します。音色はそのままです。

コピーや消去の単位は、A/AB/Bスイッチによるバリエーションに従います。

# パターンの保存
STOP/PLAYスイッチをPLAYからSTOPに切り替えると、入力したパターンを内蔵SDカードに保存します。
保存できるパターンのセットは1組のみで、新しいもので上書きされます。

# 音色設定モード

SOUND SETスイッチを右にすると、音色設定モードになります。音色設定モードでは演奏が停止します。

タッチパッドをタップして設定対象を決めます。アクセント用の右下のタッチパッドには音色を設定できません。

RECORDボタンかERASEボタンを押すと音色リストを順番に変えていきます。
RECORDボタンが番号が小さくなり、ERASEボタンが大きくなります。
リストの端まで達するともう一方の端に移ります。



https://github.com/takosatou/TakoDrum/assets/52827488/db90fb47-f50e-40a4-b867-e29ad5822104


## 音色リスト
引用元： https://cdn.shopify.com/s/files/1/0520/3669/8292/files/TB_midi_instruments.pdf?v=1618565552
```
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
```

# ハードウェア

## Touch Board

Bare Conductive によるArduino互換ボードで、CPU：ATmega32U4と、タッチセンサーIC：MPR121MP3と、デコーダ兼MIDI音源チップ：VS1053bを搭載しています。
（https://www.bareconductive.com/collections/touch-board）

VS1053bは、MP3デコーダーとMIDI音源を切り替えて使用できます。今回はMIDI音源を使うので、ボード上のジャンパー2箇所をハンダを盛って接続します。

なお、MP3デコーダーとして使うと、同時再生可能な音声は1つになってしまいます。

![inner](https://github.com/takosatou/TakoDrum/assets/52827488/93454a28-dbd9-43fb-ac22-13e0a1897f26)

## アナログ入力

可変抵抗器やスイッチ類は、下記のようにTouch Boardのアナログ入力端子に接続します。基準電圧としてAREF端子の出力を用います。
Touch BoardのA/D変換器は10bit (=最大値1023) です。抵抗器に誤差があるのでA/D変換器の値にはばらつきが生じます。

### A0、A1、A2

VOLUME、TEMPO、ACCENT用に、それぞれ10kΩBの可変抵抗器を繋げます。

![image](https://github.com/takosatou/TakoDrum/assets/52827488/d09198ca-7228-426d-8059-5665c4f914ea)

### A3

6接点ロータリースイッチを繋げます。端子間には同じ値の抵抗器を入れて、6段階に分圧します。今回は4.7kΩを使いました。

| バンク | 電圧 | A/D 変換の値 |
| --- | ---: | ---: |
| 1 | 0V | 0 |
| 2 | 1V | 204 |
| 3 | 2V | 209 |
| 4 | 3V | 613 |
| 5 | 4V | 818 |
| 6 | 5V | 1023 |

![image](https://github.com/takosatou/TakoDrum/assets/52827488/98c4332b-c110-48b1-9826-b8073a8c018e)


### A4

以下のトグルスイッチを、R-2Rラダー型D/A変換回路を通じて接続します。

- METRONOME
- SOUND SET
- 16/12
- STOP/PLAY

R-2Rラダー型D/A変換回路では、R＝5kΩとしています。

![image](https://github.com/takosatou/TakoDrum/assets/52827488/08d195b7-e5fe-4286-9154-fd78e6171686)

### A5

RECORD、ERASEボタンを、R-2Rラダー型D/A変換回路を通じて接続します。

R-2Rラダー型D/A変換回路では、R＝50kΩとしています。ボタンは10kΩ抵抗器を使ってプルダウンしています。

![image](https://github.com/takosatou/TakoDrum/assets/52827488/fb94f8bc-b3cb-434a-a531-e3a0a6793f9a)


### Pin 12 (A11)

A/AB/Bの3Pトグルスイッチを接続します。センター端子を20kΩでGNDに接地し、A端子に10Ω、B端子に33kΩでそれぞれ5Vに繋げると、下記のように分圧できます。

| スイッチ位置 | 電圧 | A/D変換の値 |
| --- | ---: | ---: |
| A  | 5✖️20/30=3.33V | 682  |
| AB | 0V | 0 |
| B  | 5✖️20/53=1.89V | 386 |

![image](https://github.com/takosatou/TakoDrum/assets/52827488/7ddd5f0b-13f2-486b-ac7e-274436b8235c)

### Reset

これはアナログ入力ではありませんが、プッシュスイッチを介して、GNDに繋げます。

![image](https://github.com/takosatou/TakoDrum/assets/52827488/cc7d08a1-8e4c-4aa5-b012-1404128f9277)

## タッチパッド入力

E0〜E11までの端子から、リード線を引き出して、リン青銅板の電極に繋げます。
なお、Touch Boardの電極には直接触れず、薄い紙を挟んでも操作可能です。楽器の音色に対応したガイドの紙を上に重ねても良いでしょう。

## 出力

### Analog Out L

ボードの音声出力Lチャンネルを、標準ジャックを介してアンプに繋げます。

アンプは、秋月のPAM8012使用2ワットD級アンプモジュールを使いました。
https://akizukidenshi.com/catalog/g/gK-08217/
![image](https://github.com/takosatou/TakoDrum/assets/52827488/b001f5dc-a3b0-44e7-b90a-09af82128b01)

### Pin13 LED
10kΩ抵抗を通じてLEDに繋げます。

![image](https://github.com/takosatou/TakoDrum/assets/52827488/d7d60776-0a8d-462b-9863-a0984a2ea067)


## 電源
標準的な電源プラグと、エフェクター用に使われるセンターアースの電源プラグの両方に対応するため、ダイオードブリッジを介して入力します。

9Vから5Vに変換するためにDCDCコンバータを使います。今回はワンパッケージになった三端子DC/DCレギュレーター:ROHM BP5293-50 (https://akizukidenshi.com/catalog/g/gM-11188/) を使いました。

![image](https://github.com/takosatou/TakoDrum/assets/52827488/bd8d2885-91b9-410e-b99b-9a8e15df8114)


# SDカードの保存フォーマット

ファイル名：`takodrum.dat`

フォーマット
- 以下の形式を12個分 (16ステップ用に6個 + 12ステップ用に6個)
  - 11バイト：タッチパッドに対応する音色番号
  - 2バイト✖️32：ABパターン


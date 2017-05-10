SpoilerAL 6.1 修正パッチ


■概要

  時代に育まれたソースコードを解析職人が見直し、
  BBS住民が磨き上げた日本の味をご賞味下さい。
  アセンブラの渋みとC言語の甘さが溶け合い、
  豊かな香りと芳醇なコクを引き立てた至高の一品です。

  極論に至っては「お腹へった」という事です。


■インストール

  SpoilerAL 6.1 の SpoilerAL.exe が格納されているディレクトリに
  winmm.dll をコピーしてください。

  インストール時の設定は不要です。
  アンインストールする場合は winmm.dll を削除してください。


■ツールメニューの追加方法

  ツールメニューは追加しなくても基本動作には影響しません。

  ツールメニューを追加するには付属の menu フォルダの中身を
  SpoilerAL.exe のディレクトリにコピーしてください。

  初期のToolsフォルダには何もありません。
  プロセス選択ツールや吉里吉里解析ツールをダウンロードして
  Toolsフォルダの中に解凍してください。

  menu.ini は上記のツールを登録済みですが必要に応じて編集してください。
  ブラウザのURLを登録する事も出来ます。


■システム要件

  Microsoft Windows 2000 か、それ以降のオペレーティングシステム
  Intel Pentium III か、それ以降のＣＰＵ


■winmm.dll をロードしてない場合

  SpoilerAL.exe の実行中に winmm.dll をゴミ箱に入れてみます。
  そのまま削除できる場合はロードされていません。
  以下の手順でお願いします。

  １．バイナリエディタ（HEXエディタ）を用意
  ２．SpoilerAL.exe をバイナリエディタで開く
  ３．0024D232 のアドレスに WINMM.DLL という文字列があるので
      W(57) を _(5F) に変更して上書き
  ４．winmm.dll のファイル名を _inmm.dll に変更
  ５．SpoilerAL.exe のディレクトリに SpoilerAL.ini というファイルを作成
  ６．SpoilerAL.ini をメモ帳で開き以下の内容を記述
--------------------
[MainModule]
CRC32=0xE6ACE881
--------------------
  ７．文字コードを指定できる場合は ANSI または SHIFT-JIS を指定して保存


■修正および追加内容

  2016.06.22
  ・アドレスネーミングのUNICODE (UTF-16LE) 対応
  2016.06.24
  ・演算子の優先順位を修正 (6.2)
  2016.06.25
  ・アドレスネーミングの浮動小数点数の表示
  2016.06.30
  ・ビットシフトおよびローテート対応 (6.2、ドキュメントの差分を添付)
  2016.07.02
  ・括弧が無効化されるバグの修正 (6.2)
  2016.07.06
  ・値を固定した場合にクラッシュするバグの修正 (6.2)
  2016.07.11
  ・ダイアログ補正から全角文字や半角カナを検索できないバグを修正
  2016.07.14
  ・下位互換の確保されない内容をファイルヘッダに応じて動作するように変更
  2016.07.21
  ・ビット毎の論理否定(~)と排他的論理和(^)の書式および演算結果が等価だったため、
    ビット毎の論理否定(~)の書式をC言語の仕様に合わせ変更 (6.2)
  ・負の値を表現する場合にゼロから減算する必要があったので修正 (6.2)
  2016.07.25
  ・単項演算子が連続する場合の評価順序を修正 (6.2)
  ・アドレスコーディングを置換するタグを追加 (6.2)
  2016.07.26
  ・MName::nul と書く事でエントリーモジュールの取得に対応するようにした
  2016.08.10
  ・トグル項目のバイト列で減算できないバグを修正
  2016.08.27
  ・64bitの演算機能を追加 (6.2)
  2016.08.29
  ・単項演算子の論理否定(!)を追加 (6.2)
  ・前置および後置のインクリメント(++)とデクリメント(--)を追加 (6.2)
  2016.09.03
  ・左辺代入(=)を追加 (6.2、ドキュメントの差分を修正)
  ・複合代入演算子(+= -= *= /= %= &= |= ^= <<= >>=)を追加 (6.2)
  2016.09.04
  ・間接演算子(*)を追加 (6.2)
  2016.09.06
  ・メモリを確保する機能を追加 (6.2)
  2016.09.08
  ・アドレスネーミングにfep_numを追加し入出力変換属性に対応
  2016.09.10
  ・MName::user32.dll::MessageBoxA と書く事でAPIの取得に対応 (6.2)
  2016.09.13
  ・行末に円記号(\)を付加する事でコードの途中の改行に対応
  2016.09.17
  ・BitScanForward:: BitScanReverse:: を追加 (6.2)
  2016.10.01
  ・バイト列の反復命令に $Rel を追加 (6.2)
  2016.10.07
  ・ダイアログ補正のバイト列がリトルエンディアンにならないバグを修正
  2016.11.01
  ・符号付整数の演算子(idiv, imod, lt, gt, le, ge, I1toI4, I2toI4, I4toI8)を追加 (6.2)
  2016.11.06
  ・[repeat] の書式を拡張し符号の有無に対応
  ・ワードリピートの繰り返し回数で負の値を無視するように変更
  ・SSRファイルに [! Fn,書式 !] を追加
  ・string項目のUNICODE (UTF-16LE) 対応
  ・ワードリピートが変？だったので修正 (6.2)
  2016.11.08
  ・条件演算子(三項演算子)を追加 (6.2)
  ・セグメントアドレスの取得に対応 (6.2)
  2016.11.27
  ・[error_skip] を追加
  2016.11.28
  ・strlen:: wcslen:: を追加 (6.2)
  2017.01.06
  ・アドレスネーミングに_fmt, fep_list, fep_free_listを追加
  2017.02.05
  ・[repeat] に「$Idx」という名前の変数を追加 (6.2)
    現在のループへアクセスするには「$Idx」を使用します
    階層でアクセスするには「$Idx1, $Idx2, $Idx3, ...」を使用します
    上位のループへアクセスするには「$FwdIdx1, $FwdIdx2, $FwdIdx3, ...」を使用します
  2017.02.07
  ・<# #> で動的に展開された変数の書式化に対応
  2017.02.08
  ・リスト項目、一括リスト項目、ビットリスト項目で入出力変換属性が使えるように書式を拡張
  2017.03.12
  ・「$Addr」という名前の変数で項目へアクセスした後のアドレスを扱えるように変更 (6.2)
  ・ガイドへ出力するログを高速化
  ・while ループの実装 (6.2)
  2017.03.15
  ・左辺代入および複合代入を拡張し、間接演算子やポインタ変換演算子を用いたアドレスに書き込めるように変更 (6.2)
  ・変数名の先頭に「$」が有っても無くても動作するように変更 (6.2)
  2017.03.23
  ・memmoveを追加 (6.2)
  2017.04.19
  ・if, else, break, continue を追加 (6.2)
  2017.04.20
  ・for, do-while を追加 (6.2)
  2017.04.26
  ・printf, dprintf を追加 (6.2)
  2017.05.10
  ・return を追加 (6.2)


■SSGファイルの追加書式

  ・SSGファイルヘッダ

    「SSG for SpoilerAL ver 6.2」と記述すると以下のように動作を変更します。
    ・演算子の優先順位の修正
    ・シフト演算の追加
    ・括弧バグの修正
    ・ビット毎の論理否定
    ・負の値の表現
    ・アドレスコーディングを置換するタグの追加
    ・64bitの演算機能を追加
    ・単項演算子の論理否定(!)を追加
    ・前置および後置のインクリメント(++)とデクリメント(--)を追加
    ・左辺代入(=)を追加
    ・複合代入演算子(+= -= *= /= %= &= |= ^= <<= >>=)を追加
    ・間接演算子(*)を追加
    ・メモリを確保する機能を追加
    ・APIの取得に対応
    ・BitScanForward:: BitScanReverse:: を追加
    ・バイト列の反復命令に $Rel を追加
    ・符号付整数の演算子(idiv, imod, lt, gt, le, ge, I1toI4, I2toI4, I4toI8)を追加
    ・条件演算子(三項演算子)を追加
    ・セグメントアドレスの取得に対応
    ・strlen:: wcslen:: を追加
    ・[repeat] に「$Idx」という名前の変数を追加
    ・while ループの実装
    ・左辺代入および複合代入を拡張し、間接演算子やポインタ変換演算子を用いたアドレスに書き込めるように変更
    ・変数名の先頭に「$」が有っても無くても動作するように変更
    ・memmoveを追加
    ・if, else, break, continue を追加
    ・for, do-while を追加
    ・printf, dprintf を追加
    ・return を追加


  ・UNICODE

    UNICODEの場合は [末尾に付加するバイト列] を [unicode] と記述します。

    ANSI:
      _mem, アドレス, 最大サイズ(NULLを除くバイト数), 末尾に付加するバイト列, エラー時の代替え文字列

    UNICODE:
      _mem, アドレス, 最大サイズ(NULLを除くバイト数), unicode, エラー時の代替え文字列

    使用例:
      [subject]_mem, 0x480000, 0x10, unicode, ぬるぽ:dir

    null とか 00 とか記述する場所を unicode に置き換える事で対応します。


  ・ビットシフトおよびローテート

    添付の HowToSSG\0A\index.htm を参照してください。


■サポートとかライセンスとか

  サポートはありません。
  無償で提供される技術資料みたいなものです。

  著作権を放棄します。
  砂場に書いた落書きのような扱いです。
  問題が起きても全ては自己責任でお願いします。



= スコアリングモデリング構築
本章では、スコアリングモデルの作り方を理解しながら、
実際にサンプルデータを使ってモデリングまで実装していきましょう。
第2章「AI開発の進め方」に則って進めていきます。

== 分析環境
 * OS: macOS Mojave
 * バージョン: 10.14.3
 * 言語: Python3.X
 * 使用ライブラリ:

== ワインをスコアリングしてみよう
信用スコアを算出するためには、個人のクレジットカード支払履歴やECでの購買データが必要です。
今回は一般に公開されている有名なワインのデータセットを用いて予測モデルを作っていきましょう。

== 目的設定
「ワインが美味しいかどうかを@<kw>{予測}する」

=== 分析手法
スコアリングモデルの目的は、「YES or NO」を明確にすることです。
「お金を返すヒト／返さない人」を自動的に判断することによって業務を効率化したいからです。

そして、予測するものは、@<kw>{YESあるいはNOのいずれかの結果が得られる「確率」}です。
なぜ、確率を予測するのかというと、採点したユーザーを複数に分類（差別化／格付け）することが可能になるからです。

ワインが美味しいかどうかを予測する場合も、「美味しい or 美味しくない」を明確する点で同様です。

今回、私たちは「確率という連続した値」で美味しさを表現します。
美味しさというのは主観的で属人性が高いですから、その美味しさを構成する要素は何かを説明する必要があります。

つまり、私たちは@<kw>{美味しさを何かしらの要素で説明する回帰分析(分析手法)}を行い、
その結果から、@<kw>{予測スコアリングモデル}を構築します。

=== アルゴリズム選定
さて、アルゴリズムはどうしましょうか。最短経路の分析と最速のデプロイを実現するために、
今回は、@<kw>{ロジスティック回帰}と呼ばれる機械学習アルゴリズムを採用します。
※もちろん、機械学習アルゴリズム選定は予測精度の高さをもとに選定するべきなので、あとで方針転換する可能性は高いです。

目的を達成するモデルの大枠と分析手法、アルゴリズムの目星がつきました。

=== 仮説を立てる（主観）
実際にデータを見る前に、しっかりと仮説を立てていきましょう。
まずは、美味しいワインってどのようなものなのかイメージして簡単な言葉にしてみましょう。

 * 甘い(甘味)ワインは美味しい
 * すっぱい(酸味)ワインは美味しい
 * 果実味があるワインは美味しい
 * 重さのあるワインは美味しい

=== データに直す（主観→客観）
先ほど立てた仮説を具体的に・定量的に表現してみます。

  * 糖分が◯グラムであるワインは美味しい
  * pH7以下のワインは酸性なので美味しい
  * 果実味って具体的に何なのかわからない・・・
  * 密度が高いワインは美味しい？

それでは、実際使用するデータを見てみましょう。
== データセット
2008年10月に公開された「ポルトガル北部のワイン品質データセット」を使います。
データセットは@<href>{http://archive.ics.uci.edu/ml/machine-learning-databases/wine-quality/}から無料でダウンロードすることができます。

=== 前提
今回のワインの予測はあくまでもポルトガルの赤ワインの話であって、世界中のワインの話ではありません。
つまり、@<kw>{現状のデータでは美味しいポルトガル産赤ワインの予測モデルを作ることしかできない}のです。

もし、「世界中のワインの美味しさを予測するモデル」を作りたい場合は、世界とは何かを定量的に定義しなければなりませんし、
その後に、どのようにデータを集めていくのかを検討する必要があります。

== 探索的データ解析
基本的には統計学でいうところの記述統計に当たる作業です。
予測をする前に、保有データを集計して現状を把握することが目的です。

 1. 列の意味を知る
 2. データ全体の大きさを調べる
 3. データ個数を数え上げる
 4. 欠損値を調べる
 5. 記述統計量を算出する
 6. 全体感をグラフ（可視化）で理解する

1~4が@<kw>{データの品質}を把握する作業です。
データが汚いという場合は、1~4の中に曖昧な部分や不足箇所が多いということです。

5~6が@<kw>{データの特徴}を把握する作業です。
ここで記述統計量というものを活用します。簡単言ってしまえば、
データの特徴というのは@<kw>{どれくらい偏っているか}を確かめると理解すれば問題ないです。

そして、この偏りというのは人間にとって数値だけだとイメージしづらいのです。
ですから、グラフによる可視化作業を行うことがあります。

それでは、1~6までのステップを最短経路で走りきってみましょう！

=== 役割ごとにディレクトリを作成する
まずは、analyticsというディレクトリを作成してください。
つぎに、3つのディレクトリを作成します。分析作業は、/workspace でおこないます。
 1. dataset（データセット格納場所）
 2. model（モデル格納場所）
 3. workspace（分析場所）

//image[analytics01][ディレクトリ構造]

=== jupyterを起動する
ターミナルでjupyter notebookを起動しましょう。
//cmd{
  //ディレクトリ「analytics」上で
  $ jupyter notebook
//}

=== データセットを読み込む
//list[read_csv01][データの読込][python]{
  # 分析に必要なライブラリをインポート
  import pandas as pd
  import numpy as np

  # データセットを読み込む
  df = pd.read_csv("../dataset/winequality-red.csv")
  df.head()
//}

//image[analytics02][先頭行を表示(失敗)]

列ごとに表示されていないので、読み込み方を工夫する必要があります。
;（セミコロン）で列に分割することができそうなので、sep=';'を追記して列に分割します。

//list[read_csv02][;による列分割][python]{
  # sep=';'を追記して、再度データを読み込む
  df = pd.read_csv("../dataset/winequality-red.csv", sep=";")
  df.head()
//}

//image[analytics03][先頭行を表示(成功)]

無事、データを読み込むことができました。

=== 列名の意味を調べる
基本的にデータの列名（項目名）は@<kw>{半角英数字}です。
意味がわからない列名があれば、きちんと意味を調べましょう。
意味を理解しないまま、データ分析してはいけません。

この作業は、自分の頭の中のビジネス理解とデータ理解を突合させる作業です。
その列にはどんな意味や背景があるのか、その列に蓄積される値は正しい数値が入りそうか、欠損値が出そうか
しっかり確認しましょう。

=== スプレッドシートの翻訳関数を使おう
項目名が英語の場合、私は@<kw>{googleスプレッドシートの翻訳関数}を使うことオススメします。

最短・最速の分析作業を実現するためには、スプレッドシートやExcelは最強のツールです。
すべてをpythonで解決させるする必要はないのです。

jupyter notebookから、列名をコピーしてスプレッドシートに貼り付けます。

//image[analytics04][列名を貼り付ける]

すると、「自動的に列に分割」と表示されるのでクリックしてください。
基本的に空白やカンマ、セミコロンがあれば、綺麗に分割することができます。

//image[analytics05][列に分割された]

つぎに、翻訳したい列のとなりに新しい列を挿入してください。
そこに、翻訳関数を書きます。

//list[read_csv03][翻訳関数][google]{
  =GOOGLETRANSLATE(翻訳したい列,"翻訳元の言語", "翻訳したい言語")
  =GOOGLETRANSLATE(A1,"en", "ja")
//}

//image[analytics06][翻訳関数を挿入]

//image[analytics07][日本誤訳が表示された]

=== 集計（shape＆count）

まず、データ量を把握します。
モデリングが可能なデータ量なのかどうかを確認する意味があります。

//list[read_csv04][shape][python]{
  df.shape
  (1599, 12)
//}

1599行、12列のデータテーブルであることがわかりました。
つづいて、各列（各項目）のデータ数をカウントしましょう。

//list[read_csv05][count][python]{
  df.count()
  fixed acidity           1599
  volatile acidity        1599
  citric acid             1599
  residual sugar          1599
  chlorides               1599
  free sulfur dioxide     1599
  total sulfur dioxide    1599
  density                 1599
  pH                      1599
  sulphates               1599
  alcohol                 1599
  quality                 1599
  dtype: int64
//}

各列1599個の値がはいっていることがわかりました。
今回は欠損値がなさそうです。

=== 記述統計量（describe）
各列の平均や標準偏差、最大値、最小値、最頻値などの記述統計量を算出します。
算出自体は1行書くだけなので、なぜこの1行を書いて数値を見る必要があるのかについて
簡単に解説します。

==== 期待値・平均値
データは比較してこそ意味があります。比較するためには基準が必要です。
そのために、期待値や平均値を算出します。

3月と4月のデータを比較するといった時系列データがない場合は、
データを比較するという行為は基本的に期待値(平均値)の大小を比較するものです。

例えば、

==== 分散

==== 標準偏差


//list[read_csv06][describe][python]{
  df.describe()
//}

 //image[analytics09][記述統計量]

=== データ型(dtype)
データの種類によって、集計方法は異なります。
データの種類は2種類に大別されます。@<kw>{数値であるか、そうでないか}です。

 * 数値: 数値データ（気温、身長、金額）
 * 数値ではない: カテゴリデータ（性別、天気、ステータス）

ちなみに、数値データをカテゴリデータに変換できます。
下記のようなイメージです。

//table[envvars][重要な環境変数]{
数値データ（アルコール度数）    カテゴリデータ（醸造酒分類）
-------------------------------------------------------------
5%                         ビール
7%                         マッコリ
12%                        シャンパン
14%                        ワイン
15%                        日本酒
//}

==== @<kw>{度数分布}
同じものがいくつ存在するのかを把握します。
数値データの場合は、一旦カテゴリデータに変換して集計することが多いです。


=== カテゴリデータの必要性
結果をどれくらいの粒度で把握したいのかによって、カテゴリデータの量が変わってきます。全体をひとまとまりで扱うのであれば不要だし、何かの基準を設けてデータを分けたいなら、そのカテゴリ分類が必要です。
ちなみに、全体のを一括りで分析するのは、大事な視点を見逃してしまう恐れがあるから、層別化して分析することは大切です。



=== 可視化
回帰分析は、相関関係がベースになっています。なのでまずは総関係について説明します。

よくあるのがグラフの使い方とグラフの変数の選び方がわからないというケース。
だから、高いBIツールなどを使いこなすことができていない。
そこを今回は回帰に必要なところに絞って解説します。





== 中間テーブル作成
=== データクレンジングって一体なんなん
データ整形を端的にいうなら下のルールをまとめろってこと。
 * 1行に1レコードしかいれるな
 * 1列に1フィールドしかいれるな
 * 先頭行に列名（データラベル）を絶対に入れろ
 * 空白の列・行を絶対に作るな
 * 余計な情報（スペース、自由入力テキスト）をいれるな

== データ分析／機械学習

=== 要因分析の限界
また、影響度の高い要素がAだとしてもAを変えることが困難である場合は、その要因分析は施策実行性が低い。
動き出せないなら、そのデータはゴミ。それくらい思い切ってアウトプットを意識していく。
ビジネスやサービスにAIをつかう＝限界がある。それをわかった上で扱う必要がある。そのために、できるかぎりデータを正しく整理して収集・保有し、データを正しく扱う。

データは真実を語る面と恣意的解釈が混在している

== モデリング
=== 精度検証
=== エクスポート



== 回帰分析とは
回帰分析とはひところで言うと、複数の項目をまとめて使った分析手法の１つです。統計学ではいろいろな分析手法があります。何かを予測したいときに、それに影響を与える要因は１つだけとは限りません。

そういう場合に、複数の項目を使って予測を行うときに@<kw>{回帰分析（Regression Analysis）}という統計手法を活用します。ちなみに、イメージのデータテーブルは下記のようなものになります。

【ここに図がはいる】

このように複数の変数（項目のことを変数と呼ぶ）と多くのデータ行数を対象分析を行う手法を、@<kw>{多変量解析（nultivariate Analysis）}と呼びます。回帰分析は多変量解析の１つです。

== データ準備
 * 何を知りたいのか、分析の目的を明確にする
 * 分析の目的を明確にすると、分析不法が決まる
 * 分析手法が決まると、必要なデータの型が決まる
 * データの型に合うように、分析用データを集める




== より見込みの高い顧客を「1人1人」予測 - 施策効果を最大化 -

顧客に紐づく様々なデータ（顧客属性、購買に
関する指標など）を用いて、データマイニング
のアプローチを行うことによって、「個人」単
位での反応率を定量的に求めることができま
す。
=== 多変量解析
複数の対象（サンプル）について 複数の変数（カテゴ
リー）による測定値に対し、これらのデータを独立に
扱わずに、各変数間の関連性を調べる統計手法です。

== 「データマイニング」による、最適化
顧客にひもづく様々なデータ（顧客属性、購買に関する指標
など）を用いて、データマイニング（BA）でのアプローチを
行うことによって、「個人」単位での反応率を定量的に求め
ることができます。
「セグメント」単位での送付対象抽出と比較して、より精度
の高いターゲティングが可能になります。
データマイニングでは、様々なデータ項目（多変量）を一度
に扱うことができるので、各データ項目がDMへの反応率に
どれくらい影響するのかを定量的に可視化できます。過去実
績を用いた分析モデルの適用によって、送付対象1人1人の反
応率を事前に予測することが可能になります。

== スコアリングの実行
個人単位での予測は、データマイニングのスコアリング（ロ
ジスティック回帰分析）を行うことで実現できます。
顧客に紐づく様々なデータ（顧客属性、購買に関する指標な
ど）を用いたスコアリングによって、個人単位での反応率を
定量的に求めることができます。
「セグメント」単位での送付対象抽出と比較して、より精度
の高いターゲティングが可能になります。
スコアリングでは、様々なデータ項目（多変量）を一度に扱
うことができるので、各データ項目がDMへの反応率にどれ
くらい影響するのかを定量的に可視化できます。過去実績を
用いた分析モデルの適用によって、送付対象1人1人の反応率
を事前に予測することが可能になります




==== 正の相関と負の相関
正の相関：一方が多い（少ない）ときに、もう一方も多い（少ない）
負の相関：一方が多い（少ない）ときに、もう一方は少ない（多い）


なんでグラフにする必要があるの？→データの特徴を把握しやすいから

【相関関係の図】
散布図の作り方
 * 予測したい変数や注目したい変数を縦軸に配置する
 * 原因と結果という関係にある場合、原因となる変数は横軸。結果となる変数を縦軸にする
 * 時系列で考えたときは、先に発生する変数を横軸に、あとから発生する変数が縦軸

相関関係と相関係数
 * 相関係数は常に-1から1の間に収まる
 * 相関係数が0から1に近ければ近いほど、強い正の相関がある
 * 相関係数が0から-1に近ければ近いほど、強い負の相関がある

【相関の強さ判断テーブル表がはいります】
0.8　強い相関
0.6　相関がある
0.4 弱い相関
0.2未満　ほとんど相関がない



== モデルをつくろう！
どんなモデルを作りたいのかを整理してみましょう
【ここに図がはいる】

予測と要因分析をおこないたい！
「売り場面積が2,050平方メートルで、最寄り駅からの所要時間が21分、駐車場の収容台数が66台の場所に立地している店舗の場合、売上予測は1億1000万円です。
ほかの条件が変わらない場合、駐車場の収容台数を66台から80台にすると、売上は400万円増の1億1,400万円が見込めます」といえるロジック・説明を用意したい。

【写真にとって文章とプロセスを挿入する】

=== 最適なモデルを作るためのステップ
 * まずはすべての説明変数をつかって回帰分析を実行する
 * 影響度がもっと小さい説明変数を取り除いて、再び回帰分析を実行する
 * 説明変数が一個になるまで繰り返す
 * すべての回帰分析実行結果から、「補正R2」の欄、自由度調整済決定係数を比較して、もっとも大きな値を示した実行結果から作る回帰式を最適な回帰式とする

=== 前提条件
 * 絶対に当たる予測モデルは存在しない
 * 業界によって必ず（または精度良く）予測に使える分析手法（統計手法）というのは存在しない
 * 業界によって必ず予測に使える説明変数というのは存在しない

だから、一旦モデルを構築したあとに、分析手法や説明変数の見直しの機会を設けること。
そして、いきなり将来の予測ぉせずに、正解がわかっている現在手元にあるデータを基に。仮の予測を行い、精度よく予測ができることがわかった上で、将来の予測に入る。
（これが機械学習モデルを用いた教師あり学習予測モデル構築プロセス）



===[column]
@<kw>{精度の高いDeepLearningよりも説明性の高い決定木？}
絶対に当たる予測モデルが創れないことを知ると、人間は「結果ではなく根拠を知りたがる」傾向にあります。
なので、最終的にDeepLarningで予測モデルを構築するとしても、説明性の高い分析を事前に行うほうがいいかもしれません。

説明性とは
 * どのようなデータを用意したのか
 * 予測をするための数式はどのように求めたのか
 * その予測の数式によって、予測の値はいくらになるのか




===[/column]


=== 今回は教師あり学習

=== モデルを吐き出す

第４章へ

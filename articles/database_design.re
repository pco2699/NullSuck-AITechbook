= スコアリングモデリング構築
本章では、スコアリングモデルの作り方を理解しながら、
実際にサンプルデータを使ってモデリングまで実装していきましょう。
第2章「AI開発の進め方」に則って進めていきます。

==== 分析環境
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

==== データセット
2008年10月に公開された「ポルトガル北部のワイン品質データセット」を使います。
データセットは@<href>{http://archive.ics.uci.edu/ml/machine-learning-databases/wine-quality/}から無料でダウンロードすることができます。

==== 前提
今回のワインの予測はあくまでもポルトガルの赤ワインの話であって、世界中のワインの話ではありません。
つまり、@<kw>{現状のデータでは美味しいポルトガル産赤ワインの予測モデルを作ることしかできない}のです。

もし、「世界中のワインの美味しさを予測するモデル」を作りたい場合は、世界とは何かを定量的に定義しなければなりませんし、
その後に、どのようにデータを集めていくのかを検討する必要があります。

====[column] データ収集と分析手法の関係
今回は、サンプルデータをそのまま利用してモデリングします。
しかし、実際は探索的データ解析をする以前の段階でデータ不足によって
つまづくことがとても多いです。

その場合は、下記のステップでデータを収集すると、
データ整形の工数を大幅に減らしながら探索的データ解析に進むことができます。

  1. 何を知りたいのか、分析の目的を明確にする
  2. 分析の目的を明確にすると、分析手法が決まる
  3. 分析手法が決まると、必要なデータ型が決まる
  4. データの型に合うように、DBを設計する
  5. 目的のためのデータを集める

====[/column]

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

そして、この偏りは数値だけだとイメージすることが難しいです。
そのために、グラフによる可視化作業を行います。

最短経路の分析には、可視化するものとしないものを明確に分ける判断が重要です。
数値を見てわかることは@<kw>{テーブル表}で十分です。
テーブル表でも、数値の意味を理解することが難しいときに@<kw>{グラフによる可視化}をおこないます。

それでは、1~6までのステップを最短経路で走りきってみましょう！

==== 役割ごとにディレクトリを作成する
まずは、analyticsというディレクトリを作成してください。
つぎに、3つのディレクトリを作成します。分析作業は、/workspace でおこないます。
 1. dataset（データセット格納場所）
 2. model（モデル格納場所）
 3. workspace（分析場所）

//image[analytics01][ディレクトリ構造]

==== jupyterを起動する
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

==== 列名の意味を調べる
基本的にデータの列名（項目名）は@<kw>{半角英数字}です。
意味がわからない列名があれば、きちんと意味を調べましょう。
意味を理解しないまま、データ分析してはいけません。

この作業は、自分の頭の中のビジネス理解とデータ理解を突合させる作業です。
その列にはどんな意味や背景があるのか、その列に蓄積される値は正しい数値が入りそうか、欠損値が出そうか
しっかり確認しましょう。

==== スプレッドシートの翻訳関数を使おう
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

//list[read_csv06][describe][python]{
  df.describe()
//}

//image[analytics09][describe]

==== 期待値・平均値
データは比較してこそ意味があります。比較するためには基準が必要です。
そのために、期待値や平均値を算出します。

3月と4月のデータを比較するといった時系列データがない場合は、
データを比較するという行為は基本的に期待値(平均値)の大小を比較するものです。

例えば、あなたはいつも500円のランチを食べているとしましょう。500円が平均ランチ代です。
もし、あなたがいつも1,000円のランチを食べている友人とご飯にいったとすると、
友人は「いつもどおり」と感じるけれど、あなたは「高い」と思うのです。
それはつまり、@<kw>{平均と比較して高いと感じている}ということなのです。

==== 分散・標準偏差
偏差とは@<kw>{データの値から平均値を引いた値}のことです。
でもこれだけでは、その値がどれだけ凄いのか（普通or珍しい）がわかりません。
つまり、標準偏差はある値と平均の差が@<kw>{どれだけ凄いのか}を把握するために使います。
そして、分散はばらつきの大きさを表現しています。

第3章でも書きましたが、モデルを作るためのデータセットは
@<kw>{総合的であれば、あるほどいい}のです。それは、偏りが少ないということを意味します。

=== データ型(dtype)
データの種類によって、集計方法は異なります。
データの種類は2種類に大別されます。@<kw>{数値であるか、そうでないか}です。

 * 数値: 数値データ（気温、身長、金額）
 * 数値ではない: カテゴリデータ（性別、天気、ステータス）

機械学習モデルを作るときには、データ型の把握は特に重要です。
データ型によってプログラミングによる前処理のプロセスが変わるからです。

//list[read_csv07][dtypes][python]{
 df.dtypes
 fixed acidity           float64
 volatile acidity        float64
 citric acid             float64
 residual sugar          float64
 chlorides               float64
 free sulfur dioxide     float64
 total sulfur dioxide    float64
 density                 float64
 pH                      float64
 sulphates               float64
 alcohol                 float64
 quality                   int64
 dtype: object
//}


=== 可視化

//list[read_csv08][hist][python]{
  # 可視化ライブラリのインポート
  import matplotlib.pyplot as plt
  import seaborn as sns

  # matplotlibによる可視化
  plt.hist(df['quality'], bins=10 )

//}
==== 度数分布
同じものがいくつ存在するのかを把握します。
数値データの場合は、一旦カテゴリデータに変換して集計することが多いです。

今回、美味しさは列名「quality」= 品質と定義します。
その分布を見てみましょう。

//image[analytics10][qualityのヒストグラム]

== 中間テーブル作成
本書では、中間テーブルを@<kw>{分析やモデリングで必要な列と行だけを抽出したテーブル}と定義します。

=== 中間テーブル鬼の5原則
整形されたデータというのは@<kw>{隙間がなく、規則性がある}状態のデータです。
モデリングの学習データとなるデータテーブルは、
最終的に下記の5つのルールを必ず満たしている状態にしましょう。

 * 1行に1レコードしかいれるな！
 * 1列に1フィールドしかいれるな！
 * 先頭行に列名（データラベル）を絶対に入れろ！
 * 空白の列・行を絶対に作るな！
 * 余計な情報（スペース、自由入力テキスト）をいれるな！

=== カテゴリデータの必要性
予測結果をどれくらいの粒度で把握したいのかによって、カテゴリデータの量が変わってきます。
全体をひとまとまりとして扱うのであれば不要です。

しかし、もし何かしらの基準を設けてデータを分ける可能性があるなら、
このステップで、そのカテゴリ分類を新たに作る必要があります。

ちなみに、全体のを一括りで分析するのは大事な視点を見逃してしまう可能性が高いです。
ユニークなAIを作りたい場合は、ユニークな切り口のカテゴリを作ることをオススメします。

そのカテゴリデータをもとに層別化して分析すると、新しい発見があるかもしれません。

=== 数値データとカテゴリデータ
新しいカテゴリを作りたい場合は、数値データをカテゴリデータに変換します。
下記のようなイメージです。

//table[envvars][重要な環境変数]{
数値データ（アルコール度数）	カテゴリデータ（醸造酒分類）
-------------------------------------------------------------
5%	ビール
7%	マッコリ
12%	シャンパン
14%	ワイン
15%	日本酒
//}

== データ分析／機械学習
ロジスティック回帰によるアルゴリズムを作成する前に、
簡単にロジスティック回帰について解説します。

=== 回帰分析
回帰分析とは、複数の項目をまとめて使った分析手法の1つです。
何かを予測したいときに、それに影響を与える要因は1つだけとは限りません。

家賃で例えるとイメージしやすいです。
家賃は、部屋の広さ、築年数、駅からの距離・・・いろいろな要因が絡み合って決まっています。

このように、複数の項目を使って予測を行いたいときに@<kw>{回帰予測モデル}を作ります。
逆に、1つの現象を複数の項目を使って説明したいときに@<kw>{回帰分析（Regression Analysis）}という分析手法を活用します。

イメージのデータテーブルは下記のようなものになります。

【ここに図がはいる】

このように複数の変数（項目のことを変数と呼ぶ）と多くのデータ行数を対象分析を行う手法を、
@<kw>{多変量解析（nultivariate Analysis）}と呼びます。
回帰分析は多変量解析の1つです。

=== 相関関係
回帰分析は相関関係がベースになっている分析手法です。
ですから、次に相関関係について説明します。

==== 正の相関と負の相関
相関関係があるといった場合、表現方法は2つしかありません。

//table[soukan][相関関係の表現方法]{
相関関係	解釈
-------------------------------------------------------------
正の相関	一方が多い（少ない）ときに、もう一方も多い（少ない）
負の相関	一方が多い（少ない）ときに、もう一方は少ない（多い）
//}

相関関係があるときは@<kw>{「AはBと正(or負)の相関がある」} といったように
具体的な比較対象と相関の表現方法を必ず伝えましょう。

=== 散布図
回帰分析と相関関係について理解することができました。
それでは、予測したい変数がどんな変数と総関係があるのかを調べてみましょう。
そんなときは@<kw>{散布図}を使って可視化する方法が有効です。

==== 散布図の作り方
一言で言うと、@<kw>{知りたい結果を『縦軸』に。}です。
 1. 【基本ルール】予測したい変数や注目したい変数を縦軸にする
 2. 【原因と結果】原因となる変数は横軸。結果となる変数を縦軸にする
 3. 【時系列】先に発生する変数を横軸に、あとから発生する変数を縦軸にする

【散布図の図】

=== 相関係数
相関関係の有無がわかったら、どれくらい相関関係があるのか。
その大きさを数値でくわしく見てみます。そこで登場するのが@<kw>{相関係数}です。
相関係数は、AとBがどれくらい相関しているかを表す数値です

==== 相関係数の見方
一言で言うと、@<kw>{正なら正。負ならば負。}です。
  1. 相関係数は常に-1から1の間に収まる
  2. 相関係数が0から1に近ければ近いほど、強い正の相関がある
  3. 相関係数が0から-1に近ければ近いほど、強い負の相関がある

【相関の強さ判断テーブル表がはいります】

==== 相関の強さを比較する
一言で言うと、@<kw>{0.2ずつ4段階で強さが変わる。}です。

//table[soukan_tsuyosa][相関係数の強さ]{
相関係数	解釈
-------------------------------------------------------------
0.8以上	強い総関係がある
0.6	相関関係がある
0.4	弱い相関関係がある
0.2未満	ほとんど相関がない
//}

====[column] 要因がわかるだけでは、世の中は何も変わらない
データ分析をするときに、AとBの相関関係を発見することはとても面白いです。
@<kw>{おむつとビール}の話がわかりやすい事例です。

もし、あなたが飲料メーカで働いているとします。
スーパーのおむつコーナーにビールを一緒に置けば、そのお店におけるビールの売上がUPしそうです。
しかし、スーパーの店員さんはおむつコーナーの隣にビールを置くことを簡単に許してくれそうでしょうか。

つまり、データ分析において新しい相関関係を発見すること自体は価値があったとしても、
実際に施策に落とし込むことが難しい場合は、@<kw>{ビジネスとして価値が低い}のです。

施策に落とし込めないのであれば、どんなに膨大なデータであっても意味がない。
それくらい思い切って@<kw>{アウトプットを意識していくことが、最短経路のデータ分析}を実現します。
====[/column]

== モデリング
=== 最適なモデルを作るためのステップ
 * まずはすべての説明変数をつかって回帰分析を実行する
 * 影響度がもっと小さい説明変数を取り除いて、再び回帰分析を実行する
 * 説明変数が一個になるまで繰り返す
 * すべての回帰分析実行結果から、「補正R2」の欄、自由度調整済決定係数を比較して、もっとも大きな値を示した実行結果から作る回帰式を最適な回帰式とする

==== 前提条件
 * 絶対に当たる予測モデルは存在しない
 * 業界によって必ず（または精度良く）予測に使える分析手法（統計手法）というのは存在しない
 * 業界によって必ず予測に使える説明変数というのは存在しない

だから、一旦モデルを構築したあとに、分析手法や説明変数の見直しの機会を設けること。
そして、いきなり将来の予測ぉせずに、正解がわかっている現在手元にあるデータを基に。仮の予測を行い、精度よく予測ができることがわかった上で、将来の予測に入る。
（これが機械学習モデルを用いた教師あり学習予測モデル構築プロセス）

=== 精度検証

=== 出力
システム化するために、Pickleを使ってモデルを出力します。
PickleはPython標準ライブラリに含まれているモジュールです。

//list[modeling][pickleを使ってモデルをdumpする][python]{
  # pickleのインポート
  import pickle
  # pickleでモデルをdumpする
  filename = 'nullsuckAi_model.sav'
  pickle.dump(model, open(filename, 'wb'))
//}

== 画面設計
=== 初期デザイン
==== 見本の入手
==== 手書きで書き起こし
=== adobeXD
==== 使い方
==== コンポーネントの有効活用
==== 開発者用出力

====[column] 予測精度と説明性のジレンマ
AIブームが落ち着いて、みんなが思っていることは@<kw>{AIをには限界がある}ということではないでしょうか。
おそらくそれは正しいです。その理由は何でしょう。ぜひ、少し考えてみてください。

AIが完全でない理由は1つではありません。AIのモデルに使われた@<kw>{学習データの品質が悪い}こと原因かもしれません。
あるいは、採用した@<kw>{アルゴリズムが不適切}である場合もあるでしょう。

私はもう一つ理由があることに気づきました。
ヒトは絶対に当たる予測モデルが作れないことを知ると、予測結果ではなく@<kw>{説明できる根拠}を知りたがるから、
ビジネス実装することが難しいのです。

例えば、DeepLarningを使って予測精度の高いモデルを構築しても、
その予測モデルを求めていた当事者が@<kw>{予測の根拠}を知りたがるのです。
しかし、機械学習アルゴリズムにおいて@<kw>{予測精度の高さと説明性の高さは絶対的な正の相関関係があるわけではありません。}

もし、あなたが@<kw>{的中率100%で噂の占い師に「彼が、あなたを幸せにしてくれる運命の人です。結婚しなさい。」}と言われても、
簡単に結婚を決断できない理由と同じなのかもしれません。
====[/column]

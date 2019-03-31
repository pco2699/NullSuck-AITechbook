= スコアリングモデリング構築
本章では、スコアリングモデルの作り方を理解しながら、
実際にサンプルデータを使ってモデリングまで実装していきましょう。
第2章「AI開発の進め方」に則って進めていきます。

==== 分析環境
 * OS: macOS Mojave
 * バージョン: 10.14.3
 * 言語: Python3.6
 * 分析ツール: Jupyter Notebook
 * 使用ライブラリ: NumPy, Pandas, Matplotlib, Seaborn, Scikit-learn

== ワインをスコアリングしてみよう
信用スコアを算出するためには、個人のクレジットカード支払履歴やECでの購買データが必要です。
今回は一般に公開されている有名なワインのデータセットを用いて予測モデルを作っていきましょう。

== 目的設定
「ワインが美味しいかどうか（二値分類）を@<kw>{予測}する」

=== 分析手法
スコアリングモデルの目的は、「YES or NO」を明確にすることです。
例えば、「お金を返す人／返さない人」を自動的に判断することによって業務を効率化したいからです。

そして、予測結果は、@<kw>{YESあるいはNOのいずれかの結果が得られる「確率」}です。
なぜ、確率を出力するのかというと、採点したユーザーを確率ごとにグループに分けることによって、
差別化・格付けをすることが可能になるからです。ビジネスにおいても施策に落とし込みやすくなります。

ワインが美味しいかどうかを予測する場合も、「美味しい or 美味しくない」を明確する点で同様です。
そして今回、私たちは「確率という連続した値」で美味しさを表現します。

美味しさというのは主観的で属人性が高いですから、その美味しさを構成する要素は何かを説明する必要があります。

つまり、私たちは@<kw>{美味しさを何かしらの要素で説明する回帰分析(分析手法)}を行い、
その結果から、@<kw>{予測スコアリングモデル}を構築します。

=== アルゴリズム選定
最短経路の分析と最速のデプロイを実現するために、
複数のアルゴリズムを試して予測精度を比較しません。

コードを1行変えるだけで、採用するアルゴリズムを簡単に変えることができます。
余裕がある方は試してみてください。（もっといい予測モデルが作れるかも？）

今回は、@<kw>{ロジスティック回帰}と呼ばれる機械学習アルゴリズムを採用します。

目的を達成するためのモデル全体像とそれを実現するための
分析手法、アルゴリズムを検討することができました。

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
今回の予測は、あくまでもポルトガル北部の赤ワインのデータをもとに予測します。
そうです、世界中のワインのデータを使って予測モデルを作るわけではありません。

つまり、これから作る『ワインの美味しさを判別するAI（モデル）』は、
@<kw>{美味しいポルトガル産赤ワインのデータのみ}を判断材料としているのです。

もし、「世界中のワインの美味しさを予測するモデル」を作りたい場合は、世界とは何かを定量的に定義しなければなりません。
その上で、どのようにデータを集めていくのかを検討する必要があります。

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
予測する前に、保有データを集計して現状を把握することが目的です。
未来への予測は現状の理解から始まります。

 1. 【意味の理解】列の意味を知る
 2. 【全体の把握】データ全体の大きさを調べる
 3. 【個数の把握】データ個数を数え上げる
 4. 【品質の把握】欠損値を調べる
 5. 【基準の発見】記述統計量を算出する
 6. 【偏りの発見】グラフ（可視化）で理解する

1~4が@<kw>{データの品質}を把握する作業です。
データが汚いという場合は、1~4の中に曖昧な部分や不足箇所が多いということです。

5~6が@<kw>{データの特徴}を把握する作業です。
ここで記述統計量というものを活用します。
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
意味を理解しないまま、データを分析してはいけません。

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

//table[label][列名の意味]{
属性（単位）  英語表記
------------------------------
ワインの味（グレード）  quality; from 0 (very bad) to 10 (excellent)
酒石酸濃度（g/dm3）  fixed acidity (g(tartaric acid)/dm3)
酢酸濃度（g/dm3）  volatile acidity (g(acetic acid)/dm3)
クエン酸濃度（g/dm3）  citric acid (g/dm3)
残留糖分濃度（g/dm3）  residual sugar (g/dm3)
塩化ナトリウム濃度（g/dm3）  chlorides (g(sodium chloride)/dm3)
遊離亜硫酸濃度（mg/dm3）  free sulfur dioxide (mg/dm3)
総亜硫酸濃度（mg/dm3）  total sulfur dioxide (mg/dm3)
密度（g/dm3）  density (g/dm3)
pH  pH
硫酸カリウム濃度（g/dm3）  sulphates (g(potassium sulphate)/dm3)
アルコール度数（% vol.）  alcohol (% vol.)
//}

11項目の化学測定指標と、ワインの評価スコアが存在することがわかりました。

今回は英語表記の列名を効率よく理解するために、googleスプレッドシートを利用しました。
データ分析を行うときは、@<kw>{データ理解はExcel, モデリングはPython}で行うというイメージでいいと考えています。
すべてをPythoでやらなくてもいいことを頭に入れておきましょう。
（Pythonが苦手な人は、モデリング前の作業は極力Excelで挑戦してみるといいですよ！）

=== 集計（shape＆count）

まず、データ量を把握します。
モデリングが可能なデータ量なのかどうかを確認する意味があります。
また、データ量が大きすぎて計算ができない場合はデータを分割することを検討します。

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
今回、欠損値はなさそうです。
（実際のデータは欠損値がたくさんあり、欠損の原因もその数だけあります。）

=== 記述統計量（describe）
各列の平均や標準偏差、最大値、最小値、最頻値などの記述統計量を算出します。
算出自体はコードを1行書くだけなので、なぜこの1行を書いて数値を見る必要があるのかについて
簡単に解説します。

//list[read_csv06][describe][python]{
  df.describe()
//}

//image[analytics09][describe]

==== 期待値・平均値
データは比較してこそ意味があります。比較するためには基準が必要です。
そのために、期待値や平均値を算出します。

3月と4月のデータを比較するといった時系列データがない場合は、
データを比較するという行為は基本的に期待値(平均値)との大小を比較するものです。

例えば、あなたはいつも500円のランチを食べているとしましょう。500円が平均ランチ代です。
もし、あなたがいつも1,000円のランチを食べている友人とご飯にいったとすると、
友人は「いつもどおり」と感じるけれど、あなたは「高い」と思うのです。
それはつまり、@<kw>{平均と比較して高いと感じている}ということなのです。

==== 分散・標準偏差
偏差とは@<kw>{データの値から平均値を引いた値}のことです。

期待値・平均値は、その値がどれだけ凄いのか（普通or珍しい）を一概に判断することはできません。
そこで活躍するのが@<kw>{（標準）偏差}です。
標準偏差はある値と平均の差が@<kw>{どれだけ凄いのか}を把握するために使います。
そして、分散はばらつきの大きさを表現しています。

第3章でも書きましたが、モデルを作るためのデータセットは
@<kw>{総合的であれば、あるほどいい}のです。それは、偏りが少ないということを意味します。

=== データ型(dtypes)
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

今回、美味しさは列名「quality」= ワインの品質の値と定義します。
その分布を見てみましょう。

//image[analytics10][qualityのヒストグラム]

ワインの品質は1~10の10段階で設定されていますが、
データセットには3から8までの評価しか入っていないことがわかります。

== 機械学習用データセット作成
本書では、機械学習用データセットとは@<kw>{分析やモデリングで必要な列と行だけを抽出したデータテーブル}と定義します。

=== データセット鬼の5原則
整形されたデータというのは@<kw>{隙間がなく、規則性がある}状態のデータです。
モデリングの学習データとなるデータテーブルは、
最終的に下記の5つの原則を必ず満たしている状態にしましょう。

 * 1行に1レコードしかいれるな！
 * 1列に1フィールドしかいれるな！
 * 先頭行に列名（データラベル）を絶対に入れろ！
 * 空白の列・行を絶対に作るな！
 * 余計な情報（スペース、自由入力テキスト）をいれるな！

=== カテゴリデータの必要性
予測結果をどれくらいの粒度で把握したいのかによって、
必要なカテゴリデータ量が変わってきます。
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

実際の予測スコアリングモデルでは、カテゴリデータをダミー変数（0,1で表現）
にすることによって、定性的な情報を定量的に判断する工夫をしています。

==== 美味しいワインを判断する関数を作ろう
//list[delicious][quality7以上は美味しいワインだと定義する][python]{
  # 関数を作ります。
def delicious_score(x):
    # もしqualityが7以上であれば美味しい(1)
    if x >= 7:
        return 1
    # 7以上でないなれば、美味しくない(0)
    else:
        return 0

# applyを使って、新しい列用のデータを作りましょう。
df['delicious'] = df['quality'].apply(delicious_score)
df.head()
//}

//image[analytics20][新しい列が追加されたデータセット]

=== 正規化
今回はワインのスコアをレーダーチャートによってアプリ上で可視化します。
レーダーチャートは、複数の評価軸がある場合に適した可視化方法です。
レーダーチャート作成のポイントは@<kw>{数値の単位を揃えること}です。

そのために、説明変数として用いるデータを@<kw>{正規化,Normalization}することによって、
どの評価軸も@<kw>{最小値0, 最大値1}の数値に変換します。

機械学習をおこなうためのデータセットは、数値の単位がバラバラであったり、
数値の大きさが極端に異なっていることは避ける必要があります。

ロジスティック回帰では、データのスケールを変換する方法として、
@<kw>{標準化,Standardization}という方法を使うケースが多い印象です。

また、適切な予測モデルを構築する（過学習を防ぐ）ために、
@<kw>{正則化,Regularization}（正規化ではない）という方法もあります。

//list[Normalization][正規化][python]{
  # データ前処理に必要なライブラリ
  from sklearn import preprocessing

  # インスタンスの作成
  mmscaler = preprocessing.MinMaxScaler()

  # 説明変数の最大・最小を計算
  mmscaler.fit(df)
  df_mms = pd.DataFrame(mmscaler.transform(df))

  # 統計量を見ることで、最小0最大1に変換されているか確認
  df_mms.describe()

//}

//image[analytics21][正規化されたデータセット]

//list[Normalization02][列名変換][python]{
  # スケール変換によって変わってしまった列名を直す
  df = df_mms.rename(columns={
      0: 'fixed acidity',
      1: 'volatile acidity',
      2: 'citric acid',
      3: 'residual sugar',
      4: 'chlorides',
      5: 'free sulfur dioxide',
      6: 'total sulfur dioxide',
      7: 'density',
      8: 'pH',
      9: 'sulphates',
      10: 'alcohol',
      11: 'quality',
      12: 'delicious'
  })
  # 先頭行を表示し、正しく変換されているか確認
  df.head()
//}

//image[analytics22][列名修正後のデータセット]

ここまでで、@<kw>{隙間がなく、規則性がある}機械学習用のデータセットを作ることができました。
機械学習を使ったデータ分析のステップに進んでいきましょう。

== データ分析
ロジスティック回帰によるアルゴリズムを作成する前に、
簡単にロジスティック回帰について解説します。

=== ロジスティック回帰
==== シグモイド関数によるロジスティック回帰
0or1という2つのクラスに分類し、それぞれの確率を出力します。

例:
 * 美味しいワイン(1)、美味しくないワイン(0)
 * 信用できる人(1)、信用できない人(0)

今回は、1=美味しいワインとすることによって、
入力されたワインが美味しいワインである確率を予測します。

==== 多クラスロジスティック回帰
確率によって表現されるので、基本的な機能は同じですが、
2つ以上のクラスに分類することができます。

例:
 * 神の雫のようなワイン(1)、普通のワイン(2)、まずいワイン(3)
 * 信用レベル100(1)、信用レベル80(2)、信用レベル60(3)

世の中の問題を「分ける（分類）」することによって解決したいとき
YESorNO問題であることは少ないです。
AorBorCのように、3つ以上に分けることによって解決する問題のほうが多いのです。

そのような問題には、多クラスロジスティック回帰を活用します。

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

==== 散布図マトリクスを表示する

//list[Scatter plot][散布図マトリクス][python]{
  grr = pd.plotting.scatter_matrix(
    iris_dataframe, c=iris_dataset['target'],
    figsize=(15, 15),
    marker='o', hist_kwds={'bins':20},
    s=60, alpha=.8, cmap=mglearn.cm3
  )
//}

しかし、最短経路でデータ分析をする場合は
美味しいワインと美味しくないワインの違いを、それぞれの平均値から比較しましょう。

//list[groupby][0と1の統計量の違いを平均値で比較][python]{
  df.groupby('delicious').mean()
//}

//image[analytics23][groupbyを使って0と1の違いを把握]


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
±0.8以上	強い総関係がある
±0.6	相関関係がある
±0.4	弱い相関関係がある
±]0.2未満	ほとんど相関がない
//}

==== ヒートマップで相関性を把握する
簡単にcorr()メソッドとヒートマップで相関係数を見てみましょう。

//list[corr][corr()で相関係数を表示][python]{
  # 可視化ライブラリ
  import seaborn as sns
  # 相関係数を算出
  df_corr = df.corr()
  # 具体的な数値が見たければ、print()で表示
  print(df_corr)
  # ヒートマップを表示
  sns.heatmap(df_corr, vmax=1, vmin=-1, center=0)
//}

//image[analytics24][今回はヒートマップで全体感のみ把握]

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
お待たせしました！AIの根幹であるモデリングの時間です。
まず、モデリングの進め方と前提条件を整理します。

=== 最適なモデルを作るためのステップ
 * まずはすべての説明変数をつかって回帰分析を実行する
 * 影響度がもっと小さい説明変数を取り除いて、再び回帰分析を実行する
 * 説明変数が一個になるまで繰り返す
 * すべての回帰分析実行結果から、「補正R2」の欄、自由度調整済決定係数を比較して、もっとも大きな値を示した実行結果から作る回帰式を最適な回帰式とする

==== 前提条件
 * 絶対に当たる予測モデルは存在しない
 * 必ず予測に使える説明変数は存在しない
 * 何にでも使える分析手法は存在しない

一旦モデルを構築したあとに、分析手法や説明変数の見直しの機会を設けることは大切です。
そして、いきなり未来予測をせずに、正解がわかっている現在手元にあるデータを基に仮の予測を行い、
精度よく予測ができることがわかった上で、未来予測に挑戦します。これは@<kw>{教師あり学習による予測モデル}の構築プロセスです。

=== データ分割
説明変数（X）と目的変数（Y）にデータを分割します。
今回は「quality（ワインの品質）」と「delicious（美味しさ）」を除く説明変数を使って、
「delicious（美味しさ）」を予測します。

//list[modeling01][データ分割][python]{
  # 目的変数
  Y = df2["delicious"]
  # 説明変数
  X = df2.drop(["quality", "delicious"], axis=1)
//}

=== 機械学習
機械学習のオープンソースライブラリである@<kw>{scikit-learn,サイキット・ラーン}を使います。
交差検証によってモデルの汎化性能（未知のデータに対応できる能力）を高めます。

//quote{
  交差検証（交差確認）（こうさけんしょう、英: Cross-validation）とは、統計学において標本データを分割し、その一部をまず解析して、残る部分でその解析のテストを行い、解析自身の妥当性の検証・確認に当てる手法を指す。
  交差検証 - Wikipedia
  https://ja.wikipedia.org/wiki/交差検証
//}

//list[modeling02][機械学習][python]{
  # ロジスティック回帰
  from sklearn.linear_model import LogisticRegression
  # 交差検証
  from sklearn.cross_validation import train_test_split

  # インスタンス作成
  log_model = LogisticRegression()
  # 学習用データと検証用データにデータを分割。テストデータは全体の25%とします。
  X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.25,random_state=3)
  # 学習用データを使って学習
  log_model.fit(X_train, Y_train)
//}

//image[analytics25][学習モデル]


pythonによるモデリングはscikit-learnを使えば、基本的には5行程度で完了します。
まずは、採用したいアルゴリズムや必要に応じてライブラリをインポートします。
モデリング自体は、モデルのインスタンスを作成し、データ分割を行い、学習を実行する3ステップです。

=== 精度検証
テストデータを使って学習したモデルの精度を検証しましょう。

//list[modeling03][精度検証][python]{
  # 精度検証
  from sklearn import metrics
  # テストデータで予測
  Y_pred = log_model.predict(X_test)
  # 精度をprint()で表示
  print(metrics.accuracy_score(Y_test,Y_pred))
//}

//image[analytics26][予測精度]

=== 出力
最後に構築したモデルをPythonの標準ライブラリである@<kw>{picke,ピックル}
モジュールを使ってモデルをdumpします。

//list[modeling][pickleを使ってモデルをdumpする][python]{
  # pickleのインポート
  import pickle
  # モデルのファイル名を指定
  filename = 'nullsuckAi_01model.sav'
  # モデルをdumpする
  pickle.dump(log_model, open(filename, 'wb'))
//}

dumpされたモデルファイルが下記の通り保存されていれば完了です。

//image[analytics27][dumpされたファイルはworkspaceにある]



== 画面設計
Webアプリケーション開発に進む前に、画面設計に挑戦してみましょう。
=== 設計仕様
今回のAIアプリに使用するモデルは@<kw>{教師あり学習モデル}です。
ユーザーに新しいデータを入力してもらい、そのデータをモデルに格納して予測結果を算出します。
その予測モデルをAIアプリ化すると図のような設計仕様になります。

今回、最小の画面枚数は@<kw>{データ入力画面と予測結果表示画面の2つ}です。

//image[ui11][アプリのAI化]

=== 最小の技術で最速のUI設計
最短経路のUI設計のポイントは3つです。
 1. 見本を手に入れろ！
 2. 取り入れたい要素を見極めろ！
 3. AdobeXDのデザインキットをを使おう！

非デザイナーである私は基本的に好きなアプリのUIをそのまま参考にします。
すべてを再現することは現実的ではないので、取り入れたい要素を絞り込みます。
最後に、AdobeXDというデザインツールのデザインキットを使うことによって、
最短経路でのUI設計を実現します。

//image[ui10][画面設計のステップ]

==== 見本の入手
第2章で芝麻信用について詳しく書いてきたので、芝麻信用のUIを見本にしましょう。
ヘッダーがあり、メインメニューにスコアをレーダーチャートによって可視化しています。
==== 要素の絞り込み
芝麻信用のUIから3要素を取り入れることにしました。固定ヘッダーとスコア表示、
最後に項目の詳細が書いてある項目カードです。
==== キラー画面作成
今回のアプリで必要な画面数は2つです。画面を作成する際は、
ユーザーに最もインパクトを残したい画面から作るようにしています。
予測結果をユーザーにぬるさくで表示させたいので、予測結果表示画面から作ります。
==== デザインキットの有効活用
AdobeXDは無償版が提供されています。さらに、無料のデザインキットが提供されているため個人開発に最適です。
AdobeXDはチュートリアルが豊富であるため、本書では詳しい解説は割愛します。
//image[ui12][AdobeXDによる画面設計]
できあがったUI設計は共有リンクを作成してチームに展開することも可能です。
ぜひ使ってみてください。

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

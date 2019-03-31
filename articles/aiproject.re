={aiproject} AIアプリ開発の進め方
本章では、AI開発の進め方を7つのステップで解説します。
読み終わった後には、きっとあなたが作りたいAIが明確になると思います。

== 目的から考えよう

AIは目的ではなく、実現手段です。@<kw>{「目的から考える」}ことの大切さは、AIアプリ開発以外においても共通だと思います。
しかし、データを活用するAIアプリは一般的なWebアプリよりも、最初の目的設定が特に重要です。
なぜかというと、AIアプリ開発は、そのモデル構築に必要なデータを集めるところから作業が始まるからです。

データを集め、分析する段階から@<kw>{「実現したいこと（目的）があって、その実現手段として機械学習（技術）が存在する」}
という因果を忘れてはいけません。目的がなければ、どんなAIアプリ開発も必ず迷子になります。

夢を感じる最新技術はすぐにでも使ってみたいものです。
しかし、それが課題を解決するための最適な技術なのかをしっかり検討する必要があります。

AIは基本的に@<kw>{開発にも運用にもコストがかかります。}
機械学習を用いてデータ分析をするためには大量のデータが必要です。
そのために、データを保管できる十分なデータベースを準備する必要もあります。
さらに、構築したモデルの精度は初めからよい数値が出ることはまれです。
モデル構築に使用したアルゴリズムは、継続的に改善する必要があるということです。

だからこそ、開発中に手戻りが起こらないように、データ分析の作業が短縮できるように、
目的に対して一貫性のある無駄のない設計を行う必要があるのです。

== 目的変数に必要なデータセットを作ろう
AIアプリ開発で必要なのは、何よりもまず@<kw>{目的（目的変数）に必要なデータセット}です。
日本の大企業がどれだけビッグデータを持っていても、データ活用がうまく進まないのはいくつかの理由があります。
その理由のひとつは、蓄積されたデータが目的のために集められたデータではなく、有効活用できないからです。

@<kw>{ただデータがあるだけでは、あなたの作りたいAIアプリを開発ことはできません。}これは紛れもない事実です。

== AI開発のステップ
AIを作るためには1つずつステップを踏んでいく必要があります。AI開発に王道なしです。
私はデータサイエンティストとして、クライアントがどのステップの段階にいるのかを見極めることを大切にしています。
図のようなピラミッド構造でAIプロジェクトを進めています。

//image[aistep][AI開発の7ステップ]

以降、各ステップを解説していきます。

=== 目的設定
目的設定とは、どんなAIを作りたいのか？つまり、どんなモデルを構築するのかを明確にすることです。
目的は複数あることが多いので、@<kw>{1つの目的に、1つのモデル。という形式で整理し、1モデルごとに仮説を設定}します。
一般に、目的をモデルに落とし込む作業は機械学習の知識がなければ難しいでしょう。
ですから、このステップはデータサイエンティストに求められている大切な役割のひとつだと考えています。

==== 目的をモデルに落とし込んでみよう
目的をモデルに落とし込む方法は簡単です。
目的をどうするかを4つの選択肢から選んで整理するだけです。

 1. 回帰：データを元に目的を説明する
 2. 分類：データを元に目的をAとBに分ける
 3. 推定：データを元に目的に与えている影響が何かを知る
 4. 予測：新しいデータから目的に関する未来の結果を得る

たとえば、「私の理想の結婚相手と出会う（見極める）こと」が目的だとします。
このとき大切なことは「私の理想の結婚相手を@<kw>{どのように判断}したいのか」を1つに絞ってみることです。

「私の理想の結婚相手を@<kw>{予測}するモデル」「私の理想の結婚相手を@<kw>{分類}するモデル」は似て非なるモデルです。
分析のアプローチ方法が異なるのです。

下記のような表で目的をモデルに変換してみましょう。
なんとなく、実現したい目的が具体的になってきた気がしませんか？

//table[mokuteki_model][目的のモデル化]{
目的	を	◯◯	したい	モデル名
-------------------------------------------------------------
信頼できる人	を	分類	したい	信頼別分類モデル
信頼できる人	を	確率予測	したい	信頼度確率予測モデル
信頼できる人の特徴	を	説明	したい	信頼要素の回帰分析
//}

==== 仮説を立て、データを当てはめてみよう
仮説とは、何らかの現象や法則性を説明する判断内容・条件のことを指します。
具体的に考えてみましょう。

あなたが結婚相手に求める条件は何でしょうか。2つ以上条件を考えてみてください。

外見？収入？性格？いろいろあるでしょう。
きっとみなさんは2つ以上簡単に条件をあげることができたのではないでしょうか。
私はこれが目的に対して仮説を立てる力の根源だと思っています。

次に、これを少しだけ客観的に想像してみます。
「理想の結婚相手には年収1,000万以上が条件である私」は、
マジョリティなのかマイノリティなのかを想像してみましょう。

仮説は自分の価値観や体験を、みんなはどうなのだろうか？と想像して
少しだけ一般化して整理したものだと考えています。
この条件を知るために、どのようなデータが必要なのかを図のシートで整理してみましょう。

//image[kasetsu_data][1つの目的に対して、仮説をデータに置き換える]

目的に対して必要なデータは何なのか？を整理できました。
いかがでしょうか？あなたが作りたいモデルを作るために、十分なデータはそろっていますか？

難しく考えてしまうと、目的に必要なデータが何なのかわからなくなってしまいます。
@<kw>{目的に対して仮説を立てることができたなら、あなたはもう立派なデータサイエンティスト}です。

特にAI化というのは、@<kw>{今まで人がやっていた判断基準を数値化・分類化する}ことが大きなテーマです。
その属人的な業務がいくつの要素で構成されており、それぞれの要素は目的に対してどのくらい影響しているか？
という仮説を立て、プロジェクトを進めていきます。

理想の結婚相手の条件を挙げることができたあなたは、もうすでにデータサイエンス力があります。
引き続き、AI開発のステップを理解していきましょう。

=== データ収集
目的と仮説が明確になると、目的を実現するためのデータが不足しているかどうかを把握できます。
必要なデータが不足している場合は、インターネット上に公開されているデータを活用したり、あるいはデータ収集基盤を構築します。

もちろん企業の場合は、既存データを活用して取り組むケースが多いでしょう。
しかし、私は思い切って必要なデータを確実に蓄積できる@<kw>{データ収集するための仕組みやアプリケーション}を作ることをお勧めします。

理由は2つあります。まず、データ収集するタイミングを考えることは、属人的な業務のノウハウがどこに隠れているのかを深く理解することにつながるからです。
つぎに、既存データを目的に使えるようにデータを整形する作業は想像以上に時間がかかって効率が悪いからです。

データ収集方法を考える作業は@<kw>{データとビジネスの距離感を近付けるとても大切なプロセス}です。
既存データのテーブル定義書だけを見ていても、実現したい目的に対して本当の課題を見つけることは難しいです。
逆に、データ収集方法を考えずに、ビジネスのお話だけではAI開発は何も進みません。

=== 探索的データ解析
いよいよデータが集まってきたらやるべきことは、@<kw>{分析ではなく集計}です。
このとき大切なことは、@<kw>{列名・カラム名}の意味を把握することと、行（index）に格納される値の種類と意味をしっかりと理解することです。
「◯◯日から◯◯日の間に何がいくつあるのか」といった「数えて、集める」という基本を徹底しなければ、有効なAI開発は不可能です。

探索的データ解析はモデリングの精度を上げるためには非常に有効な分析プロセスです。
しかし、数字に対する肌感覚・データの現状を把握するために、この基本的な集計作業から取り組むことを徹底するべきです。

また、この作業だけでも十分にデータによる意思決定（判断）ができます。
本書では、無料で個人も使える「Googleデータポータル」というBIツールでのダッシュボード作成方法も付録で紹介しています。　

=== 機械学習用データセット作成
モデリングのもとになるデータセットを作成します。
@<kw>{分析やモデリングで必要な列と行だけを抽出したデータテーブル}だと理解していただければ十分です。

実務では、1ファイルごとにデータ整形をするだけでなく、中間テーブルなどを多用して作成していきます。
中間テーブルは関連テーブルとも呼ばれ、多対多のデータの関係を表すテーブルを意味しています。
データベースを設計したことがない人にとっては専門的で難しいと思うので、詳しい説明は割愛します。

最初のステップで取り組んだ目的設定と仮説が明確であれば、データセットを作ることは簡単です。
目的設定の段階で機械学習用データセットの列名（収集したいデータ項目）に目星がついているはずだからです。

私はここが@<kw>{データ分析を最短でデプロイするキーポイント}だと考えています。

大企業が保有しているデータを活用してAIを作るときは、どこにどんなデータが存在しているのかを把握するにも一苦労です。
特に、それぞれのデータテーブルがそれぞれの目的をもって存在しているため、中間テーブルを作ること自体が困難な場合も少なくありません。

実際、データ分析に至るまでのステップに時間がかかります。
ですから、今回のAIアプリ開発では、このステップから始められるようにオープンデータを活用してサンプルアプリを開発していきます。

//image[datakouzou][データセットを作るときのあるある]


=== データ分析（機械学習）
みなさんがイメージしているデータサイエンスの醍醐味である機械学習を使ったデータ分析を行います。
同時に、機械による自動化も進んでいます。また、参考書籍やインターネットに情報も豊富ですので、
本書では、手法の数学的背景には触れずに、分析のステップを詳しく説明します。

=== モデリング（機械学習）
データから学習済予測モデルを構築します。
こだわればこだわるほど吟味できる部分ですので、試行錯誤ボリューム満点です。
モデルの予測精度を向上させることは大切です。予測精度が低ければ、ただの人工無脳ですからね。

しかし、デプロイ後にも改善できるため、本書ではアルゴリズム選定にはあまり時間をかけずに進めます。
今回は、予測精度改善の優先順位を少し下げて、次のステップへ進みます。

=== AI化
使用した技術と実現したい目的によって、AI化の定義は変わります。
今回は予測モデルをAPI化することによって、既存のアプリケーション内のシステムに組み込みます。
予測モデルを組み込んだアプリケーションをAI化されたAIアプリと定義します。

本書では、予測モデルをシステムに組み込める形式で出力します。
それを使ってAPIを作成していきましょう。

本書では、最短でここまで走りきることを目標にしています。
モデルの予測精度向上はそのあとに個人的に取り組むように構成しています。
そのほうがAIアプリ開発を途中で諦めたりすることがなくなると思ったからです。

APIをWebアプリに組み込むことができれば、AIアプリの完成です。
データ分析をデプロイできました。

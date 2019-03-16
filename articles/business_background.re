= 目的から考えよう
//lead{
実際にAIアプリを作り始める前に、AIアプリを開発するに当たって事前に考えるべきことをご紹介します。
//}
== 機械学習プロジェクトの失敗あるある
 失敗する要因として、@<kw>{手段が目的になってしまって失敗する}ケースがとても多いです。

 「とにかくAI化してみたい！」という気持ちはとてもわかります。最新の技術はすぐにでも使ってみたいものです。しかし、それが課題を解決するための適切な技術なのかを検討する必要があります。
 なぜなら、機械学習を用いてデータを活用するためにはデータを保管する大量のデータベースが必要です。モデルを継続的に改善しつづける必要もあります。@<kw>{開発にも運用にもコストがかかる}のです。

 AI開発で必要なのは、何よりもまず@<kw>{目的(変数)に必要なデータセット}です。
 日本の大企業がどれだけビッグデータを持っていても、データ活用が上手く進まないのはいくつかの理由があります。その理由の1つは、「目的のために集められたデータセットではないため有効活用できないのです。

 わたし個人の意見ですが、昔のデータが使えないのならいち早く@<kw>{「データ収集基盤」を作る}ことをオススメしています。データクレンジングがデータの値や取得の背景を理解するにも時間がかかります。
 しかし、目的に対して効果が大きいデータは直近に取得したデータです。だからこそ、目的に必要なデータを適切な形で収集できる基盤を作るアプローチのほうが最短で目的を達成できると考えています。

 ここでは、@<kw>{①AIアプリは開発・運用コストが高いこと②目的に合ったデータセットが必要であること}の2点を理解し、そもそも機械学習は目的変数に必要な説明変数がなければ適切に活用できないことを改めて認識していただければと思います。@<kw>{ただデータがあるだけでは、あなたの作りたいAIを作ることはできません。}

== 目的に対して仮説を立てる
 だからこそ、データサイエンティストの役割は@<kw>{複数ある目的を1モデル1目的に整理し、それぞれ仮説を設定する}ことだと考えています。1つのモデルで複数の目的を達成できると過信しないことが大切です。

 例えば、「私の理想の結婚相を予測する」ことを目的とした予測モデルを作ってみるとしましょう。あなたが結婚相手に求める条件は何でしょうか。2つ以上条件を考えてみてください。

 （考えてから読み進めてください）外見？収入？性格？いろいろあるでしょう。きっとみなさんは2つ以上簡単に条件をあげることができたのではないでしょうか。私はこれが目的に対して仮説を立てる力だと信じています。

 難しく考えてしまうと、目的に必要なデータが何なのかわからなくなってしまいがちです。でもこれで十分ではありませんか？@<kw>{目的に対して仮説をたてることができたらなら、あなたはもう立派なデータサイエンティスト}です。この感覚を意識して、AI化までのステップを理解していきましょう。

== AI化までのステップを知ろう
いろいろな書籍で、AIプロジェクトの進め方のフローが紹介されています。私は図のようなピラミッド構造でAIプロジェクトを進めています。
//image[AiProject_step][AIステップピラミッド][scale=0.9]
 * 目的設計
 * データ収集基盤の構築
 * 集計／count
 * 中間テーブル作成
 * 機械学習を活用したデータ分析
 * モデル構築
 * システム組み込み（AI化）
== AIプロジェクトの進め方
 * 人の業務の型化
 * 業務のデータ化
 * データを分析
 * モデル構築
 * システム化
 * AIによる業務支援
== 新米データサイエンティストに必要な要素

===[column]
@<kw>{私が出会った企業内のAIプロジェクトがうまくいかない理由}
//image[shippai_AiProject][実際の企業内データ構造][scale=0.9]


===[/column]

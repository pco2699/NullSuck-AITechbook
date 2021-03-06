= スコアリングモデル概論
本章では、スコアリングアプリを開発する前にスコアリングモデルについて解説します。
モデルの歴史や特徴が分かると、実際にモデルを開発するときの楽しさも倍増するはずです。

== スコアリングモデルとは
スコアリングモデルは、統計手法を用いて@<kw>{企業や個人の信用力を採点する（スコアリング）}方法です。
たとえば、企業の決算書データを入力すると、その企業の信用力を示すスコアがすぐに出力されます。
そのスコア（点数）に合わせて、提供するサービスを変える（格付けする）ことによって、
業務効率化を実現することが主たる目的です。

== スコアリングモデルの歴史
=== FICOモデルの誕生
スコアリングモデルの歴史は古く、第二次世界大戦後の1950年に登場しました。
その後、1956年に米国のビル・フェリー氏とアール・アイザック氏が設立したフェア・アイザック社が個人の信用リスクをスコアリングするモデルを作りました。
このモデルは@<kw>{FICOモデル}と呼ばれています。そして、現在も米国のクレジットカード審査や住宅ローン審査に使われています。

1960年代には、割賦販売という分割払いで商品を購入する商習慣が生まれました。
すると、購入者の支払い能力を審査する業務が大量に増えるようになったのです。
その膨大な審査業務を効率化するために、スコアリングモデルは役に立ちました。

1970年代に米国でクレジットカードが普及し、一部の企業や銀行がスコアリングモデルを活用し始めます。
1990年代に入ってコンピュータの性能が向上し、スコアリングモデルは飛躍的に普及しました。

=== スコアリング融資という悪夢
2000年代にはいると、@<kw>{スコアリング融資}が活発化しました。
しかし、多くの金融機関でスコアリング融資による損失が発生するようになり、
スコアリングモデルは使えないというネガティブなイメージが定着し始めます。

スコアリングモデルという予測モデルに過度な期待をして判断を委ね過ぎたことによって、
大きな損失を被った歴史的事実は、現在のAIプロジェクト失敗ケースと同じようなものを感じます。

=== 芝麻信用の誕生と行動ログ収集による飛躍
中国における「個人信用調査元年」である2015年に@<kw>{芝麻信用}による信用サービスが開始されました。
芝麻信用のユニークな取り組みによって、スコアリングモデルが再び注目されるようになりました。

中国はインターネットの普及に伴いP2Pレンディングや消費者金融といった
個人向けの貸付サービスが急激に成長し、新たなブームになっていました。
これは1960年代の米国と同じような状況です。

米国をはじめとする先進諸国では、すでに成熟した信用調査システムが構築されている一方、
中国ではまだ不完全であり、信用調査モデルにおいては後手であったのです。

従来の信用調査モデルは、過去の融資記録などの相関性の高いデータから
得られることが前提とされていました。ほとんどのユーザーに融資実績がない中国では
そのモデルを活用するためのデータがなかったのです。

そこで、ユーザーのインターネット上での消費データや行動データを
既存金融機関の融資記録などに紐付けることによって、
個人の信用力を示す特徴を発見し、今までにないユーザーの信用スコアの価値を発見したのです。

== スコアリングモデルとデータ
データは@<kw>{解決したい課題、つまり実現したい目的と関係性がある}ことが大前提です。
そしてデータは総合的であればあるほどよいです。

たとえば、芝麻信用は幅広いデータを保有しています。
インターネット上の購買データはアリババ系列サイトから収集し、
学歴や納税データに至るまで業務提携先から収集しています。

単独のデータではユーザーの信用スコアを断定できませんが、
総合的なデータの蓄積によって、一人の人間としての信用スコアを予測可能なものにさせるのです。

また、データの正確性も重要です。
理由は単純で、データが正確でなければ客観的に公平にスコアリングできないからです。

==== 信用と強い相関のある5つのデータ
芝麻信用は、大量のデータを分析した結果、
個人の経済的な信用と強い相関性のあるデータを5つ割り出すことに成功しました。

信用履歴、行動傾向、契約履行能力、経歴特性、そして人間関係の5つです。
この中でもっとも相関性が低いのは人間関係です。
理由は、データからは友人の信用スコアと本人の信用スコアが直接的に相関性があることを証明することが難しいからです。

このように5つの項目は、それぞれ信用スコアに与える影響度が異なるので
信用スコアに占める比率もバラバラです。そして、常に調整・改善され続けています。

== スコアリングモデルは生活を変えるか
=== スコアリングモデルのメリット
スコアリングモデルのメリットは、2つあります。
まず、全員に同じサービスを提供しないことによって、業務効率を上げること。
なぜ、業務効率が上がるかというと対面作業と調査業務を省略できるからです。

次に、@<kw>{リスクの高いユーザーにも一定のサービスを提供できる}ことです。

たとえば、銀行における融資の場合、リスクの高い企業と低い企業がいたとします。
もし、どちらに融資しても金利が同じ（一律金利）だとすると、銀行はリスクの高い企業には融資しないのが普通です。

しかし、リスクの高い企業に融資すると金利も高く、低い企業に融資すると金利も低くなる（変動金利）場合、
リスクをとっても、金利の高い融資を行う銀行も出てきます。

これは、これまで融資してもらえなかった企業に対して機会を与えることができたと解釈できます。
@<kw>{スコアリングモデルによって、サービスの敷居を低くすることが可能}なのです。

=== スコアリングモデルのデメリット
スコアリングモデルのデメリットも、2つあります。
まず、@<kw>{全員に同じサービスを提供しないことによって、ユーザーが不平等を感じる}ことです。

たとえば、航空会社のステータスのように贅沢品と思われるようなサービスにおいて、
スコアリングモデルによるユーザーの差別化は効果を発揮します。
しかし、ユーザーに対してサービスを平等に一定品質で提供することに価値がある領域において、
スコアリングモデルを導入すると、ユーザーから反感を買ってしまう可能性があります。

つぎに、スコアリングのルールを悪用するユーザーが出現することです。
ユーザーが利便性の高い生活をするためにスコアハックをするということです。

信用スコアに振り回される人間たちをおもしろく描いているドラマがあります。
@<kw>{Netfrix,ネットフリックス}で『ブラックミラー』という人気ドラマが配信されています。
シーズン3の第1話「ランク社会」をぜひみなさんにご覧になっていただきたいです。

==== 信用スコア社会が危険視される理由
スコアリングする事業者側が自分たちのリスクを低くするために、
リスクの高いユーザーに対して著しく不便な状態にさせる可能性があるからです。

たとえば、スコアの低いユーザーは必要最低限のサービスでさえ、
利用することを許されなくなってしまうといったケースが上げられます。

ですから、スコアリングモデルを作る際は、スコアによってユーザーに提供するサービスが違えど
@<kw>{リスクの高いユーザーには最大の機会を、リスクの低いユーザーには最上の品質を与える}ことを
意識したビジネスやサービス設計が大切です。

== スコアリングの種類
=== 予測スコアリング
予測スコアリングは、@<kw>{未来のことを予測}するためのものです。
AIに使われているスコアリングはほぼこれを指します。

=== リードスコアリング
リードとは見込み顧客のことです。
リードスコアリングは、見込み顧客の@<kw>{現状を把握}するためのものです。

デモグラフィックデータと呼ばれる性別、年齢、職業、学歴、居住地など人工統計学的属性に点数をつけ（属性スコアリング）、
さらに、行動ひとつひとつにも細かく点数をつけます。（行動スコアリング）

点数の付け方は属人的ですので、このスコアリングモデルはAIと呼ぶにはふさわしくありません。

=== アンサンブルスコアリング
予測スコアリングとリードスコアリングのどちらの要素も活用する手法です。
アンサンブルスコアリングというのは正式名称ではなく、私が勝手に名付けました。
（ほかに正しい呼び方があれば、教えてください）

リードスコアリングによってユーザーに点数をつけ、
実際に目的にあったユーザーのデータのリードスコアを教師データとすることによって
予測スコアリングモデルを構築する方法です。

前述の予測スコアリングは、精緻な教師データが存在することが大前提です。
しかし、個人で開発する場合、大量の教師データを持っていることはほぼないでしょう。

それをリードスコアリングによって自分なりのデータを収集することによって打開します。
しかし、リードスコアリングは属人性が強いので、そのままで品質が低いです。
ですから、結果として得られたデータ教師として、機械学習することによって客観的な答えを見出します。

== スコアリングの活用方法
スコアリングの活用方法は大きく分けて4つあります。

==== 定量的理解
さまざまなデータ項目（多変量）を一度に扱うことができるので、
各データ項目が目的変数にどれくらい影響するのかを定量的に可視化できます。

==== 格付け
「セグメント」単位でユーザーを抽出し比較することで、
より精度の高いターゲティングが可能です。

==== 予測
過去データを用いた分析モデルの適用によって、
一人一人の未来の行動・結果を事前に予測できます。

==== 育成
目的変数に影響するさまざまな説明変数を用いたスコアリングモデルは、
個人単位で、目的変数を1にするための方法を定量的に求めることができます。

== モデリングへの招待
これから一緒に作っていくスコアリングモデルは、ユーザー（あるいはモノ）を採点するアルゴリズムです。

しかし、あなたが採点されるユーザーだとしたら、
その採点結果を素直に納得することはできますか。

なぜ、そのような点数になったのか、その理由は何か。
ユーザーに対してそのスコアを納得してもらえるものにする必要があります。

そのためには、モデリングする前に、
データに対してモデルを作る側が前提として
頭に入れて置かなければいけないことがあります。

それは、@<kw>{データドリブン, Data-Driven}と@<kw>{データインフォームド, Data-Informed}という考え方です。

=== データドリブン（Data-Driven）
データドリブンとは、@<kw>{データ分析を通して意思決定を行う}スキル・文化を意味します。
データドリブンである組織は、社内にダッシュボードを内製化することによって、
データ（事実）を根拠として、意思決定の正しさと決断スピード向上の両立を目指します。

=== データインフォームド（Data-Informed）
データインフォームドとは、
そのデータは@<kw>{あくまでも目的を実現する方法を指し示す一部である}という前提を
持って、データと接することを意味します。

特にスコアリングモデルでは、この@<kw>{データインフォームド的思考}が大切です。
ユーザーである人間を判断するために収集したデータは、必ず人間の意図が介在しています。
そのデータの因果関係や正しさに適切な懐疑心をもって接することが重要です。

つまり、自分のなかの@<kw>{バイアス,bias}に惑わされないように
データの背景を想像して、倫理観を持ってデータと向き合うことが大切ということです。

=== アルゴリズムとモデルの違い
また、AIを開発するにあたってカタカナ語にたくさんぶち当たります。
ですので、ここで簡単に整理します。

==== アルゴリズム
私の大好きな本のひとつ『世界でもっとも強力な9のアルゴリズム』に
//quote{
アルゴリズムとは、問題を解決するために必要な手順を正確に規定したレシピである。
//}
と書かれています。

私たちは、機械学習のアルゴリズムを学ばなくても、アルゴリズムに触れています。
たとえば、小学校のころに学んだ「足し算」はアルゴリズムです。

足し算は
//quote{
まず、2つの数値の1の位を足し算する。
計算結果の1の位を下に書き出す。10の位があれば、繰り上がりとして左の欄に書き出す。
次に10の位を足し算する。このとき、前の計算での繰り上がりも忘れずに足す・・・
//}
この作業を繰り返すアルゴリズムです。

アルゴリズムのポイントは

 * 1つ1つの手順が、絶対的に正確であること
 * 入力された値が何であれ、必ず機能すること

これはコンピュータが、
プログラムとしてアルゴリズムを使うために必要な要素だからです。

また、機械学習アルゴリズムと指す場合は、
「教師あり学習」「教師なし学習」「強化学習」などを意味します。
そして、その技法（あるいは手法）として、「決定木学習」「ニューラルネットワーク（NN）」など
たくさんの手法が存在します。

「決定木学習」をアルゴリズムとするのか、あくまでも、技法（分析手法）とするのかは、人によってまちまちです。

==== モデル
一般にモデルと呼ばれる場合は、
@<kw>{学習済モデル}や@<kw>{アルゴリズムモデル}を指すことがほとんどでしょう。
どちらを指すにしても、モデルは@<kw>{何かしらを別のモノで表現したもの}です。

たとえば、芝麻信用におけるスコアリングモデルは、
@<kw>{中国でアリババ系サービスを利用するユーザーの信用力を、5つの項目を使って数値で表現したもの}です。


モデルというのは、
@<kw>{何かの状態（目的）を、機械学習アルゴリズムを使って、別のモノで表現した}ものです。
そして、機械学習アルゴリズムにはいくつもの種類があるので、
どんなデータに対してどのようなアルゴリズムを使ったのかによって、モデルはまったく別のものになる可能性を持っています。

=== 統計モデルと機械学習モデル
どちらもデータからモデルを構築することは一緒です。
しかし、@<kw>{実現したい目的が異なります。}

==== 統計モデル
膨大なデータをシンプルにして、私たちが抱える疑問に答えを用意することが主たる目的です。
複雑なデータをシンプルな形にすることで人間にとって理解しやすくする（記述統計）。
また、何か意思決定をするときのためのフレームワークを、目的の結果が起こる確率を算出する（推測統計）など
統計にもいろいろな種類があります。何かの目的に対してそれを説明する要素が複数あったときに、
その説明変数の重要度をそれぞれ明らかにするのは@<kw>{説明的であり、統計モデル}といえます。

==== 機械学習モデル
機械によって、最高の未来予測を生成することが主たる目的です。
ある程度探索的データ解析を行うものの、それはアルゴリズムに渡すためのデータセットの準備のためです。
@<kw>{データから予測精度を追求するのは、機械学習モデル}といえます。

ユーザーがAIに対して懐疑的に思う場合は、往々にして
@<kw>{モデルの説明性と予測精度の高さ}のバランスが悪いときです。

人間にわかりやすく理解してもらうためには、統計的アプローチが必要です。
同時に、AI開発はたとえ説明性が低くなったとしても、予測精度の高さを追求する必要があります。

どちらが優位ということはなく、実務を通じて思うことは、
結局どちらのアプローチも必要ということです。@<br>{}

本書は、最小限の@<kw>{機械学習モデル的アプローチ}で進めていきます。
しかし、それは完全ではありません。

ですから、@<kw>{「データインフォームド（そのモデルに良い意味で懐疑的）であろう。モデルを作り終わったらじっくり統計的アプローチ（今回は割愛）をしよう。」}
という姿勢を持ちながら、このまま読み進めてほしいと思います。

====[column] 行動ログから属性を与えるということ
　スコアリングモデルとは、人の行動を数値化することによって、未来の行動や結果を予測するモデルのことを指します。
中国で話題になった「芝麻信用」がアプリとしてリリースしたことで再び話題になりました。
しかし、このスコアリングモデル自体は機械学習やAIによって精度が高くなったものの、最新技術によって生まれたモデルではありません。@<br>{}

　なぜ、機械学習でもっともホットな分野である画像認識や自然言語処理・音声認識を本書で扱わなかったのかというと、
AIによるスコアリングは開発者であるヒトの主観にもっとも影響を受ける@<kw>{属人性の強いAI}だからです。
私はそこに強い魅力を感じています。

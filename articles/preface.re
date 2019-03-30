= まえがき
== データ分析をデプロイしよう
初めまして。新米データサイエンティストの@hidefknです。

本書のテーマは@<kw>{データ分析をデプロイしよう}です。
本屋さんには、Pythonを使った機械学習やDeepLearningの技術書がたくさん並んでいます。
また、おカネがない子もインターネットさえ使うことができれば、無料でデータサイエンスを学べる環境があります。
学びたい気持ちさえあれば、誰もが機械学習を使ったモデル構築方法とそのために必要な知識を学ぶことができる時代です。

しかし、私がデータサイエンティストとして働くようになって感じたことが1つあります。
それは、AIを開発するために@<kw>{どんなデータを集めて、どんな方法で分析し、どのようなステップでAIアプリを開発すればよいのか？}
詳しく解説された本が少ないことです。

もちろん、技術書は技術について詳しく書くことが当たり前です。
しかし、ことデータを活用するAIアプリ開発においては、
@<kw>{開発目的ドリブン}な技術書の存在が大切な気がしています。

本書は、
@<kw>{AIアプリの開発目的を明確にし、その目的に対して最短経路でデータ分析を行い、分析結果をモデル化し、Webアプリケーションに組込み、プロダクトをAIアプリに昇華できる}
ことを目標にしています。

== 本書の内容
=== 最小の技術で最大のインパクト
この言葉は、私がG'sACADEMY（ジーズアカデミー）というプログラミングスクールに通っていたときに、
メンターのえふしんさんが仰っていた言葉です。
プロダクトに実装する技術が@<kw>{ギミックになってはいけない}という意味だと理解しています。
私はこの言葉をとても気に入っています。

本書は、データ分析のプロセスについて解説しますが、機械学習やディープラーニングについて詳細に書いておりません。
その代わり、AIアプリをコーディングしてデプロイするところまで完遂できるような内容にしています。

=== Nuxt.jsでモダンなアプリを作ろう
アプリ開発は、Vue.jsアプリケーションを構築するためのフレームワークであるNuxt.jsを採用しています。
その理由は、2つあります。

 * HTML5やCSS3、JavaScriptの知識があれば、すんなり理解できて学習コストが低いから
 * HTML5やCSS3、JavaScriptだけを利用するより、シンプルに・簡単に躍動感溢れるヌルっ！サクっ！としたWebアプリを作ることができるから

データを使うAIアプリを開発するにあたって、操作性に@<kw>{ぬるさく感}を込めることを大切にしました。
なぜなら、データを入力したり、データを表示する操作をユーザーに楽しいと思ってほしいからです。

== 本書の構成
本書の構成は次のとおりです。

==== 【理論編】
@<kw>{第1章}では、どのようなステップを踏んでAIアプリを開発すればいいのかについて解説しています。
AIアプリ開発の全体像が見えたところで、@<kw>{第2章}では、スコアリングモデルについて理解を深めていきます。

==== 【実装編】
@<kw>{第3章}では、ワインのオープンデータを活用して、データ分析から機械学習によるモデリングに挑戦します。
@<kw>{第4章}において、Nuxt.jsを使ったAIアプリのフロントエンド開発を始め、
@<kw>{第5章}では、第4章で構築した予測モデルをPythonを使ってAPI化します。これにより、第4章で開発したWebアプリがAIアプリに進化します。
最後の@<kw>{第6章}では、これまで開発したAIアプリをデプロイします。
>>>>>>> dea56ba0db22dca45f0fc863566762d2ad462fb4

== 対象読者
 * データ分析はできるが、アプリ開発をしたことがないデータサイエンティスト
 * アプリ開発はできるが、どうすればAI化できるのかわからないエンジニア
 * データを使って何かを変えたいと思っているすべての人

誰もが無料でデータサイエンスという武器を手に入れることができます。
だからこそ、私もデータサイエンティストになることができました。

一方、新米データサイエンティストの私は、今からどう頑張っても
東大の松尾研でディープラーニングを深く学んでいる専門性の高い学生に敵わないことを自覚しています。

また、数学や統計学においても『1週間で◯◯が分かる本』のような手軽に学べる本が増えてきました。
しかし、付け焼き刃の知識は、生のビッグデータに屈することが少なくありません。
やはり、社会に信頼してもらえる専門性を養うためには、ある程度時間をかけて学ぶ必要があります。

AI（人工知能）ブームで賑やかになりつつあるデータサイエンス業界ですが、
同時に、生半可な世界ではないなと思うのが私の正直な感想です。

でも、私は何かを変えるために、実現するために、データサイエンスを学んでいる人たちの味方でありたいです。
そういう人の武器になるようにと思いながら本を書きました。

@<kw>{そこに目的があるのなら、この本で一緒にデプロイしましょう。}

それでは、新米データサイエンティストによる渾身の薄い本をお楽しみください。

====[column] 私がデータサイエンティストになった理由
私はデータ分析や機械学習が好きでデータサイエンティストになったわけではありません。
ですから、統計学に明るいわけでもないですし、理系出身でもありません。
そんな私がデータサイエンスと出会った理由は、@<kw>{データを分析した結果をデプロイする}必要があったからです。

私は家族や友達どうしでおカネを融通しあえるアプリを作りたいと思っています。
2年前からそんなアプリを作ろうと思ってプログラミングを学び続けていました。

そのアプリを開発している中でぶち当たった壁がありました。
それは、@<kw>{おカネを融通するに値する人物かどうかを判断するしくみ}がないことでした。
今、こうして振り返って考えてみると当たり前なのですが、アプリの中でおカネの貸し借りすることには当然不安を感じますよね。

おカネを貸し借りするときは、その人がおカネを返してくれそうか？そもそも、その人はどんな人なのか？
そういうことがわからないと、人におカネを送ったりしませんよね。

もし、アプリの中でしか会えない誰かにおカネを貸してもらうことで助けてもらうには、
あるいは、自分が誰かを助けるとき、どんな信用（あるいは理由、根拠）が必要なのだろうか。

@<kw>{信用に値する人はどんな要素を持っているのか}を判断できるしくみを作りたい。そう考えるようになりました。
そして、人はどういう人やものごとにおカネを使うのだろうか？そんなことを客観的に証明できて、
アプリに組み込むことができれば、私は作りたかったアプリを作れるのではないか？

この課題を技術的に解決できる可能性をデータサイエンスに感じて、私はこの世界に入ったのです。

====[/column]

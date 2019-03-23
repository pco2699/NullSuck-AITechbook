= 俺はスコアリングアプリが作りたい
== データサイエンティストになった理由
私はデータ分析や機械学習が好きで、データサイエンティストになったわけではありません。
ですから、統計学に明るいわけでもないですし、理系出身でもありません。
そんな私がデータサイエンスと出会ったのは、@<kw>{データを分析した結果をデプロイする}必要があったからです。

=== アプリにデータによる根拠が足りなかった
私は家族や友達同士でおカネを融通しあえるアプリを作りたいと思っています。
2年前からそんなアプリを作ろうと思ってプログラミングを学び続けています。

そのアプリを開発している中でぶち当たった壁が@<kw>{おカネを融通するに値する人物かを判断する仕組み}がなかったことでした。
今こうして振り返って考えてみると当たり前なのですが、アプリの中でおカネの貸し借りすることには不安を感じますよね。

おカネを貸し借りするときは、その人がおカネを返してくれそうか？そもそも、その人はどんな人なんだろうか？
そういうことがわからないと、人におカネを送ったりしませんよね？

もし、アプリの中でしか会えない誰かにおカネを貸してもらうことで助けてもらうには、
あるいは、自分が誰かを助けるのにはどんな信用（あるいは理由、根拠）が必要なのだろうか。
@<kw>{信用に値する人はどんな要素を持っているのか}を判断できる仕組みを作りたい。そう考えるようになりました。

人はどういう人や物事におカネを使うのだろうか？
それを客観的に証明できて、アプリに組みこむことができれば、作りたいものを作れるのではないか？
この課題を技術的に解決できる可能性をデータサイエンスに感じて、この世界に入ったのです。

=== スコアリングモデルとの出会い
そして、この世界で出会ったのが、@<kw>{スコアリング,採点}という考え方でした。
そうです。この本で開発するAIアプリは@<kw>{スコアリングアプリ}です。

スコアリングモデルとは、人の行動を数値化することによって、行動の結果を予測するモデルのことを指します。
中国で話題になった「芝麻信用」がアプリとしてリリースしたことで話題になりました。
しかし、このスコアリングモデル自体は最近できたものではなく歴史があります。
それについては、第3章でご紹介します。

なぜ、機械学習で最もホットな分野である画像認識や自然言語処理・音声認識を使わないのかというと、
AIによるスコアリングは開発者であるヒトの主観に最も影響を受ける@<kw>{属人性の強いAI}だからです。
私はそこに強い魅力を感じています。

== スコアリングアプリをつくろう
@<comment>{ここの文章はあとで精査する}
というわけで、私はスコアリングアプリを作るためにデータサイエンティストになって色々と学んできました。
その渾身のアウトプットがこの本なのです。

本書の構成は次のとおりです。@<kw>{第1章から第3章は【理論編】}です。
この@<kw>{第1章}では、今回作るAIアプリについて、私の自己紹介も含めてご紹介しました。
スコアリングの考え方を理解することができれば、世の中にあふれているAIがどういったものなのか。
その長所と短所を見極められる審美眼が養われるはずです。

次の@<kw>{第2章}では、どのようなステップを踏んでAIアプリを開発すればいいのかについて解説します。
AIアプリ開発の全体像が見えたところで、@<kw>{第3章}ではスコアリングモデルについて理解を深めていきます。

@<kw>{第4章から第6章は【実装編】}です。
@<kw>{第4章}ではワインに関するオープンデータを活用してデータ分析に挑戦します。
@<kw>{第5章}において、AIアプリのフロント開発を始め、
@<kw>{第6章}で第4章で構築したモデルをAIアプリに組み込むためのAPI開発を行います。
最後の@<kw>{第7章}でこれまで開発したアプリをデプロイしていきます。

それでは、一緒にスコアリングアプリを一緒に作っていきましょう。

===[column] コラムが入ります。
@<kw>{「お金のいらない国」}

===[/column]

= Googleデータポータルを使ってみよう
== Googleデータポータルとは
 BIツールというのをご存知でしょうか？マーケティング担当者やデータサイエンティストなら知っていると思いますが、BusinessIntelligenceツールと呼ばれているもので、@<kw>{非プログラマー向けのデータ可視化ツール}
です。可視化された内容を見て、迅速に意思決定を行うためのデータによって作られた武器です。
== Googleデータポータルの特徴
 Googleデータポータルの特徴は、@<kw>{①無料で使える ②スプレッドシートをインポートできる ③SQLも連携できる}の3つです。

 データ活用はアナリストだけでなくエンジニア、ビジネスサイドもできるに越したことはないので、動的に管理できるダッシュボードの作り方はぜひ習得してほしいところです。
=== なぜ、私がGoogleデータポータルをオススメするのか
 BIツールで有名なのはTableau（タブロー）です。Microsoft社のPowerBIも有名ですが、どちらも十分に活用するためには安くない金額を支払わなければなりません。

 もちろん大きな組織でデータ活用を進める場合は、こういった有料のサービスを使ったほうが効率がいいかもしれません。
 しかし、今回はみなさんのような個人が手軽にダッシュボードを作ることができ、且つ運用コストが限りなく低い（GCPを使っている場合は別）方法を選ぶことが大切です。

 この点において、ダッシュボードにGoogleデータポータルを活用することは、最小の技術で最大のインパクトを発揮できるはずです。

== Googleデータポータルの使い方
4つのステップでダッシュボードを一緒に作って、活用していきましょう。

=== 1. ダッシュボードの大枠をデザインしよう
手書きでもいいので、どんなデータをどのようなデザインで可視化すれば、あなたが知りたいことを短時間で効率よく把握することができるのかを考えましょう。
ダッシュボードの作り方のポイントは3つです。@<kw>{①比較できる状態にする ②実数と割合とカテゴリを分類する ③グラフの見方にこだわる}

=== 比較できる状態にする
まず、比較するために必要なデータは時系列データ。つまりTimestampです。時間ごとの比較が可能になります。
つぎに、カテゴリ分類データです。このデータがあるとカテゴリごとの比較が可能になります。

=== データに入っている数値を分類する
その値は実数なのか、確率なのか、数値についてもっと細かく考えてみましょう。
少し面倒かもしれませんが、これを考えてダッシュボードを設計できるようになると、コードの書き方さえ覚えればあなたは精緻なデータベースを作ることができます。

私はこの作業を習得することがとても大切だと考えています。初学者向けのアプリ開発の書籍ではMySQLでユーザーテーブルを作る程度しか学ぶことができません。
もちろん簡単なデータベースを作ることに対しては適切ですが、分析できるデータテーブルになっていないことが問題なのです。

＜ここに手書きの図がはいる＞
===  2. データを連携させよう
ここまでできたら、そのイメージをまずはExcelで書き起こしましょう。Excelで書き起こすことによって、あなたのイメージしていたものが少しずつ具体化され実現可能性が高いものに変わっていきます。
最初からスプレッドシートで作成することをおすすめします。

これができたら、googleデータポータルと連携させるだけです。

===  3. 表示させたいデータを選択しよう
===  4. みんなに共有しよう
なんでダッシュボードを作るのか？みんなに共有すべき理由は何か？そえは意思決定に必要なデータに基づく基礎的な情報が誰でも得られることを、みんなが認識できるから。

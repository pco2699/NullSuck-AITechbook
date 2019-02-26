= NuxtでAIアプリのフロントを作ろう
それでは、今まで@hidefに設計してもらったAIアプリを実際に実装していきましょう。

今回のサンプルアプリケーションはすべて以下のGithubリポジトリにあります。
本文の説明と合わせて参照いただけると理解が進みます。

== 今回作るアプリ
今回は、次の様な構成でアプリを実装していきます。
#@# アプリの構成図を入れる
#@# アプリの構成の説明

本アプリは主に、フロントをNuxt.jsというフロントエンドフレームワークを用いて
実装していきます。
本章では、そのフロント部の実装を中心に説明していきます。

== Nuxt.jsとは？
Nuxt.jsとは？
#@# 説明追加

=== Nuxt.jsを使うメリット
#@# 説明追加

== 実際に作ってみよう
ここからは、実際に手順を追ってNuxt.jsを使ってフロントを組み立ていきます。
なお、Nuxt.jsを動作させるためにはNode.jsの動作環境が必要です。

Node.jsの動作環境のインストールについて、今回は省略いたしますので、適宜、Web等で調査いただき
導入をお願いします。

=== プロジェクト作成
まずは、プロジェクトを作成していきましょう。
今回は、create-nuxt-appというツールを用いて、Nuxtのプロジェクトを作成します。

create-nuxt-appはコマンド一発でNuxtの必要なモジュールを取得して、プロジェクト・ディレクトリを作成してくれる非常に便利です。

他にもvue-cliなどNuxtのプロジェクトを作成する方法がありますが、Nuxtでプロジェクトを作る場合は、2019年現在 create-nuxt-appを利用するのが非常にお勧めです。
# ![スクリーンショット](https://github.com/s059ff/ZephyrEngine/blob/master/screenshots/letter.png "スクリーンショット")epherEngineへようこそ！
## はじめに
__XepherEngine__ は 3D ゲームを簡単に作るための C++/C# 統合ゲーム開発環境です。  
__XepherEngine__ はゲームアプリケーションが直接参照して使うライブラリ部分と、開発を間接的に支援するツール部分から構成され、開発者はこれらのうち必要なものだけを使って開発できます。  
https://github.com/s059ff/ZephyrEngine でオープンソースを公開しています。  
https://www.youtube.com/watch?v=zsBg610JShQ でパワーポイントの動画資料を公開しています。  
https://s059ff.github.io/ZephyrEngine/ でAPIのリファレンスを公開しています。     
![スクリーンショット](https://github.com/s059ff/ZephyrEngine/blob/master/screenshots/XepherEngine.png "スクリーンショット") 

## 動作環境
__XepherEngine__ の動作に必要な環境は以下の通りです。
* Microsoft Windows10 64bit の OS。
* Visual Studio 2017 もしくは Visual Studio 2017 の Visual C++ 再頒布可能パッケージ。
* Shader Model 5.0 対応 / DirectX11 世代の グラフィックス カード。(ない場合は、ソフトウェアエミュレーションのため、動作が遅くなります。)
* 最新の .NET Framework Runtime。
* Autodesk FBX SDK。
* Microsoft DirectX SDK (June 2010)。

## コアシステム
XepherEngine のコアシステムを紹介します。  

* __グラフィックスシステム__  
    ![スクリーンショット](https://github.com/s059ff/ZephyrEngine/blob/master/screenshots/graphics.png "スクリーンショット")   
    DirectX9, DirectX11, Direct2D を簡単に扱うためのライブラリです。  
    3DモデルのフォーマットはFBX形式と独自形式のCX形式を取り扱うことができます。

* __3D数学/衝突判定システム__  
    ![スクリーンショット](https://github.com/s059ff/ZephyrEngine/blob/master/screenshots/collision.png "スクリーンショット")   
    行列、クォータニオンなどの3Dゲームに欠かせない数学ライブラリと、  
    球や直方体などの物体に対する衝突判定システムです。

* __サウンドシステム__  
    DirectSoundのラッパーライブラリです。
    ストリーミング再生にも対応しています。

* __入力システム__  
    DirectInputのラッパーライブラリです。

* __スクリプトシステム__  
    エンジン独自言語であるC#/Script言語のコンパイル、実行をサポートします。

* __ゲームシステム__  
    ゲーム空間における様々な要素（人、車、木）を管理します。
    汎用ゲームエンジンのUnityにおけるGameObjectの機能に相当します。

## デバッギング ツール
XepherEngine は以下のデバッギング ツールを同梱しており、ゲーム開発を最大限に効率化します。

### ゲームシステムモニター
![スクリーンショット](https://github.com/s059ff/ZephyrEngine/blob/master/screenshots/GameSystemMonitor.png "スクリーンショット")  
(左)この一覧に表示されているのは、”ゲームエンティティ”です。（Unity のゲームオブジェクトと同じものと思ってもらえばよいです）  
ゲームエンティティには複数の”ゲームコンポーネント”が取り付けられており、ゲームエンティティをダブルクリックして展開すると、取り付けられているゲームコンポーネントが参照できます。  
さらに、ゲームコンポーネントをダブルクリックすると、  
(右)のようにゲームコンポーネントの内部データにアクセスでき、一部の変数は変更可能です。  
例えば、"player"エンティティの"TransformComponent"の"Position"コンポーネントの値を"0,0,0"にしてみてください。  
プレイヤーの操作する戦闘機が原点に強制移動します。  

### コマンドランナー
![スクリーンショット](https://github.com/s059ff/ZephyrEngine/blob/master/screenshots/CommandRunner.png "スクリーンショット")  
このツールは、アプリケーションの実行中にプログラムを実行する端末のようなものです。  
例えば、"Open"ボタンを押して、"runtime script/generate enemy.cs"を開き、実行してみてください。  
敵と味方が新しく出現します。  

### ステートマシンモニター
![スクリーンショット](https://github.com/s059ff/ZephyrEngine/blob/master/screenshots/StateMachineMonitor.png "スクリーンショット")  
このツールは、NPCの頭の中を表示するものです。グラフの各ノードは状態を、エッジとエッジの上の数字は、状態遷移確率を示しています。  
敵AIが「Attack」と「Retreat」を交互に繰り返し、ミサイルが飛んでくると「Avoid missile」に状態が切り替わることを確認してください。

## インストール・ビルド方法（開発者向け）
1. 外部ライブラリのインストール
    1. __XepherEngine__ のビルドを行うには Visual Studio 2017 が必要です。Microsoft 社のホームページからダウンロードできます。
なお、 Visual Studio 2017 のインストール時には 必ず Native C++ の開発環境も併せてインストールしてください。
    2. グラフィックスシステムを使用する場合、お使いのコンピュータに Autodesk 社の FBXSDK をインストールする必要があります。
インストールは http://www.autodesk.com/products/fbx/overview から Visual Studio 2017 用の最新のものをダウンロードしてください。
2. https://github.com/s059ff/ZephyrEngine にアクセスしてリポジトリをクローンします。  
3. Visual Studio 2017 で Visual Studio のソリューションファイルを開きます。
4. C++ でゲーム開発を行う場合は、xepher〇〇というプロジェクトを参照に加えるか、ライブラリファイル(*.lib)をリンクする必要があります。 
5. C# でゲーム開発を行う場合は、XepherSharp〇〇というプロジェクトを参照に加えるか、クラスライブラリ(*.dll)を参照する必要があります。

## サンプルアプリ
1. __application01__

![スクリーンショット](https://github.com/s059ff/ZephyrEngine/blob/master/screenshots/application_01.png "スクリーンショット")  
ただボールが跳ねるだけのプログラムです。  
このプログラムを実行する場合は、「application01」というプロジェクトをビルド・実行してください。

2. __application03__  

![スクリーンショット](https://github.com/s059ff/ZephyrEngine/blob/master/screenshots/application_03.png "スクリーンショット")  
３Dフライトシューティングゲームです。
このプログラムを実行する場合は、「application02」というプロジェクトをビルド・実行してください。

【ゲーム内容】  
戦闘機を操作して、敵の戦闘機を全部撃ち落としてください。

【操作方法】
![スクリーンショット](https://github.com/s059ff/ZephyrEngine/blob/master/screenshots/application_03_keyboard.png "スクリーンショット")  

| キー |  |
|:-----------|:------------|
|Esc|ゲーム終了|
|← or →キー|ロール（Z軸で戦闘機回転）|
|↑ or ↓キー|ピッチアップ・ダウン（X軸で戦闘機回転）|
|← or →キー + Shift|ヨーイング（Y軸で戦闘機回転）|
|↑ or ↓キー + Shift|ピッチアップ・ダウン（X軸で戦闘機回転、微調整）|
|↓二回押し|緊急回避（方向転換）|
|Aキー|レーダー範囲の拡大・縮小|
|Sキー|ターゲット変更|
|Sキー長押し|ターゲット注視|
|Wキー|ターゲット変更（最優先ターゲットに切り替え）|
|Dキー|カメラ位置変更（ビハインド⇔コックピット）|
|Zキー|スロットルを開く（加速）|
|Xキー|スロットルを閉じる（減速）|
|Cキー|ミサイル発射（ロックオン済みのターゲットに対してはミサイルがターゲットを追従）|
|Vキー|機関砲発射|
|Ctrl + A or S or D or W 長押し|カメラ方向調整|
|←→同時押し|オートパイロット（自動操縦）|

## 企業向け情報
* プログラムの製作人数は私一人です。
* アプリケーションにおけるサウンドや 3D グラフィックスモデルなどの素材は、インターネット上で公開されているものを使用しています。
* 製作期間は、エンジン部分が約３年、application03 が約 3 カ月です。
* 作品の詳細は添付しているパワーポイントの資料をご覧ください。
* __アピールポイント__
    * 数学計算やグラフィックスなど、基本から組み立てたこと。
    * ４万行を超える大規模なプログラム。
    * モジュール毎に分割した再利用性の高いプログラム構成。

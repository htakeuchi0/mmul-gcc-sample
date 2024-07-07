# 行列積の計算時間測定プログラム

## 概要

本ソースセットは，C++における行列の表現方法や，行列積の計算手順などによって，
実行時間にどのような差が出るかを実験的に確認するためのものです．

## 動作環境

下記環境で動作することを確認しています．

* CPU: 13th Gen Intel(R) Core(TM) i7-1360P (16コア)
* メモリ: 16.0GiB
* OS: Linux (Ubuntu 22.04.3 LTS)
* コンパイラ: g++ (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0

## ディレクトリ構成

```
|- LICENSE                ライセンスファイル
|- README.md              本ファイル
|- build-avx.sh           AVX2を利用する場合の実験スクリプト
|- build-openmp.sh        OpenMPを利用する場合の実験スクリプト
|- build.sh               通常の場合の実験スクリプト
|- include/
|   |- mmul-gcc-sample/   ヘッダファイル
|
|- log/                   取得済みログファイル
|- main/                  メインファイル
|- script/                結果描画スクリプト
|  |- output/             描画結果
|
|- src/                   ソースコード
```

## 実行方法

`build.sh`, `build-openmp.sh`, `build-avx.sh` で実験ができます．

# aplfw/sample_win32

hosのWindows向け実装サンプル(hos-v4a/aplfw/sample/win/win32)をCMakeを使ってビルドするように設定  
[![aplfw sample_win32 build](https://github.com/steelpipe75/itron_training_hos/actions/workflows/CI-aplfw-sample_win32.yml/badge.svg)](https://github.com/steelpipe75/itron_training_hos/actions/workflows/CI-aplfw-sample_win32.yml)

## How to Run

```bat
cmake -S . -B build
cd build
cmake --build .
sample.exe
```

### サンプルの動作確認

サンプルを起動した状態で  
VT100エミュレータソフト（TeraTermなど）で  
ホスト : localhost ポート : 9997  
に接続

```

================================================================
 Hyper Operating System  Application Framework

                          Copyright (C) 1998-2010 by Project HOS
                          http://sourceforge.jp/projects/hos/
================================================================

%


```
上記起動メッセージが表示されたらコマンドを入力  
コマンド`help`でコマンド一覧表示  

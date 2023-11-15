# itron_training_hos

[hos-v4a](https://github.com/ryuz/hos-v4a) のWindows向け実装 (win/win32) を使った itron を使う練習
兼 CMake書く練習

## Visual Studio を使ったデバッグ時の注意

CMake に出力させたVisual Studioの.slnファイルを使ってデバッグする際、  
ALL_BUILDではなく、add_executable()で指定した実行ファイルをスタートアッププロジェクトに設定すること  
（ソリューションエクスプローラーの右クリックメニューから設定できる）

## CMake を使った hos-v4a サンプル のビルド

### [./hos_sample_cmake/sample/sample_win32](./hos_sample_cmake/sample/sample_win32/README.md)

hosのWindows向け実装サンプル(hos-v4a/sample/win/win32)をCMakeを使ってビルドするように設定  
[![sample sample_win32 build](https://github.com/steelpipe75/itron_training_hos/actions/workflows/CI-sample-sample_win32.yml/badge.svg)](https://github.com/steelpipe75/itron_training_hos/actions/workflows/CI-sample-sample_win32.yml)

### [./hos_sample_cmake/sample/sample_win32_cli](./hos_sample_cmake/sample/sample_win32_cli/README.md)

sample_win32 を MessageBox を使わないように作り変え  
[![sample sample_win32_cli build](https://github.com/steelpipe75/itron_training_hos/actions/workflows/CI-sample-sample_win32_cli.yml/badge.svg)](https://github.com/steelpipe75/itron_training_hos/actions/workflows/CI-sample-sample_win32_cli.yml)

### [./hos_sample_cmake/aplfw/sample_win32](./hos_sample_cmake/aplfw/sample_win32/README.md)

hos aplfwのWindows向け実装サンプル(hos-v4a/aplfw/sample/win/win32)をCMakeを使ってビルドするように設定  
[![aplfw sample_win32 build](https://github.com/steelpipe75/itron_training_hos/actions/workflows/CI-aplfw-sample_win32.yml/badge.svg)](https://github.com/steelpipe75/itron_training_hos/actions/workflows/CI-aplfw-sample_win32.yml)

## Acknowledgements

- This project utilizes OSS (Open Source Software)
    - [NOTICE.md](NOTICE.md)

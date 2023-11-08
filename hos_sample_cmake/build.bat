cd /d %~dp0

cmake -B      ./aplfw/sample_win32/build/Ninja       -S ./aplfw/sample_win32      -G "Ninja"
cmake --build ./aplfw/sample_win32/build/Ninja
cmake -B      ./aplfw/sample_win32/build/VS2017      -S ./aplfw/sample_win32      -G "Visual Studio 15 2017"
cmake --build ./aplfw/sample_win32/build/VS2017

cmake -B      ./sample/sample_win32/build/Ninja      -S ./sample/sample_win32     -G "Ninja"
cmake --build ./sample/sample_win32/build/Ninja
cmake -B      ./sample/sample_win32/build/VS2017     -S ./sample/sample_win32     -G "Visual Studio 15 2017"
cmake --build ./sample/sample_win32/build/VS2017

cmake -B      ./sample/sample_win32_cli/build/Ninja  -S ./sample/sample_win32_cli -G "Ninja"
cmake --build ./sample/sample_win32_cli/build/Ninja
cmake -B      ./sample/sample_win32_cli/build/VS2017 -S ./sample/sample_win32_cli -G "Visual Studio 15 2017"
cmake --build ./sample/sample_win32_cli/build/VS2017

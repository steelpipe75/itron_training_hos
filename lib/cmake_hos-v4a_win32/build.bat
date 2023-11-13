cd /d %~dp0

cmake -B      ./aplfw/build/Ninja       -S ./aplfw      -G "Ninja"
cmake --build ./aplfw/build/Ninja
cmake -B      ./aplfw/build/VS2017      -S ./aplfw      -G "Visual Studio 15 2017"
cmake --build ./aplfw/build/VS2017

cmake -B      ./cfgrtr/build/Ninja      -S ./cfgrtr     -G "Ninja"
cmake --build ./cfgrtr/build/Ninja
cmake -B      ./cfgrtr/build/VS2017     -S ./cfgrtr     -G "Visual Studio 15 2017"
cmake --build ./cfgrtr/build/VS2017

cmake -B      ./kernel/build/Ninja      -S ./kernel     -G "Ninja"
cmake --build ./kernel/build/Ninja
cmake -B      ./kernel/build/VS2017     -S ./kernel     -G "Visual Studio 15 2017"
cmake --build ./kernel/build/VS2017

cmake -B      ./kernel_ex/build/Ninja   -S ./kernel_ex  -G "Ninja"
cmake --build ./kernel_ex/build/Ninja
cmake -B      ./kernel_ex/build/VS2017  -S ./kernel_ex  -G "Visual Studio 15 2017"
cmake --build ./kernel_ex/build/VS2017

cmd /k

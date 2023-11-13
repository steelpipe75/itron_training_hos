cd /d %~dp0

cmake -B      ./googletest/build/Ninja      -S ./googletest     -G "Ninja"
cmake --build ./googletest/build/Ninja
cmake -B      ./googletest/build/VS2017     -S ./googletest     -G "Visual Studio 15 2017"
cmake --build ./googletest/build/VS2017

cmake -B      ./vter_knl/build/Ninja        -S ./vter_knl       -G "Ninja"
cmake --build ./vter_knl/build/Ninja
cmake -B      ./vter_knl/build/VS2017       -S ./vter_knl       -G "Visual Studio 15 2017"
cmake --build ./vter_knl/build/VS2017

cmd /k

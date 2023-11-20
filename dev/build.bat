cd /d %~dp0

cmake -B      ./extension/sample/build/Ninja        -S ./extension/sample       -G "Ninja"
cmake --build ./extension/sample/build/Ninja
cmake -B      ./extension/sample/build/VS2017       -S ./extension/sample       -G "Visual Studio 15 2017"
cmake --build ./extension/sample/build/VS2017

cmake -B      ./extension/aplfw/build/Ninja         -S ./extension/aplfw        -G "Ninja"
cmake --build ./extension/aplfw/build/Ninja
cmake -B      ./extension/aplfw/build/VS2017        -S ./extension/aplfw        -G "Visual Studio 15 2017"
cmake --build ./extension/aplfw/build/VS2017

cmake -B      ./extension/sample_cli/build/Ninja    -S ./extension/sample_cli   -G "Ninja"
cmake --build ./extension/sample_cli/build/Ninja
cmake -B      ./extension/sample_cli/build/VS2017   -S ./extension/sample_cli   -G "Visual Studio 15 2017"
cmake --build ./extension/sample_cli/build/VS2017

cmake -B      ./extension/aplfw_cli/build/Ninja     -S ./extension/aplfw_cli    -G "Ninja"
cmake --build ./extension/aplfw_cli/build/Ninja
cmake -B      ./extension/aplfw_cli/build/VS2017    -S ./extension/aplfw_cli    -G "Visual Studio 15 2017"
cmake --build ./extension/aplfw_cli/build/VS2017

cmake -B      ./googletest/build/Ninja              -S ./googletest             -G "Ninja"
cmake --build ./googletest/build/Ninja
cmake -B      ./googletest/build/VS2017             -S ./googletest             -G "Visual Studio 15 2017"
cmake --build ./googletest/build/VS2017

cmake -B      ./googlemock/build/Ninja              -S ./googletest             -G "Ninja"
cmake --build ./googlemock/build/Ninja
cmake -B      ./googlemock/build/VS2017             -S ./googletest             -G "Visual Studio 15 2017"
cmake --build ./googlemock/build/VS2017

cmd /k

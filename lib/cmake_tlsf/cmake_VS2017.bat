cd /d %~dp0
cmake -S . -B build/VS2017 -G "Visual Studio 15 2017"
cd .\build\VS2017
cmd /k

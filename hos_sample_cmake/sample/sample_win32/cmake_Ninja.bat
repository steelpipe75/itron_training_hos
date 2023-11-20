cd /d %~dp0
cmake -S . -B build/Ninja -G "Ninja"
cd .\build\Ninja
cmd /k

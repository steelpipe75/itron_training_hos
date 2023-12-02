cd /d %~dp0
cmake -S . -B build/Ninja -G "Ninja" -D BUILD_TLSF_SAMPLE=ON
cd .\build\Ninja
cmd /k

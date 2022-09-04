@echo off
cd ..
cmake -B build_MSYS -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cd build_MSYS
mingw32-make -j 8
pause
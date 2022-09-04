@echo off
cd ..
cmake -B build_MinGW -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cd build_MinGW
mingw32-make -j 8
pause
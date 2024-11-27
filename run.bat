@echo off
if exist build rd /s /q build
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
if exist GraphicsLibrary.exe (
    GraphicsLibrary.exe
)

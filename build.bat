@echo off

if not exist build mkdir build

pushd build
cl /Fe:Game.exe /EHsc /MP /Zi /I C:\libs\SDL2-2.0.14\include /I C:\libs\SDL2_image-2.0.5\include ..\src\*.cpp /link /DEBUG:FASTLINK /NOLOGO shell32.lib /LIBPATH C:\libs\SDL2-2.0.14\lib\x64\SDL2.lib /LIBPATH C:\libs\SDL2-2.0.14\lib\x64\SDL2main.lib /LIBPATH C:\libs\SDL2_image-2.0.5\lib\x64\SDL2_image.lib /SUBSYSTEM:CONSOLE
popd

echo.
echo [Build completed]

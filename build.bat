cd build\
cl /Fe"Game.exe" /Zi /I "C:\libs\SDL2-2.0.14\include" /I "C:\libs\SDL2_image-2.0.5\include" ..\src\*.cpp shell32.lib /link /LIBPATH "C:\libs\SDL2-2.0.14\lib\x64\SDL2.lib" "C:\libs\SDL2-2.0.14\lib\x64\SDL2main.lib" "C:\libs\SDL2_image-2.0.5\lib\x64\SDL2_image.lib" /SUBSYSTEM:CONSOLE
cd ..

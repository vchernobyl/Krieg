@echo off

if not exist build mkdir build

pushd build
cl /nologo /Fe:Game.exe /DDEBUG /EHsc /MP /Zi /I ..\external\pugixml\include /I ..\external\SDL2\include /I ..\external\SDL2_image\include /I ..\external\FMOD\api\studio\include /I ..\external\FMOD\api\core\include ..\src\*.cpp ..\external\pugixml\lib\pugixml.lib ..\external\FMOD\api\core\lib\x64\fmod_vc.lib shell32.lib ..\external\SDL2\lib\x64\SDL2.lib ..\external\SDL2\lib\x64\SDL2main.lib ..\external\SDL2_image\lib\x64\SDL2_image.lib ..\external\FMOD\api\studio\lib\x64\fmodstudio_vc.lib /link /DEBUG:FASTLINK /SUBSYSTEM:CONSOLE
popd

echo.
echo [Build completed]

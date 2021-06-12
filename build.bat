@echo off

if not exist build mkdir build

pushd build
cl /nologo /Fe:Game.exe /DDEBUG /EHsc /MP /Zi /I ..\external\pugixml\include /I ..\external\SDL2\include /I ..\external\SDL2_image\include /I "C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\studio\inc" /I "C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core\inc" ..\src\*.cpp ..\external\pugixml\lib\pugixml.lib "C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core\lib\x64\fmod_vc.lib" shell32.lib ..\external\SDL2\lib\x64\SDL2.lib ..\external\SDL2\lib\x64\SDL2main.lib ..\external\SDL2_image\lib\x64\SDL2_image.lib "C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\studio\lib\x64\fmodstudio_vc.lib" /link /DEBUG:FASTLINK /SUBSYSTEM:CONSOLE
popd

echo.
echo [Build completed]

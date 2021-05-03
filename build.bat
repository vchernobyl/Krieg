@echo off

if not exist build mkdir build

pushd build
cl /Fe:Game.exe /DDEBUG /EHsc /MP /Zi /I C:\libs\SDL2-2.0.14\include /I C:\libs\SDL2_image-2.0.5\include /I "C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\studio\inc" /I "C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core\inc" ..\src\*.cpp /link /DEBUG:FASTLINK /NOLOGO shell32.lib /LIBPATH C:\libs\SDL2-2.0.14\lib\x64\SDL2.lib /LIBPATH C:\libs\SDL2-2.0.14\lib\x64\SDL2main.lib /LIBPATH C:\libs\SDL2_image-2.0.5\lib\x64\SDL2_image.lib /LIBPATH "C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\studio\lib\x64\fmodstudio_vc.lib" /LIBPATH "C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core\lib\x64\fmod_vc.lib" /SUBSYSTEM:CONSOLE
popd

echo.
echo [Build completed]

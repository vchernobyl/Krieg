@echo off

set application=Game
set compile_flags=/nologo /DDEBUG /EHsc /MP /Zi
set link_flags=/DEBUG:FASTLINK /SUBSYSTEM:CONSOLE

set include_flags=/I ..\external\box2d\include^
    /I ..\external\pugixml\include^
    /I ..\external\SDL2\include^
    /I ..\external\SDL2_image\include^
    /I ..\external\FMOD\api\studio\include^
    /I ..\external\FMOD\api\core\include

set libs=shell32.lib^
    ..\external\pugixml\lib\pugixml.lib^
    ..\external\FMOD\api\core\lib\x64\fmod_vc.lib^
    ..\external\box2d\lib\x64\box2d.lib^
    ..\external\SDL2\lib\x64\SDL2.lib^
    ..\external\SDL2\lib\x64\SDL2main.lib^
    ..\external\SDL2_image\lib\x64\SDL2_image.lib^
    ..\external\FMOD\api\studio\lib\x64\fmodstudio_vc.lib

if not exist build mkdir build
pushd build
cl %compile_flags% %include_flags% ..\src\*.cpp %libs% /link %link_flags% /out:%application%.exe
popd

echo.
echo [Build completed]

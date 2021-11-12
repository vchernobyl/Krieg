@echo off

set application=Game
set compile_flags=/nologo /DDEBUG /EHsc /MP /Zi /std:c++17
set link_flags=/DEBUG:FASTLINK /SUBSYSTEM:CONSOLE

set include_flags=/I ..\external\box2d\include^
    /I ..\external\pugixml\include^
    /I ..\external\SDL\include^
    /I ..\external\FMOD\api\studio\include^
    /I ..\external\FMOD\api\core\include^
    /I ..\external\glew\include^
    /I ..\external\SOIL\include\^
    /I ..\external\freetype\include

set libs=shell32.lib^
    ..\external\pugixml\lib\pugixml.lib^
    ..\external\FMOD\api\core\lib\x64\fmod_vc.lib^
    ..\external\box2d\lib\x64\box2d.lib^
    ..\external\SDL\lib\x64\SDL2.lib^
    ..\external\SDL\lib\x64\SDL2main.lib^
    ..\external\SDL\lib\x64\SDL2_ttf.lib^
    ..\external\FMOD\api\studio\lib\x64\fmodstudio_vc.lib^
    ..\external\glew\lib\x64\glew32.lib^
    ..\external\SOIL\lib\x64\SOIL.lib^
    ..\external\freetype\lib\x64\freetype.lib^
    opengl32.lib
    
if not exist build mkdir build
pushd build
cl %compile_flags% %include_flags% ..\src\*.cpp %libs% /link %link_flags% /out:%application%.exe
popd

if not exist .\build\SDL2.dll copy external\SDL\lib\x64\SDL2.dll .\build
if not exist .\build\SDL2_ttf.dll copy external\SDL\lib\x64\SDL2_ttf.dll .\build
if not exist .\build\glew32.dll copy external\glew\lib\x64\glew32.dll .\build

echo.
echo [Build completed]

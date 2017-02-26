@echo off

IF NOT EXIST .\build mkdir .\build
pushd .\build

cl -Od -MTd -nologo -Zi ..\hellowindow.c /link -opt:ref user32.lib gdi32.lib winmm.lib

popd

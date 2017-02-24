@echo off

IF NOT EXIST .\build mkdir .\build
pushd .\build

cl -Od -MTd -nologo -Zi ..\ScreenSize.c /link -opt:ref user32.lib 

popd

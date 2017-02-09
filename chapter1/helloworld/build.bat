@echo off

IF NOT EXIST .\build mkdir .\build
pushd .\build

cl -Od -MTd -nologo -Zi ..\HelloMsg.c /link -opt:ref user32.lib

dir

popd

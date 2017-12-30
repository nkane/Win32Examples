IF NOT EXIST .\build MKDIR .\build
PUSHD .\build

cl /MTd /Od /Zi /nologo ..\main.c /link  /opt:ref user32.lib gdi32.lib winmm.lib

POPD

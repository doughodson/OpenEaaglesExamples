rem
call ..\makedefs.bat
rem
%mcpp% inputs/test.epp  > test.edl   -I ..\data -DFONT_PATH="\"../data/fonts/\""  -DFONT_11_19_PATH="\"../data/fonts/11x19/normal/\"" -DTEXTURES_PATH="\"../data/textures/\""
%mcpp% inputs/test2.epp > test2.edl  -I ..\data -DFONT_PATH="\"../data/fonts/\""  -DFONT_11_19_PATH="\"../data/fonts/11x19/normal/\"" -DTEXTURES_PATH="\"../data/textures/\""


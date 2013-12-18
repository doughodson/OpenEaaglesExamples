rem
call ..\makedefs.bat
rem
%mcpp% configs/test.epp > test.edl -I ..\..\openeaagles\include  -I ..\data -DFONT_PATH="\"../data/fonts/\""  -DFONT_11_19_PATH="\"../data/fonts/11x19/normal/\"" -DTEXTURES_PATH="\"../data/textures/\""


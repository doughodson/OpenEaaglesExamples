rem
call ..\makedefs.bat
rem
%mcpp% inputs\test1.epp > test1.edl -I ..\data -I ..\include  -DFONT_PATH="\"../data/fonts/\""  -I ..\..\openeaagles\include  -DFONT_11_19_PATH="\"../data/fonts/11x19/normal/\"" -DTEXTURES_PATH="\"../data/textures/\""
%mcpp% inputs\recordTest.epp > recordTest.edl  -I ..\data -I ..\include  -DFONT_PATH="\"../data/fonts/\""  -I ..\..\openeaagles\include  -DFONT_11_19_PATH="\"../data/fonts/11x19/normal/\"" -DTEXTURES_PATH="\"../data/textures/\""


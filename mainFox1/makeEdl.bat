rem
call ..\makedefs.bat
rem
%mcpp% inputs/testfox.epp >testfox.edl  -I ..\..\openeaagles\include\openeaagles -I ..\data -DFONT_PATH="\"../data/fonts/\"" -DTEXTURES_PATH="\"../data/textures/\""


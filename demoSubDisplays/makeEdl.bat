rem
call ..\makedefs.bat
rem
%mcpp% configs/test.epp > test.edl  -I ..\..\openeaagles\include -I ..\data -DFONT_PATH="\"../data/fonts/\"


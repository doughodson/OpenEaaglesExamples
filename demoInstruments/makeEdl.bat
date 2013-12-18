rem
call ..\makedefs.bat
rem
%mcpp% configs/testinstruments.epp > testinstruments.edl  -I ..\..\openeaagles\include -I ..\data -DFONT_PATH="\"../data/fonts/\"


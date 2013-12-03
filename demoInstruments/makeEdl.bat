rem
call ..\makedefs.bat
rem
%mcpp% inputs/testinstruments.epp > testinstruments.edl  -I ..\..\openeaagles\include -I ..\data -DFONT_PATH="\"../data/fonts/\"


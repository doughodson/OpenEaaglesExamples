rem
call ..\makedefs.bat
rem
%mcpp% inputs/test.epp > test.edl -I ..\data -DFONT_PATH="\"../data/fonts/\""

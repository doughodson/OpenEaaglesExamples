rem
call ..\makedefs.bat
rem
%mcpp% configs/test.epp > test.edl -I ..\data -DFONT_PATH="\"../data/fonts/\""

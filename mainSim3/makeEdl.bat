rem
call ..\makedefs.bat
rem
%mcpp% configs/test0.epp > test0.edl -I ..\data -DFONT_PATH="\"../data/fonts/\""

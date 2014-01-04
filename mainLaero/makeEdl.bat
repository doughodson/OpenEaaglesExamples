rem
call ..\makedefs.bat
rem
%mcpp% configs/test.epp > test.edl ^
 -I ..\shared\data ^
 -DFONT_PATH="\"../shared/data/fonts/\""

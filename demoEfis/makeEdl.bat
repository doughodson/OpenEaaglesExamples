rem
call ..\makedefs.bat
rem
%mcpp% configs/glutdisplay.epp > glutdisplay.edl ^
 -I ..\shared\data ^
 -DFONT_PATH="\"../shared/data/fonts/\"" ^
 -DTEXTURES_PATH="\"../shared/data/textures/\""

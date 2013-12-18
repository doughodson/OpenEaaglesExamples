rem
call ..\makedefs.bat
rem
%mcpp% configs/puzzle.epp > puzzle.edl -DTEXTURES_PATH="\"../data/textures/\""


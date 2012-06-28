rem
call ..\makedefs.bat
rem
%mcpp% inputs/puzzle.epp > puzzle.edl -DTEXTURES_PATH="\"../data/textures/\""


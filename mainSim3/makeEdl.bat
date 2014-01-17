rem
call ..\makedefs.bat
rem
%mcpp% configs/test0.epp > test0.edl ^
 -I ..\shared\data ^
 -DFONT_PATH="\"../shared/data/fonts/\"" ^
 -DJSBSIM_PATH="\"../shared/data/JSBSim/\""

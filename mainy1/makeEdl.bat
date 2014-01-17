rem
call ..\makedefs.bat
rem
%mcpp% configs\test1.epp > test1.edl ^
 -I ..\shared ^
 -I ..\shared\data ^
 -I ..\..\openeaagles\include ^
 -DFONT_PATH="\"../shared/data/fonts/\"" ^
 -DFONT_11_19_PATH="\"../shared/data/fonts/11x19/normal/\"" ^
 -DTEXTURES_PATH="\"../shared/data/textures/\"" ^
 -DJSBSIM_PATH="\"../shared/data/JSBSim/\""

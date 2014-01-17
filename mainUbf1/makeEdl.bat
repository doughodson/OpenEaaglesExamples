rem
call ..\makedefs.bat
rem
%mcpp% configs\simAgentTest.epp > simAgentTest.edl ^
 -I ..\shared ^
 -I ..\shared\data ^
 -DFONT_PATH="\"../shared/data/fonts/\"" ^
 -DFONT_11_19_PATH="\"../shared/data/fonts/11x19/normal/\"" ^
 -DTEXTURES_PATH="\"../shared/data/textures/\"" ^
 -DJSBSIM_PATH="\"../shared/data/JSBSim/\""

%mcpp% configs\agentTest.epp > agentTest.edl ^
 -I ..\shared ^
 -I ..\shared\data ^
 -DFONT_PATH="\"../shared/data/fonts/\"" ^
 -DFONT_11_19_PATH="\"../shared/data/fonts/11x19/normal/\"" ^
 -DTEXTURES_PATH="\"../shared/data/textures/\"" ^
 -DJSBSIM_PATH="\"../shared/data/JSBSim/\""

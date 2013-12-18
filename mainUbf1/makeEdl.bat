rem
call ..\makedefs.bat
rem
%mcpp% configs\simAgentTest.epp > simAgentTest.edl  -I ..\data  -I ..\shared-libs  -DFONT_PATH="\"../data/fonts/\""  -DFONT_11_19_PATH="\"../data/fonts/11x19/normal/\"" -DTEXTURES_PATH="\"../data/textures/\""
%mcpp% configs\agentTest.epp    > agentTest.edl     -I ..\data  -I ..\shared-libs  -DFONT_PATH="\"../data/fonts/\""  -DFONT_11_19_PATH="\"../data/fonts/11x19/normal/\"" -DTEXTURES_PATH="\"../data/textures/\""


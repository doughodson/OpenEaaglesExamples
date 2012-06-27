rem
@set mcpp=..\..\OpenEaagles3rdParty\bin\mcpp.exe
rem
%mcpp% inputs/test.epp >test.edl -I ..\data -DFONT_PATH="\"../data/fonts/\""  -DTEXTURES_PATH="\"../data/textures/\""

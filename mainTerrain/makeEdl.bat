rem
call ..\makedefs.bat
rem
%mcpp% inputs/test.epp > test.edl -DDATA_PATH="\"../data\""


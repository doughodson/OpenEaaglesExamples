rem
call ..\makedefs.bat
rem
%mcpp% configs/test.epp > test.edl -DDATA_PATH="\"../shared/data\""


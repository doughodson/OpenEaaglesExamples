rem
call ..\makedefs.bat
rem
%mcpp% configs/test1.epp > test1.edl -I ..\shared\data
%mcpp% configs/test2.epp > test2.edl -I ..\shared\data


rem
call ..\makedefs.bat
rem
%mcpp% configs/test00.epp > test00.edl -I ..\shared\data
%mcpp% configs/test01.epp > test01.edl -I ..\shared\data


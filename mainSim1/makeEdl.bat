rem
call ..\makedefs.bat
rem
%mcpp% configs/test0.epp > test0.edl -I ..\shared\data
%mcpp% configs/test1.epp > test1.edl -I ..\shared\data
%mcpp% configs/test2.epp > test2.edl -I ..\shared\data
rem %mcpp% configs/test3.epp > test3.edl -I ..\shared\data
%mcpp% configs/test4.epp > test4.edl -I ..\shared\data


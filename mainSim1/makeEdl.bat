rem
call ..\makedefs.bat
rem
%mcpp% configs/test.epp  > test.edl  -I ..\shared\data
%mcpp% configs/testH.epp > testH.edl -I ..\shared\data


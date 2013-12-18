rem
call ..\makedefs.bat
rem
%mcpp% configs/test.epp  > test.edl   -I ..\data
%mcpp% configs/testH.epp > testH.edl  -I ..\data


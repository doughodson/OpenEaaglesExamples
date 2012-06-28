rem
call ..\makedefs.bat
rem
%mcpp% inputs/test.epp  > test.edl   -I ..\data
%mcpp% inputs/testH.epp > testH.edl  -I ..\data


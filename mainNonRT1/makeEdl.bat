rem
call ..\makedefs.bat
rem
%mcpp% inputs/test1.epp >test1.edl  -I ..\data
%mcpp% inputs/test2.epp >test2.edl  -I ..\data


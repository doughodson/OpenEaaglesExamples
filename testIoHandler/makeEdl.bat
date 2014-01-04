rem
call ..\makedefs.bat
rem
%mcpp% configs\test1.epp  > test1.edl ^
 -DFONT_11_19_NORMAL_PATH="\"../shared/data/fonts/11x19/normal/\"" ^
 -DFONT_11_19_UNDERLINE_PATH="\"../shared/data/fonts/11x19/underline/\"" ^
 -DFONT_11_19_SPECIAL_PATH="\"../shared/data/fonts/11x19/special/\""

%mcpp% configs\test2.epp  > test2.edl ^
 -DFONT_11_19_NORMAL_PATH="\"../shared/data/fonts/11x19/normal/\"" ^
 -DFONT_11_19_UNDERLINE_PATH="\"../shared/data/fonts/11x19/underline/\"" ^
 -DFONT_11_19_SPECIAL_PATH="\"../shared/data/fonts/11x19/special/\""

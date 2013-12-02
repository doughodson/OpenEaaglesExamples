rem
call ..\makedefs.bat
rem
%mcpp% inputs\test1.epp  > test1.edl -DFONT_11_19_NORMAL_PATH="\"../../OpenEaaglesExamples/data/fonts/11x19/normal/\""   -DFONT_11_19_UNDERLINE_PATH="\"../../OpenEaaglesExamples/data/fonts/11x19/underline/\""  -DFONT_11_19_SPECIAL_PATH="\"../../OpenEaaglesExamples/data/fonts/11x19/special/\""
%mcpp% inputs\test2.epp  > test2.edl -DFONT_11_19_NORMAL_PATH="\"../../OpenEaaglesExamples/data/fonts/11x19/normal/\""   -DFONT_11_19_UNDERLINE_PATH="\"../../OpenEaaglesExamples/data/fonts/11x19/underline/\""  -DFONT_11_19_SPECIAL_PATH="\"../../OpenEaaglesExamples/data/fonts/11x19/special/\""


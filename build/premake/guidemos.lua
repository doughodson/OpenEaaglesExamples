
--------------------------------------------------------
-- GUI demos
--------------------------------------------------------

-- mainFltk1: Fltk-based GUI
project "mainFltk1"
   targetname "mainFltk1"
   targetdir "../../mainFltk1"
   files {
      "../../mainFltk1/**.cpp",
      "../../mainFltk1/**.h",
      "../../mainFltk1/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments" }
      links {"oesimulation", "oedafif"}
      links {"ftgl", "freetype2"}
      links {"fltk", "fltkforms", "fltkgl", "fltkimages"}
      links {"fltkjpeg", "fltkpng", "fltkz"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d"}
      links {"oesimulation_d", "oedafif_d"}
      links {"ftgl_d", "freetype2_d"}
      links {"fltk_d",  "fltkforms_d", "fltkgl_d", "fltkimages_d"}
      links {"fltkjpeg_d", "fltkpng_d", "fltkz_d"}

-- mainFox1: Fox-based GUI
project "mainFox1"
   targetname "mainFox1"
   targetdir "../../mainFox1"
   files {
      "../../mainFox1/**.cpp",
      "../../mainFox1/**.h",
      "../../mainFox1/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include",
      "../../../OpenEaagles3rdParty/include/fox-1.6"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   defines {"FOX_1_6"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments" }
      links {"oesimulation", "oedafif"}
      links {"ftgl", "freetype2"}
      links {"fox-1.6"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d"}
      links {"oesimulation_d", "oedafif_d"}
      links {"ftgl_d", "freetype2_d"}
      links {"fox-1.6_d"}


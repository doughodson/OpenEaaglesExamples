
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
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeSimulation", "oeDafif"}
      links {"oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", LibFreetype, LibGLU, LibGL}
      if (os.is("linux")) then
         links {"fltk_images", "fltk_gl", "fltk"}
         links {"X11", "Xft", "pthread", "rt"}
      else
         links {"fltkimages", "fltkgl", "fltk"}
--         links {"fltkjpeg", "fltkpng", "fltkz"}
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeSimulation_d", "oeDafif_d"}
      links {"oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"fltkimages_d", "fltkgl_d", "fltk_d"}
--      links {"fltkjpeg_d", "fltkpng_d", "fltkz_d"}
      links {"ftgl_d", "freetype2_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}


-- mainFox1: Fox-based GUI
project "mainFox1"
   targetname "mainFox1"
   targetdir "../../mainFox1"
   files {
      "../../mainFox1/**.cpp",
      "../../mainFox1/**.h",
      "../../mainFox1/**.epp"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OE3rdPartyIncPath.."/fox-1.6" }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines {"FOX_1_6"}
   configuration "Release"
      links {"oeSimulation", "oeDafif", "oeInstruments"}
      links {"oeBasicGL", "oeBasic"}
      links {"FOX-1.6"}
      links {"ftgl", LibFreetype, LibGLU, LibGL}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeSimulation_d", "oeDafif_d", "oeInstruments_d"}
      links {"oeBasicGL_d", "oeBasic_d"}
      links {"FOX-1.6_d"}
      links {"ftgl_d", "freetype2_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}



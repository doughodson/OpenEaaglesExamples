
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
      links {"fltk_images", "fltk_gl", "fltk"}
--    links {"fltk_jpeg", "fltk_png", "fltk_z"}
      links {"ftgl", LibFreetype, LibGLU, LibGL}
      if (os.is("linux")) then
         links {"X11", "Xft", "pthread", "rt"}
      else
         links {"WS2_32", "WinMM", "ComCtl32", "Ole32", "ComDlg32", "Uuid", "Gdi32"}
      end
   configuration "Debug"
      links {"oeSimulation_d", "oeDafif_d"}
      links {"oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"fltk_images_d", "fltk_gl_d", "fltk_d"}
--      links {"fltk_jpeg_d", "fltk_png_d", "fltk_z_d"}
      links {"ftgl_d", "freetype2_d"}
      links {"glu32", "opengl32"}
      links {"WS2_32", "WinMM", "ComCtl32", "Ole32", "ComDlg32", "Uuid", "Gdi32"}


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
         links {"WS2_32", "WinMM", "ComCtl32", "Gdi32"}
      end
   configuration "Debug"
      links {"oeSimulation_d", "oeDafif_d", "oeInstruments_d"}
      links {"oeBasicGL_d", "oeBasic_d"}
      links {"FOX-1.6_d"}
      links {"ftgl_d", "freetype2_d"}
      links {"glu32", "opengl32"}
      links {"WS2_32", "WinMM", "ComCtl32", "Gdi32"}


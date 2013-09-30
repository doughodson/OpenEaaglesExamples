--------------------------------------------------------
-- GUI examples
--------------------------------------------------------

-- mainFltk1: Fltk-based GUI
project "mainFltk1"
   targetname "mainFltk1"
   targetdir "../../mainFltk1"
   debugdir "../../mainFltk1"
   files {
      "../../mainFltk1/**.cpp",
      "../../mainFltk1/**.h",
      "../../mainFltk1/**.epp"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oeSimulation", "oeDafif"}
      links {"oeInstruments", "oeBasicGL", "oeBasic"}
      links {"fltk_images", "fltk_gl", "fltk"}
--    links {"fltk_jpeg", "fltk_png", "fltk_z"}
      links {LibFtgl, LibFreetype, LibGLU, LibGL}
      links {"WS2_32", "WinMM", "ComCtl32", "Ole32", "ComDlg32", "Uuid", "Gdi32"}
   configuration "Debug"
      links {"oeSimulation_d", "oeDafif_d"}
      links {"oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"fltk_images_d", "fltk_gl_d", "fltk_d"}
--      links {"fltk_jpeg_d", "fltk_png_d", "fltk_z_d"}
      links {LibFtgl_d, LibFreetype_d, LibGLU, LibGL}
      links {"WS2_32", "WinMM", "ComCtl32", "Ole32", "ComDlg32", "Uuid", "Gdi32"}


-- mainFox1: Fox-based GUI
project "mainFox1"
   targetname "mainFox1"
   targetdir "../../mainFox1"
   debugdir "../../mainFox1"
   files {
      "../../mainFox1/**.cpp",
      "../../mainFox1/**.h",
      "../../mainFox1/**.epp"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OE3rdPartyIncPath.."/fox-1.6" }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   defines {"FOX_1_6"}
   configuration "Release"
      links {"oeSimulation", "oeDafif", "oeInstruments"}
      links {"oeBasicGL", "oeBasic"}
      links {"FOX-1.6"}
      links {LibFtgl, LibFreetype, LibGLU, LibGL}
      links {"WS2_32", "WinMM", "ComCtl32", "Gdi32"}
   configuration "Debug"
      links {"oeSimulation_d", "oeDafif_d", "oeInstruments_d"}
      links {"oeBasicGL_d", "oeBasic_d"}
      links {"FOX-1.6_d"}
      links {LibFtgl_d, LibFreetype_d, LibGLU, LibGL}
      links {"WS2_32", "WinMM", "ComCtl32", "Gdi32"}


-- mainGlfw : basic display using Glfw example
project "mainGlfw"
   targetname "mainGlfw"
   targetdir "../../mainGlfw"
   debugdir "../../mainGlfw"
   files {
      "../../mainGlfw/**.cpp",
      "../../mainGlfw/**.h",
      "../../mainGlfw/**.epp",
      "../../mainGlfw/**.edl"
   }

   defines { "GLEW_STATIC" }

   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oeGlfw", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGLU, LibGL, "glfw3", "glew32s" }
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlfw_d", "oeBasicGL_d", "oeBasic_d"}
      links {LibFtgl_d, LibFreetype_d, LibGLU, LibGL, "glew32s_d", "glfw3_d" }
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}


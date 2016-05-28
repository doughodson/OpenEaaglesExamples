--------------------------------------------------------
-- GUI examples
--------------------------------------------------------

-- GLUT-based GUI example
project "mainGlut"
   kind "ConsoleApp"
   targetname "mainGlut"
   targetdir "../../mainGlut"
   debugdir "../../mainGlut"
   files {
      "../../mainGlut/**.cpp",
      "../../mainGlut/**.h",
      "../../mainGlut/**.epp",
      "../../mainGlut/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oeglut", "oeinstruments", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Fltk-based GUI example
project "mainFltk1"
   kind "WindowedApp"
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
   filter "configurations:Release*"
      links {"oesimulation", "oedafif"}
      links {"oeinstruments", "oegraphics", "oebase"}
      links {"fltk_images", "fltk_gl", "fltk"}
--    links {"fltk_jpeg", "fltk_png", "fltk_z"}
      links {LibFtgl, LibFreetype, LibGLU, LibGL}
      links {"WS2_32", "WinMM", "ComCtl32", "Ole32", "ComDlg32", "Uuid", "Gdi32"}
   filter "configurations:Debug*"
      links {"oesimulation_d", "oedafif_d"}
      links {"oeinstruments_d", "oegraphics_d", "oebase_d"}
      links {"fltk_images_d", "fltk_gl_d", "fltk_d"}
--      links {"fltk_jpeg_d", "fltk_png_d", "fltk_z_d"}
      links {LibFtgl_d, LibFreetype_d, LibGLU, LibGL}
      links {"WS2_32", "WinMM", "ComCtl32", "Ole32", "ComDlg32", "Uuid", "Gdi32"}

-- Fox-based GUI example
project "mainFox1"
   kind "WindowedApp"
   targetname "mainFox1"
   targetdir "../../mainFox1"
   debugdir "../../mainFox1"
   files {
      "../../mainFox1/**.cpp",
      "../../mainFox1/**.h",
      "../../mainFox1/**.epp"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OE3rdPartyIncPath.."/fox-1.7" }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE", "HAVE_GL_H", "HAVE_GLU_H" }
   filter "configurations:Release*"
      links {"oesimulation", "oedafif", "oeinstruments"}
      links {"oegraphics", "oebase"}
      links {"fox-1.7"}
      links {LibFtgl, LibFreetype, LibGLU, LibGL}
      links {"WS2_32", "WinMM", "ComCtl32", "Gdi32", "mpr", "imm32"}
   filter "configurations:Debug*"
      links {"oesimulation_d", "oedafif_d", "oeinstruments_d"}
      links {"oegraphics_d", "oebase_d"}
      links {"fox-1.7_d"}
      links {LibFtgl_d, LibFreetype_d, LibGLU, LibGL}
      links {"WS2_32", "WinMM", "ComCtl32", "Gdi32", "mpr", "imm32"}

-- Fox-based GUI example
project "mainFox2"
   kind "WindowedApp"
   targetname "mainFox2"
   targetdir "../../mainFox2"
   debugdir "../../mainFox2"
   files {
      "../../mainFox2/**.cpp",
      "../../mainFox2/**.h",
      "../../mainFox2/**.epp"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OE3rdPartyIncPath.."/fox-1.7" }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE", "HAVE_GL_H", "HAVE_GLU_H" }
   filter "configurations:Release*"
      links {"oesimulation", "oedafif", "oeinstruments"}
      links {"oegraphics", "oebase"}
      links {"fox-1.7"}
      links {LibFtgl, LibFreetype, LibGLU, LibGL}
      links {"WS2_32", "WinMM", "ComCtl32", "Gdi32", "mpr", "imm32"}
   filter "configurations:Debug*"
      links {"oesimulation_d", "oedafif_d", "oeinstruments_d"}
      links {"oegraphics_d", "oebase_d"}
      links {"fox-1.7_d"}
      links {LibFtgl_d, LibFreetype_d, LibGLU, LibGL}
      links {"WS2_32", "WinMM", "ComCtl32", "Gdi32", "mpr", "imm32"}

-- Fox-based GUI example
project "mainFox3"
   kind "WindowedApp"
   targetname "mainFox3"
   targetdir "../../mainFox3"
   debugdir "../../mainFox3"
   files {
      "../../mainFox3/**.cpp",
      "../../mainFox3/**.h",
      "../../mainFox3/**.epp"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OE3rdPartyIncPath.."/fox-1.7" }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE", "HAVE_GL_H", "HAVE_GLU_H" }
   filter "configurations:Release*"
      links {"oesimulation", "oedafif", "oeinstruments"}
      links {"oegraphics", "oebase"}
      links {"fox-1.7"}
      links {LibFtgl, LibFreetype, LibGLU, LibGL}
      links {"WS2_32", "WinMM", "ComCtl32", "Gdi32", "mpr", "imm32"}
   filter "configurations:Debug*"
      links {"oesimulation_d", "oedafif_d", "oeinstruments_d"}
      links {"oegraphics_d", "oebase_d"}
      links {"fox-1.7_d"}
      links {LibFtgl_d, LibFreetype_d, LibGLU, LibGL}
      links {"WS2_32", "WinMM", "ComCtl32", "Gdi32", "mpr", "imm32"}


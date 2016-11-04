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
      "../../mainGlut/**.h*",
      "../../mainGlut/**.cpp",
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


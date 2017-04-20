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
      links {"oe_gui_glut", "oe_instruments", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_gui_glut_d", "oe_instruments_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {LibWindows}


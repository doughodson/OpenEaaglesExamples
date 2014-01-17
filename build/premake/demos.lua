--------------------------------------------------------
-- Demo applications
--------------------------------------------------------

-- demoEfis: demo of EFIS
project "demoEfis"
   -- base filename for compiled binary target
   targetname "demoEfis"
   targetdir "../../demoEfis"
   debugdir "../../demoEfis"
   files {
      "../../demoEfis/**.cpp",
      "../../demoEfis/**.h",
      "../../demoEfis/**.epp",
      "../../demoEfis/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Flight Display 1 demo
project "demoFlightDisplays1"
   targetname "demoFlightDisplays1"
   targetdir "../../demoFlightDisplays1"
   debugdir "../../demoFlightDisplays1"
   files {
      "../../demoFlightDisplays1/**.cpp",
      "../../demoFlightDisplays1/**.h",
      "../../demoFlightDisplays1/**.epp",
      "../../demoFlightDisplays1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Flight Display 2 demo
project "demoFlightDisplays2"
   targetname "demoFlightDisplays2"
   targetdir "../../demoFlightDisplays2"
   debugdir "../../demoFlightDisplays2"
   files {
      "../../demoFlightDisplays2/**.cpp",
      "../../demoFlightDisplays2/**.h",
      "../../demoFlightDisplays2/**.epp",
      "../../demoFlightDisplays2/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- demoInstruments
project "demoInstruments"
   targetname "demoInstruments"
   targetdir "../../demoInstruments"
   debugdir "../../demoInstruments"
   files {
      "../../demoInstruments/**.cpp",
      "../../demoInstruments/**.h",
      "../../demoInstruments/**.epp",
      "../../demoInstruments/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- demoSubDisplays
project "demoSubDisplays"
   targetname "demoSubDisplays"
   targetdir "../../demoSubDisplays"
   debugdir "../../demoSubDisplays"
   files {
      "../../demoSubDisplays/**.cpp",
      "../../demoSubDisplays/**.h",
      "../../demoSubDisplays/**.epp",
      "../../demoSubDisplays/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}


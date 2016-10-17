--------------------------------------------------------
-- Demo applications
--------------------------------------------------------

-- demoEfis: demo of EFIS
project "demoEfis"
   kind "WindowedApp"
   targetname "demoEfis"
   targetdir "../../demoEfis"
   debugdir "../../demoEfis"
   files {
      "../../demoEfis/**.h*",
      "../../demoEfis/**.cpp",
      "../../demoEfis/**.epp",
      "../../demoEfis/**.edl"
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

-- Flight Display 1 demo
project "demoFlightDisplays1"
   kind "WindowedApp"
   targetname "demoFlightDisplays1"
   targetdir "../../demoFlightDisplays1"
   debugdir "../../demoFlightDisplays1"
   files {
      "../../demoFlightDisplays1/**.h*",
      "../../demoFlightDisplays1/**.cpp",
      "../../demoFlightDisplays1/**.epp",
      "../../demoFlightDisplays1/**.edl"
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

-- Flight Display 2 demo
project "demoFlightDisplays2"
   kind "WindowedApp"
   targetname "demoFlightDisplays2"
   targetdir "../../demoFlightDisplays2"
   debugdir "../../demoFlightDisplays2"
   files {
      "../../demoFlightDisplays2/**.h*",
      "../../demoFlightDisplays2/**.cpp",
      "../../demoFlightDisplays2/**.epp",
      "../../demoFlightDisplays2/**.edl"
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

-- demoInstruments
project "demoInstruments"
   kind "WindowedApp"
   targetname "demoInstruments"
   targetdir "../../demoInstruments"
   debugdir "../../demoInstruments"
   files {
      "../../demoInstruments/**.h*",
      "../../demoInstruments/**.cpp",
      "../../demoInstruments/**.epp",
      "../../demoInstruments/**.edl"
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

-- demoSubDisplays
project "demoSubDisplays"
   kind "WindowedApp"
   targetname "demoSubDisplays"
   targetdir "../../demoSubDisplays"
   debugdir "../../demoSubDisplays"
   files {
      "../../demoSubDisplays/**.h*",
      "../../demoSubDisplays/**.cpp",
      "../../demoSubDisplays/**.epp",
      "../../demoSubDisplays/**.edl"
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


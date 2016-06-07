--------------------------------------------------------
-- Example applications
--------------------------------------------------------

-- Simple cockpit
project "mainCockpit"
   kind "ConsoleApp"
   targetname "mainCockpit"
   targetdir "../../mainCockpit"
   debugdir "../../mainCockpit"
   files {
      "../../mainCockpit/**.cpp",
      "../../mainCockpit/**.h",
      "../../mainCockpit/**.epp",
      "../../mainCockpit/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath, OEExamplesLibPath }
   links       { "libxPanel" }
   -- zeromq nethandlers
   defines { "ZMQ_STATIC" }
   links { "libxzmq" }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links { "oemodels", "JSBSim", "libzmq" }
      links { "oeotw", LibCigi }
      links { "oedis", "oerecorder", "oeiodevice" }
      links { "oesimulation", "oedafif", "oeterrain" }
      links { "oeglut", "oeinstruments", "oegraphics", "oebase" }
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL }
      links { "libprotobuf" }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links { "oemodels_d", "JSBSim_d", "libzmq_d" }
      links { "oeotw_d",  LibCigi_d }
      links { "oedis_d", "oerecorder_d", "oeiodevice_d" }
      links { "oesimulation_d", "oedafif_d", "oeterrain_d" }
      links { "oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d" }
      links { LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL }
      links { "libprotobuf_d" }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }

-- Ground Mapping Radar example
project "mainGndMapRdr"
   kind "ConsoleApp"
   targetname "mainGndMapRdr"
   targetdir "../../mainGndMapRdr"
   debugdir "../../mainGndMapRdr"
   files {
      "../../mainGndMapRdr/**.cpp",
      "../../mainGndMapRdr/**.h",
      "../../mainGndMapRdr/**.epp",
      "../../mainGndMapRdr/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oesimulation", "oedafif", "oeterrain"}
      links {"oeglut", "oeinstruments", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oesimulation_d", "oedafif_d", "oeterrain_d"}
      links {"oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- mainLaero example
project "mainLaero"
   kind "WindowedApp"
   targetname "mainLaero"
   targetdir "../../mainLaero"
   debugdir "../../mainLaero"
   files {
      "../../mainLaero/**.cpp",
      "../../mainLaero/**.h",
      "../../mainLaero/**.epp",
      "../../mainLaero/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   -- zeromq nethandlers
   defines { "ZMQ_STATIC" }
   links { "libxzmq" }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oemodels", "JSBSim", "libzmq" }
      links {"oedis", "oeiodevice"}
      links {"oesimulation", "oedafif", "oeterrain"}
      links {"oeglut", "oeinstruments", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oemodels_d", "JSBSim_d", "libzmq_d" }
      links {"oedis_d", "oeiodevice_d"}
      links {"oesimulation_d", "oedafif_d", "oeterrain_d"}
      links {"oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Non-RealTime 1 example
project "mainNonRT1"
   kind "ConsoleApp"
   targetname "mainNonRT1"
   targetdir "../../mainNonRT1"
   debugdir "../../mainNonRT1"
   files {
      "../../mainNonRT1/**.cpp",
      "../../mainNonRT1/**.h",
      "../../mainNonRT1/**.epp",
      "../../mainNonRT1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oemodels", "JSBSim"}
      links {"oeotw", LibCigi}
      links {"oedis" }
      links {"oesimulation", "oedafif", "oeterrain"}
      links {"oeglut", "oeinstruments", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oemodels_d", "JSBSim_d"}
      links {"oeotw_d", LibCigi_d}
      links {"oedis_d" }
      links {"oesimulation_d", "oedafif_d", "oeterrain_d"}
      links {"oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Puzzle 1 example
project "mainPuzzle1"
   targetname "mainPuzzle1"
   targetdir "../../mainPuzzle1"
   debugdir "../../mainPuzzle1"
   files {
      "../../mainPuzzle1/**.cpp",
      "../../mainPuzzle1/**.h",
      "../../mainPuzzle1/**.epp",
      "../../mainPuzzle1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oeglut", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oeglut_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Puzzle 2 example
project "mainPuzzle2"
   targetname "mainPuzzle2"
   targetdir "../../mainPuzzle2"
   debugdir "../../mainPuzzle2"
   files {
      "../../mainPuzzle2/**.cpp",
      "../../mainPuzzle2/**.h",
      "../../mainPuzzle2/**.epp",
      "../../mainPuzzle2/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oeglut", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oeglut_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

 -- simple Simulation 1 example
project "mainSim1"
   targetname "mainSim1"
   targetdir "../../mainSim1"
   debugdir "../../mainSim1"
   files {
      "../../mainSim1/**.cpp",
      "../../mainSim1/**.h",
      "../../mainSim1/**.epp",
      "../../mainSim1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   -- zeromq nethandlers
   defines { "ZMQ_STATIC" }
   links { "libxzmq" }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links { "oemodels", "JSBSim", "libzmq" }
      links { "oeotw", LibCigi }
      links { "oedis" }
      links { "oesimulation", "oedafif", "oeterrain" }
      links { "oeglut", "oeinstruments", "oegraphics", "oebase" }
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }
   filter "configurations:Debug*"
      links { "oemodels_d", "JSBSim_d", "libzmq_d" }
      links { "oeotw_d", LibCigi_d }
      links { "oedis_d" }
      links { "oesimulation_d", "oedafif_d", "oeterrain_d" }
      links { "oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d" }
      links { LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }

-- simple Simulation 2 example
project "mainSim2"
   targetname "mainSim2"
   targetdir "../../mainSim2"
   debugdir "../../mainSim2"
   files {
      "../../mainSim2/**.cpp",
      "../../mainSim2/**.h",
      "../../mainSim2/**.epp",
      "../../mainSim2/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   -- zeromq nethandlers
   defines { "ZMQ_STATIC" }
   links { "libxzmq" }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links { "oemodels", "JSBSim", "libzmq" }
      links { "oeotw", LibCigi}
      links { "oedis", "oeiodevice"}
      links { "oesimulation", "oedafif", "oeterrain"}
      links { "oeglut", "oeinstruments", "oegraphics", "oebase"}
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links { "Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links { "oemodels_d", "JSBSim_d", "libzmq_d" }
      links { "oeotw_d", LibCigi_d }
      links { "oedis_d", "oeiodevice_d" }
      links { "oesimulation_d", "oedafif_d", "oeterrain_d" }
      links { "oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d" }
      links { LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }

-- simple Simulation 3 example
project "mainSim3"
   targetname "mainSim3"
   targetdir "../../mainSim3"
   debugdir "../../mainSim3"
   files {
      "../../mainSim3/**.cpp",
      "../../mainSim3/**.h",
      "../../mainSim3/**.epp",
      "../../mainSim3/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   -- zeromq nethandlers
   defines { "ZMQ_STATIC" }
   links { "libxzmq" }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links { "oemodels", "JSBSim", "libzmq" }
      links { "oeotw", LibCigi }
      links { "oedis" }
      links { "oesimulation", "oedafif", "oeterrain" }
      links { "oeglut", "oeinstruments", "oegraphics", "oebase" }
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }
   filter "configurations:Debug*"
      links { "oemodels_d", "JSBSim_d", "libzmq_d" }
      links { "oeotw_d", LibCigi_d }
      links { "oedis_d" }
      links { "oesimulation_d", "oedafif_d", "oeterrain_d" }
      links { "oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d" }
      links { LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }

-- Terrain loading example
project "mainTerrain"
   targetname "mainTerrain"
   targetdir "../../mainTerrain"
   debugdir "../../mainTerrain"
   files {
      "../../mainTerrain/**.cpp",
      "../../mainTerrain/**.h",
      "../../mainTerrain/**.epp",
      "../../mainTerrain/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oeterrain"}
      links {"oeglut", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oeterrain_d"}
      links {"oeglut_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}


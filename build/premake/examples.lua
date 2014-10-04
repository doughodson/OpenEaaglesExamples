--------------------------------------------------------
-- Example applications
--------------------------------------------------------

-- Simple cockpit
project "mainCockpit"
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
   links { "libxZeroMQHandlers" }
   defines { "_CONSOLE" }
   configuration "Release"
      links { "oeDynamics", "JSBSim", "libzmq" }
      links { "oeOtw", LibCigi }
      links { "oeDis", "oeRecorder", "oeSensors", "oeIoDevice" }
      links { "oeSimulation", "oeDafif", "oeTerrain" }
      links { "oeGlut", "oeInstruments", "oeBasicGL", "oeBasic" }
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL }
      links { "libprotobuf" }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links { "oeDynamics_d", "JSBSim_d", "libzmq_d" }
      links { "oeOtw_d",  LibCigi_d }
      links { "oeDis_d", "oeRecorder_d", "oeSensors_d", "oeIoDevice_d" }
      links { "oeSimulation_d", "oeDafif_d", "oeTerrain_d" }
      links { "oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d" }
      links { LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL }
      links { "libprotobuf_d" }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }

-- OpenGL example
project "mainGL"
   targetname "mainGL"
   targetdir "../../mainGL"
   debugdir "../../mainGL"
   files {
      "../../mainGL/**.cpp",
      "../../mainGL/**.h",
      "../../mainGL/**.epp",
      "../../mainGL/**.edl"
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

-- Ground Mapping Radar example
project "mainGndMapRdr"
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
   configuration "Release"
      links {"oeSimulation", "oeDafif", "oeTerrain"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeSimulation_d", "oeDafif_d", "oeTerrain_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- mainIr example
project "mainIr"
   targetname "mainIr"
   targetdir "../../mainIr"
   debugdir "../../mainIr"
   files {
      "../../mainIr/**.cpp",
      "../../mainIr/**.h",
      "../../mainIr/**.epp",
      "../../mainIr/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oeDynamics", "JSBSim"}
      links {"oeOtw", LibCigi}
      links {"oeDis", "oeSensors"}
      links {"oeSimulation", "oeDafif", "oeTerrain"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeDynamics_d", "JSBSim_d"}
      links {"oeOtw_d", LibCigi_d}
      links {"oeDis_d", "oeSensors_d"}
      links {"oeSimulation_d", "oeDafif_d", "oeTerrain_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- mainLaero example
project "mainLaero"
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
   links { "libxZeroMQHandlers" }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oeDynamics", "JSBSim", "libzmq" }
      links {"oeDis", "oeSensors", "oeIoDevice"}
      links {"oeSimulation", "oeDafif", "oeTerrain"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeDynamics_d", "JSBSim_d", "libzmq_d" }
      links {"oeDis_d", "oeSensors_d", "oeIoDevice_d"}
      links {"oeSimulation_d", "oeDafif_d", "oeTerrain_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Non-RealTime 1 example
project "mainNonRT1"
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
   configuration "Release"
      links {"oeDynamics", "JSBSim"}
      links {"oeOtw", LibCigi}
      links {"oeDis", "oeSensors"}
      links {"oeSimulation", "oeDafif", "oeTerrain"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeDynamics_d", "JSBSim_d"}
      links {"oeOtw_d", LibCigi_d}
      links {"oeDis_d", "oeSensors_d"}
      links {"oeSimulation_d", "oeDafif_d", "oeTerrain_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
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
   configuration "Release"
      links {"oeGlut", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeBasicGL_d", "oeBasic_d"}
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
   configuration "Release"
      links {"oeGlut", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeBasicGL_d", "oeBasic_d"}
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
   links { "libxZeroMQHandlers" }
   defines { "_CONSOLE" }
   configuration "Release"
      links { "oeDynamics", "JSBSim", "libzmq" }
      links { "oeOtw", LibCigi }
      links { "oeDis", "oeSensors" }
      links { "oeSimulation", "oeDafif", "oeTerrain" }
      links { "oeGlut", "oeInstruments", "oeBasicGL", "oeBasic" }
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }
   configuration "Debug"
      links { "oeDynamics_d", "JSBSim_d", "libzmq_d" }
      links { "oeOtw_d", LibCigi_d }
      links { "oeDis_d", "oeSensors_d" }
      links { "oeSimulation_d", "oeDafif_d", "oeTerrain_d" }
      links { "oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d" }
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
   links { "libxZeroMQHandlers" }
   defines { "_CONSOLE" }
   configuration "Release"
      links { "oeDynamics", "JSBSim", "libzmq" }
      links { "oeOtw", LibCigi }
      links { "oeDis", "oeSensors" }
      links { "oeSimulation", "oeDafif", "oeTerrain" }
      links { "oeGlut", "oeInstruments", "oeBasicGL", "oeBasic" }
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }
   configuration "Debug"
      links { "oeDynamics_d", "JSBSim_d", "libzmq_d" }
      links { "oeOtw_d", LibCigi_d }
      links { "oeDis_d", "oeSensors_d" }
      links { "oeSimulation_d", "oeDafif_d", "oeTerrain_d" }
      links { "oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d" }
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
   links { "libxZeroMQHandlers" }
   defines { "_CONSOLE" }
   configuration "Release"
      links { "oeDynamics", "JSBSim", "libzmq" }
      links { "oeOtw", LibCigi}
      links { "oeDis", "oeSensors", "oeIoDevice"}
      links { "oeSimulation", "oeDafif", "oeTerrain"}
      links { "oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links { "Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links { "oeDynamics_d", "JSBSim_d", "libzmq_d" }
      links { "oeOtw_d", LibCigi_d }
      links { "oeDis_d", "oeSensors_d", "oeIoDevice_d" }
      links { "oeSimulation_d", "oeDafif_d", "oeTerrain_d" }
      links { "oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d" }
      links { LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }

-- simple Simulation 4 example
project "mainSim4"
   targetname "mainSim4"
   targetdir "../../mainSim4"
   debugdir "../../mainSim4"
   files {
      "../../mainSim4/**.cpp",
      "../../mainSim4/**.h",
      "../../mainSim4/**.epp",
      "../../mainSim4/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   -- zeromq nethandlers
   defines { "ZMQ_STATIC" }
   links { "libxZeroMQHandlers" }
   defines { "_CONSOLE" }
   configuration "Release"
      links { "oeDynamics", "JSBSim", "libzmq" }
      links { "oeOtw", LibCigi }
      links { "oeDis", "oeSensors" }
      links { "oeSimulation", "oeDafif", "oeTerrain" }
      links { "oeGlut", "oeInstruments", "oeBasicGL", "oeBasic" }
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }
   configuration "Debug"
      links { "oeDynamics_d", "JSBSim_d", "libzmq_d" }
      links { "oeOtw_d", LibCigi_d }
      links { "oeDis_d", "oeSensors_d" }
      links { "oeSimulation_d", "oeDafif_d", "oeTerrain_d" }
      links { "oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d" }
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
   configuration "Release"
      links {"oeTerrain"}
      links {"oeGlut", "oeBasicGL", "oeBasic"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeTerrain_d"}
      links {"oeGlut_d", "oeBasicGL_d", "oeBasic_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- mainUbf1
project "mainUbf1"
   targetname "mainUbf1"
   targetdir "../../mainUbf1"
   debugdir "../../mainUbf1"
   files {
      "../../mainUbf1/**.cpp",
      "../../mainUbf1/**.h",
      "../../mainUbf1/**.epp",
      "../../mainUbf1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath, OEExamplesLibPath }
   links { "libxBehaviors",  "libxPanel" }
   defines { "_CONSOLE" }
   configuration "Release"
      links { "oeDynamics", "JSBSim" }
      links { "oeOtw", LibCigi }
      links { "oeDis", "oeSensors", "oeIoDevice" }
      links { "oeSimulation", "oeDafif", "oeTerrain" }
      links { "oeGlut", "oeInstruments", "oeBasicGL", "oeBasic" }
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }
   configuration "Debug"
      links { "oeDynamics_d", "JSBSim_d" }
      links { "oeOtw_d", LibCigi_d }
      links { "oeDis_d", "oeSensors_d", "oeIoDevice_d" }
      links { "oeSimulation_d", "oeDafif_d", "oeTerrain_d" }
      links { "oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d" }
      links { LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }



--------------------------------------------------------
-- Test applications
--------------------------------------------------------

-- testEvents: test of event passing
project "testEvents"
   targetname "testEvents"
   targetdir "../../testEvents"
   debugdir "../../testEvents"
   files {
      "../../testEvents/**.cpp",
      "../../testEvents/**.h",
      "../../testEvents/**.epp",
      "../../testEvents/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oeglut", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeglut_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- testGraphics : test of basic graphics
project "testGraphics"
   targetname "testGraphics"
   targetdir "../../testGraphics"
   debugdir "../../testGraphics"
   files {
      "../../testGraphics/**.cpp",
      "../../testGraphics/**.h",
      "../../testGraphics/**.epp",
      "../../testGraphics/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oeglut", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeglut_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- testIoHandler: I/O handler test
project "testIoHandler"
   targetname "testIoHandler"
   targetdir "../../testIoHandler"
   debugdir "../../testIoHandler"
   files {
      "../../testIoHandler/**.cpp",
      "../../testIoHandler/**.h",
      "../../testIoHandler/**.epp",
      "../../testIoHandler/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oeiodevice", "oeglut", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeiodevice_d", "oeglut_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- testLinearSys: test of linear system components
project "testLinearSys"
   targetname "testLinearSys"
   targetdir "../../testLinearSys"
   debugdir "../../testLinearSys"
   files {
      "../../testLinearSys/**.cpp",
      "../../testLinearSys/**.h",
      "../../testLinearSys/**.epp",
      "../../testLinearSys/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oelinearsystem", "oebase"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oelinearsystem_d", "oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testMatrix
project "testMatrix"
   targetname "testMatrix"
   targetdir "../../testMatrix"
   debugdir "../../testMatrix"
   files {
      "../../testMatrix/**.cpp",
      "../../testMatrix/**.h",
      "../../testMatrix/**.epp",
      "../../testMatrix/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   configuration "Debug"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testNavigation
project "testNavigation"
   targetname "testNavigation"
   targetdir "../../testNavigation"
   debugdir "../../testNavigation"
   files {
      "../../testNavigation/**.cpp",
      "../../testNavigation/**.h",
      "../../testNavigation/**.epp",
      "../../testNavigation/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   configuration "Debug"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testNetHandler
project "testNetHandler"
   targetname "testNetHandler"
   targetdir "../../testNetHandler"
   debugdir "../../testNetHandler"
   files {
      "../../testNetHandler/**.cpp",
      "../../testNetHandler/**.h",
      "../../testNetHandler/**.epp",
      "../../testNetHandler/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   -- zeromq nethandlers
   defines { "ZMQ_STATIC" }
   links { "libxzmq" }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oebase", "libzmq" }
      links {"Ws2_32", "Winmm", "comctl32"}
   configuration "Debug"
      links {"oebase_d", "libzmq_d" }
      links {"Ws2_32", "Winmm", "comctl32"}

-- testRadar
project "testRadar"
   targetname "testRadar"
   targetdir "../../testRadar"
   debugdir "../../testRadar"
   files {
      "../../testRadar/**.cpp",
      "../../testRadar/**.h",
      "../../testRadar/**.epp",
      "../../testRadar/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oemodels", "JSBSim"}
      links {"oeotw", LibCigi}
      links {"oedis", "oeiodevice"}
      links {"oesimulation", "oedafif", "oeterrain"}
      links {"oeglut", "oeinstruments", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oemodels_d", "JSBSim_d"}
      links {"oeotw_d", LibCigi_d}
      links {"oedis_d", "oeiodevice_d"}
      links {"oesimulation_d", "oedafif_d", "oeterrain_d"}
      links {"oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- testRecordData
project "testRecordData"
   targetname "testRecordData"
   targetdir "../../testRecordData"
   debugdir "../../testRecordData"
   files {
      "../../testRecordData/**.cpp",
      "../../testRecordData/**.h",
      "../../testRecordData/**.epp",
      "../../testRecordData/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath, OEExamplesLibPath }
   links       { "libxrecorder", "libxpanel" }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oemodels", "JSBSim" }
      links {"oeotw", LibCigi }
      links {"oedis", "oerecorder", "oeiodevice" }
      links {"oesimulation", "oedafif", "oeterrain" }
      links {"oeglut", "oeinstruments", "oegraphics", "oebase" }
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"libprotobuf" }
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oemodels_d", "JSBSim_d" }
      links {"oeotw_d",  LibCigi_d }
      links {"oedis_d", "oerecorder_d", "oeiodevice_d" }
      links {"oesimulation_d", "oedafif_d", "oeterrain_d" }
      links {"oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d" }
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"libprotobuf_d" }
      links {"Ws2_32", "Winmm", "comctl32", "gdi32" }

-- testRecorderRead
project "testRecorderRead"
   targetname "testRecorderRead"
   targetdir "../../testRecorderRead"
   debugdir "../../testRecorderRead"
   files {
      "../../testRecorderRead/**.cpp",
      "../../testRecorderRead/**.h",
      "../../testRecorderRead/**.epp",
      "../../testRecorderRead/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath, OEExamplesLibPath }
   links       { "libxrecorder" }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oerecorder", "oesimulation", "oedafif", "oebase", "libprotobuf"}
      links {"Ws2_32", "Winmm", "comctl32"}
   configuration "Debug"
      links {"oerecorder_d", "oesimulation_d", "oedafif_d", "oebase_d", "libprotobuf_d" }
      links {"Ws2_32", "Winmm", "comctl32" }

-- testRecorderWrite
project "testRecorderWrite"
   targetname "testRecorderWrite"
   targetdir "../../testRecorderWrite"
   debugdir "../../testRecorderWrite"
   files {
      "../../testRecorderWrite/**.cpp",
      "../../testRecorderWrite/**.h",
      "../../testRecorderWrite/**.epp",
      "../../testRecorderWrite/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath, OEExamplesLibPath }
   links       { "libxrecorder" }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oerecorder", "oesimulation", "oedafif", "oebase", "libprotobuf"}
      links {"Ws2_32", "Winmm", "comctl32"}
   configuration "Debug"
      links {"oerecorder_d", "oesimulation_d", "oedafif_d", "oebase_d", "libprotobuf_d" }
      links {"Ws2_32", "Winmm", "comctl32" }

-- testRng
project "testRng"
   targetname "testRng"
   targetdir "../../testRng"
   debugdir "../../testRng"
   files {
      "../../testRng/**.cpp",
      "../../testRng/**.h",
      "../../testRng/**.epp",
      "../../testRng/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   configuration "Debug"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testStateMach
project "testStateMach"
   targetname "testStateMach"
   targetdir "../../testStateMach"
   debugdir "../../testStateMach"
   files {
      "../../testStateMach/**.cpp",
      "../../testStateMach/**.h",
      "../../testStateMach/**.epp",
      "../../testStateMach/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   configuration "Debug"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testTables
project "testTables"
   targetname "testTables"
   targetdir "../../testTables"
   debugdir "../../testTables"
   files {
      "../../testTables/**.cpp",
      "../../testTables/**.h",
      "../../testTables/**.epp",
      "../../testTables/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   configuration "Debug"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testTimer
project "testTimer"
   targetname "testTimer"
   targetdir "../../testTimer"
   debugdir "../../testTimer"
   files {
      "../../testTimer/*.cpp",
      "../../testTimer/*.h",
      "../../testTimer/*.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   configuration "Release"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   configuration "Debug"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}


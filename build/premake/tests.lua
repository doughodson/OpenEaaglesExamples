--------------------------------------------------------
-- Test applications
--------------------------------------------------------

-- test dafif library functionality
project "testDafif"
   kind "ConsoleApp"
   targetname "testDafif"
   targetdir "../../testDafif"
   debugdir "../../testDafif"
   files {
      "../../testDafif/**.h*",
      "../../testDafif/**.cpp",
      "../../testDafif/**.cxx",
      "../../testDafif/**.epp",
      "../../testDafif/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oedafif", "oebase"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oedafif_d", "oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testEvents: test of event passing
project "testEvents"
   kind "WindowedApp"
   targetname "testEvents"
   targetdir "../../testEvents"
   debugdir "../../testEvents"
   files {
      "../../testEvents/**.h*",
      "../../testEvents/**.cpp",
      "../../testEvents/**.epp",
      "../../testEvents/**.edl"
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

-- testGraphics : test of basic graphics
project "testGraphics"
   kind "WindowedApp"
   targetname "testGraphics"
   targetdir "../../testGraphics"
   debugdir "../../testGraphics"
   files {
      "../../testGraphics/**.h*",
      "../../testGraphics/**.cpp",
      "../../testGraphics/**.epp",
      "../../testGraphics/**.edl"
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

-- testInfrared: IR test
project "testInfrared"
   kind "ConsoleApp"
   targetname "testInfrared"
   targetdir "../../testInfrared"
   debugdir "../../testInfrared"
   files {
      "../../testInfrared/**.h*",
      "../../testInfrared/**.cpp",
      "../../testInfrared/**.epp",
      "../../testInfrared/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oemodels", "JSBSim"}
      links {"oeotw", LibCigi}
      links {"oedis", "oeinterop" }
      links {"oesimulation", "oeterrain"}
      links {"oeglut", "oeinstruments", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oemodels_d", "JSBSim_d"}
      links {"oeotw_d", LibCigi_d}
      links {"oedis_d", "oeinterop_d" }
      links {"oesimulation_d", "oeterrain_d"}
      links {"oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- testIoHandler: I/O handler test
project "testIoHandler"
   kind "WindowedApp"
   targetname "testIoHandler"
   targetdir "../../testIoHandler"
   debugdir "../../testIoHandler"
   files {
      "../../testIoHandler/**.h*",
      "../../testIoHandler/**.cpp",
      "../../testIoHandler/**.epp",
      "../../testIoHandler/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oeiodevice", "oeglut", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oeiodevice_d", "oeglut_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- testLinearSys: test of linear system components
project "testLinearSys"
   targetname "testLinearSys"
   targetdir "../../testLinearSys"
   debugdir "../../testLinearSys"
   files {
      "../../testLinearSys/**.h*",
      "../../testLinearSys/**.cpp",
      "../../testLinearSys/**.epp",
      "../../testLinearSys/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oelinearsystem", "oebase"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oelinearsystem_d", "oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testMatrix
project "testMatrix"
   targetname "testMatrix"
   targetdir "../../testMatrix"
   debugdir "../../testMatrix"
   files {
      "../../testMatrix/**.h*",
      "../../testMatrix/**.cpp",
      "../../testMatrix/**.epp",
      "../../testMatrix/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   filter "configurations:Debug*"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testMetaObject
project "testMetaObject"
   targetname "testMetaObject"
   targetdir "../../testMetaObject"
   debugdir "../../testMetaObject"
   files {
      "../../testMetaObject/**.h*",
      "../../testMetaObject/**.cpp",
      "../../testMetaObject/**.epp",
      "../../testMetaObject/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   filter "configurations:Debug*"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testNavigation
project "testNavigation"
   targetname "testNavigation"
   targetdir "../../testNavigation"
   debugdir "../../testNavigation"
   files {
      "../../testNavigation/**.h*",
      "../../testNavigation/**.cpp",
      "../../testNavigation/**.epp",
      "../../testNavigation/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   filter "configurations:Debug*"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testNetHandler
project "testNetHandler"
   targetname "testNetHandler"
   targetdir "../../testNetHandler"
   debugdir "../../testNetHandler"
   files {
      "../../testNetHandler/**.h*",
      "../../testNetHandler/**.cpp",
      "../../testNetHandler/**.epp",
      "../../testNetHandler/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   -- zeromq nethandlers
   defines { "ZMQ_STATIC" }
   links { "libxzmq" }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oebase", "libzmq" }
      links {"Ws2_32", "Winmm", "comctl32"}
   filter "configurations:Debug*"
      links {"oebase_d", "libzmq_d" }
      links {"Ws2_32", "Winmm", "comctl32"}

-- testRadar
project "testRadar"
   targetname "testRadar"
   targetdir "../../testRadar"
   debugdir "../../testRadar"
   files {
      "../../testRadar/**.h*",
      "../../testRadar/**.cpp",
      "../../testRadar/**.epp",
      "../../testRadar/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oemodels", "JSBSim"}
      links {"oeotw", LibCigi}
      links {"oedis", "oeinterop", "oeiodevice"}
      links {"oesimulation", "oeterrain"}
      links {"oeglut", "oeinstruments", "oegraphics", "oebase"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oemodels_d", "JSBSim_d"}
      links {"oeotw_d", LibCigi_d}
      links {"oedis_d", "oeinterop_d", "oeiodevice_d"}
      links {"oesimulation_d", "oeterrain_d"}
      links {"oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- testRecordData
project "testRecordData"
   targetname "testRecordData"
   targetdir "../../testRecordData"
   debugdir "../../testRecordData"
   files {
      "../../testRecordData/**.h*",
      "../../testRecordData/**.cpp",
      "../../testRecordData/**.epp",
      "../../testRecordData/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath, OEExamplesLibPath }
   links       { "libxrecorder", "libxpanel" }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oemodels", "JSBSim" }
      links {"oeotw", LibCigi }
      links {"oedis", "oeinterop", "oerecorder", "oeiodevice" }
      links {"oesimulation", "oeterrain" }
      links {"oeglut", "oeinstruments", "oegraphics", "oebase" }
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"libprotobuf" }
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   filter "configurations:Debug*"
      links {"oemodels_d", "JSBSim_d" }
      links {"oeotw_d",  LibCigi_d }
      links {"oedis_d", "oeinterop_d", "oerecorder_d", "oeiodevice_d" }
      links {"oesimulation_d", "oeterrain_d" }
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
      "../../testRecorderRead/**.h*",
      "../../testRecorderRead/**.cpp",
      "../../testRecorderRead/**.epp",
      "../../testRecorderRead/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath, OEExamplesLibPath }
   links       { "libxrecorder" }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oemodels", "JSBSim" }
      links {"oerecorder", "oesimulation", "oebase", "libprotobuf"}
      links {"Ws2_32", "Winmm", "comctl32"}
   filter "configurations:Debug*"
      links {"oemodels_d", "JSBSim_d" }
      links {"oerecorder_d", "oesimulation_d", "oebase_d", "libprotobuf_d" }
      links {"Ws2_32", "Winmm", "comctl32" }

-- testRecorderWrite
project "testRecorderWrite"
   targetname "testRecorderWrite"
   targetdir "../../testRecorderWrite"
   debugdir "../../testRecorderWrite"
   files {
      "../../testRecorderWrite/**.h*",
      "../../testRecorderWrite/**.cpp",
      "../../testRecorderWrite/**.epp",
      "../../testRecorderWrite/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath, OEExamplesLibPath }
   links       { "libxrecorder" }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oemodels", "JSBSim" }
      links {"oerecorder", "oesimulation", "oebase", "libprotobuf"}
      links {"Ws2_32", "Winmm", "comctl32"}
   filter "configurations:Debug*"
      links {"oemodels_d", "JSBSim_d" }
      links {"oerecorder_d", "oesimulation_d", "oebase_d", "libprotobuf_d" }
      links {"Ws2_32", "Winmm", "comctl32" }

-- testRng
project "testRng"
   targetname "testRng"
   targetdir "../../testRng"
   debugdir "../../testRng"
   files {
      "../../testRng/**.h*",
      "../../testRng/**.cpp",
      "../../testRng/**.epp",
      "../../testRng/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   filter "configurations:Debug*"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testStateMach
project "testStateMach"
   targetname "testStateMach"
   targetdir "../../testStateMach"
   debugdir "../../testStateMach"
   files {
      "../../testStateMach/**.h*",
      "../../testStateMach/**.cpp",
      "../../testStateMach/**.epp",
      "../../testStateMach/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   filter "configurations:Debug*"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testTables
project "testTables"
   targetname "testTables"
   targetdir "../../testTables"
   debugdir "../../testTables"
   files {
      "../../testTables/**.h*",
      "../../testTables/**.cpp",
      "../../testTables/**.epp",
      "../../testTables/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   filter "configurations:Debug*"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testTemplates
project "testTemplates"
   targetname "testTemplates"
   targetdir "../../testTemplates"
   debugdir "../../testTemplates"
   files {
      "../../testTemplates/**.h*",
      "../../testTemplates/**.cpp",
      "../../testTemplates/**.epp",
      "../../testTemplates/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   filter "configurations:Debug*"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testTimer
project "testTimer"
   targetname "testTimer"
   targetdir "../../testTimer"
   debugdir "../../testTimer"
   files {
      "../../testTimer/*.h*",
      "../../testTimer/*.cpp",
      "../../testTimer/*.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oebase"}
      links {"Ws2_32", "Winmm", "comctl32"}
   filter "configurations:Debug*"
      links {"oebase_d"}
      links {"Ws2_32", "Winmm", "comctl32"}


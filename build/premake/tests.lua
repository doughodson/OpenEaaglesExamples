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
      links {"oe_models", "oe_simulation", "oe_terrain", "oe_dafif", "oe_base"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_models_d", "oe_simulation_d", "oe_terrain_d", "oe_dafif_d", "oe_base_d"}
      links {LibWindows}

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
      links {"oe_gui_glut", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_gui_glut_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {LibWindows}

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
      links {"oe_gui_glut", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_gui_glut_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {LibWindows}

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
      links {"oe_models", "JSBSim"}
      links {"oe_otw", LibCigi}
      links {"oe_interop_dis", "oe_interop" }
      links {"oe_simulation", "oe_terrain"}
      links {"oe_gui_glut", "oe_instruments", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_models_d", "JSBSim_d"}
      links {"oe_otw_d", LibCigi_d}
      links {"oe_interop_dis_d", "oe_interop_d" }
      links {"oe_simulation_d", "oe_terrain_d"}
      links {"oe_gui_glut_d", "oe_instruments_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {LibWindows}

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
      links {"oe_iodevice", "oe_gui_glut", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_iodevice_d", "oe_gui_glut_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {LibWindows}

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
      links {"oe_linearsystem", "oe_base"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_linearsystem_d", "oe_base_d"}
      links {LibWindows}

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
      links {"oe_base"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_base_d"}
      links {LibWindows}

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
      links {"oe_base"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_base_d"}
      links {LibWindows}

-- test navigation utility functions
project "testNavUtils"
   targetname "testNavUtils"
   targetdir "../../testNavUtils"
   debugdir "../../testNavUtils"
   files {
      "../../testNavUtils/**.h*",
      "../../testNavUtils/**.cpp",
      "../../testNavUtils/**.epp",
      "../../testNavUtils/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oe_base"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_base_d"}
      links {LibWindows}

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
      links {"oe_base", "libzmq" }
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_base_d", "libzmq_d" }
      links {LibWindows}

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
      links {"oe_models", "JSBSim"}
      links {"oe_otw", LibCigi}
      links {"oe_interop_dis", "oe_interop", "oe_iodevice"}
      links {"oe_simulation", "oe_terrain"}
      links {"oe_gui_glut", "oe_instruments", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_models_d", "JSBSim_d"}
      links {"oe_otw_d", LibCigi_d}
      links {"oe_interop_dis_d", "oe_interop_d", "oe_iodevice_d"}
      links {"oe_simulation_d", "oe_terrain_d"}
      links {"oe_gui_glut_d", "oe_instruments_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {LibWindows}

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
      links {"oe_models", "JSBSim" }
      links {"oe_otw", LibCigi }
      links {"oe_interop_dis", "oe_interop", "oe_recorder", "oe_iodevice" }
      links {"oe_simulation", "oe_terrain" }
      links {"oe_gui_glut", "oe_instruments", "oe_graphics", "oe_base" }
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"libprotobuf" }
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_models_d", "JSBSim_d" }
      links {"oe_otw_d",  LibCigi_d }
      links {"oe_interop_dis_d", "oe_interop_d", "oe_recorder_d", "oe_iodevice_d" }
      links {"oe_simulation_d", "oe_terrain_d" }
      links {"oe_gui_glut_d", "oe_instruments_d", "oe_graphics_d", "oe_base_d" }
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"libprotobuf_d" }
      links {LibWindows}

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
      links {"oe_models", "JSBSim" }
      links {"oe_recorder", "oe_simulation", "oe_base", "libprotobuf"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_models_d", "JSBSim_d" }
      links {"oe_recorder_d", "oe_simulation_d", "oe_base_d", "libprotobuf_d" }
      links {LibWindows}

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
      links {"oe_models", "JSBSim" }
      links {"oe_recorder", "oe_simulation", "oe_base", "libprotobuf"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_models_d", "JSBSim_d" }
      links {"oe_recorder_d", "oe_simulation_d", "oe_base_d", "libprotobuf_d" }
      links {LibWindows}

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
      links {"oe_base"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_base_d"}
      links {LibWindows}

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
      links {"oe_base"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_base_d"}
      links {LibWindows}

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
      links {"oe_base"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_base_d"}
      links {LibWindows}

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
      links {"oe_base"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_base_d"}
      links {LibWindows}

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
      links {"oe_base"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_base_d"}
      links {LibWindows}


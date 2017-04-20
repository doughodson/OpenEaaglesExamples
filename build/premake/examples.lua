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
      "../../mainCockpit/**.h*",
      "../../mainCockpit/**.cpp",
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
      links {"oe_models", "JSBSim", "libzmq"}
      links {"oe_otw", LibCigi}
      links {"oe_interop_dis", "oe_interop", "oe_recorder", "oe_iodevice"}
      links {"oe_simulation", "oe_terrain"}
      links {"oe_gui_glut", "oe_instruments", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {"libprotobuf"}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_models_d", "JSBSim_d", "libzmq_d"}
      links {"oe_otw_d",  LibCigi_d}
      links {"oe_interop_dis_d", "oe_interop_d", "oe_recorder_d", "oe_iodevice_d"}
      links {"oe_simulation_d", "oe_terrain_d"}
      links {"oe_gui_glut_d", "oe_instruments_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {"libprotobuf_d" }
      links {LibWindows}

-- Ground Mapping Radar example
project "mainGndMapRdr"
   kind "ConsoleApp"
   targetname "mainGndMapRdr"
   targetdir "../../mainGndMapRdr"
   debugdir "../../mainGndMapRdr"
   files {
      "../../mainGndMapRdr/**.h*",
      "../../mainGndMapRdr/**.cpp",
      "../../mainGndMapRdr/**.epp",
      "../../mainGndMapRdr/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oe_models", "oe_simulation", "JSBSim", "oe_terrain"}
      links {"oe_gui_glut", "oe_instruments", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_models_d", "oe_simulation_d", "JSBSim_d", "oe_terrain_d"}
      links {"oe_gui_glut_d", "oe_instruments_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {LibWindows}

-- mainLaero example
project "mainLaero"
   kind "ConsoleApp"
   targetname "mainLaero"
   targetdir "../../mainLaero"
   debugdir "../../mainLaero"
   files {
      "../../mainLaero/**.h*",
      "../../mainLaero/**.cpp",
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
      links {"oe_models", "JSBSim", "libzmq" }
      links {"oe_interop_dis", "oe_interop", "oe_iodevice"}
      links {"oe_simulation", "oe_terrain"}
      links {"oe_gui_glut", "oe_instruments", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_models_d", "JSBSim_d", "libzmq_d" }
      links {"oe_interop_dis_d", "oe_interop_d", "oe_iodevice_d"}
      links {"oe_simulation_d", "oe_terrain_d"}
      links {"oe_gui_glut_d", "oe_instruments_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {LibWindows}

-- Non-RealTime 1 example
project "mainNonRT1"
   kind "ConsoleApp"
   targetname "mainNonRT1"
   targetdir "../../mainNonRT1"
   debugdir "../../mainNonRT1"
   files {
      "../../mainNonRT1/**.h*",
      "../../mainNonRT1/**.cpp",
      "../../mainNonRT1/**.epp",
      "../../mainNonRT1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oe_models", "JSBSim"}
      links {"oe_otw", LibCigi}
      links {"oe_simulation", "oe_terrain"}
      links {"oe_gui_glut", "oe_instruments", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_models_d", "JSBSim_d"}
      links {"oe_otw_d", LibCigi_d}
      links {"oe_simulation_d", "oe_terrain_d"}
      links {"oe_gui_glut_d", "oe_instruments_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {LibWindows}

-- Puzzle 1 example
project "mainPuzzle1"
   targetname "mainPuzzle1"
   targetdir "../../mainPuzzle1"
   debugdir "../../mainPuzzle1"
   files {
      "../../mainPuzzle1/**.h*",
      "../../mainPuzzle1/**.cpp",
      "../../mainPuzzle1/**.epp",
      "../../mainPuzzle1/**.edl"
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

-- Puzzle 2 example
project "mainPuzzle2"
   targetname "mainPuzzle2"
   targetdir "../../mainPuzzle2"
   debugdir "../../mainPuzzle2"
   files {
      "../../mainPuzzle2/**.h*",
      "../../mainPuzzle2/**.cpp",
      "../../mainPuzzle2/**.epp",
      "../../mainPuzzle2/**.edl"
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

 -- simple Simulation 1 example
project "mainSim1"
   targetname "mainSim1"
   targetdir "../../mainSim1"
   debugdir "../../mainSim1"
   files {
      "../../mainSim1/**.h*",
      "../../mainSim1/**.cpp",
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
      links {"oe_models", "JSBSim", "libzmq"}
      links {"oe_otw", LibCigi}
      links {"oe_interop_dis", "oe_interop"}
      links {"oe_simulation", "oe_terrain"}
      links {"oe_gui_glut", "oe_instruments", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_models_d", "JSBSim_d", "libzmq_d"}
      links {"oe_otw_d", LibCigi_d}
      links {"oe_interop_dis_d", "oe_interop_d"}
      links {"oe_simulation_d", "oe_terrain_d"}
      links {"oe_gui_glut_d", "oe_instruments_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {LibWindows}

-- simple Simulation 2 example
project "mainSim2"
   targetname "mainSim2"
   targetdir "../../mainSim2"
   debugdir "../../mainSim2"
   files {
      "../../mainSim2/**.h*",
      "../../mainSim2/**.cpp",
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
      links {"oe_models", "JSBSim", "libzmq"}
      links {"oe_otw", LibCigi}
      links {"oe_interop_dis", "oe_interop", "oe_iodevice"}
      links {"oe_simulation", "oe_terrain"}
      links {"oe_gui_glut", "oe_instruments", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_models_d", "JSBSim_d", "libzmq_d"}
      links {"oe_otw_d", LibCigi_d}
      links {"oe_interop_dis_d", "oe_interop_d", "oe_iodevice_d"}
      links {"oe_simulation_d", "oe_terrain_d"}
      links {"oe_gui_glut_d", "oe_instruments_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {LibWindows}

-- simple Simulation 3 example
project "mainSim3"
   targetname "mainSim3"
   targetdir "../../mainSim3"
   debugdir "../../mainSim3"
   files {
      "../../mainSim3/**.h*",
      "../../mainSim3/**.cpp",
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
      links { "oe_models", "JSBSim", "libzmq" }
      links { "oe_otw", LibCigi }
      links { "oe_interop_dis", "oe_interop", LibCigi }
      links { "oe_simulation", "oe_terrain" }
      links { "oe_gui_glut", "oe_instruments", "oe_graphics", "oe_base" }
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL }
      links { LibWindows }
   filter "configurations:Debug*"
      links { "oe_models_d", "JSBSim_d", "libzmq_d" }
      links { "oe_otw_d", LibCigi_d }
      links { "oe_interop_dis_d", "oe_interop_d" }
      links { "oe_simulation_d", "oe_terrain_d" }
      links { "oe_gui_glut_d", "oe_instruments_d", "oe_graphics_d", "oe_base_d" }
      links { LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL }
      links { LibWindows }

-- Terrain loading example
project "mainTerrain"
   targetname "mainTerrain"
   targetdir "../../mainTerrain"
   debugdir "../../mainTerrain"
   files {
      "../../mainTerrain/**.h*",
      "../../mainTerrain/**.cpp",
      "../../mainTerrain/**.epp",
      "../../mainTerrain/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oe_terrain", "oe_simulation"}
      links {"oe_gui_glut", "oe_graphics", "oe_base"}
      links {LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL}
      links {LibWindows}
   filter "configurations:Debug*"
      links {"oe_terrain_d", "oe_simulation_d"}
      links {"oe_gui_glut_d", "oe_graphics_d", "oe_base_d"}
      links {LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL}
      links {LibWindows}

-- mainUbf1
project "mainUbf1"
   targetname "mainUbf1"
   targetdir "../../mainUbf1"
   debugdir "../../mainUbf1"
   files {
      "../../mainUbf1/**.h*",
      "../../mainUbf1/**.cpp",
      "../../mainUbf1/**.epp",
      "../../mainUbf1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath, OEExamplesLibPath }
   links { "libxbehaviors",  "libxpanel" }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links { "oe_models", "JSBSim" }
      links { "oe_otw", LibCigi }
      links { "oe_interop_dis", "oe_interop", "oe_iodevice" }
      links { "oe_simulation", "oe_terrain" }
      links { "oe_gui_glut", "oe_instruments", "oe_graphics", "oe_base" }
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL }
      links { LibWindows }
   filter "configurations:Debug*"
      links { "oe_models_d", "JSBSim_d" }
      links { "oe_otw_d", LibCigi_d }
      links { "oe_interop_dis_d", "oe_interop_d", "oe_iodevice_d" }
      links { "oe_simulation_d", "oe_terrain_d" }
      links { "oe_gui_glut_d", "oe_instruments_d", "oe_graphics_d", "oe_base_d" }
      links { LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL }
      links { LibWindows }

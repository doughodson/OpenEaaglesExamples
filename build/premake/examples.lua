
--------------------------------------------------------
-- Example applications
--------------------------------------------------------

-- mainEfis: example EFIS
project "mainEfis"
   -- base filename for compiled binary target
   targetname "mainEfis"
   targetdir "../../mainEfis"
   files {
      "../../mainEfis/**.cpp",
      "../../mainEfis/**.h",
      "../../mainEfis/**.epp",
      "../../mainEfis/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Flight Display 1 example
project "mainfd1"
   targetname "mainfd1"
   targetdir "../../mainfd1"
   files {
      "../../mainfd1/**.cpp",
      "../../mainfd1/**.h",
      "../../mainfd1/**.epp",
      "../../mainfd1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Flight Display 2 example
project "mainfd2"
   targetname "mainfd2"
   targetdir "../../mainfd2"
   files {
      "../../mainfd2/**.cpp",
      "../../mainfd2/**.h",
      "../../mainfd2/**.epp",
      "../../mainfd2/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- OpenGL example
project "mainGL"
   targetname "mainGL"
   targetdir "../../mainGL"
   files {
      "../../mainGL/**.cpp",
      "../../mainGL/**.h",
      "../../mainGL/**.epp",
      "../../mainGL/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Ground Mapping Radar example
project "mainGndMapRdr"
   targetname "mainGndMapRdr"
   targetdir "../../mainGndMapRdr"
   files {
      "../../mainGndMapRdr/**.cpp",
      "../../mainGndMapRdr/**.h",
      "../../mainGndMapRdr/**.epp",
      "../../mainGndMapRdr/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeSimulation", "oeDafif", "oeTerrain"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeSimulation_d", "oeDafif_d", "oeTerrain_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- mainIr example
project "mainIr"
   targetname "mainIr"
   targetdir "../../mainIr"
   files {
      "../../mainIr/**.cpp",
      "../../mainIr/**.h",
      "../../mainIr/**.epp",
      "../../mainIr/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeVehicles", "oeDis", "oeOtw", "oeSensors"}
      links {"oeSimulation", "oeDafif", "oeTerrain"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"jsbsim", "ccl_lib"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeVehicles_d", "oeDis_d", "oeOtw_d", "oeSensors_d"}
      links {"oeSimulation_d", "oeDafif_d", "oeTerrain_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"jsbsim_d", "ccl_lib_d"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Non-RealTime 1 example
project "mainNonRT1"
   targetname "mainNonRT1"
   targetdir "../../mainNonRT1"
   files {
      "../../mainNonRT1/**.cpp",
      "../../mainNonRT1/**.h",
      "../../mainNonRT1/**.epp",
      "../../mainNonRT1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeVehicles", "oeSensors", "oeSimulation"}
      links {"oeDafif", "oeBasic"}
      links {"jsbsim"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeVehicles_d", "oeSensors_d", "oeSimulation_d"}
      links {"oeDafif_d", "oeBasic_d"}
      links {"jsbsim_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Puzzle 1 example
project "mainPuzzle1"
   targetname "mainPuzzle1"
   targetdir "../../mainPuzzle1"
   files {
      "../../mainPuzzle1/**.cpp",
      "../../mainPuzzle1/**.h",
      "../../mainPuzzle1/**.epp",
      "../../mainPuzzle1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeGlut", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Puzzle 2 example
project "mainPuzzle2"
   targetname "mainPuzzle2"
   targetdir "../../mainPuzzle2"
   files {
      "../../mainPuzzle2/**.cpp",
      "../../mainPuzzle2/**.h",
      "../../mainPuzzle2/**.epp",
      "../../mainPuzzle2/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeGlut", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

 -- simple Simulation 1 example
project "mainSim1"
   targetname "mainSim1"
   targetdir "../../mainSim1"
   files {
      "../../mainSim1/**.cpp",
      "../../mainSim1/**.h",
      "../../mainSim1/**.epp",
      "../../mainSim1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeVehicles", "oeDis", "oeOtw", "oeSensors"}
      links {"oeSimulation", "oeDafif", "oeTerrain"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"jsbsim", "ccl_lib"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeVehicles_d", "oeDis_d", "oeOtw_d", "oeSensors_d"}
      links {"oeSimulation_d", "oeDafif_d", "oeTerrain_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"jsbsim_d", "ccl_lib_d"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- simple Simulation 2 example
project "mainSim2"
   targetname "mainSim2"
   targetdir "../../mainSim2"
   files {
      "../../mainSim2/**.cpp",
      "../../mainSim2/**.h",
      "../../mainSim2/**.epp",
      "../../mainSim2/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeVehicles", "oeDis", "oeOtw", "oeSensors"}
      links {"oeSimulation", "oeDafif", "oeTerrain"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"jsbsim", "ccl_lib"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeVehicles_d", "oeDis_d", "oeOtw_d", "oeSensors_d"}
      links {"oeSimulation_d", "oeDafif_d", "oeTerrain_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"jsbsim_d", "ccl_lib_d"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- simple Simulation 3 example
project "mainSim3"
   targetname "mainSim3"
   targetdir "../../mainSim3"
   files {
      "../../mainSim3/**.cpp",
      "../../mainSim3/**.h",
      "../../mainSim3/**.epp",
      "../../mainSim3/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeVehicles", "oeDis", "oeOtw", "oeSensors", "oeIoDevice"}
      links {"oeSimulation", "oeDafif", "oeTerrain"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"jsbsim", "ccl_lib"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeVehicles_d", "oeDis_d", "oeOtw_d", "oeSensors_d", "oeIoDevice_d"}
      links {"oeSimulation_d", "oeDafif_d", "oeTerrain_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"jsbsim_d", "ccl_lib_d"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- simple Simulation 4 example
project "mainSim4"
   targetname "mainSim4"
   targetdir "../../mainSim4"
   files {
      "../../mainSim4/**.cpp",
      "../../mainSim4/**.h",
      "../../mainSim4/**.epp",
      "../../mainSim4/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeVehicles", "oeDis", "oeOtw", "oeSensors"}
      links {"oeSimulation", "oeDafif", "oeTerrain"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"jsbsim", "ccl_lib"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeVehicles_d", "oeDis_d", "oeOtw_d", "oeSensors_d"}
      links {"oeSimulation_d", "oeDafif_d", "oeTerrain_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"jsbsim_d", "ccl_lib_d"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Terrain loading example
project "mainTerrain"
   targetname "mainTerrain"
   targetdir "../../mainTerrain"
   files {
      "../../mainTerrain/**.cpp",
      "../../mainTerrain/**.h",
      "../../mainTerrain/**.epp",
      "../../mainTerrain/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeTerrain"}
      links {"oeGlut", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeTerrain_d"}
      links {"oeGlut_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- Vmap example
project "mainVmap"
   targetname "mainVmap"
   targetdir "../../mainVmap"
   files {
      "../../mainVmap/**.cpp",
      "../../mainVmap/**.h",
      "../../mainVmap/**.epp",
      "../../mainVmap/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oemaps"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oemaps_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}


-- mainw : basic graphics example
project "mainw"
   targetname "mainw"
   targetdir "../../mainw"
   files {
      "../../mainw/**.cpp",
      "../../mainw/**.h",
      "../../mainw/**.epp",
      "../../mainw/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeGlut", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- mainx9
project "mainx9"
   targetname "mainx9"
   targetdir "../../mainx9"
   files {
      "../../mainx9/**.cpp",
      "../../mainx9/**.h",
      "../../mainx9/**.epp",
      "../../mainx9/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeVehicles", "oeDis", "oeOtw", "oeSensors", "oeIoDevice"}
      links {"oeSimulation", "oeDafif", "oeTerrain"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"jsbsim", "ccl_lib"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeVehicles_d", "oeDis_d", "oeOtw_d", "oeSensors_d", "oeIoDevice_d"}
      links {"oeSimulation_d", "oeDafif_d", "oeTerrain_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"jsbsim_d", "ccl_lib_d"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- mainy1
project "mainy1"
   targetname "mainy1"
   targetdir "../../mainy1"
   files {
      "../../mainy1/**.cpp",
      "../../mainy1/**.h",
      "../../mainy1/**.epp",
      "../../mainy1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeVehicles", "oeDis", "oeOtw", "oeSensors", "oeIoDevice"}
      links {"oeSimulation", "oeDafif", "oeTerrain"}
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"jsbsim", "ccl_lib"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeVehicles_d", "oeDis_d", "oeOtw_d", "oeSensors_d", "oeIoDevice_d"}
      links {"oeSimulation_d", "oeDafif_d", "oeTerrain_d"}
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"jsbsim_d", "ccl_lib_d"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- mainz1
project "mainz1"
   targetname "mainz1"
   targetdir "../../mainz1"
   files {
      "../../mainz1/**.cpp",
      "../../mainz1/**.h",
      "../../mainz1/**.epp",
      "../../mainz1/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- mainz2
project "mainz2"
   targetname "mainz2"
   targetdir "../../mainz2"
   files {
      "../../mainz2/**.cpp",
      "../../mainz2/**.h",
      "../../mainz2/**.epp",
      "../../mainz2/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeGlut", "oeInstruments", "oeBasicGL", "oeBasic"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
   configuration "Debug"
      links {"oeGlut_d", "oeInstruments_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}


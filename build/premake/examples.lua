
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
      "../../mainEfis/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oeglut"}
      links {"ftgl", "freetype2", "freeglut" }
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oeglut_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d" }

-- Flight Display 1 example
project "mainfd1"
   targetname "mainfd1"
   targetdir "../../mainfd1"
   files {
      "../../mainfd1/**.cpp",
      "../../mainfd1/**.h",
      "../../mainfd1/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oeglut" }
      links {"ftgl", "freetype2", "freeglut" }
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oeglut_d" }
      links {"ftgl_d", "freetype2_d", "freeglut_d" }

-- Flight Display 2 example
project "mainfd2"
   targetname "mainfd2"
   targetdir "../../mainfd2"
   files {
      "../../mainfd2/**.cpp",
      "../../mainfd2/**.h",
      "../../mainfd2/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oeglut" }
      links {"ftgl", "freetype2", "freeglut" }
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oeglut_d" }
      links {"ftgl_d", "freetype2_d", "freeglut_d" }

-- openGL example
project "mainGL"
   targetname "mainGL"
   targetdir "../../mainGL"
   files {
      "../../mainGL/**.cpp",
      "../../mainGL/**.h",
      "../../mainGL/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
    }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oeglut" }
      links {"ftgl", "freetype2", "freeglut" }
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oeglut_d" }
      links {"ftgl_d", "freetype2_d", "freeglut_d" }

-- Ground Mapping Radar example
project "mainGndMapRdr"
   targetname "mainGndMapRdr"
   targetdir "../../mainGndMapRdr"
   files {
      "../../mainGndMapRdr/**.cpp",
      "../../mainGndMapRdr/**.h",
      "../../mainGndMapRdr/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oeglut"}
      links {"oeterrain", "oesimulation", "oedafif" }
      links {"ftgl", "freetype2", "freeglut" }
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oeglut_d"}
      links {"oeterrain_d", "oesimulation_d", "oedafif_d" }
      links {"ftgl_d", "freetype2_d", "freeglut_d" }

-- mainIr example
project "mainIr"
   targetname "mainIr"
   targetdir "../../mainIr"
   files {
      "../../mainIr/**.cpp",
      "../../mainIr/**.h",
      "../../mainIr/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oeglut"}
      links {"oeiodevice", "oesimulation", "oesensors"}
      links {"oevehicles", "oedis", "oedafif", "oeotw"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"jsbsim", "ccl_lib"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oeglut_d"}
      links {"oeiodevice_d", "oesimulation_d", "oesensors_d"}
      links {"oevehicles_d", "oedis_d", "oedafif_d", "oeotw_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"jsbsim_d", "ccl_lib_d"}

-- Non-RealTime 1 example
project "mainNonRT1"
   targetname "mainNonRT1"
   targetdir "../../mainNonRT1"
   files {
      "../../mainNonRT1/**.cpp",
      "../../mainNonRT1/**.h",
      "../../mainNonRT1/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oesimulation", "oesensors"}
      links {"oevehicles", "oedafif" }
      links {"jsbsim"}
   configuration "Debug"
      links {"oebasic_d", "oesimulation_d", "oesensors_d"}
      links {"oevehicles_d", "oedafif_d" }
      links {"jsbsim_d"}

-- Puzzle 1 example
project "mainPuzzle1"
   targetname "mainPuzzle1"
   targetdir "../../mainPuzzle1"
   files {
      "../../mainPuzzle1/**.cpp",
      "../../mainPuzzle1/**.h",
      "../../mainPuzzle1/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeglut"}
      links {"ftgl", "freetype2", "freeglut"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeglut_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}

-- Puzzle 2 example
project "mainPuzzle2"
   targetname "mainPuzzle2"
   targetdir "../../mainPuzzle2"
   files {
      "../../mainPuzzle2/**.cpp",
      "../../mainPuzzle2/**.h",
      "../../mainPuzzle2/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeglut"}
      links {"ftgl", "freetype2", "freeglut"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeglut_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}

-- simple Simulation 1 example
project "mainSim1"
   targetname "mainSim1"
   targetdir "../../mainSim1"
   files {
      "../../mainSim1/**.cpp",
      "../../mainSim1/**.h",
      "../../mainSim1/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oesimulation", "oesensors"}
      links {"oevehicles", "oedis", "oedafif", "oeotw"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"jsbsim", "ccl_lib"}
   configuration "Debug"
      links {"oebasic_d", "oesimulation_d", "oesensors_d"}
      links {"oevehicles_d", "oedis_d", "oedafif_d", "oeotw_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"jsbsim_d", "ccl_lib_d"}

-- simple Simulation 2 example
project "mainSim2"
   targetname "mainSim2"
   targetdir "../../mainSim2"
   files {
      "../../mainSim2/**.cpp",
      "../../mainSim2/**.h",
      "../../mainSim2/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oesimulation", "oesensors"}
      links {"oevehicles", "oedis", "oedafif", "oeotw"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"jsbsim", "ccl_lib"}
   configuration "Debug"
      links {"oebasic_d", "oesimulation_d", "oesensors_d"}
      links {"oevehicles_d", "oedis_d", "oedafif_d", "oeotw_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"jsbsim_d", "ccl_lib_d"}

-- simple Simulation 3 example
project "mainSim3"
   targetname "mainSim3"
   targetdir "../../mainSim3"
   files {
      "../../mainSim3/**.cpp",
      "../../mainSim3/**.h",
      "../../mainSim3/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oeglut"}
      links {"oeioDevice", "oesimulation", "oesensors"}
      links {"oevehicles", "oedis", "oedafif", "oeotw"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"jsbsim", "ccl_lib"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oeglut_d"}
      links {"oeioDevice_d", "oesimulation_d", "oesensors_d"}
      links {"oevehicles_d", "oedis_d", "oedafif_d", "oeotw_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"jsbsim_d", "ccl_lib_d"}

-- simple Simulation 4 example
project "mainSim4"
   targetname "mainSim4"
   targetdir "../../mainSim4"
   files {
      "../../mainSim4/**.cpp",
      "../../mainSim4/**.h",
      "../../mainSim4/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oeglut"}
      links {"oeioDevice", "oesimulation", "oesensors"}
      links {"oevehicles", "oedis", "oedafif", "oeotw"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"jsbsim", "ccl_lib"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oeglut_d"}
      links {"oeioDevice_d", "oesimulation_d", "oesensors_d"}
      links {"oevehicles_d", "oedis_d", "oedafif_d", "oeotw_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"jsbsim_d", "ccl_lib_d"}

-- Terrain loading example
project "mainTerrain"
   targetname "mainTerrain"
   targetdir "../../mainTerrain"
   files {
      "../../mainTerrain/**.cpp",
      "../../mainTerrain/**.h",
      "../../mainTerrain/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeterrain", "oeglut"}
      links {"ftgl", "freetype2", "freeglut"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeterrain_d", "oeglut_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}

-- Vmap example
project "mainVmap"
   targetname "mainVmap"
   targetdir "../../mainVmap"
   files {
      "../../mainVmap/**.cpp",
      "../../mainVmap/**.h",
      "../../mainVmap/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oemaps", "oeglut"}
      links {"ftgl", "freetype2", "freeglut"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oemaps_d", "oeglut_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}

-- mainw : basic graphics example
project "mainw"
   targetname "mainw"
   targetdir "../../mainw"
   files {
      "../../mainw/**.cpp",
      "../../mainw/**.h",
      "../../mainw/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeglut"}
      links {"ftgl", "freetype2", "freeglut"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeglut_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}

-- mainx9
project "mainx9"
   targetname "mainx9"
   targetdir "../../mainx9"
   files {
      "../../mainx9/**.cpp",
      "../../mainx9/**.h",
      "../../mainx9/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   if (_ACTION == "vs2008") or (_ACTION == "vs2010") then
      links {"Ws2_32", "Winmm", "comctl32"}
   end
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oeglut"}
      links {"oeioDevice", "oesimulation", "oesensors"}
      links {"oevehicles", "oedis", "oedafif", "oeotw"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"jsbsim", "ccl_lib"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oeglut_d"}
      links {"oeioDevice_d", "oesimulation_d", "oesensors_d"}
      links {"oevehicles_d", "oedis_d", "oedafif_d", "oeotw_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"jsbsim_d", "ccl_lib_d"}

-- mainy1
project "mainy1"
   targetname "mainy1"
   targetdir "../../mainy1"
   files {
      "../../mainy1/**.cpp",
      "../../mainy1/**.h",
      "../../mainy1/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oeglut"}
      links {"oeioDevice", "oesimulation", "oesensors"}
      links {"oevehicles", "oedis", "oedafif", "oeotw"}
      links {"ftgl", "freetype2", "freeglut"}
      links {"jsbsim", "ccl_lib"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oeglut_d"}
      links {"oeioDevice_d", "oesimulation_d", "oesensors_d"}
      links {"oevehicles_d", "oedis_d", "oedafif_d", "oeotw_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"jsbsim_d", "ccl_lib_d"}

-- mainz1
project "mainz1"
   targetname "mainz1"
   targetdir "../../mainz1"
   files {
      "../../mainz1/**.cpp",
      "../../mainz1/**.h",
      "../../mainz1/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oeglut"}
      links {"ftgl", "freetype2", "freeglut"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oeglut_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}

-- mainz2
project "mainz2"
   targetname "mainz2"
   targetdir "../../mainz2"
   files {
      "../../mainz2/**.cpp",
      "../../mainz2/**.h",
      "../../mainz2/**.epp"
   }
   includedirs {
      "../../../OpenEaagles/include",
      "../../../OpenEaagles3rdParty/include"
   }
   libdirs {
      "../../../OpenEaagles/lib/".._ACTION,
      "../../../OpenEaagles3rdParty/lib",
      "../../../OpenEaagles3rdParty/lib/".._ACTION.."-32"
   }
   links {"Ws2_32", "Winmm", "comctl32"}
   links {"opengl32", "glu32"}
   configuration "Release"
      links {"oebasic", "oebasicGL", "oeinstruments", "oeglut"}
      links {"ftgl", "freetype2", "freeglut"}
   configuration "Debug"
      links {"oebasic_d", "oebasicGL_d", "oeinstruments_d", "oeglut_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}


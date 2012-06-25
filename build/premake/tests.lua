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
   configuration "Release"
      links {"oeGlut", "oeBasicGL", "oeBasic"}
      links {"ftgl", LibFreetype, LibGlut, LibGLU, LibGL}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeGlut_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
      links {"Ws2_32", "Winmm", "comctl32", "gdi32"}

-- testIo: I/O test
project "testIo"
   targetname "testIo"
   targetdir "../../testIo"
   debugdir "../../testIo"
   files {
      "../../testIo/**.cpp",
      "../../testIo/**.h",
      "../../testIo/**.epp",
      "../../testIo/**.edl"
   }
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeIoDevice", "oeGlut", "oeBasicGL", "oeBasic"}
      links {"ftgl", LibFreetype, LibGlut, LibGLU, LibGL}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeIoDevice_d", "oeGlut_d", "oeBasicGL_d", "oeBasic_d"}
      links {"ftgl_d", "freetype2_d", "freeglut_d"}
      links {"glu32", "opengl32"}
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
   configuration "Release"
      links {"oeLinearSys", "oeBasic"}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeLinearSys_d", "oeBasic_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testNav
project "testNav"
   targetname "testNav"
   targetdir "../../testNav"
   debugdir "../../testNav"
   files {
      "../../testNav/**.cpp",
      "../../testNav/**.h",
      "../../testNav/**.epp",
      "../../testNav/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   configuration "Release"
      links {"oeBasic"}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeBasic_d"}
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
   configuration "Release"
      links {"oeBasic"}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeBasic_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

-- testNet
project "testNet"
   targetname "testNet"
   targetdir "../../testNet"
   debugdir "../../testNet"
   files {
      "../../testNet/**.cpp",
      "../../testNet/**.h",
      "../../testNet/**.epp",
      "../../testNet/**.edl"
   }
   includedirs { OEIncPath }
   libdirs     { OELibPath }
   configuration "Release"
      links {"oeBasic"}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeBasic_d"}
      links {"Ws2_32", "Winmm", "comctl32"}

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
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeBasic", "oeRecorder", "libprotobuf"}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeIoDevice_d", "oeGlut_d", "oeBasicGL_d", "oeBasic_d", "oeRecorder_d" }
      links {"oeBasic_d", "Ws2_32", "Winmm", "comctl32", "oesimulation_d", "oedafif_d", "libprotobuf_d" }

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
   includedirs { OEIncPath, OE3rdPartyIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath }
   configuration "Release"
      links {"oeBasic", "oeRecorder", "libprotobuf"}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeIoDevice_d", "oeGlut_d", "oeBasicGL_d", "oeBasic_d", "oeRecorder_d" }
      links {"oeBasic_d", "Ws2_32", "Winmm", "comctl32", "oesimulation_d", "oedafif_d", "libprotobuf_d" }

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
   configuration "Release"
      links {"oeBasic"}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeBasic_d"}
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
   configuration "Release"
      links {"oeBasic"}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeBasic_d"}
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
   configuration "Release"
      links {"oeBasic"}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeBasic_d"}
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
   configuration "Release"
      links {"oeBasic"}
      if (os.is("linux")) then
         links {"X11", "pthread", "rt"}
      else
         links {"Ws2_32", "Winmm", "comctl32", "gdi32"}
      end
   configuration "Debug"
      links {"oeBasic_d"}
      links {"Ws2_32", "Winmm", "comctl32"}


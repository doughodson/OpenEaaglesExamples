--------------------------------------------------------
-- Test applications
--------------------------------------------------------

-- testEvents: test of event passing
project "testEvents"
    targetname "testEvents"
    targetdir "../../testEvents"
    files {
        "../../testEvents/**.cpp",
        "../../testEvents/**.h",
        "../../testEvents/**.epp"
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

-- testIo: I/O test
project "testIo"
    targetname "testIo"
    targetdir "../../testIo"
    files {
        "../../testIo/**.cpp",
        "../../testIo/**.h",
        "../../testIo/**.epp"
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
        links {"oebasic", "oebasicGL", "oeioDevice", "oeglut"}
        links {"ftgl", "freetype2", "freeglut"}
    configuration "Debug"
        links {"oebasic_d", "oebasicGL_d", "oeioDevice_d", "oeglut_d"}
        links {"ftgl_d", "freetype2_d", "freeglut_d"}

-- testLinearSys: test of linear system components
project "testLinearSys"
    targetname "testLinearSys"
    targetdir "../../testLinearSys"
    files {
        "../../testLinearSys/**.cpp",
        "../../testLinearSys/**.h",
        "../../testLinearSys/**.epp"
    }
    includedirs {
        "../../../OpenEaagles/include"
    }
    libdirs {
        "../../../OpenEaagles/lib/".._ACTION
    }
    links {"Ws2_32", "Winmm", "comctl32"}
    configuration "Release"
        links {"oebasic", "oelinearSys"}
    configuration "Debug"
        links {"oebasic_d", "oelinearSys_d"}

-- testNav
project "testNav"
    targetname "testNav"
    targetdir "../../testNav"
    files {
        "../../testNav/**.cpp",
        "../../testNav/**.h",
        "../../testNav/**.epp"
    }
    includedirs {
        "../../../OpenEaagles/include"
    }
    libdirs {
        "../../../OpenEaagles/lib/".._ACTION
    }
    links {"Ws2_32", "Winmm", "comctl32"}
    configuration "Release"
        links {"oebasic"}
    configuration "Debug"
        links {"oebasic_d"}

-- testMatrix
project "testMatrix"
    targetname "testMatrix"
    targetdir "../../testMatrix"
    files {
        "../../testMatrix/**.cpp",
        "../../testMatrix/**.h",
        "../../testMatrix/**.epp"
    }
    includedirs {
        "../../../OpenEaagles/include"
    }
    libdirs {
        "../../../OpenEaagles/lib/".._ACTION
    }
    links {"Ws2_32", "Winmm", "comctl32"}
    configuration "Release"
        links {"oebasic"}
    configuration "Debug"
        links {"oebasic_d"}

-- testNet
project "testNet"
    targetname "testNet"
    targetdir "../../testNet"
    files {
        "../../testNet/**.cpp",
        "../../testNet/**.h",
        "../../testNet/**.epp"
    }
    includedirs {
        "../../../OpenEaagles/include"
    }
    libdirs {
        "../../../OpenEaagles/lib/".._ACTION
    }
    links {"Ws2_32", "Winmm", "comctl32"}
    configuration "Release"
        links {"oebasic"}
    configuration "Debug"
        links {"oebasic_d"}

-- testRng
project "testRng"
    targetname "testRng"
    targetdir "../../testRng"
    files {
        "../../testRng/**.cpp",
        "../../testRng/**.h",
        "../../testRng/**.epp"
    }
    includedirs {
        "../../../OpenEaagles/include"
    }
    libdirs {
        "../../../OpenEaagles/lib/".._ACTION
    }
    links {"Ws2_32", "Winmm", "comctl32"}
    configuration "Release"
        links {"oebasic"}
    configuration "Debug"
        links {"oebasic_d"}

-- testStateMach
project "testStateMach"
    targetname "testStateMach"
    targetdir "../../testStateMach"
    files {
        "../../testStateMach/**.cpp",
        "../../testStateMach/**.h",
        "../../testStateMach/**.epp"
    }
    includedirs {
        "../../../OpenEaagles/include"
    }
    libdirs {
        "../../../OpenEaagles/lib/".._ACTION
    }
    links {"Ws2_32", "Winmm", "comctl32"}
    configuration "Release"
        links {"oebasic"}
    configuration "Debug"
        links {"oebasic_d"}

-- testTables
project "testTables"
    targetname "testTables"
    targetdir "../../testTables"
    files {
        "../../testTables/**.cpp",
        "../../testTables/**.h",
        "../../testTables/**.epp"
    }
    includedirs {
        "../../../OpenEaagles/include"
    }
    libdirs {
        "../../../OpenEaagles/lib/".._ACTION
    }
    links {"Ws2_32", "Winmm", "comctl32"}
    configuration "Release"
        links {"oebasic"}
    configuration "Debug"
        links {"oebasic_d"}

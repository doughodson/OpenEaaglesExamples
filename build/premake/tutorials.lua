--------------------------------------------------------
-- Tutorial applications
--------------------------------------------------------

-- tutorial01
project "tutorial01"
    targetname "tutorial01"
    targetdir "../../tutorial01"
    files {
        "../../tutorial01/**.cpp",
        "../../tutorial01/**.h"
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

-- tutorial02
project "tutorial02"
    targetname "tutorial02"
    targetdir "../../tutorial02"
    files {
        "../../tutorial02/**.cpp",
        "../../tutorial02/**.h"
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

-- tutorial03
project "tutorial03"
    targetname "tutorial03"
    targetdir "../../tutorial03"
    files {
        "../../tutorial03/**.cpp",
        "../../tutorial03/**.h",
        "../../tutorial03/**.epp",
        "../../tutorial03/**.edl"
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

-- tutorial04
project "tutorial04"
    targetname "tutorial04"
    targetdir "../../tutorial04"
    files {
        "../../tutorial04/**.cpp",
        "../../tutorial04/**.h",
        "../../tutorial04/**.epp",
        "../../tutorial04/**.edl"
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

-- tutorial05
project "tutorial05"
    targetname "tutorial05"
    targetdir "../../tutorial05"
    files {
        "../../tutorial05/**.cpp",
        "../../tutorial05/**.h",
        "../../tutorial05/**.epp",
        "../../tutorial05/**.edl"
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

-- tutorial06
project "tutorial06"
    targetname "tutorial06"
    targetdir "../../tutorial06"
    files {
        "../../tutorial06/**.cpp",
        "../../tutorial06/**.h",
        "../../tutorial06/**.epp",
        "../../tutorial06/**.edl"
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

-- tutorial07
project "tutorial07"
    targetname "tutorial07"
    targetdir "../../tutorial07"
    files {
        "../../tutorial07/**.cpp",
        "../../tutorial07/**.h",
        "../../tutorial07/**.epp",
        "../../tutorial07/**.edl"
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

-- tutorial08
project "tutorial08"
    targetname "tutorial08"
    targetdir "../../tutorial08"
    files {
        "../../tutorial08/**.cpp",
        "../../tutorial08/**.h",
        "../../tutorial08/**.epp",
        "../../tutorial08/**.edl"
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
    links {"Ws2_32", "Winmm", "comctl32" }
    links {"opengl32", "glu32"}
    configuration "Release"
        links {"oebasic", "oebasicGL", "oeglut"}
        links {"ftgl", "freetype2", "freeglut"}
    configuration "Debug"
        links {"oebasic_d", "oebasicGL_d", "oeglut_d"}
        links {"ftgl_d", "freetype2_d", "freeglut_d"}


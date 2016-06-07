--------------------------------------------------------
-- UBF examples
--------------------------------------------------------

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
   links { "libxbehaviors",  "libxpanel" }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links { "oemodels", "JSBSim" }
      links { "oeotw", LibCigi }
      links { "oedis", "oeiodevice" }
      links { "oesimulation", "oedafif", "oeterrain" }
      links { "oeglut", "oeinstruments", "oegraphics", "oebase" }
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }
   filter "configurations:Debug*"
      links { "oemodels_d", "JSBSim_d" }
      links { "oeotw_d", LibCigi_d }
      links { "oedis_d", "oeiodevice_d" }
      links { "oesimulation_d", "oedafif_d", "oeterrain_d" }
      links { "oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d" }
      links { LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }

-- mainLua example
project "mainLua"
    targetname "mainLua"
    targetdir "../../mainLua"
    debugdir "../../mainLua"
    files {
        "../../mainLua/**.cpp",
        "../../mainLua/**.h",
        "../../mainLua/**.epp",
        "../../mainLua/**.edl"
    }
   includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
   libdirs     { OELibPath, OE3rdPartyLibPath, OEExamplesLibPath }
   defines { "_CONSOLE" }
   filter "configurations:Release*"
      links {"oebehaviors", "oeclips", "oelua", "oesoar" }
      links { "oemodels", "JSBSim" }
      links { "oeotw", LibCigi, "Soar" }
      links { "oedis", "oeiodevice" }
      links { "oesimulation", "oedafif", "oeterrain" }
      links { "oeglut", "oeinstruments", "oegraphics", "oebase" }
      links { LibFtgl, LibFreetype, LibGlut, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }
   filter "configurations:Debug*"
      links {"oebehaviors_d", "oeclips_d", "oelua_d", "oesoar_d" }
      links { "oemodels_d", "JSBSim_d" }
      links { "oeotw_d", LibCigi_d, "Soar" }
      links { "oedis_d", "oeiodevice_d" }
      links { "oesimulation_d", "oedafif_d", "oeterrain_d" }
      links { "oeglut_d", "oeinstruments_d", "oegraphics_d", "oebase_d" }
      links { LibFtgl_d, LibFreetype_d, LibGlut_d, LibGLU, LibGL }
      links { "Ws2_32", "Winmm", "comctl32", "gdi32" }

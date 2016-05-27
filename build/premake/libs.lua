--------------------------------------------------------------------------------
-- creating the example libraries
--------------------------------------------------------------------------------

    --  eXample UBF behaviors library
    project "libxbehaviors"
      kind "StaticLib"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      files {
         "../../shared/xbehaviors/*.cpp",
         "../../shared/xbehaviors/*.h",
      }
      defines { "_LIB" }
      filter "configurations:Release*"
         targetname "xbehaviors"
      filter "configurations:Debug*"
         targetname "xbehaviors_d"

    --  eXample library that extends the data recorder
    project "libxrecorder"
      kind "StaticLib"
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      targetdir (OEExamplesLibPath)
      files {
         "../../shared/xrecorder/**.cpp",
         "../../shared/xrecorder/**.cc",
         "../../shared/xrecorder/**.h",
         "../../shared/xrecorder/**.proto",
      }
      defines { "_LIB" }
      defines { "_SCL_SECURE_NO_WARNINGS" } -- suppress protocol buffer warning
      filter "configurations:Release*"
         targetname "xrecorder"
      filter "configurations:Debug*"
         targetname "xrecorder_d"

    --  eXample Panel library -- common instrument panel code for several examples
    project "libxpanel"
      kind "StaticLib"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      files {
         "../../shared/xpanel/*.cpp",
         "../../shared/xpanel/*.h",
         "../../shared/xpanel/**.epp",
      }
      defines { "_LIB" }
      filter "configurations:Release*"
         targetname "xpanel"
      filter "configurations:Debug*"
         targetname "xpanel_d"

    --  eXample ZeroMQ network handlers
    project "libxzmq"
      kind "StaticLib"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      defines { "ZMQ_STATIC" }
      files {
         "../../shared/xzmq/*.cpp",
         "../../shared/xzmq/*.h",
         "../../shared/xzmq/**.epp",
      }
      defines { "_LIB" }
      filter "configurations:Release*"
         targetname "xzmq"
      filter "configurations:Debug*"
         targetname "xzmq_d"


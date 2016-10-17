--------------------------------------------------------------------------------
-- creating the example libraries
--------------------------------------------------------------------------------

    --  eXample UBF behaviors library
    project "libxbehaviors"
      kind "StaticLib"
      targetname "xbehaviors"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      files {
         "../../shared/xbehaviors/*.h*",
         "../../shared/xbehaviors/*.cpp",
      }
      defines { "_LIB" }

    --  eXample library that extends the data recorder
    project "libxrecorder"
      kind "StaticLib"
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      targetname "xrecorder"
      targetdir (OEExamplesLibPath)
      files {
         "../../shared/xrecorder/**.h*",
         "../../shared/xrecorder/**.cpp",
         "../../shared/xrecorder/**.cc",
         "../../shared/xrecorder/**.proto",
      }
      defines { "_LIB" }
      defines { "_SCL_SECURE_NO_WARNINGS" } -- suppress protocol buffer warning

    --  eXample Panel library -- common instrument panel code for several examples
    project "libxpanel"
      kind "StaticLib"
      targetname "xpanel"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      files {
         "../../shared/xpanel/*.h*",
         "../../shared/xpanel/*.cpp",
         "../../shared/xpanel/**.epp",
      }
      defines { "_LIB" }

    --  eXample ZeroMQ network handlers
    project "libxzmq"
      kind "StaticLib"
      targetname "xzmq"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      defines { "ZMQ_STATIC" }
      files {
         "../../shared/xzmq/*.h*",
         "../../shared/xzmq/*.cpp",
         "../../shared/xzmq/**.epp",
      }
      defines { "_LIB" }

--------------------------------------------------------------------------------
-- creating the example libraries
--------------------------------------------------------------------------------

    --  eXample UBF behaviors library
    project "libxBehaviors"
      kind "StaticLib"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      files {
         "../../shared/xBehaviors/*.cpp",
         "../../shared/xBehaviors/*.h",
      }
      defines { "_LIB" }
      configuration "Release"
         targetname "xBehaviors"
      configuration "Debug"
         targetname "xBehaviors_d"

    --  eXample IEEE HLA interoperability library
    project "libxHla"
      kind "StaticLib"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      files {
         "../../shared/xHla/**.cpp",
         "../../shared/xHla/**.h",
      }
      includedirs { HLAIncPath }
      defines { "RTI_USES_STD_FSTREAM" }
      defines { "_LIB" }
      configuration "Release"
         targetname "xHla"
      configuration "Debug"
         targetname "xHla_d"

    --  eXample library that extends the data recorder
    project "libxRecorder"
      kind "StaticLib"
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      targetdir (OEExamplesLibPath)
      files {
         "../../shared/xRecorder/*.cpp",
         "../../shared/xRecorder/*.cc",
         "../../shared/xRecorder/*.h",
         "../../shared/xRecorder/*.proto",
      }
      defines { "_LIB" }
      defines { "_SCL_SECURE_NO_WARNINGS" } -- suppress protocol buffer warning
      configuration "Release"
         targetname "xRecorder"
      configuration "Debug"
         targetname "xRecorder_d"

    --  eXample Panel library -- common instrument panel code for several examples
    project "libxPanel"
      kind "StaticLib"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      files {
         "../../shared/xPanel/*.cpp",
         "../../shared/xPanel/*.h",
         "../../shared/xPanel/**.epp",
      }
      defines { "_LIB" }
      configuration "Release"
         targetname "xPanel"
      configuration "Debug"
         targetname "xPanel_d"

    --  eXample ZeroMQ network handlers
    project "libxZeroMQHandlers"
      kind "StaticLib"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      defines { "ZMQ_STATIC" }
      files {
         "../../shared/xZeroMQHandlers/*.cpp",
         "../../shared/xZeroMQHandlers/*.h",
         "../../shared/xZeroMQHandlers/**.epp",
      }
      defines { "_LIB" }
      configuration "Release"
         targetname "xZeroMQHandlers"
      configuration "Debug"
         targetname "xZeroMQHandlers_d"


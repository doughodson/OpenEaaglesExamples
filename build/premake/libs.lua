--------------------------------------------------------------------------------
-- creating the example libraries
--------------------------------------------------------------------------------

    --  eXample UBF behaviors library
    project "libxBehaviors"
      kind "StaticLib"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      files {
         "../../shared-libs/xBehaviors/*.cpp",
         "../../shared-libs/xBehaviors/*.h",
      }
      defines { "_LIB" }
      configuration "Release"
         targetname "xBehaviors"
      configuration "Debug"
         targetname "xBehaviors_d"

    --  eXample library that extends the data recorder
    project "libxRecorder"
      kind "StaticLib"
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      targetdir (OEExamplesLibPath)
      files {
         "../../shared-libs/xRecorder/*.cpp",
         "../../shared-libs/xRecorder/*.cc",
         "../../shared-libs/xRecorder/*.h",
         "../../shared-libs/xRecorder/*.proto",
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
         "../../shared-libs/xPanel/*.cpp",
         "../../shared-libs/xPanel/*.h",
         "../../shared-libs/xPanel/**.epp",
      }
      defines { "_LIB" }
      configuration "Release"
         targetname "xPanel"
      configuration "Debug"
         targetname "xPanel_d"



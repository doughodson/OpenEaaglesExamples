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
    project "libxDataRecorder"
      kind "StaticLib"
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      targetdir (OEExamplesLibPath)
      files {
         "../../shared-libs/xDataRecorder/*.cpp",
         "../../shared-libs/xDataRecorder/*.cc",
         "../../shared-libs/xDataRecorder/*.h",
         "../../shared-libs/xDataRecorder/*.proto",
      }
      defines { "_LIB" }
      configuration "Release"
         targetname "xDataRecorder"
      configuration "Debug"
         targetname "xDataRecorder_d"

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



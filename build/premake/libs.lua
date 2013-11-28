--------------------------------------------------------------------------------
-- creating the example libraries
--------------------------------------------------------------------------------

    --  Example extended data recorder library
    project "libMyRecorder"
      kind "StaticLib"
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      targetdir (OEExamplesLibPath)
      files {
         "../../shared-libs/myRecorder/*.cpp",
         "../../shared-libs/myRecorder/*.cc",
         "../../shared-libs/myRecorder/*.h",
         "../../shared-libs/myRecorder/*.proto",
      }
      defines { "_LIB" }
      configuration "Release"
         targetname "myRecorder"
      configuration "Debug"
         targetname "myRecorder_d"

    --  Example UBF plane behaviors library
    project "libPlaneBehaviors"
      kind "StaticLib"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      files {
         "../../shared-libs/planeBehaviors/*.cpp",
         "../../shared-libs/planeBehaviors/*.h",
      }
      defines { "_LIB" }
      configuration "Release"
         targetname "planeBehaviors"
      configuration "Debug"
         targetname "planeBehaviors_d"

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



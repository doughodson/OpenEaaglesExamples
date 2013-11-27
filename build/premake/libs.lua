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


    --  Y1 Panel library -- common instrument panel code for several examples
    project "libY1Panel"
      kind "StaticLib"
      targetdir (OEExamplesLibPath)
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      files {
         "../../shared-libs/y1panel/*.cpp",
         "../../shared-libs/y1panel/*.h",
         "../../shared-libs/y1panel/**.epp",
      }
      defines { "_LIB" }
      configuration "Release"
         targetname "y1Panel"
      configuration "Debug"
         targetname "y1Panel_d"

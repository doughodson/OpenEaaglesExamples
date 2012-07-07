--------------------------------------------------------------------------------
-- creating the example libraries
--------------------------------------------------------------------------------

    --  Example extended data recorder library
    project "libMyRecorder"
      kind "StaticLib"
      includedirs { OEIncPath, OE3rdPartyIncPath, OEExamplesIncPath }
      targetdir (OEExamplesLibPath)
      files {
         "../../src/myRecorder/*.cpp",
         "../../src/myRecorder/*.cc",
         "../../include/myRecorder/*.h",
         "../../include/myRecorder/*.proto",
      }
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
         "../../src/planeBehaviors/*.cpp",
         "../../include/planeBehaviors/*.h",
      }
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
         "../../src/y1panel/*.cpp",
         "../../include/y1panel/*.h",
         "../../include/y1panel/**.epp",
      }
      configuration "Release"
         targetname "y1Panel"
      configuration "Debug"
         targetname "y1Panel_d"

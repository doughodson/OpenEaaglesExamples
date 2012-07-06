--------------------------------------------------------------------------------
-- creating the example libraries
--------------------------------------------------------------------------------

    --  Example extended data recorder
    project "LibMyRecorder"
      kind "StaticLib"
      includedirs { OEIncPath, OE3rdPartyIncPath, "../../include/" }
      targetdir ("../../lib/".._ACTION)
      files {
         "../../src/myRecorder/*.cpp",
         "../../src/myRecorder/*.cc",
         "../../include/myRecorder/*.h",
         "../../include/myRecorder/*.proto",
      }
      configuration "Release"
         targetname "libMyRecorder"
      configuration "Debug"
         targetname "libMyRecorder_d"


    --  Example UBF plane behaviors
    project "libPlaneBehaviors"
      kind "StaticLib"
      targetdir ("../../lib/".._ACTION)
      includedirs { OEIncPath, OE3rdPartyIncPath, "../../include/" }
      files {
         "../../src/planeBehaviors/*.cpp",
         "../../include/planeBehaviors/*.h",
      }
      configuration "Release"
         targetname "libPlaneBehaviors"
      configuration "Debug"
         targetname "libPlaneBehaviors_d"



    --  Y1 Panel library -- common instrument panel code for several examples
    project "libY1Panel"
      kind "StaticLib"
      targetdir ("../../lib/".._ACTION)
      includedirs { OEIncPath, OE3rdPartyIncPath, "../../include/" }
      files {
         "../../src/y1panel/*.cpp",
         "../../include/y1panel/*.h",
         "../../include/y1panel/**.epp",
      }
      configuration "Release"
         targetname "libY1Panel"
      configuration "Debug"
         targetname "libY1Panel_d"



--------------------------------------------------------
-- Libraries
--------------------------------------------------------

-- ubf plane behaviors
project "planeBehaviors"
   -- creating static library
   kind "StaticLib"
   targetdir "../../planeBehaviors"
   debugdir "../../planeBehaviors"
   files {
      "../../planeBehaviors/**.cpp",
      "../../planeBehaviors/**.h"
   }
   includedirs { OEIncPath }
   configuration "Release"
      -- filename for compiled binary target
      targetname "oePlaneBehaviors"
   configuration "Debug"
      -- filename for compiled binary target
      targetname "oePlaneBehaviors_d"


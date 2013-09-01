--
-- If premake command is not supplied an action (target compiler), exit!
--
-- Target of interest:
--     vs2008     (Visual Studio 2008)
--     vs2010     (Visual Studio 2010)
--     vs2012     (Visual Studio 2012)
--     codeblocks (Code::Blocks)
--     codelite   (CodeLite)
--

-- we must have an ide/compiler specified
if (_ACTION == nil) then
  return
end

--
-- directory locations for framework and 3rd party dependencies
--
OE_ROOT           = "../../../OpenEaagles"
OE_3RD_PARTY_ROOT = "../../../OpenEaagles3rdParty"

--
-- set include and library paths
--
if (_ACTION == "vs2008") or (_ACTION == "vs2010") or (_ACTION == "vs2012") then
   OEIncPath         = OE_ROOT.."/include"
   OELibPath         = OE_ROOT.."/lib/".._ACTION
   OE3rdPartyIncPath = OE_3RD_PARTY_ROOT.."/include"
   OE3rdPartyLibPath = OE_3RD_PARTY_ROOT.."/lib/".._ACTION.."-32"
   OEExamplesIncPath = "../../include"
   OEExamplesLibPath = "../../lib/".._ACTION
end
if (_ACTION == "codelite") or (_ACTION == "codeblocks") then
   OEIncPath         = OE_ROOT.."/include"
   OELibPath         = OE_ROOT.."/lib/mingw"
   OE3rdPartyIncPath = OE_3RD_PARTY_ROOT.."/include"
   OE3rdPartyLibPath = OE_3RD_PARTY_ROOT.."/lib/mingw-32"
   OEExamplesIncPath = "../../include"
   OEExamplesLibPath = "../../lib/mingw"
end
print ("OpenEaagles Paths:")
print ("  Include   : "..OEIncPath)
print ("  Libraries : "..OELibPath)
print ("OpenEaagles3rdParty Paths:")
print ("  Include   :"..OE3rdPartyIncPath)
print ("  Libraries :"..OE3rdPartyLibPath)
print ("OpenEaaglesExamples Paths:")
print ("  Include   :"..OEExamplesIncPath)
print ("  Libraries :"..OEExamplesLibPath)

locationPath  = "../" .. _ACTION

--
-- 3rd party library names
--
LibCigi       = "ccl_lib"
LibFtgl       = "ftgl"
LibFreetype   = "freetype2"
LibGlut       = "freeglut"

LibCigi_d     = LibCigi.."_d"
LibFtgl_d     = LibFtgl.."_d"
LibFreetype_d = LibFreetype.."_d"
LibGlut_d     = LibGlut.."_d"

LibGLU        = "glu32"
LibGL         = "opengl32"

solution "examples"

   -- destination directory for generated solution/project files
   location (locationPath)

   -- creating console application
   kind "ConsoleApp"

   -- C++ code in all projects
   language "C++"

   --
   -- Build (solution) configuration options:
   --     Release        (Application linked to Multi-threaded DLL)
   --     Debug          (Application linked to Multi-threaded Debug DLL)
   --
   configurations { "Release", "Debug" }

   -- common release configuration flags and symbols
   configuration { "Release" }
      flags { "Optimize" }
      if (_ACTION == "vs2008") or (_ACTION == "vs2010") or (_ACTION == "vs2012") then
         -- enable compilier intrinsics and favor speed over size
         buildoptions { "/Oi", "/Ot" }
         defines { "WIN32", "NDEBUG" }
      end

   -- common debug configuration flags and symbols
   configuration { "Debug" }
      flags { "Symbols" }
      if (_ACTION == "vs2008") or (_ACTION == "vs2010") or (_ACTION == "vs2012") then
         -- enable compilier intrinsics
         buildoptions { "/Oi" }
         defines { "WIN32", "_DEBUG" }
      end


   -- libraries
   dofile "libs.lua"

   -- examples
   dofile "examples.lua"

   -- tests
   dofile "tests.lua"

   -- tutorial
   dofile "tutorials.lua"

   -- gui examples
   dofile "guidemos.lua"


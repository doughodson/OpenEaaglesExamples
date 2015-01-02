--
-- If premake command is not supplied an action (target compiler), exit!
--
-- Target of interest:
--     vs2008     (Visual Studio 2008)
--     vs2010     (Visual Studio 2010)
--     vs2012     (Visual Studio 2012)
--     vs2013     (Visual Studio 2013)
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
if (_ACTION == "vs2008") or (_ACTION == "vs2010") or (_ACTION == "vs2012") or (_ACTION == "vs2013") then
   OEIncPath         = OE_ROOT.."/include"
   OELibPath         = OE_ROOT.."/lib/".._ACTION
   OE3rdPartyIncPath = OE_3RD_PARTY_ROOT.."/include"
   OE3rdPartyLibPath = OE_3RD_PARTY_ROOT.."/lib/".._ACTION.."-32"
   OEExamplesIncPath = "../../shared"
   OEExamplesLibPath = "../../lib/".._ACTION
end
if (_ACTION == "codelite") or (_ACTION == "codeblocks") then
   OEIncPath         = OE_ROOT.."/include"
   OELibPath         = OE_ROOT.."/lib/mingw"
   OE3rdPartyIncPath = OE_3RD_PARTY_ROOT.."/include"
   OE3rdPartyLibPath = OE_3RD_PARTY_ROOT.."/lib/mingw-32"
   OEExamplesIncPath = "../../shared"
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

--
-- directory location for HLA include and library paths
--
HLA_ROOT = "../../../portico-2.0.1"
HLAIncPath = HLA_ROOT.."/include/hla13"
if (_ACTION == "vs2008") then
  HLALibPath = HLA_ROOT.."/lib/vc9"
end
if (_ACTION == "vs2010") then
  HLALibPath = HLA_ROOT.."/lib/vc10"
end
if (_ACTION == "vs2012") then
  HLALibPath = HLA_ROOT.."/lib/vc11"
end
if (_ACTION == "vs2013") then
  HLALibPath = HLA_ROOT.."/lib/vc12"
end
print ("HLA Paths:")
print ("  Include   : "..HLALibPath)
--print ("  Libraries : "..OELibPath)

locationPath  = "../" .. _ACTION

-- for now, premake does not support this action, so use 2012 instead
--if (_ACTION == "vs2013") then
--   _ACTION = "vs2012"
--end

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
      if (_ACTION == "vs2008") or (_ACTION == "vs2010") or (_ACTION == "vs2012") or (_ACTION == "vs2013") then
         -- enable compiler intrinsics and favour speed over size
         buildoptions { "/Oi", "/Ot" }
         defines { "WIN32", "NDEBUG" }
      end

   -- common debug configuration flags and symbols
   configuration { "Debug" }
      flags { "Symbols" }
      if (_ACTION == "vs2008") or (_ACTION == "vs2010") or (_ACTION == "vs2012") or (_ACTION == "vs2013") then
         -- enable compiler intrinsics
         buildoptions { "/Oi" }
         defines { "WIN32", "_DEBUG" }
      end


   -- libraries
   dofile "libs.lua"

   -- demos
   dofile "demos.lua"

   -- examples
   dofile "examples.lua"

   -- tests
   dofile "tests.lua"

   -- tutorial
   dofile "tutorials.lua"

   -- gui examples
   dofile "guidemos.lua"


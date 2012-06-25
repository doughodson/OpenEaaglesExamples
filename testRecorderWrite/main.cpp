
#include "DataRecordTest.h"

#include "openeaagles/simulation/simulationFF.h"
#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/simulation/Station.h"
#include "openeaagles/simulation/Player.h"
#include "openeaagles/basic/basicFF.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"

namespace Eaagles {
namespace TestRecorder {

//const float UPDATE_RATE = 10.0; // Main loop update rate

//=============================================================================
// Main test functions
//=============================================================================


//-----------------------------------------------------------------------------
// testFormFunc() -- our form function used by the parser
//-----------------------------------------------------------------------------
static Eaagles::Basic::Object* testFormFunc(const char* formname)
{
   Eaagles::Basic::Object* newform = 0;

   // This test:
   if ( strcmp(formname, DataRecordTest::getFormName()) == 0 ) {
      newform = new DataRecordTest();
   }

    else {
       if (newform == 0) newform = Eaagles::Simulation::simulationFormFunc(formname);
       if (newform == 0) newform = Eaagles::Basic::basicFormFunc(formname);
       if (newform == 0) newform = Eaagles::Recorder::recorderFormFunc(formname);
    }

   return newform;
}

//-----------------------------------------------------------------------------
// readTest() -- function to the read description files
//-----------------------------------------------------------------------------
static DataRecordTest* readTest(const char* const testFile)
{
   if (testFile == 0) return 0;

 //  std::cout << "Reading file : " << testFile << std::endl;

   // Read the description file
   int errors = 0;
   Eaagles::Basic::Object* q1 = lcParser(testFile, testFormFunc, &errors);
   if (errors > 0) {
      std::cerr << "File: " << testFile << ", errors: " << errors << std::endl;
  //    exit(1);
   }

   // Set 'sys' to our basic description object.
   DataRecordTest* sys = 0;
   if (q1 != 0) {
      // When we were given a Pair, get the pointer to its object.
      Eaagles::Basic::Pair* pp = dynamic_cast<Eaagles::Basic::Pair*>(q1);
      if (pp != 0) {
         q1 = pp->object();
      }

      // What we should have here is the description object and
      // it should be of type 'Station'.
      sys = dynamic_cast<DataRecordTest*>(q1);
   }

   return sys;
}

int exec(int argc, char* argv[])
{
   const char* testFile = "test.edl";

   // Get the command line arguments
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i],"-f") == 0) {
         testFile = argv[++i];
      }
   }

   // Must have a test file name
   if (testFile == 0) {
      std::cerr << "usage:  test -f testFile" << std::endl;
      return EXIT_FAILURE;
   }

   // Read in the description files
   DataRecordTest* sys = readTest(testFile);

   // Must have a valid system of type DataRecordTest
   if (sys == 0) {
      std::cerr << "Invalid test file" << std::endl;
      return EXIT_FAILURE;
   }

   // Start test (we don't come back!)
 //  sys->testEvents();
   sys->testSerialize();
 //  sys->testSelect();


   return EXIT_SUCCESS;
}

} // namespace TestRecorder
}

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   Eaagles::TestRecorder::exec(argc, argv);
}


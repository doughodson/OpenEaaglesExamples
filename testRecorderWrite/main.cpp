
#include "DataRecordTest.h"

#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/simulation/Station.h"
#include "openeaagles/simulation/Player.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"

// class factories
#include "openeaagles/simulation/Factory.h"
#include "openeaagles/basic/Factory.h"
#include "openeaagles/recorder/Factory.h"

namespace Eaagles {
namespace Test {

//const float UPDATE_RATE = 10.0; // Main loop update rate

//=============================================================================
// Main test functions
//=============================================================================

// our class factory
static Basic::Object* factory(const char* name)
{
   Basic::Object* obj = 0;

   // This test:
   if ( strcmp(name, DataRecordTest::getFactoryName()) == 0 ) {
      obj = new DataRecordTest();
   }

   else {
      if (obj == 0) obj = Eaagles::Simulation::Factory::createObj(name);
      if (obj == 0) obj = Eaagles::Basic::Factory::createObj(name);
      if (obj == 0) obj = Eaagles::Recorder::Factory::createObj(name);
   }

   return obj;
}

// build recorder test
static DataRecordTest* builder(const char* const testFile)
{
   if (testFile == 0) return 0;

 //  std::cout << "Reading file : " << testFile << std::endl;

   // Read the description file
   int errors = 0;
   Eaagles::Basic::Object* q1 = lcParser(testFile, factory, &errors);
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

   // Build a recorder test
   DataRecordTest* sys = builder(testFile);

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

}
}

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   Eaagles::Test::exec(argc, argv);
}


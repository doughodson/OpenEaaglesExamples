
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

#include <cstring>
#include <cstdlib>

namespace oe {
namespace test {

// our class factory
static basic::Object* factory(const char* name)
{
   basic::Object* obj = nullptr;

   //
   if ( std::strcmp(name, DataRecordTest::getFactoryName()) == 0 ) {
      obj = new DataRecordTest();
   }

   else {
      if (obj == nullptr) obj = oe::Simulation::Factory::createObj(name);
      if (obj == nullptr) obj = oe::basic::Factory::createObj(name);
      if (obj == nullptr) obj = oe::recorder::Factory::createObj(name);
   }

   return obj;
}

// DataRecordTest builder
static DataRecordTest* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   basic::Object* obj = basic::lcParser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a basic::Pair, if so, point to object in Pair, not Pair itself
   basic::Pair* pair = dynamic_cast<basic::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   DataRecordTest* dataRecordTest = dynamic_cast<DataRecordTest*>(obj);
   if (dataRecordTest == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return dataRecordTest;
}

//
int main(int argc, char* argv[])
{
   // default configuration filename
   const char* configFilename = "test.edl";
   // parse command line arguments
   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i],"-f") == 0) {
         configFilename = argv[++i];
      }
   }

   // build data recorder test
   DataRecordTest* dataRecordTest = builder(configFilename);

   // Start test (we don't come back!)
 //  dataRecordTest->testEvents();
   dataRecordTest->testSerialize();
 //  dataRecordTest->testSelect();

   return EXIT_SUCCESS;
}

}
}

//
int main(int argc, char* argv[])
{
   oe::test::main(argc, argv);
}


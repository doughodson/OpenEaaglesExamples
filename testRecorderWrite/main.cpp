
#include "DataRecordTest.h"

#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/simulation/Station.h"
#include "openeaagles/simulation/Player.h"
#include "openeaagles/base/edl_parser.h"
#include "openeaagles/base/Pair.h"

// factories
#include "openeaagles/simulation/factory.h"
#include "openeaagles/base/factory.h"
#include "openeaagles/recorder/factory.h"

#include <string>
#include <cstdlib>

namespace oe {
namespace test {

// our class factory
base::Object* factory(const std::string& name)
{
   base::Object* obj = nullptr;

   //
   if ( name == DataRecordTest::getFactoryName() ) {
      obj = new DataRecordTest();
   }
   else {
      if (obj == nullptr) obj = oe::simulation::factory(name);
      if (obj == nullptr) obj = oe::base::factory(name);
      if (obj == nullptr) obj = oe::recorder::factory(name);
   }

   return obj;
}

// DataRecordTest builder
DataRecordTest* builder(const std::string& filename)
{
   // read configuration file
   unsigned int errors = 0;
   base::Object* obj = base::edl_parser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   base::Pair* pair = dynamic_cast<base::Pair*>(obj);
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
   std::string  configFilename = "test.edl";
   // parse command line arguments
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
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


#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/base/edl_parser.h"
#include "openeaagles/base/Pair.h"

// factories
#include "openeaagles/simulation/factory.h"
#include "openeaagles/models/factory.h"
#include "openeaagles/base/factory.h"

#include <string>
#include <cstdlib>

namespace oe {
namespace example {

// frame rate (50 Hz)
const unsigned int frameRate = 50;

simulation::Simulation* simulation = nullptr;

// our class factory
base::Object* factory(const std::string& name)
{
   base::Object* obj = nullptr;

   if (obj == nullptr) obj = simulation::factory(name);
   if (obj == nullptr) obj = models::factory(name);
   if (obj == nullptr) obj = base::factory(name);

   return obj;
}

// simulation builder
simulation::Simulation* builder(const std::string& filename)
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
   simulation::Simulation* simulation = dynamic_cast<simulation::Simulation*>(obj);
   if (simulation == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return simulation;
}

int main(int argc, char* argv[])
{
   // default configuration filename
   std::string configFilename = "test1.edl";

   // read filename from command line if provided
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   // build simulation
   simulation = builder(configFilename);

   // reset component tree
   simulation->reset();

   // delta time (20ms)
   const double dt = 1.0 / static_cast<double>(frameRate);

   // execute simulation as fast as possible
   for(; simulation->getExecTimeSec() < 50.0; ) {
      // print out simulation time
      std::cout << simulation->getExecTimeSec() << std::endl;
      // execute timestep
      simulation->tcFrame( dt );
      simulation->updateData( dt );
   }
   return 0;
}

}
}

//
int main(int argc, char* argv[])
{
  oe::example::main(argc, argv);
}


#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"

// class factories
#include "openeaagles/simulation/Factory.h"
#include "openeaagles/dynamics/Factory.h"
#include "openeaagles/sensors/Factory.h"
#include "openeaagles/basic/Factory.h"

#include <cstring>
#include <cstdlib>

namespace Eaagles {
namespace Example {

// frame rate (50 Hz)
const unsigned int frameRate = 50;

static Simulation::Simulation* simulation = nullptr;

// our class factory
static Basic::Object* factory(const char* name)
{
   Basic::Object* obj = nullptr;

   if (obj == nullptr) obj = Simulation::Factory::createObj(name);
   if (obj == nullptr) obj = Dynamics::Factory::createObj(name);
   if (obj == nullptr) obj = Sensor::Factory::createObj(name);
   if (obj == nullptr) obj = Basic::Factory::createObj(name);

   return obj;
}

// simulation builder
static Simulation::Simulation* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   Basic::Object* obj = Basic::lcParser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a Basic::Pair, if so, point to object in Pair, not Pair itself
   Basic::Pair* pair = dynamic_cast<Basic::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   Simulation::Simulation* simulation = dynamic_cast<Simulation::Simulation*>(obj);
   if (simulation == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return simulation;
}

int main(int argc, char* argv[])
{
   // default configuration filename
   const char* configFilename = "test1.edl";

   // read filename from command line if provided
   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i],"-f") == 0) {
         configFilename = argv[++i];
      }
   }

   // build simulation
   simulation = builder(configFilename);

   // reset component tree
   simulation->reset();

   // delta time (20ms)
   LCreal dt = static_cast<LCreal>(1.0)/static_cast<LCreal>(frameRate);

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

} // namespace Example
} // namespace Eaagles

//
int main(int argc, char* argv[])
{
  Eaagles::Example::main(argc, argv);
}


#include "openeaagles/simulation/Station.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Integer.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/osg/Vec3"
#include "openeaagles/otw/OtwPC.h"

// factories
#include "../shared/xzmq/factory.h"
#include "openeaagles/simulation/factory.h"
#include "openeaagles/models/factory.h"
#include "openeaagles/dis/factory.h"
#include "openeaagles/otw/factory.h"
#include "openeaagles/basic/factory.h"

#include <cstring>
#include <cstdlib>

namespace oe {
namespace example {

// background frame rate
const int bgRate = 10;

static simulation::Station* station = nullptr;

// our class factory
static basic::Object* factory(const char* name)
{
   basic::Object* obj = nullptr;

   // example libraries
   if (obj == nullptr) obj = xZeroMQHandlers::factory(name);

   // framework libraries
   if (obj == nullptr) obj = otw::factory(name);
   if (obj == nullptr) obj = simulation::factory(name);
   if (obj == nullptr) obj = models::factory(name);
   if (obj == nullptr) obj = network::dis::factory(name);
   if (obj == nullptr) obj = basic::factory(name);

   return obj;
}

// station builder
static simulation::Station* builder(const char* const filename)
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
   simulation::Station* station = dynamic_cast<simulation::Station*>(obj);
   if (station == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return station;
}

int main(int argc, char* argv[])
{
   // default configuration filename
   const char* configFilename = "test00.edl";

   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i],"-f") == 0) {
         configFilename = argv[++i];
      }
   }

   // build Station
   station = builder(configFilename);

   // send a reset event and frame sim once
   station->event(basic::Component::RESET_EVENT);
   station->tcFrame( static_cast<LCreal>(1.0/static_cast<double>(station->getTimeCriticalRate())) );

   // create time critical thread
   station->createTimeCriticalProcess();
   // short pause to allow os to startup thread
   lcSleep(2000);

   // calc delta time for background thread
   const double dt = 1.0/static_cast<double>(bgRate);

   // system Time of Day
   double simTime = 0.0;                         // Simulator time reference
   const double startTime = getComputerTime();   // Time of day (sec) run started

   int k = 0;
   std::cout << "Starting background main loop ..." << std::endl;
   for(;;) {

      // update background thread
      station->updateData( static_cast<LCreal>(dt) );

      simTime += dt;                             // time of next frame
      const double timeNow = getComputerTime();  // time now
      const double elapsedTime = timeNow - startTime;
      const double nextFrameStart = simTime - elapsedTime;
      const int sleepTime = static_cast<int>(nextFrameStart*1000.0);

      // wait for the next frame
      if (sleepTime > 0)
         lcSleep(sleepTime);

      std::cout << ".";
      k += 1;
      if ( k == 40 ) {
         std::cout << "\n";
         k = 0;
      }
   }
   return 0;
}

} // namespace example
} // namespace oe

//
int main(int argc, char* argv[])
{
   return oe::example::main(argc, argv);
}

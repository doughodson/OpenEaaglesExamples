
#include "openeaagles/simulation/Station.h"
#include "openeaagles/base/edl_parser.h"
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/Integer.h"
#include "openeaagles/base/units/Angles.h"
#include "openeaagles/base/osg/Vec3"
#include "openeaagles/otw/OtwPC.h"
#include "openeaagles/base/util/system.h"

// factories
#include "../shared/xzmq/factory.h"
#include "openeaagles/simulation/factory.h"
#include "openeaagles/models/factory.h"
#include "openeaagles/networks/dis/factory.h"
#include "openeaagles/otw/factory.h"
#include "openeaagles/base/factory.h"

#include <string>
#include <cstdlib>

namespace oe {
namespace example {

// background frame rate
const unsigned int bgRate = 10;

simulation::Station* station = nullptr;

// our class factory
base::Object* factory(const std::string& name)
{
   base::Object* obj = nullptr;

   // example libraries
   if (obj == nullptr) obj = xzmq::factory(name);

   // framework libraries
   if (obj == nullptr) obj = simulation::factory(name);
   if (obj == nullptr) obj = models::factory(name);
   if (obj == nullptr) obj = dis::factory(name);
   if (obj == nullptr) obj = base::factory(name);
   return obj;
}

// station builder
simulation::Station* builder(const std::string& filename)
{
   // read configuration file
   unsigned int num_errors = 0;
   base::Object* obj = base::edl_parser(filename, factory, &num_errors);
   if (num_errors > 0) {
      std::cerr << "File: " << filename << ", number of errors: " << num_errors << std::endl;
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
   std::string configFilename = "test1.edl";

   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   //
   station = builder(configFilename);

   // send a reset event and frame sim once
   station->event(base::Component::RESET_EVENT);
   station->tcFrame( static_cast<double>(1.0/static_cast<double>(station->getTimeCriticalRate())) );

   // create time critical thread
   station->createTimeCriticalProcess();
   // short pause to allow os to startup thread
   base::msleep(2000);

   // calculate delta time for background thread
   const double dt = 1.0/static_cast<double>(bgRate);

   // system time of day
   double simTime = 0.0;                                // Simulator time reference
   const double startTime = base::getComputerTime();    // Time of day (sec) run started

   //int k = 0;
   std::cout << "Starting background main loop ..." << std::endl;
   for(;;) {

      // update background thread
      station->updateData( static_cast<double>(dt) );

      simTime += dt;                                   // time of next frame
      const double timeNow = base::getComputerTime();  // time now
      const double elapsedTime = timeNow - startTime;
      const double nextFrameStart = simTime - elapsedTime;
      const int sleepTime = static_cast<int>(nextFrameStart*1000.0);

      // wait for the next frame
      if (sleepTime > 0)
         base::msleep(sleepTime);

/*
    std::cout << ".";
    k += 1;
    if ( k == 40 ) {
      std::cout << "\n";
      k = 0;
    }
*/

   }
   return 0;
}

}
}

//
int main(int argc, char* argv[])
{
   return oe::example::main(argc, argv);
}

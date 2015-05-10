//--------------------------------------------------------------
// Example that demonstrates Laero model functionality
//--------------------------------------------------------------

#include "openeaagles/basicGL/Graphic.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/simulation/Station.h"
#include "Factory.h"

#include <GL/glut.h>
#include <cstring>
#include <cstdlib>

namespace Eaagles {
namespace Example {

// background frame rate
const int bgRate = 10;

// top level Station object
static Simulation::Station* station = nullptr;

// station builder
static Simulation::Station* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   Basic::Object* obj = Basic::lcParser(filename, Factory::createObj, &errors);
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
   Simulation::Station* station = dynamic_cast<Simulation::Station*>(obj);
   if (station == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return station;
}

//-----------------------------------------------------------------------------
// Station's background tasks -- a callback from a GLUT timer, it's basically the
// top level of our background thread.  (Note: GlutDisplay will handle the
// background thread, updateData, for all of its graphics components)
//-----------------------------------------------------------------------------
static void updateDataCB(int)
{
   double dt0 = 1.0 / static_cast<double>(bgRate);
   unsigned int millis = static_cast<unsigned int>(dt0 * 1000);
   glutTimerFunc(millis, updateDataCB, 1);

   // current time
   double time = getComputerTime();

   // N-1 Time
   static double time0 = time;

   // compute delta time
   LCreal dt = static_cast<LCreal>(time - time0);
   time0 = time;

   station->updateData(dt);
}

//
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   const char* configFilename = "test.edl";

   // parse command arguments
   for (int i=1; i<argc; i++) {
      if (std::strcmp(argv[i], "-f") == 0) {
         configFilename = argv[++i];
      }
   }

   // build a station
   station = builder(configFilename);

   // reset the simulation
   station->event(Basic::Component::RESET_EVENT);

   // create the time critical thread
   station->createTimeCriticalProcess();

   // set timer for the background tasks
   double dt = 1.0/static_cast<double>(bgRate);
   unsigned int millis = static_cast<unsigned int>(dt * 1000);

   // ensure everything is reset
   station->updateData(dt);
   station->event(Basic::Component::RESET_EVENT);

   glutTimerFunc(millis, updateDataCB, 1);

   // main loop to update graphics
   glutMainLoop();

   return EXIT_SUCCESS;
}

}
}

//
int main(int argc, char* argv[])
{
   return Eaagles::Example::main(argc, argv);
}

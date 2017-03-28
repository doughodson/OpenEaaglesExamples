//--------------------------------------------------------------
// Example program that demonstrates UBF functionality
//--------------------------------------------------------------

#include "openeaagles/simulation/Station.hpp"
#include "openeaagles/graphics/Graphic.hpp"
#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/Timers.hpp"
#include "openeaagles/base/util/system_utils.hpp"

#include "factory.hpp"

#include <GL/glut.h>
#include <string>
#include <cstdlib>

// default background frame rate
const unsigned int bgRate = 10;

// top level Station object
oe::simulation::Station* station = nullptr;

// station builder
oe::simulation::Station* builder(const std::string& filename)
{
   // read configuration file
   unsigned int num_errors = 0;
   oe::base::Object* obj = oe::base::edl_parser(filename, factory, &num_errors);
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
   const auto pair = dynamic_cast<oe::base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   const auto station = dynamic_cast<oe::simulation::Station*>(obj);
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
void updateDataCB(int msecs)
{
   glutTimerFunc(msecs, updateDataCB, msecs);

   // current time
   const double time = oe::base::getComputerTime();

   // compute delta time
   static double time0 = time;   // N-1 Time
   const auto dt = static_cast<double>(time - time0);
   time0 = time;

   station->updateData(dt);
}

//
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration file
   std::string configFilename = "test00.edl";

   // parse command arguments
   for (int i=1; i<argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   // build a station
   station = builder(configFilename);

   // reset the simulation
   station->event(oe::base::Component::RESET_EVENT);

   // set timer for the background tasks
   const double dt = 1.0 / static_cast<double>(bgRate);
   const auto msecs = static_cast<int>(dt * 1000);

   // ensure everything is reset
   station->updateData(dt);
   station->updateTC(dt);
   station->event(oe::base::Component::RESET_EVENT);
   station->reset();

   glutTimerFunc(msecs, updateDataCB, msecs);

   // create the time critical thread
   station->createTimeCriticalProcess();

   // main loop to update graphics
   glutMainLoop();

   return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------
// Infrared calculations test program
//------------------------------------------------------------------------------

#include "TestStation.hpp"

#include "factory.hpp"

#include "openeaagles/graphics/Graphic.hpp"
#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/Timers.hpp"
#include "openeaagles/base/util/system_utils.hpp"

#include <GL/glut.h>

#include <string>
#include <cstdlib>

// background frame rate
const unsigned int bgRate = 10;

TestStation* testStation = nullptr;

// test station builder
TestStation* builder(const std::string& filename)
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
   const auto testStation = dynamic_cast<TestStation*>(obj);
   if (testStation == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return testStation;
}

//-----------------------------------------------------------------------------
// Station's background tasks -- a callback from a GLUT timer, it's the
// top level of our background thread.  (Note: GlutDisplay will handle the
// background thread, updateData, for all of its graphics components)
//-----------------------------------------------------------------------------
void updateDataCB(int)
{
   const double dt0 = 1.0 / static_cast<double>(bgRate);
   const auto millis = static_cast<unsigned int>(dt0 * 1000);
   glutTimerFunc(millis, updateDataCB, 1);

   // Current time
   const double time = oe::base::getComputerTime();

   // N-1 Time
   static double time0 = time;

   // Compute delta time
   const auto dt = static_cast<double>(time - time0);
   time0 = time;

   oe::base::Timer::updateTimers(dt);
   oe::graphics::Graphic::flashTimer(dt);
   testStation->updateData(dt);
}

//
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   std::string configFilename = "test1.edl";

   // parse arguments
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   testStation = builder(configFilename);

   // reset the Simulation
   testStation->event(oe::base::Component::RESET_EVENT);

   // set timer for the background tasks
   const double dt = 1.0 / static_cast<double>(bgRate);
   const auto millis = static_cast<unsigned int>(dt * 1000);

   // ensure everything is reset
   testStation->updateData(dt);
   testStation->updateTC(dt);
   testStation->event(oe::base::Component::RESET_EVENT);

   glutTimerFunc(millis, updateDataCB, 1);

   testStation->createTimeCriticalProcess();

   // ---
   // Main loop
   // ---
   glutMainLoop();
   return 0;
}

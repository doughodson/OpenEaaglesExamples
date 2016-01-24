//------------------------------------------------------------------------------
// IR example
//------------------------------------------------------------------------------

#include "TestStation.h"

#include "Factory.h"

#include "openeaagles/basicGL/Graphic.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include <GL/glut.h>

#include <cstring>
#include <cstdlib>

namespace oe {
namespace example {

// background frame rate
const int bgRate = 10;

static TestStation* testStation = nullptr;

// test station builder
static TestStation* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   basic::Object* obj = basic::lcParser(filename, Factory::createObj, &errors);
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
   TestStation* testStation = dynamic_cast<TestStation*>(obj);
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
static void updateDataCB(int)
{
   const double dt0 = 1.0 / static_cast<double>(bgRate);
   const unsigned int millis = static_cast<unsigned int>(dt0 * 1000);
   glutTimerFunc(millis, updateDataCB, 1);

   // Current time
   const double time = getComputerTime();

   // N-1 Time
   static double time0 = time;

   // Compute delta time
   const LCreal dt = static_cast<LCreal>(time - time0);
   time0 = time;

   basic::Timer::updateTimers(dt);
   BasicGL::Graphic::flashTimer(dt);
   testStation->updateData(dt);
}

//
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   const char* configFilename = "test1.edl";

   // parse arguments
   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i],"-f") == 0) {
         configFilename = argv[++i];
      }
   }

   testStation = builder(configFilename);

   // reset the Simulation
   testStation->event(basic::Component::RESET_EVENT);

   // set timer for the background tasks
   const double dt = 1.0 / static_cast<double>(bgRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);

   // ensure everything is reset
   testStation->updateData(dt);
   testStation->updateTC(dt);
   testStation->event(oe::basic::Component::RESET_EVENT);

   glutTimerFunc(millis, updateDataCB, 1);

   testStation->createTimeCriticalProcess();

   // ---
   // Main loop
   // ---
   glutMainLoop();
   return 0;
}

} // end example namespace
} // end oe namespace

//
int main(int argc, char* argv[])
{
   return oe::example::main(argc, argv);
}


//------------------------------------------------------------------------------
// Example simulation #3
//------------------------------------------------------------------------------

#include "SimStation.h"

#include "Factory.h"

#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basicGL/Graphic.h"
#include "openeaagles/basicGL/Texture.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

#include <cstdlib>

namespace Eaagles {
namespace Example {

// default background frame rate
static const int BG_RATE = 10;

static SimStation* simStation = nullptr;

// SimStation builder
static SimStation* builder(const char* const filename)
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
   SimStation* simStation = dynamic_cast<SimStation*>(obj);
   if (simStation == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return simStation;
}

//-----------------------------------------------------------------------------
// updateDataCB() -- Station's background tasks
//-----------------------------------------------------------------------------
static void updateDataCB(int msecs)
{
   glutTimerFunc(msecs, updateDataCB, msecs);

   // Current time
   double time = Eaagles::getComputerTime();

   // Compute delta time
   static double time0 = time;   // N-1 Time
   Eaagles::LCreal dt = static_cast<Eaagles::LCreal>(time - time0);
   time0 = time;

   simStation->updateData(dt);
}

//
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   const char* configFilename = "test0.edl";
   // parse arguments
   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i],"-f") == 0) {
         configFilename = argv[++i];
      }
   }
   simStation = builder(configFilename);

   // reset station
   simStation->event(Basic::Component::RESET_EVENT);

   // set timer for background tasks
   double dt = 1.0/static_cast<double>(BG_RATE);
   int msecs = static_cast<int>(dt * 1000);

   // ensure everything is reset
   simStation->updateData(dt);
   simStation->updateTC(dt);
   simStation->event(Basic::Component::RESET_EVENT);

   glutTimerFunc(msecs, updateDataCB, msecs);

   simStation->createTimeCriticalProcess();

   glutMainLoop();
   return 0;
}

} // End Example namespace
} // End Eaagles namespace

//
int main(int argc, char* argv[])
{
   return Eaagles::Example::main(argc, argv);
}

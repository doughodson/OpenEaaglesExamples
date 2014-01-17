//=============================================================================
// Example simulation #3
//=============================================================================

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

namespace Eaagles {
namespace Example {

// Default configuration file
static const char* const DEFAULT_CONFIG_FILE = "test0.edl";

// Default background frame rate
static const int BG_RATE = 10;

// System descriptions
static SimStation* station = 0;

//-----------------------------------------------------------------------------
// readTest() -- function to the read description files
//-----------------------------------------------------------------------------
static SimStation* readTest(const char* const fileName)
{
   int errors = 0;
   Basic::Object* q1 = lcParser(fileName, Factory::createObj, &errors);
   if (errors > 0) {
      std::cerr << "Errors in reading file: " << errors << std::endl;
      return 0;
   }

   SimStation* sys = 0;
   if (q1 != 0) {

      // When we were given a Basic::Pair, get the pointer to its object.
      Basic::Pair* pp = dynamic_cast<Basic::Pair*>(q1);
         if (pp != 0) {
         q1 = pp->object();
      }

      // What we should have here is the description object and
      // it should be of the correct type
      sys = dynamic_cast<SimStation*>(q1);

   }
   return sys;
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
   Eaagles::LCreal dt = Eaagles::LCreal(time - time0);
   time0 = time;

   station->updateData(dt);
}


//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // Config file file
   const char* configFile = DEFAULT_CONFIG_FILE;

   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i],"-f") == 0) {
         configFile = argv[++i];
      }
   }

// ---
// Read in the description files
// ---
   station = readTest(configFile);

    // Make sure we did get a valid object (we must have one!)
    if (station == 0) {
        std::cout << "Invalid description file!" << std::endl;
        return 0;
    }

// ---
// Reset the station
// ---
    station->event(Basic::Component::RESET_EVENT);
    
// ---
// Set timer for background tasks
// ---

   double dt = 1.0/double(BG_RATE);
   int msecs = (int) (dt * 1000);

   // ensure everything is reset
   station->updateData(dt);
   station->updateTC(dt);
   station->event(Eaagles::Basic::Component::RESET_EVENT);

   glutTimerFunc(msecs, updateDataCB, msecs);

// ---
// Create Time Critical Thread
// ---
    station->createTimeCriticalProcess();

// ---
// Main loop
// ---

    glutMainLoop();
    return 0;
}

} // End Example namespace
} // End Eaagles namespace


//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::Example::main(argc, argv);
}

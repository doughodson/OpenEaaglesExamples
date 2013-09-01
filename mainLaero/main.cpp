//*****************************************************************************
// MainDyn4Dof -- test program that will test out the Dynamic 4 degree
// of freedom model.  
//*****************************************************************************

#include "openeaagles/basicGL/Graphic.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/simulation/Station.h"
#include "formFunc.h"
#include <GL/glut.h>


namespace Eaagles {
namespace MainDyn4Dof {

// Background frame rate
const int bgRate = 10;

// System descriptions
static Simulation::Station* station = 0;	

//-----------------------------------------------------------------------------
// Read the configuration file
//-----------------------------------------------------------------------------
static Simulation::Station* readConfigFile(const char* const fileName)
{
	Simulation::Station* p = 0;


   // Read the description file
   int errors = 0;
   Basic::Object* q1 = Basic::lcParser(fileName, formFunc, &errors);
   if (errors > 0) {
      std::cerr << "File: " << fileName << ", errors: " << errors << std::endl;
      return 0;
   }

   if (q1 != 0) {
      // When we were given a Basic::Pair, get the pointer to its object.
      Basic::Pair* pp = dynamic_cast<Basic::Pair*>(q1);
      if (pp != 0) {
         q1 = pp->object();
      }

      // What we should have here is the Station object
	  p = dynamic_cast<Simulation::Station*>(q1);
   }

   //LDBp->serialize(std::cout);
    
   return p;
}

//-----------------------------------------------------------------------------
// Station's background tasks -- a callback from a GLUT timer, it's basicly the
// top level of our background thread.  (Note: GlutDisplay will handle the
// background thread, updateData, for all of its graphics components)
//-----------------------------------------------------------------------------
static void updateDataCB(int)
{
   double dt0 = 1.0/double(bgRate);
   unsigned int millis = (unsigned int) (dt0 * 1000);
   glutTimerFunc(millis, updateDataCB, 1);

   // Current time
   double time = getComputerTime();

   // N-1 Time
   static double time0 = time;

   // Compute delta time
   LCreal dt = LCreal(time - time0);
   time0 = time;

   station->updateData(dt);
}


//-----------------------------------------------------------------------------
// Eaagles::Mainx9::main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // Config file file
   const char* configFile = "test.edl";

   // Parse arguments
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i],"-f") == 0) {
         configFile = argv[++i];
      }
   }

// ---
// Read in the description files
// ---
   station = readConfigFile(configFile);
   if (station == 0) {
      std::cerr << "Invalid configuration file!" << std::endl;
      exit(EXIT_FAILURE);
   }

// ---
// Reset the Simulation
// ---
   station->event(Basic::Component::RESET_EVENT);

// ---
// Set timer for the background tasks
// ---
// ---
// Create the Time Critical Thread (updateTC())
// ---
   station->createTimeCriticalProcess();

   double dt = 1.0/double(bgRate);
   unsigned int millis = (unsigned int) (dt * 1000);

   // ensure everything is reset
   station->updateData(dt);
   station->event(Eaagles::Basic::Component::RESET_EVENT);

   glutTimerFunc(millis, updateDataCB, 1);



// ---
// Main loop
// ---
   glutMainLoop();
   return 0;
}

} // End MainDyn4Dof namespace
} // End Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::MainDyn4Dof::main(argc, argv);
}
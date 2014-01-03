//------------------------------------------------------------------------------
// testRadar -- A general purpose radar test program.
//------------------------------------------------------------------------------

#include "TestStation.h"
#include "Factory.h"

#include "openeaagles/basicGL/Graphic.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include <GL/glut.h>

//#define PARSE_TIMING_TEST

namespace Eaagles {
namespace Test {

// Background frame rate
const int bgRate = 10;

// System descriptions
static TestStation* station = 0;

// build a station
static TestStation* builder(const char* const fileName)
{
   TestStation* p = 0;

#ifdef PARSE_TIMING_TEST
    LARGE_INTEGER cFreq;
    QueryPerformanceFrequency(&cFreq);
    LONGLONG freq = cFreq.QuadPart;

    LARGE_INTEGER fcnt;
    QueryPerformanceCounter(&fcnt);
    LONGLONG startCnt = fcnt.QuadPart;
#endif

   // Read the description file
   int errors = 0;
   Basic::Object* q1 = lcParser(fileName, Factory::createObj, &errors);
   if (errors > 0) {
      std::cerr << "File: " << fileName << ", errors: " << errors << std::endl;
      return 0;
   }

#ifdef PARSE_TIMING_TEST
    QueryPerformanceCounter(&fcnt);
    LONGLONG endCnt = fcnt.QuadPart;
    double dfreq = freq;
    double dcnt = endCnt - startCnt;
    double dtime = dcnt/dfreq;
    //double dtime1 = ( dtime * 1000.0 );
    std::cout << "dtime1 = " << dtime1 << "MS" << std::endl;
#endif

   if (q1 != 0) {
      // When we were given a Basic::Pair, get the pointer to its object.
      Basic::Pair* pp = dynamic_cast<Basic::Pair*>(q1);
      if (pp != 0) {
         q1 = pp->object();
      }

      // What we should have here is the Station object
      p = dynamic_cast<TestStation*>(q1);
   }

   //p->serialize(std::cout);
    
   return p;
}

//-----------------------------------------------------------------------------
// Station's background tasks -- a callback from a GLUT timer, it's basically the
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
// Eaagles::Test::main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // Config file file
   const char* configFile = "test2a.edl";

   // Parse arguments
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i],"-f") == 0) {
         configFile = argv[++i];
      }
   }

// ---
// Build a station
// ---
   station = builder(configFile);
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

   double dt = 1.0/double(bgRate);
   unsigned int millis = (unsigned int) (dt * 1000);

   // ensure everything is reset
   station->updateData(dt);
   station->updateTC(dt);
   station->event(Eaagles::Basic::Component::RESET_EVENT);

   glutTimerFunc(millis, updateDataCB, 1);

// ---
// Create the Time Critical Thread (updateTC())
// ---
    station->createTimeCriticalProcess();

// ---
// Main loop
// ---
   glutMainLoop();
   return 0;
}

} // End Test namespace
} // End Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::Test::main(argc, argv);
}

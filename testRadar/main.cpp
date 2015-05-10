//------------------------------------------------------------------------------
// A general purpose radar test program.
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

//#define PARSE_TIMING_TEST

namespace Eaagles {
namespace Test {

// background frame rate
const int bgRate = 10;

//
static TestStation* testStation = nullptr;

// test station builder
static TestStation* builder(const char* const filename)
{
#ifdef PARSE_TIMING_TEST
    LARGE_INTEGER cFreq;
    QueryPerformanceFrequency(&cFreq);
    LONGLONG freq = cFreq.QuadPart;

    LARGE_INTEGER fcnt;
    QueryPerformanceCounter(&fcnt);
    LONGLONG startCnt = fcnt.QuadPart;
#endif

   // read configuration file
   int errors = 0;
   Basic::Object* obj = Basic::lcParser(filename, Factory::createObj, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
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
   TestStation* testStation = dynamic_cast<TestStation*>(obj);
   if (testStation == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return testStation;
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

   testStation->updateData(dt);
}

//
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   const char* configFilename = "test2a.edl";

   // parse arguments
   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i], "-f") == 0) {
         configFilename = argv[++i];
      }
   }

   // build a station
   testStation = builder(configFilename);

   // reset the Simulation
   testStation->event(Basic::Component::RESET_EVENT);

   // set timer for the background tasks
   double dt = 1.0/static_cast<double>(bgRate);
   unsigned int millis = static_cast<unsigned int>(dt * 1000);

   // ensure everything is reset
   testStation->updateData(dt);
   testStation->updateTC(dt);
   testStation->event(Basic::Component::RESET_EVENT);

   glutTimerFunc(millis, updateDataCB, 1);

   // create the Time Critical Thread (updateTC())
   testStation->createTimeCriticalProcess();

   // main loop
   glutMainLoop();
   return 0;
}

} // end Test namespace
} // end Eaagles namespace

//
int main(int argc, char* argv[])
{
   return Eaagles::Test::main(argc, argv);
}

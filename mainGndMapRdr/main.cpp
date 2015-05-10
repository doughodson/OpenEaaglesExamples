
#include "Station.h"
#include "Factory.h"

#include "openeaagles/terrain/ded/DedFile.h"

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/functors/Tables.h"
#include "openeaagles/basic/units/Angles.h"

#include "openeaagles/basicGL/Graphic.h"
#include "openeaagles/basicGL/basicGLFF.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

#include <cstdlib>

namespace Eaagles {
namespace Example {

// background rate
const int bgRate = 20;

// System descriptions
static class TestStation* testStation = nullptr;

// updateDataCB() -- Station's background tasks
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

   Basic::Timer::updateTimers(dt);
   BasicGL::Graphic::flashTimer(dt);
   testStation->updateData(dt);
}

// test station builder
static TestStation* builder(const char* const filename)
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
   TestStation* testStation = dynamic_cast<TestStation*>(obj);
   if (testStation == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return testStation;
}

//
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

   // default configuration filename
   const char* configFilename = "test.edl";

   // build a test station
   testStation = builder(configFilename);

   // resetting the system will load the data files

   std::cout << "starting loading files --" << std::endl;
   double start = getComputerTime();

   testStation->reset();

   double end = getComputerTime();
   double dtime = (end - start);
   std::cout << "finished loading files: time(s) = " << dtime << std::endl;

   // set timer for background tasks
   double dt = 1.0/static_cast<double>(bgRate);
   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, updateDataCB, 1);

   testStation->createTimeCriticalProcess();

   glutMainLoop();
   return 0;
}

} // end Example namespace
} // end Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::Example::main(argc,argv);
}


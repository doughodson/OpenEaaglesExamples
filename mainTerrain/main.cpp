//------------------------------------------------------------------------------
// Example terrain functions
//------------------------------------------------------------------------------
#include "Display.h"
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
#include "openeaagles/gui/glut/glutFF.h"
#include <GL/glut.h>

#include <cstdlib>

namespace Eaagles {
namespace Example {

// frame rate
const int frameRate = 10;

static class Display* display = nullptr;

// timerFunc() -- time critical stuff
static void timerFunc(int)
{
   double dt = 1.0 / static_cast<double>(frameRate);

   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   Basic::Timer::updateTimers(static_cast<LCreal>(dt));
   BasicGL::Graphic::flashTimer(static_cast<LCreal>(dt));
   display->tcFrame(static_cast<LCreal>(dt));
}

// display builder
static Display* builder(const char* const filename)
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
   Display* display = dynamic_cast<Display*>(obj);
   if (display == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return display;
}

//
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

   // default configuration filename
   const char* configFilename = "test.edl";

   // build a display
   display = builder(configFilename);

   // resetting the system will load the data files
   std::cout << "starting loading files --" << std::endl;
   double start = getComputerTime();

   display->reset();

   double end = getComputerTime();
   double dtime = (end - start);
   std::cout << "finished loading files: time(s) = " << dtime << std::endl;

   // create a display window
   display->createWindow();

   // set timer
   double dt = 1.0/static_cast<double>(frameRate);
   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   glutMainLoop();
   return 0;
}

} // end Example namespace
} // end Eaagles namespace

//
int main(int argc, char* argv[])
{
   return Eaagles::Example::main(argc,argv);
}

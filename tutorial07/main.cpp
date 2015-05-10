
#include <cstring>
#include <cstdlib>

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

// class factories
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/basic/Factory.h"
#include "openeaagles/gui/glut/Factory.h"

#include "Worm.h"

namespace Eaagles {
namespace Tutorial {

// frame rate
const int frameRate = 20;

static class Glut::GlutDisplay* glutDisplay = nullptr;

// timerFunc() -- Time critical stuff)
static void timerFunc(int)
{
   double dt = 1.0 / static_cast<double>(frameRate);

   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   Basic::Timer::updateTimers(static_cast<float>(dt));
   BasicGL::Graphic::flashTimer(static_cast<LCreal>(dt));
   glutDisplay->tcFrame(static_cast<LCreal>(dt));
}

// our class factory
static Basic::Object* factory(const char* const name)
{
  Basic::Object* obj = nullptr;

  if ( std::strcmp(name, Worm::getFactoryName()) == 0 ) {
    obj = new Worm;
  }

  // Default to base classes
  if (obj == nullptr) obj = Glut::Factory::createObj(name);
  if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
  if (obj == nullptr) obj = Basic::Factory::createObj(name);

  return obj;
}

// display builder
static Glut::GlutDisplay* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   Basic::Object* obj = Basic::lcParser(filename, factory, &errors);
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
   Glut::GlutDisplay* glutDisplay = dynamic_cast<Glut::GlutDisplay*>(obj);
   if (glutDisplay == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return glutDisplay;
}

int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   const char* configFilename = "file0.edl";

   // build a display
   glutDisplay = builder(configFilename);

   // create a display window
   glutDisplay->createWindow();

   // set timer
   double dt = 1.0/static_cast<double>(frameRate);
   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   // main loop
   glutMainLoop();
   return 0;
}

} // namespace Tutorial
} // namespace Eaagles

//
int main(int argc, char* argv[])
{
   Eaagles::Tutorial::main(argc, argv);
}



#include <cstring>
#include <cstdlib>

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

// class factories
#include "openeaagles/basic/Factory.h"
#include "openeaagles/graphics/Factory.h"
#include "openeaagles/gui/glut/Factory.h"

#include "MyPager.h"
#include "Worm.h"

namespace oe {
namespace Tutorial {

// frame rate
const int frameRate = 20;

static class glut::GlutDisplay* glutDisplay = nullptr;

// timerFunc() -- Time critical stuff)
static void timerFunc(int)
{
    double dt = 1.0 / static_cast<double>(frameRate);

    unsigned int millis = static_cast<unsigned int>(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    basic::Timer::updateTimers(dt);
    graphics::Graphic::flashTimer(dt);
    glutDisplay->tcFrame(dt);
}

// our class factory
static basic::Object* factory(const char* const name)
{
  basic::Object* obj = nullptr;

  if ( std::strcmp(name, MyPager::getFactoryName()) == 0 ) {
    obj = new MyPager;
  }
  else if ( std::strcmp(name, Worm::getFactoryName()) == 0 ) {
    obj = new Worm;
  }

  if (obj == nullptr) obj = glut::Factory::createObj(name);
  if (obj == nullptr) obj = graphics::Factory::createObj(name);
  if (obj == nullptr) obj = basic::Factory::createObj(name);

  return obj;
}

// display builder
static glut::GlutDisplay* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   basic::Object* obj = basic::lcParser(filename, factory, &errors);
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
   glut::GlutDisplay* glutDisplay = dynamic_cast<glut::GlutDisplay*>(obj);
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
} // namespace oe

//
int main(int argc, char* argv[])
{
   oe::Tutorial::main(argc, argv);
}

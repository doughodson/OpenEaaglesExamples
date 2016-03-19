
#include <cstring>
#include <cstdlib>

#include "openeaagles/base/Pair.h"
#include "openeaagles/base/Timers.h"
#include "openeaagles/base/parser.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

// factories
#include "openeaagles/base/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"

#include "MyPager.h"
#include "Worm.h"

namespace oe {
namespace tutorial {

// frame rate
const int frameRate = 20;

static class glut::GlutDisplay* glutDisplay = nullptr;

// timerFunc() -- Time critical stuff)
static void timerFunc(int)
{
    double dt = 1.0 / static_cast<double>(frameRate);

    unsigned int millis = static_cast<unsigned int>(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    base::Timer::updateTimers(dt);
    graphics::Graphic::flashTimer(dt);
    glutDisplay->tcFrame(dt);
}

// our class factory
static base::Object* factory(const char* const name)
{
  base::Object* obj = nullptr;

  if ( std::strcmp(name, MyPager::getFactoryName()) == 0 ) {
    obj = new MyPager;
  }
  else if ( std::strcmp(name, Worm::getFactoryName()) == 0 ) {
    obj = new Worm;
  }

  if (obj == nullptr) obj = glut::factory(name);
  if (obj == nullptr) obj = graphics::factory(name);
  if (obj == nullptr) obj = base::factory(name);

  return obj;
}

// display builder
static glut::GlutDisplay* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   base::Object* obj = base::edlParser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   base::Pair* pair = dynamic_cast<base::Pair*>(obj);
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

} // namespace tutorial
} // namespace oe

//
int main(int argc, char* argv[])
{
   oe::tutorial::main(argc, argv);
}

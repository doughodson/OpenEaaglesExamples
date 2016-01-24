//----------------------------------------------------------------
// Test Component send command, using different parameters
//----------------------------------------------------------------
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Timers.h"

#include <GL/glut.h>

// class factories
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/basic/Factory.h"
#include "openeaagles/gui/glut/Factory.h"

#include "Display.h"
#include "ObjectHandler.h"

#include <cstring>
#include <cstdlib>

namespace oe {
namespace test {

// frame rate
const int frameRate = 20;

static class Display* display = nullptr;

// timerFunc()
static void timerFunc(int)
{
   double dt = 1.0 / static_cast<double>(frameRate);

   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   basic::Timer::updateTimers(static_cast<LCreal>(dt));
   BasicGL::Graphic::flashTimer(static_cast<LCreal>(dt));
   display->tcFrame(static_cast<LCreal>(dt));
}

// our class factory
static basic::Object* factory(const char* name)
{
   basic::Object* obj = nullptr;

   if (std::strcmp(name, Display::getFactoryName()) == 0) {
      obj = new Display();
   }
   else if (std::strcmp(name, ObjectHandler::getFactoryName()) == 0) {
      obj = new ObjectHandler();
   }
   else {
      if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
      if (obj == nullptr) obj = glut::Factory::createObj(name);
      if (obj == nullptr) obj = basic::Factory::createObj(name);
   }

   return obj;
}

// display builder
static Display* builder(const char* const filename)
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

   display = builder(configFilename);

   // create a display window
   display->createWindow();

   // set timer
   double dt = 1.0/static_cast<double>(frameRate);
   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   // main loop
   glutMainLoop();

   return 0;
}

} // End test namespace
} // End oe namespace

//
int main(int argc, char* argv[])
{
   return oe::test::main(argc,argv);
}

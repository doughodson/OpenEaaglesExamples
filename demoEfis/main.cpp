//----------------------------------------------------------------
// Demo app for Efis
//----------------------------------------------------------------
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/Timers.h"
#include "openeaagles/base/parser.h"
#include "openeaagles/graphics/Graphic.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

// factories
#include "openeaagles/instruments/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/base/factory.h"

// Test pages
#include "TestMechanical.h"
#include "TestElectronic.h"

#include <cstring>
#include <cstdlib>

namespace oe {
namespace demo {

// frame rate
const int frameRate = 20;

// System descriptions
glut::GlutDisplay* glutDisplay = nullptr;

// timerFunc() -- Time critical stuff)
void timerFunc(int)
{
   double dt = 1.0f / static_cast<double>(frameRate);

   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   base::Timer::updateTimers(dt);
   graphics::Graphic::flashTimer(dt);
   glutDisplay->updateTC(dt);
}

// our class factory
base::Object* factory(const char* name)
{
   base::Object* obj = nullptr;

   // Tests
   if ( std::strcmp(name, TestMechanical::getFactoryName()) == 0 ) {
      obj = new TestMechanical;
   }
   else if ( std::strcmp(name, TestElectronic::getFactoryName()) == 0 ) {
      obj = new TestElectronic;
   }

   else {
      if (obj == nullptr) obj = oe::instruments::factory(name);
      if (obj == nullptr) obj = oe::graphics::factory(name);
      if (obj == nullptr) obj = oe::glut::factory(name);
      if (obj == nullptr) obj = oe::base::factory(name);
   }
   return obj;
}

// display builder
glut::GlutDisplay* builder(const char* const filename)
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

//
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   const char* configFilename = "test.edl";

   glutDisplay = builder(configFilename);

   // create a display window
   glutDisplay->createWindow();

   // set timer
   double dt = 1.0/static_cast<double>(frameRate);
   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   glutMainLoop();
   return 0;
}

} // end demo namespace
} // end oe namespace

//
int main(int argc, char* argv[])
{
   return oe::demo::main(argc, argv);
}

//----------------------------------------------------------------
// Test Component send command, using different parameters
//----------------------------------------------------------------
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/edl_parser.h"
#include "openeaagles/base/Timers.h"

#include <GL/glut.h>

// factories
#include "openeaagles/graphics/factory.h"
#include "openeaagles/base/factory.h"
#include "openeaagles/gui/glut/factory.h"

#include "Display.h"
#include "ObjectHandler.h"

#include <string>
#include <cstdlib>

namespace oe {
namespace test {

// frame rate
const unsigned int frameRate = 20;

Display* display = nullptr;

// timerFunc()
void timerFunc(int)
{
   const double dt = 1.0 / static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   base::Timer::updateTimers(static_cast<double>(dt));
   graphics::Graphic::flashTimer(static_cast<double>(dt));
   display->tcFrame(static_cast<double>(dt));
}

// our class factory
base::Object* factory(const std::string& name)
{
   base::Object* obj = nullptr;

   if ( name == Display::getFactoryName() ) {
      obj = new Display();
   }
   else if ( name == ObjectHandler::getFactoryName() ) {
      obj = new ObjectHandler();
   }
   else {
      if (obj == nullptr) obj = graphics::factory(name);
      if (obj == nullptr) obj = glut::factory(name);
      if (obj == nullptr) obj = base::factory(name);
   }

   return obj;
}

// display builder
Display* builder(const std::string& filename)
{
   // read configuration file
   unsigned int errors = 0;
   base::Object* obj = base::edl_parser(filename, factory, &errors);
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
   std::string configFilename = "test.edl";

   display = builder(configFilename);

   // create a display window
   display->createWindow();

   // set timer
   const double dt = 1.0 / static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   // main loop
   glutMainLoop();

   return 0;
}

}
}

//
int main(int argc, char* argv[])
{
   return oe::test::main(argc,argv);
}

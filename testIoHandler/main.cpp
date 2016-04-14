//----------------------------------------------------------------
// I/O device test program
//----------------------------------------------------------------
#include "Display.h"
#include "factory.h"

#include "openeaagles/base/Pair.h"
#include "openeaagles/base/Timers.h"
#include "openeaagles/base/parser.h"

#include <GL/glut.h>

#include <string>
#include <cstdlib>

namespace oe {
namespace test {

// frame rate
const unsigned int frameRate = 20;

Display* display = nullptr;

// timerFunc() -- Time critical stuff)
void timerFunc(int)
{
   const double dt = 1.0 / static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   base::Timer::updateTimers(dt);
   graphics::Graphic::flashTimer(dt);
   display->updateTC(dt);
}

// display builder
Display* builder(const std::string& filename)
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
   std::string configFilename = "test1.edl";
   // parse arguments
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   // build a display
   display = builder(configFilename);

   // create a display window
   display->createWindow();

   // reset the system
   display->reset();

   // set timer
   const double dt = 1.0 / static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   // main loop
   glutMainLoop();
   return 0;
}

} // end of test namespace
} // end of oe namespace

//
int main(int argc, char* argv[])
{
   oe::test::main(argc,argv);
}

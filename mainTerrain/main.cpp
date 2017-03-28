//------------------------------------------------------------------------------
// Example terrain functions
//------------------------------------------------------------------------------
#include "Display.hpp"
#include "factory.hpp"

#include "openeaagles/terrain/ded/DedFile.hpp"
#include "openeaagles/base/util/system_utils.hpp"

#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/Timers.hpp"
#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/base/functors/Tables.hpp"
#include "openeaagles/base/units/Angles.hpp"
#include "openeaagles/graphics/Graphic.hpp"

#include "openeaagles/gui/glut/GlutDisplay.hpp"
#include <GL/glut.h>

#include <string>
#include <cstdlib>

// frame rate
const unsigned int frameRate = 10;

Display* display = nullptr;

// timerFunc() -- time critical stuff
void timerFunc(int)
{
   const double dt = 1.0 / static_cast<double>(frameRate);
   const auto millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   oe::base::Timer::updateTimers(static_cast<double>(dt));
   oe::graphics::Graphic::flashTimer(static_cast<double>(dt));
   display->tcFrame(static_cast<double>(dt));
}

// display builder
Display* builder(const std::string& filename)
{
   // read configuration file
   unsigned int num_errors = 0;
   oe::base::Object* obj = oe::base::edl_parser(filename, factory, &num_errors);
   if (num_errors > 0) {
      std::cerr << "File: " << filename << ", number of errors: " << num_errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   const auto pair = dynamic_cast<oe::base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   const auto display = dynamic_cast<Display*>(obj);
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

   // build a display
   display = builder(configFilename);

   // resetting the system will load the data files
   std::cout << "starting loading files --" << std::endl;
   const double start = oe::base::getComputerTime();

   display->reset();

   const double end = oe::base::getComputerTime();
   const double dtime = (end - start);
   std::cout << "finished loading files: time(s) = " << dtime << std::endl;

   // create a display window
   display->createWindow();

   // set timer
   const double dt = 1.0 / static_cast<double>(frameRate);
   const auto millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   glutMainLoop();
   return 0;
}

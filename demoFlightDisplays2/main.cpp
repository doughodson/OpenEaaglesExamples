//----------------------------------------------------------------
// Example flight displays 2
//----------------------------------------------------------------
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/Timers.hpp"
#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/graphics/Graphic.hpp"
#include "openeaagles/gui/glut/GlutDisplay.hpp"
#include <GL/glut.h>

// factories
#include "openeaagles/base/factory.hpp"
#include "openeaagles/graphics/factory.hpp"
#include "openeaagles/instruments/factory.hpp"
#include "openeaagles/gui/glut/factory.hpp"

// test pages
#include "TestPfd.hpp"
// instruments
#include "Pfd.hpp"
#include "SpdLines.hpp"

#include <string>
#include <cstdlib>

// frame rate
const unsigned int frameRate = 20;

// System descriptions
oe::glut::GlutDisplay* glutDisplay = nullptr;

// timerFunc() -- Time critical stuff
void timerFunc(int)
{
    const double dt = 1.0 / static_cast<double>(frameRate);
    const auto millis = static_cast<unsigned int>(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    oe::base::Timer::updateTimers(dt);
    oe::graphics::Graphic::flashTimer(dt);
    glutDisplay->updateTC(dt);
}

// our class factory
oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

    // Test the primary flight display (PFD)
    if ( name == TestPfd::getFactoryName() ) {
        obj = new TestPfd;
    }
    // Pfd
    else if ( name == Pfd::getFactoryName() ) {
        obj = new Pfd;
    }
    // SpdLines
    else if ( name == SpdLines::getFactoryName() ) {
        obj = new SpdLines;
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
oe::glut::GlutDisplay* builder(const std::string& filename)
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
   const auto glutDisplay = dynamic_cast<oe::glut::GlutDisplay*>(obj);
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
   std::string configFilename = "test.edl";
   glutDisplay = builder(configFilename);

   glutDisplay->createWindow();

   // setup timer
   const double dt = 1.0 / static_cast<double>(frameRate);
   const auto millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   glutMainLoop();
   return 0;
}

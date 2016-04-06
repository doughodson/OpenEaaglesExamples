//----------------------------------------------------------------
// Example flight displays 1
//----------------------------------------------------------------
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/Timers.h"
#include "openeaagles/base/parser.h"

#include "openeaagles/graphics/Graphic.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

// factories
#include "openeaagles/base/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/instruments/factory.h"
#include "openeaagles/gui/glut/factory.h"

// test pages
#include "TestPfd.h"
#include "TestSD.h"
// instruments
#include "CrsPntr.h"
#include "Hsi.h"
#include "Pfd.h"
#include "RdrAlt.h"
#include "SituationalDisplay.h"
#include "SpdLines.h"
#include "TerrainFollower.h"

#include <cstring>
#include <cstdlib>

namespace oe {
namespace demo {

// frame rate
const unsigned int frameRate = 20;

// System descriptions
glut::GlutDisplay* glutDisplay = nullptr;

// timerFunc() -- Time critical stuff
void timerFunc(int)
{
    const double dt = 1.0 / static_cast<double>(frameRate);
    const unsigned int millis = static_cast<unsigned int>(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    base::Timer::updateTimers(dt);
    graphics::Graphic::flashTimer(dt);
    glutDisplay->updateTC(dt);
}

// our class factory
base::Object* factory(const char* name)
{
   base::Object* obj = nullptr;

   // Test the primary flight display (PFD)
   if ( std::strcmp(name, TestPfd::getFactoryName()) == 0 ) {
      obj = new TestPfd;
   }
   // situational display
   else if ( std::strcmp(name, TestSD::getFactoryName()) == 0 ) {
      obj = new TestSD;
   }
   // CrsPntr
   else if ( std::strcmp(name, CrsPntr::getFactoryName()) == 0 ) {
      obj = new CrsPntr;
   }
   // Hsi
   else if ( std::strcmp(name, Hsi::getFactoryName()) == 0 ) {
      obj = new Hsi;
   }
   // Pfd
   else if ( std::strcmp(name, Pfd::getFactoryName()) == 0 ) {
      obj = new Pfd;
   }
   // RdrAlt
   else if ( std::strcmp(name, RdrAlt::getFactoryName()) == 0 ) {
      obj = new RdrAlt;
   }
   // SituationalDisplay
   else if ( std::strcmp(name, SituationalDisplay::getFactoryName()) == 0 ) {
      obj = new SituationalDisplay;
   }
   // SpdLines
   else if ( std::strcmp(name, SpdLines::getFactoryName()) == 0 ) {
      obj = new SpdLines;
   }
   // TerrainFollower
   else if ( std::strcmp(name, TerrainFollower::getFactoryName()) == 0 ) {
      obj = new TerrainFollower;
   }

   if (obj == nullptr) obj = instruments::factory(name);
   if (obj == nullptr) obj = graphics::factory(name);
   if (obj == nullptr) obj = glut::factory(name);
   if (obj == nullptr) obj = base::factory(name);

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

   glutDisplay->createWindow();

   // set timer
   const double dt = 1.0/static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   // main loop
   glutMainLoop();
   return 0;
}

} // End demo namespace
} // End oe namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return oe::demo::main(argc, argv);
}

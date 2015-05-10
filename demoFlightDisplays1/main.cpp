//----------------------------------------------------------------
// Example flight displays 1
//----------------------------------------------------------------
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"

#include "openeaagles/basicGL/Graphic.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

// class factories
#include "openeaagles/basic/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/gui/glut/Factory.h"

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

namespace Eaagles {
namespace Demo {

// frame rate
const int frameRate = 20;

// System descriptions
static class Glut::GlutDisplay* glutDisplay = nullptr;

// timerFunc() -- Time critical stuff
static void timerFunc(int)
{
    LCreal dt = 1.0f/static_cast<LCreal>(frameRate);

    unsigned int millis = static_cast<unsigned int>(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    Basic::Timer::updateTimers(dt);
    BasicGL::Graphic::flashTimer(dt);
    glutDisplay->updateTC(dt);
}

// our class factory
static Basic::Object* factory(const char* name)
{
   Basic::Object* obj = nullptr;

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

   if (obj == nullptr) obj = Instruments::Factory::createObj(name);
   if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
   if (obj == nullptr) obj = Glut::Factory::createObj(name);
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

//
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   const char* configFilename = "test.edl";
   glutDisplay = builder(configFilename);

   glutDisplay->createWindow();

   // set timer
   double dt = 1.0/static_cast<double>(frameRate);
   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   // main loop
   glutMainLoop();
   return 0;
}

} // End Demo namespace
} // End Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::Demo::main(argc, argv);
}

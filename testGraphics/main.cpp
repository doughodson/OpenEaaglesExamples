//------------------------------------------------------------------------------
// Test of graphics system
//------------------------------------------------------------------------------
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/Timers.h"
#include "openeaagles/base/edl_parser.h"
#include "openeaagles/base/functors/Tables.h"
#include "openeaagles/base/Nav.h"
#include "openeaagles/base/units/Angles.h"

#include "openeaagles/graphics/Graphic.h"
#include "openeaagles/graphics/Image.h"

#include "openeaagles/gui/glut/GlutDisplay.h"

#include "TestDisplay.h"

// factories
#include "openeaagles/base/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"

#include <GL/glut.h>

#include "MfdPage.h"
#include "TestOne.h"
#include "TestTwo.h"
#include "TdAzPtr.h"
#include "TdElevPtr.h"
#include "TestRotator.h"

#include <string>
#include <cstdlib>

// graphics frame rate (Hz)
const unsigned int frame_rate = 10;
// derived delta times
const double dt_secs = 1.0 / static_cast<double>(frame_rate);
const unsigned int dt_msecs = static_cast<unsigned int>(dt_secs * 1000.0);

TestDisplay* testDisplay = nullptr;

// timerFunc() -- time critical stuff
void timerFunc(int)
{
   glutTimerFunc(dt_msecs, timerFunc, 1);

   oe::base::Timer::updateTimers(dt_secs);
   oe::graphics::Graphic::flashTimer(dt_secs);
   testDisplay->tcFrame(dt_secs);
}

// our class factory
oe::base::Object* factory(const std::string& name)
{
   oe::base::Object* obj = nullptr;

   //
   if ( name == TestDisplay::getFactoryName() ) {
      obj = new TestDisplay;
   }
   else if ( name == MfdPage::getFactoryName() ) {
      obj = new MfdPage;
   }

   // TestX
   else if ( name == TestOne::getFactoryName() ) {
      obj = new TestOne;
   }

   // TestY
   else if ( name == TestTwo::getFactoryName() ) {
      obj = new TestTwo;
   }
   else if ( name == TdAzPtr::getFactoryName() ) {
      obj = new TdAzPtr;
   }
   else if ( name == TdElevPtr::getFactoryName() ) {
      obj = new TdElevPtr;
   }
   else if ( name == TestRotator::getFactoryName() ) {
      obj = new TestRotator;
   }

   else {
      if (obj == nullptr) obj = oe::graphics::factory(name);
      if (obj == nullptr) obj = oe::glut::factory(name);
      if (obj == nullptr) obj = oe::base::factory(name);
   }
   return obj;
}

// test display builder
TestDisplay* builder(const std::string& filename)
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
   oe::base::Pair* pair = dynamic_cast<oe::base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   TestDisplay* testDisplay = dynamic_cast<TestDisplay*>(obj);
   if (testDisplay == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return testDisplay;
}

int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   std::string configFilename = "test.edl";

   // parse arguments
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   // build display
   testDisplay = builder(configFilename);

   // create a display window
   testDisplay->createWindow();

   // start timer to kick off animation
   glutTimerFunc(dt_msecs, timerFunc, 1);

   glutMainLoop();

   return 0;
}

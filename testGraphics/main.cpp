//------------------------------------------------------------------------------
// Test of basic graphics system
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

namespace oe {
namespace example {

// frame rate
const int frameRate = 20;

TestDisplay* testDisplay = nullptr;

// timerFunc() -- time critical stuff
void timerFunc(int)
{
   const double dt = 1.0 / static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   base::Timer::updateTimers(static_cast<double>(dt));
   graphics::Graphic::flashTimer(static_cast<double>(dt));
   testDisplay->tcFrame(static_cast<double>(dt));
}

// our class factory
base::Object* factory(const std::string& name)
{
   base::Object* obj = nullptr;

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
      if (obj == nullptr) obj = graphics::factory(name);
      if (obj == nullptr) obj = glut::factory(name);
      if (obj == nullptr) obj = base::factory(name);
   }
   return obj;
}

// test display builder
TestDisplay* builder(const std::string& filename)
{
   // read configuration file
   unsigned int num_errors = 0;
   base::Object* obj = base::edl_parser(filename, factory, &num_errors);
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
   base::Pair* pair = dynamic_cast<base::Pair*>(obj);
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

//
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

   // set timer
   const double dt = 1.0 / static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   glutMainLoop();

   return 0;
}

} // end example namespace
} // end oe namespace

//
int main(int argc, char* argv[])
{
   return oe::example::main(argc,argv);
}

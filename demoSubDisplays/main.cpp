//------------------------------------------------------------------------------
// demo of sub-displays
//------------------------------------------------------------------------------
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/Timers.h"
#include "openeaagles/base/parser.h"
#include "openeaagles/graphics/Graphic.h"
#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

// factories
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/base/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/instruments/factory.h"

// test files
#include "TestSpeedBrake.h"
#include "TestEngineDial.h"
#include "TestCas.h"
#include "TestFtitDial.h"
#include "TestOilPressure.h"
#include "TestNozzle.h"
#include "TestRpmDial.h"
#include "TestHsi.h"
#include "TestGauge1.h"
#include "TestVVI.h"
#include "TestAlt.h"
#include "TestCompass.h"
#include "TestDigitalGauge.h"
#include "TestGMeterDial.h"
#include "TestLandingGear.h"
#include "TestEngPage.h"
#include "TestButtons.h"
#include "TestAdi.h"
#include "TestAdi2.h"

#include <string>
#include <cstdlib>

namespace oe {
namespace demo {

// frame rate
const unsigned int frameRate = 20;

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
base::Object* factory(const std::string& name)
{
   base::Object* obj = nullptr;

   // speed brake page
   if ( name == TestSpeedBrake::getFactoryName() ) {
      obj = new TestSpeedBrake;
   }
   // engine dial page
   else if ( name == TestEngineDial::getFactoryName() ) {
      obj = new TestEngineDial;
   }
   // calibrated air speed (cas) page
   else if ( name == TestCas::getFactoryName() ) {
      obj = new TestCas;
   }
   // ftit page
   else if ( name == TestFtitDial::getFactoryName() ) {
      obj = new TestFtitDial;
   }
   // TestOilPressure page
   else if ( name == TestOilPressure::getFactoryName() ) {
      obj = new TestOilPressure;
   }
   // TestNozzle page
   else if ( name == TestNozzle::getFactoryName() ) {
      obj = new TestNozzle;
   }
   // TestRpmDial page
   else if ( name == TestRpmDial::getFactoryName() ) {
      obj = new TestRpmDial;
   }
   // TestHsi page
   else if ( name == TestHsi::getFactoryName() ) {
      obj = new TestHsi;
   }
   // TestGauge1 page
   else if ( name == TestGauge1::getFactoryName() ) {
      obj = new TestGauge1;
   }
   // TestVVI page
   else if ( name == TestVVI::getFactoryName() ) {
      obj = new TestVVI;
   }
   // TestAlt page
   else if ( name == TestAlt::getFactoryName() ) {
      obj = new TestAlt;
   }
   // Compass Rose
   else if ( name == TestCompass::getFactoryName() ) {
      obj = new TestCompass;
   }
   // Digital Gauge
   else if ( name == TestDigitalGauge::getFactoryName() ) {
      obj = new TestDigitalGauge;
   }
   // TestGMeterDial page
   else if ( name == TestGMeterDial::getFactoryName() ) {
      obj = new TestGMeterDial;
   }
   // TestLandingGear page
   else if ( name == TestLandingGear::getFactoryName() ) {
      obj = new TestLandingGear;
   }
   // TestEngPage
   else if ( name == TestEngPage::getFactoryName() ) {
      obj = new TestEngPage;
   }
   // TestButtons
   else if ( name == TestButtons::getFactoryName() ) {
      obj = new TestButtons;
   }
   // TestAdi
   else if ( name == TestAdi::getFactoryName() ) {
      obj = new TestAdi;
   }
   else if ( name == TestAdi2::getFactoryName() ) {
      obj = new TestAdi2;
   }

   else {
      if (obj == nullptr) obj = instruments::factory(name);
      if (obj == nullptr) obj = graphics::factory(name);
      if (obj == nullptr) obj = glut::factory(name);
      if (obj == nullptr) obj = base::factory(name);
   }

   return obj;
}

// display builder
glut::GlutDisplay* builder(const std::string& filename)
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
   std::string configFilename = "test.edl";
   glutDisplay = builder(configFilename);

   glutDisplay->createWindow();

   // set timer
   const double dt = 1.0 / static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);
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

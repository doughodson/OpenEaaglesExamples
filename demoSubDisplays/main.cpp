//------------------------------------------------------------------------------
// demo of sub-displays
//------------------------------------------------------------------------------
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/Timers.h"
#include "openeaagles/base/edl_parser.h"
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

#include <cstring>
#include <cstdlib>

namespace oe {
namespace demo {

// frame rate
const int frameRate = 20;

static class glut::GlutDisplay* glutDisplay = nullptr;

// timerFunc() -- Time critical stuff
static void timerFunc(int)
{
   double dt = 1.0 / static_cast<double>(frameRate);

   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   base::Timer::updateTimers(dt);
   graphics::Graphic::flashTimer(dt);
   glutDisplay->updateTC(dt);
}

// our class factory
static base::Object* factory(const char* name)
{
   base::Object* obj = nullptr;

   // speed brake page
   if ( std::strcmp(name, TestSpeedBrake::getFactoryName()) == 0 ) {
      obj = new TestSpeedBrake;
   }
   // engine dial page
   else if (std::strcmp(name, TestEngineDial::getFactoryName()) == 0 ) {
      obj = new TestEngineDial;
   }
   // calibrated air speed (cas) page
   else if (std::strcmp(name, TestCas::getFactoryName()) == 0 ) {
      obj = new TestCas;
   }
   // ftit page
   else if (std::strcmp(name, TestFtitDial::getFactoryName()) == 0 ) {
      obj = new TestFtitDial;
   }
   // TestOilPressure page
   else if (std::strcmp(name, TestOilPressure::getFactoryName()) == 0 ) {
      obj = new TestOilPressure;
   }
   // TestNozzle page
   else if (std::strcmp(name, TestNozzle::getFactoryName()) == 0 ) {
      obj = new TestNozzle;
   }
   // TestRpmDial page
   else if (std::strcmp(name, TestRpmDial::getFactoryName()) == 0 ) {
      obj = new TestRpmDial;
   }
   // TestHsi page
   else if (std::strcmp(name, TestHsi::getFactoryName()) == 0 ) {
      obj = new TestHsi;
   }
   // TestGauge1 page
   else if (std::strcmp(name, TestGauge1::getFactoryName()) == 0 ) {
      obj = new TestGauge1;
   }
   // TestVVI page
   else if (std::strcmp(name, TestVVI::getFactoryName()) == 0 ) {
      obj = new TestVVI;
   }
   // TestAlt page
   else if (std::strcmp(name, TestAlt::getFactoryName()) == 0 ) {
      obj = new TestAlt;
   }
   // Compass Rose
   else if (std::strcmp(name, TestCompass::getFactoryName()) == 0 ) {
      obj = new TestCompass;
   }
   // Digital Gauge
   else if (std::strcmp(name, TestDigitalGauge::getFactoryName()) == 0 ) {
      obj = new TestDigitalGauge;
   }
   // TestGMeterDial page
   else if (std::strcmp(name, TestGMeterDial::getFactoryName()) == 0 ) {
      obj = new TestGMeterDial;
   }
   // TestLandingGear page
   else if (std::strcmp(name, TestLandingGear::getFactoryName()) == 0 ) {
      obj = new TestLandingGear;
   }
   // TestEngPage
   else if (std::strcmp(name, TestEngPage::getFactoryName()) == 0 ) {
      obj = new TestEngPage;
   }
   // TestButtons
   else if (std::strcmp(name, TestButtons::getFactoryName()) == 0 ) {
      obj = new TestButtons;
   }
   // TestAdi
   else if (std::strcmp(name, TestAdi::getFactoryName()) == 0 ) {
      obj = new TestAdi;
   }
   else if (std::strcmp(name, TestAdi2::getFactoryName()) == 0 ) {
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
static glut::GlutDisplay* builder(const char* const filename)
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
   double dt = 1.0 / static_cast<double>(frameRate);
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

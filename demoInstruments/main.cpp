//------------------------------------------------------------------------------
// Demo of instrument library
//------------------------------------------------------------------------------
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/Timers.h"
#include "openeaagles/base/edl_parser.h"
#include "openeaagles/graphics/Graphic.h"
#include "openeaagles/gui/glut/GlutDisplay.h"

// factories
#include "openeaagles/base/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/instruments/factory.h"
#include "openeaagles/gui/glut/factory.h"

#include <GL/glut.h>

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

// frame rate
const unsigned int frameRate = 20;

// System descriptions
oe::glut::GlutDisplay* glutDisplay = nullptr;

// timerFunc() -- Time critical stuff
void timerFunc(int)
{
    const double dt = 1.0 / static_cast<double>(frameRate);
    const unsigned int millis = static_cast<unsigned int>(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    oe::base::Timer::updateTimers(dt);
    oe::graphics::Graphic::flashTimer(dt);
    glutDisplay->updateTC(dt);
}

// our class factory
oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

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
    // Ftit page
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
    // TestAdi
    else if ( name == TestAdi2::getFactoryName() ) {
        obj = new TestAdi2;
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
   oe::base::Pair* pair = dynamic_cast<oe::base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   oe::glut::GlutDisplay* glutDisplay = dynamic_cast<oe::glut::GlutDisplay*>(obj);
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
   std::string configFilename = "testinstruments.edl";
   glutDisplay = builder(configFilename);

   glutDisplay->createWindow();

   // setup timer
   const double dt = 1.0 / static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   glutMainLoop();
   return 0;
}

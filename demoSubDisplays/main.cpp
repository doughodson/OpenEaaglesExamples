//------------------------------------------------------------------------------
// Demo of sub-displays
//------------------------------------------------------------------------------
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basicGL/Graphic.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

// class factories
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/basic/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/instruments/Factory.h"

// here are the test files
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

namespace Eaagles {
namespace Demo {

// Description (input) File -- After being processed by the C preprocessor
const char* testFileName = "test.edl";

// Frame Rate
const int frameRate = 20;

// System descriptions
static class Glut::GlutDisplay* sys = 0;

//=============================================================================
// Main test functions
//=============================================================================

// timerFunc() -- Time critical stuff)
static void timerFunc(int)
{
    LCreal dt = 1.0f/LCreal(frameRate);

    unsigned int millis = (unsigned int)(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    Basic::Timer::updateTimers(dt);
    BasicGL::Graphic::flashTimer(dt);
    sys->updateTC(dt);
}

// our class factory
static Basic::Object* factory(const char* name)
{
    Basic::Object* obj = 0;

    // speed brake page
    if ( strcmp(name, TestSpeedBrake::getFactoryName()) == 0 ) {
        obj = new TestSpeedBrake;
    }
    // engine dial page
    else if (strcmp(name, TestEngineDial::getFactoryName()) == 0 ) {
        obj = new TestEngineDial;
    }
    // calibrated air speed (cas) page
    else if (strcmp(name, TestCas::getFactoryName()) == 0 ) {
        obj = new TestCas;
    }
    // ftit page
    else if (strcmp(name, TestFtitDial::getFactoryName()) == 0 ) {
        obj = new TestFtitDial;
    }
    // TestOilPressure page
    else if (strcmp(name, TestOilPressure::getFactoryName()) == 0 ) {
        obj = new TestOilPressure;
    }
    // TestNozzle page
    else if (strcmp(name, TestNozzle::getFactoryName()) == 0 ) {
        obj = new TestNozzle;
    }
    // TestRpmDial page
    else if (strcmp(name, TestRpmDial::getFactoryName()) == 0 ) {
        obj = new TestRpmDial;
    }
    // TestHsi page
    else if (strcmp(name, TestHsi::getFactoryName()) == 0 ) {
        obj = new TestHsi;
    }
    // TestGauge1 page
    else if (strcmp(name, TestGauge1::getFactoryName()) == 0 ) {
        obj = new TestGauge1;
    }
    // TestVVI page
    else if (strcmp(name, TestVVI::getFactoryName()) == 0 ) {
        obj = new TestVVI;
    }
    // TestAlt page
    else if (strcmp(name, TestAlt::getFactoryName()) == 0 ) {
        obj = new TestAlt;
    }
    // Compass Rose
    else if (strcmp(name, TestCompass::getFactoryName()) == 0 ) {
        obj = new TestCompass;
    }
    // Digital Gauge
    else if (strcmp(name, TestDigitalGauge::getFactoryName()) == 0 ) {
        obj = new TestDigitalGauge;
    }
    // TestGMeterDial page
    else if (strcmp(name, TestGMeterDial::getFactoryName()) == 0 ) {
        obj = new TestGMeterDial;
    }
    // TestLandingGear page
    else if (strcmp(name, TestLandingGear::getFactoryName()) == 0 ) {
        obj = new TestLandingGear;
    }
    // TestEngPage
    else if (strcmp(name, TestEngPage::getFactoryName()) == 0 ) {
        obj = new TestEngPage;
    }
    // TestButtons
    else if (strcmp(name, TestButtons::getFactoryName()) == 0 ) {
        obj = new TestButtons;
    }
    // TestAdi
    else if (strcmp(name, TestAdi::getFactoryName()) == 0 ) {
        obj = new TestAdi;
    }
    else if (strcmp(name, TestAdi2::getFactoryName()) == 0 ) {
        obj = new TestAdi2;
    }

    else {
        if (obj == 0) obj = Instruments::Factory::createObj(name);
        if (obj == 0) obj = BasicGL::Factory::createObj(name);
        if (obj == 0) obj = Glut::Factory::createObj(name);
        if (obj == 0) obj = Basic::Factory::createObj(name);
    }

    return obj;
}

// build a display
static void builder()
{
    // Read the description file
    int errors = 0;
    Basic::Object* q1 = Basic::lcParser(testFileName, factory, &errors);
    if (errors > 0) {
        std::cerr << "Errors in reading file: " << errors << std::endl;
        exit(1);
    }

    // Set 'sys' to our basic description object.
    sys = 0;
    if (q1 != 0) {

        // When we were given a Pair, get the pointer to its object.
        Basic::Pair* pp = dynamic_cast<Basic::Pair*>(q1);
        if (pp != 0) {
            q1 = pp->object();
        }

        // What we should have here is the description object and
        // it should be of type 'InstDisplay'.
        sys = dynamic_cast<Glut::GlutDisplay*>(q1);

    }

    // Make sure we did get a valid object (we must have one!)
    if (sys == 0) {
        std::cout << "Invalid description file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //sys->serialize(std::cout);
}

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

// ---
// Build a display
// ---
    builder();

// ---
// Create a display window
// ---
    sys->createWindow();

// ---
// Set timer
// ---
    double dt = 1.0/double(frameRate);
    unsigned int millis = (unsigned int)(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

// ---
// Main loop
// ---
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

//*****************************************************************************
// Example routine for Instrument Library
//*****************************************************************************
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basicGL/Graphic.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/basic/basicFF.h"
#include "openeaagles/instruments/instrumentsFF.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include "openeaagles/gui/glut/glutFF.h"
#include <GL/glut.h>

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
const char* testFileName = "testinstruments.edl";

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

// Test Form Function
static Basic::Object* testFormFunc(const char* formname)
{
    Basic::Object* newform = 0;

    // This instrument test ...
    if ( strcmp(formname, TestSpeedBrake::getFormName()) == 0 ) {
        newform = new TestSpeedBrake;
    }
    // engine dial page
    else if (strcmp(formname, TestEngineDial::getFormName()) == 0 ) {
        newform = new TestEngineDial;
    }    
    // calibrated air speed (cas) page
    else if (strcmp(formname, TestCas::getFormName()) == 0 ) {
        newform = new TestCas;
    }    
    // ftit page
    else if (strcmp(formname, TestFtitDial::getFormName()) == 0 ) {
        newform = new TestFtitDial;
    } 
    // TestOilPressure page
    else if (strcmp(formname, TestOilPressure::getFormName()) == 0 ) {
        newform = new TestOilPressure;
    }     
    // TestNozzle page
    else if (strcmp(formname, TestNozzle::getFormName()) == 0 ) {
        newform = new TestNozzle;
    } 
    // TestRpmDial page
    else if (strcmp(formname, TestRpmDial::getFormName()) == 0 ) {
        newform = new TestRpmDial;
    }      
    // TestHsi page
    else if (strcmp(formname, TestHsi::getFormName()) == 0 ) {
        newform = new TestHsi;
    }        
    // TestGauge1 page
    else if (strcmp(formname, TestGauge1::getFormName()) == 0 ) {
        newform = new TestGauge1;
    }    
    // TestVVI page
    else if (strcmp(formname, TestVVI::getFormName()) == 0 ) {
        newform = new TestVVI;
    }    
    // TestAlt page
    else if (strcmp(formname, TestAlt::getFormName()) == 0 ) {
        newform = new TestAlt;
    }        
    // Compass Rose
    else if (strcmp(formname, TestCompass::getFormName()) == 0 ) {
        newform = new TestCompass;
    }    
    // Digital Gauge
    else if (strcmp(formname, TestDigitalGauge::getFormName()) == 0 ) {
        newform = new TestDigitalGauge;
    }    
    // TestGMeterDial page
    else if (strcmp(formname, TestGMeterDial::getFormName()) == 0 ) {
        newform = new TestGMeterDial;
    }     
    // TestLandingGear page
    else if (strcmp(formname, TestLandingGear::getFormName()) == 0 ) {
        newform = new TestLandingGear;
    }     
    // TestEngPage
    else if (strcmp(formname, TestEngPage::getFormName()) == 0 ) {
        newform = new TestEngPage;
    }      
    // TestButtons
    else if (strcmp(formname, TestButtons::getFormName()) == 0 ) {
        newform = new TestButtons;
    }      
    // TestAdi
    else if (strcmp(formname, TestAdi::getFormName()) == 0 ) {
        newform = new TestAdi;
    }      
    // TestAdi
    else if (strcmp(formname, TestAdi2::getFormName()) == 0 ) {
        newform = new TestAdi2;
    }      
        
    else {
        if (newform == 0) newform = Instruments::instrumentsFormFunc(formname);
        if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
        if (newform == 0) newform = Glut::glutFormFunc(formname);
        if (newform == 0) newform = Basic::basicFormFunc(formname);
    }
     
    return newform;
}

// readTest() -- function to the read description files
static void readTest()
{
    // Read the description file
    int errors = 0;
    Basic::Object* q1 = Basic::lcParser(testFileName, testFormFunc, &errors);
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
        // it should be of type 'GlutDisplay'
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
// Read in the description files
// ---
    readTest();

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

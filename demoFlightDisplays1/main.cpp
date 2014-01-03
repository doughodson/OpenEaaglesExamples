//*****************************************************************************
// Example Flight Display
//*****************************************************************************
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

// Test pages
#include "TestPfd.h"
#include "TestSD.h"
// Instruments
#include "CrsPntr.h"
#include "Hsi.h"
#include "Pfd.h"
#include "RdrAlt.h"
#include "SituationalDisplay.h"
#include "SpdLines.h"
#include "TerrainFollower.h"

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

    // Test the primary flight display (PFD)
    if ( strcmp(name, TestPfd::getFactoryName()) == 0 ) {
        obj = new TestPfd;
    }
    // situational display
    else if ( strcmp(name, TestSD::getFactoryName()) == 0 ) {
        obj = new TestSD;
    }
    // CrsPntr
    else if ( strcmp(name, CrsPntr::getFactoryName()) == 0 ) {
        obj = new CrsPntr;
    }
    // Hsi
    else if ( strcmp(name, Hsi::getFactoryName()) == 0 ) {
        obj = new Hsi;
    }
    // Pfd
    else if ( strcmp(name, Pfd::getFactoryName()) == 0 ) {
        obj = new Pfd;
    }
    // RdrAlt
    else if ( strcmp(name, RdrAlt::getFactoryName()) == 0 ) {
        obj = new RdrAlt;
    }
    // SituationalDisplay
    else if ( strcmp(name, SituationalDisplay::getFactoryName()) == 0 ) {
        obj = new SituationalDisplay;
    }
    // SpdLines
    else if ( strcmp(name, SpdLines::getFactoryName()) == 0 ) {
        obj = new SpdLines;
    }
    // TerrainFollower
    else if ( strcmp(name, TerrainFollower::getFactoryName()) == 0 ) {
        obj = new TerrainFollower;
    }

    if (obj == 0) obj = Instruments::Factory::createObj(name);
    if (obj == 0) obj = BasicGL::Factory::createObj(name);
    if (obj == 0) obj = Glut::Factory::createObj(name);
    if (obj == 0) obj = Basic::Factory::createObj(name);

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
// build a display
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

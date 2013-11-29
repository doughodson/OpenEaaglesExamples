//*****************************************************************************
// Example Flight Display 2
//*****************************************************************************
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/basicFF.h"

#include "openeaagles/basicGL/Graphic.h"
#include "openeaagles/basicGL/basicGLFF.h"

#include "openeaagles/instruments/instrumentsFF.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include "openeaagles/gui/glut/glutFF.h"
#include <GL/glut.h>

// Test pages
#include "TestPfd.h"
// Instruments
#include "Pfd.h"
#include "SpdLines.h"

namespace Eaagles {
namespace MainFlightDisplay2 {

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

// Test Form Function
static Basic::Object* testFormFunc(const char* formname)
{
    Basic::Object* newform = 0;

    // Test the primary flight display (PFD)
    if ( strcmp(formname, TestPfd::getFormName()) == 0 ) {
        newform = new TestPfd;
    }
    // Pfd
    else if ( strcmp(formname, Pfd::getFormName()) == 0 ) {
        newform = new Pfd;
    }
    // SpdLines
    else if ( strcmp(formname, SpdLines::getFormName()) == 0 ) {
        newform = new SpdLines;
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

} // End MainFlightDisplay2 namespace
} // End Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::MainFlightDisplay2::main(argc, argv);
}

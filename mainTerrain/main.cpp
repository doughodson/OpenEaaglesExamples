//*****************************************************************************
// Example routine for the Terrain functions
//*****************************************************************************

#include "Display.h"
#include "Factory.h"

#include "openeaagles/terrain/ded/DedFile.h"

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Tables.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basicGL/Graphic.h"
#include "openeaagles/basicGL/basicGLFF.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include "openeaagles/gui/glut/glutFF.h"
#include <GL/glut.h>

namespace Eaagles {
namespace Example {

// Description (input) File -- After being processed by the C preprocessor
const char* fileName = "test.edl";

// Frame Rate
const int frameRate = 10;

// System descriptions
static class Display* sys = 0;


//=============================================================================
// Main test functions
//=============================================================================

// timerFunc() -- Time critical stuff)
static void timerFunc(int)
{
    double dt = 1.0/double(frameRate);

    unsigned int millis = (unsigned int)(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    Basic::Timer::updateTimers((LCreal)dt);
    BasicGL::Graphic::flashTimer((LCreal)dt);
    sys->tcFrame((LCreal)dt);
}


//build a display
static void builder()
{
    // Read the description file
    int errors = 0;
    Basic::Object* q1 = Basic::lcParser(fileName, Factory::createObj, &errors);
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
           std::cout << "Form: " << *pp->slot() << std::endl;
            q1 = pp->object();
        }

        // What we should have here is the description object and
        // it should be of type 'Display'.
        sys = dynamic_cast<Display*>(q1);

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
// Resetting the system will load the data files
// ---

   std::cout << "starting loading files --" << std::endl;
   double start = getComputerTime();

   sys->reset();

   double end = getComputerTime();
   double dtime = (end - start);
   std::cout << "finished loading files: time(s) = " << dtime << std::endl;

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

} // end Example namespace
} // end Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::Example::main(argc,argv);
}

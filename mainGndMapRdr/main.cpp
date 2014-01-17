
#include "Station.h"
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
#include <GL/glut.h>


namespace Eaagles {
namespace Example {

// Description (input) File -- After being processed by the C preprocessor
const char* fileName = "test.edl";

// Background Rate
const int bgRate = 20;

// System descriptions
static class TestStation* sys = 0;

//=============================================================================
// Main test functions
//=============================================================================

// updateDataCB() -- Station's background tasks
static void updateDataCB(int)
{
    double dt0 = 1.0/double(bgRate);
    unsigned int millis = (unsigned int) (dt0 * 1000);
    glutTimerFunc(millis, updateDataCB, 1);

    // Current time
    double time = getComputerTime();

    // N-1 Time
    static double time0 = time;

    // Compute delta time
    LCreal dt = LCreal(time - time0);
    time0 = time;

    Basic::Timer::updateTimers(dt);
    BasicGL::Graphic::flashTimer(dt);
    sys->updateData(dt);
}


// readDescription() -- function to the read description files
static void readDescription()
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
        // it should be of type 'TestStation'.
        sys = dynamic_cast<TestStation*>(q1);

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
   readDescription();

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
// Set timer for background tasks
// ---

    double dt = 1.0/double(bgRate);
    unsigned int millis = (unsigned int) (dt * 1000);
    glutTimerFunc(millis, updateDataCB, 1);

// ---
// Create Time Critical Thread
// ---
    sys->createTimeCriticalProcess();

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



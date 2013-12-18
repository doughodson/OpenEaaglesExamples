//*****************************************************************************
// Simple test routine for moving map library
//*****************************************************************************
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/basicFF.h"

#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/instruments/instrumentsFF.h"
#include "openeaagles/simulation/simulationFF.h"
#include "openeaagles/dis/disFF.h"
#include "openeaagles/otw/otwFF.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include "openeaagles/gui/glut/glutFF.h"
#include <GL/glut.h>

#include "../shared-libs/xZeroMQHandlers/formFunc.h"

// Local Classes
#include "MapPage.h"
#include "Station.h"
#include "Display.h"

namespace Eaagles {
namespace MapTest {

// Description (input) File -- After being processed by the C preprocessor
const char* testFileName = "test.edl";

// Frame Rate
const int frameRate = 20;

// System descriptions
static class Station* sys = 0;


// timer function, in this case, the background (updateData) function
static void timerFunc(int)
{
    double dt0 = 1.0/double(frameRate);
    unsigned int millis = (unsigned int) (dt0 * 1000);
    glutTimerFunc(millis, timerFunc, 1);

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

// Test Form Function
static Basic::Object* testFormFunc(const char* formname)
{
    Basic::Object* newform = 0;
    if (strcmp(formname, MapPage::getFormName()) == 0) {
        newform = new MapPage();
    }
    else if (strcmp(formname, Station::getFormName()) == 0) {
        newform = new Station();
    }
    else if (strcmp(formname, Display::getFormName()) == 0) {
        newform = new Display();
    }

    // Example libraries
    if (newform == 0) newform = xZeroMQHandlers::formFunc(formname);

    // Framework libraries
    if (newform == 0) newform = Otw::otwFormFunc(formname);
    if (newform == 0) newform = Instruments::instrumentsFormFunc(formname);
    if (newform == 0) newform = Simulation::simulationFormFunc(formname);
    if (newform == 0) newform = Network::Dis::disFormFunc(formname);
    if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
    if (newform == 0) newform = Glut::glutFormFunc(formname);
    if (newform == 0) newform = Basic::basicFormFunc(formname);
    
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
           std::cout << "Form: " << *pp->slot() << std::endl;
            q1 = pp->object();
        }

        // our main object
        sys = dynamic_cast<Station*>(q1);

    }

    // Make sure we did get a valid object (we must have one!)
    if (sys == 0) {
        std::cout << "Invalid description file!" << std::endl;
        exit(EXIT_FAILURE);
    }
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
// Reset the Simulation
// ---
   sys->event(Basic::Component::RESET_EVENT);

// ---
// Set timer for the background tasks
// ---

   double dt = 1.0/double(frameRate);
   unsigned int millis = (unsigned int) (dt * 1000);

   // ensure everything is reset
   sys->updateData(dt);
   sys->updateTC(dt);
   sys->event(Eaagles::Basic::Component::RESET_EVENT);

   glutTimerFunc(millis, timerFunc, 1);

// ---
// Create the Time Critical Thread (updateTC())
// ---
   sys->createTimeCriticalProcess();

// ---
// Main loop
// ---
   glutMainLoop();
   return 0;
}

} // End MapTest namespace
} // End Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::MapTest::main(argc,argv);
}

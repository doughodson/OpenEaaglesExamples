
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

// class factories
#include "../shared/xZeroMQHandlers/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/basic/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/simulation/Factory.h"
#include "openeaagles/dis/Factory.h"
#include "openeaagles/otw/Factory.h"

#include "MapPage.h"
#include "Station.h"
#include "Display.h"

namespace Eaagles {
namespace Example {

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

// our class factory
static Basic::Object* factory(const char* name)
{
    Basic::Object* obj = 0;

    if (strcmp(name, MapPage::getFactoryName()) == 0) {
        obj = new MapPage();
    }
    else if (strcmp(name, Station::getFactoryName()) == 0) {
        obj = new Station();
    }
    else if (strcmp(name, Display::getFactoryName()) == 0) {
        obj = new Display();
    }

    // Example libraries
    if (obj == 0) obj = xZeroMQHandlers::Factory::createObj(name);

    // Framework libraries
    if (obj == 0) obj = Otw::Factory::createObj(name);
    if (obj == 0) obj = Instruments::Factory::createObj(name);
    if (obj == 0) obj = Simulation::Factory::createObj(name);
    if (obj == 0) obj = Network::Dis::Factory::createObj(name);
    if (obj == 0) obj = BasicGL::Factory::createObj(name);
    if (obj == 0) obj = Glut::Factory::createObj(name);
    if (obj == 0) obj = Basic::Factory::createObj(name);
    
    return obj;
}

// build a Station
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
// build a Station
// ---
    builder();

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

} // End Example namespace
} // End Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::Example::main(argc,argv);
}

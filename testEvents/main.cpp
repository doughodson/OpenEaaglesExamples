//*****************************************************************************
// Routine to test the Component send command, using different parameters
//*****************************************************************************

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Timers.h"

#include <GL/glut.h>

// class factories
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/basic/Factory.h"
#include "openeaagles/gui/glut/Factory.h"

#include "Display.h"
#include "ObjectHandler.h"

#include <cstring>
#include <cstdlib>

namespace Eaagles {
namespace Test {

// default configuration file
const char* testFileName = "test.edl";

// Frame Rate
const int frameRate = 20;

// System descriptions
static class Display* sys = 0;

//=============================================================================
// Main test functions
//=============================================================================

// timerFunc() -- Time critical stuff)
static void timerFunc(int)
{
    double dt = 1.0/static_cast<double>(frameRate);

    unsigned int millis = static_cast<unsigned int>(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    Basic::Timer::updateTimers(static_cast<LCreal>(dt));
    BasicGL::Graphic::flashTimer(static_cast<LCreal>(dt));
    sys->tcFrame(static_cast<LCreal>(dt));
}

// our class factory
static Basic::Object* factory(const char* name)
{
    Basic::Object* obj = 0;

    if (std::strcmp(name, Display::getFactoryName()) == 0) {
        obj = new Display();
    }
    else if (std::strcmp(name, ObjectHandler::getFactoryName()) == 0) {
        obj = new ObjectHandler();
    }
    else {
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
        std::exit(1);
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

        // What we should have here is the description object 
        sys = dynamic_cast<Display*>(q1);
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
    double dt = 1.0/static_cast<double>(frameRate);
    unsigned int millis = static_cast<unsigned int>(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

// ---
// Main loop
// ---
    glutMainLoop();

    return 0;
}

} // End Test namespace
} // End Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::Test::main(argc,argv);
}

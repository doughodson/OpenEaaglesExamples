
#include "Board.h"
#include "Puzzle.h"
#include "State.h"
#include "Factory.h"

#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"

#include <iostream>
#include <GL/glut.h>

namespace Eaagles {

namespace Example {

// Description (input) File -- After being processed by the C preprocessor
static const char* fileName = "puzzle.edl";

// Frame Rate
static const int frameRate = 20;

// System descriptions
static class Board* sys = 0;


// timerCB() -- 
static void timerCB(int)
{
    double dt0 = 1.0/double(frameRate);
    unsigned int millis = (unsigned int) (dt0 * 1000);
    glutTimerFunc(millis, timerCB, 1);
    
    // Current time
    double time = getComputerTime();

    // N-1 Time
    static double time0 = time;

    // Compute delta time
    double dt = (time - time0);
    time0 = time;

    Basic::Timer::updateTimers((LCreal)dt);
    BasicGL::Graphic::flashTimer((LCreal)dt);
    sys->tcFrame((LCreal)dt);
}

// readTest() -- function to the read description files
static void readTest()
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
        // it should be of type 'Board'.
        sys = dynamic_cast<Board*>(q1);

    }

    // Make sure we did get a valid object (we must have one!)
    if (sys == 0) {
        std::cout << "Invalid description file!" << std::endl;
        exit(EXIT_FAILURE);
    }

}

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
   glutTimerFunc(millis, timerCB, 1);

   // ---
   // Main loop
   // ---
   glutMainLoop();

   return 0;
}

}  // End of Example namespace
}  // End of Eaagles namespace


int main(int argc, char* argv[])
{
   return Eaagles::Example::main(argc, argv);
}

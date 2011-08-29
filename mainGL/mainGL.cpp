//*****************************************************************************
// Simple example program that creates a GLUT window and draws an image 
// as defined by an EDL file.
//*****************************************************************************

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/basicFF.h"

#include "openeaagles/basicGL/Graphic.h"
#include "openeaagles/basicGL/basicGLFF.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include "openeaagles/gui/glut/glutFF.h"
#include <GL/glut.h>

namespace MainGL {

// Frame Rate
static const int frameRate = 20;

// The System
static class Eaagles::Glut::GlutDisplay* sys = 0;


//=============================================================================
// MainGL functions
//=============================================================================

// timerFunc() -- Time critical stuff)
static void timerFunc(int)
{
   double dt = 1.0/double(frameRate);

   unsigned int millis = (unsigned int)(dt * 1000);
   glutTimerFunc(millis, timerFunc, 1);

   Eaagles::Basic::Timer::updateTimers((Eaagles::LCreal) dt);
   Eaagles::BasicGL::Graphic::flashTimer((Eaagles::LCreal) dt);
   sys->tcFrame((Eaagles::LCreal) dt);
}

// Our Form Function
static Eaagles::Basic::Object* formFunc(const char* formname)
{
   Eaagles::Basic::Object* newform = 0;
   if (newform == 0) newform = Eaagles::BasicGL::basicGLFormFunc(formname);
   if (newform == 0) newform = Eaagles::Glut::glutFormFunc(formname);
   if (newform == 0) newform = Eaagles::Basic::basicFormFunc(formname);
   return newform;
}

// readConfigFile() -- reads HUD description file
static Eaagles::Glut::GlutDisplay* readConfigFile(const char* const filename)
{
    // Read the description file
    int errors = 0;
    Eaagles::Basic::Object* q1 = lcParser(filename, formFunc, &errors);
    if (errors > 0) {
        std::cerr << "Errors in reading file: " << errors << std::endl;
        return 0;
    }

    // Find our main system object
    Eaagles::Glut::GlutDisplay* sys0 = 0;
    if (q1 != 0) {

        // When we were given a Pair, get the pointer to its object.
        Eaagles::Basic::Pair* pp = dynamic_cast<Eaagles::Basic::Pair*>(q1);
        if (pp != 0) {
            q1 = pp->object();
        }

        // What we should have here is the description object and
        // it should be of type 'Display'.
        sys0 = dynamic_cast<Eaagles::Glut::GlutDisplay*>(q1);
    }
    return sys0;
}

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int process(int argc, char* argv[])
{
   glutInit(&argc, argv);

   const char* fileName = "test.edl";
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i],"-f") == 0) {
         fileName = argv[++i];
      }
   }

// ---
// Read in the description files
// ---
    sys = readConfigFile(fileName);

    // Make sure we did get a valid object (we must have one!)
    if (sys == 0) {
        std::cout << "mainGL: invalid description file!" << std::endl;
        exit(EXIT_FAILURE);
    }

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

} // MainGL namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    return MainGL::process(argc,argv);
}

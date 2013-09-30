//*****************************************************************************
// Example routine for the basicGL and basic framework
//*****************************************************************************

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"

#include "openeaagles/basic/basicFF.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/gui/glfw/glfwFF.h"

#include "openeaagles/gui/glfw/GlfwDisplay.h"
#include "GLFW/glfw3.h"

namespace Eaagles {
namespace MainGlfw {

// Frame Rate
const int frameRate = 20;

// System descriptions
static class Glfw::GlfwDisplay* sys = 0;	

// Test Form Function
static Basic::Object* testFormFunc(const char* formname)
{
    Basic::Object* newform = Glfw::glfwFormFunc(formname);

   if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
   if (newform == 0) newform = Basic::basicFormFunc(formname);
   
   return newform;
}

// readTest() -- function to the read description files
static void readTest(const char* const testFileName)
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

        // What we should have here is the description object and
        // it should be of type 'TestDisplay'.
        sys = dynamic_cast<Glfw::GlfwDisplay*>(q1);
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
   // initialize glfw
   if (!glfwInit()) exit(EXIT_FAILURE);

   // Config file file
   const char* configFile = "test.edl";

   // Parse arguments
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i],"-f") == 0) {
         configFile = argv[++i];
      }
   }

// ---
// Read in the description files
// ---
    readTest(configFile);

// ---
// Create a display window
// ---
    sys->createWindow();

// ---
// Set timer
// ---
      while (!sys->isWindowShutdown()) {
         // we can also update data from here, as the callbacks are done in sequence
         sys->updateData(0.025);
         //timerFunc(glfwGetTime());
         // SLS - these are made up numbers
         sys->updateTC(0.02);

         // draw all of our schtuff
         sys->drawIt();

         // poll for any new key, refresh, or other callback that we have done
         glfwPollEvents();

         // now sleep for just a bit
         Eaagles::lcSleep(10);
      }


    return 0;
}

} // End MainGlfw namespace
} // End Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::MainGlfw::main(argc,argv);
}

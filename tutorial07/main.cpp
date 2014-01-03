
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

// class factories
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/basic/Factory.h"
#include "openeaagles/gui/glut/Factory.h"

#include "Worm.h"

namespace Eaagles {
namespace Tutorial {

// Description (input) File -- After being processed by the C preprocessor
const char* inputFileName = "file0.edl";

// Frame Rate
const int frameRate = 20;

// System descriptions
static class Glut::GlutDisplay* sys = 0;

// timerFunc() -- Time critical stuff)
static void timerFunc(int)
{
    double dt = 1.0/double(frameRate);

    unsigned int millis = (unsigned int)(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    Basic::Timer::updateTimers((float)dt);
    BasicGL::Graphic::flashTimer((LCreal)dt);
    sys->tcFrame((LCreal)dt);
}

// our class factory
static Basic::Object* factory(const char* const name)
{
  Basic::Object* obj = 0;

  if ( strcmp(name, Worm::getFactoryName()) == 0 ) {
    obj = new Worm;
  }
   
  // Default to base classes
  if (obj == 0) obj = Glut::Factory::createObj(name);
  if (obj == 0) obj = BasicGL::Factory::createObj(name);
  if (obj == 0) obj = Basic::Factory::createObj(name);

  return obj;
}

// build a display
static void builder()
{
  // Read the description file
  int errors = 0;
  Basic::Object* q1 = lcParser(inputFileName, factory, &errors);
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
    // it should be of type 'TestDisplay'.
    sys = dynamic_cast<Glut::GlutDisplay*>(q1);
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

  // build a display
  builder();

  // create a display window
  sys->createWindow();

  // set timer
  double dt = 1.0/double(frameRate);
  unsigned int millis = (unsigned int)(dt * 1000);
  glutTimerFunc(millis, timerFunc, 1);

  // main loop
  glutMainLoop();
  return 0;
}

} // namespace Tutorial
} // namespace Eaagles

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  Eaagles::Tutorial::main(argc, argv);
}


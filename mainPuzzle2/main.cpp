
#include "Board.h"
#include "Puzzle.h"
#include "State.h"
#include "Factory.h"

#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"

#include <iostream>
#include <GL/glut.h>

#include <cstdlib>

namespace Eaagles {

namespace Example {

// frame rate
static const int frameRate = 20;

static class Board* board = nullptr;

//
static void timerCB(int)
{
   double dt0 = 1.0 / static_cast<double>(frameRate);
   unsigned int millis = static_cast<unsigned int>(dt0 * 1000);
   glutTimerFunc(millis, timerCB, 1);

   // current time
   double time = getComputerTime();

   // N-1 Time
   static double time0 = time;

   // Compute delta time
   double dt = (time - time0);
   time0 = time;

   Basic::Timer::updateTimers(static_cast<LCreal>(dt));
   BasicGL::Graphic::flashTimer(static_cast<LCreal>(dt));
   board->tcFrame(static_cast<LCreal>(dt));
}

// board builder
static Board* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   Basic::Object* obj = Basic::lcParser(filename, Factory::createObj, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a Basic::Pair, if so, point to object in Pair, not Pair itself
   Basic::Pair* pair = dynamic_cast<Basic::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   Board* board = dynamic_cast<Board*>(obj);
   if (board == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return board;
}

int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   const char* configFilename = "puzzle.edl";

   board = builder(configFilename);

   // create a display window
   board->createWindow();

   // set timer
   double dt = 1.0 / static_cast<double>(frameRate);
   unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerCB, 1);

   glutMainLoop();

   return 0;
}

}  // End of Example namespace
}  // End of Eaagles namespace


int main(int argc, char* argv[])
{
   return Eaagles::Example::main(argc, argv);
}

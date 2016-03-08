
#include "Board.h"
#include "Puzzle.h"
#include "State.h"
#include "factory.h"

#include "openeaagles/base/Parser.h"
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/Timers.h"

#include <iostream>
#include <GL/glut.h>

#include <cstdlib>

namespace oe {
namespace example {

// frame rate
static const int frameRate = 20;

static class Board* board = nullptr;

//
static void timerCB(int)
{
   const double dt0 = 1.0 / static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt0 * 1000);
   glutTimerFunc(millis, timerCB, 1);

   // current time
   const double time = base::getComputerTime();

   // N-1 Time
   static double time0 = time;

   // compute delta time
   const double dt = (time - time0);
   time0 = time;

   base::Timer::updateTimers(static_cast<double>(dt));
   graphics::Graphic::flashTimer(static_cast<double>(dt));
   board->tcFrame(static_cast<double>(dt));
}

// board builder
static Board* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   base::Object* obj = base::lcParser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   base::Pair* pair = dynamic_cast<base::Pair*>(obj);
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
   const double dt = 1.0 / static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);
   glutTimerFunc(millis, timerCB, 1);

   glutMainLoop();

   return 0;
}

}  // End of example namespace
}  // End of oe namespace


int main(int argc, char* argv[])
{
   return oe::example::main(argc, argv);
}



#include "SimStation.hpp"

#include "factory.hpp"

#include "openeaagles/base/Timers.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/base/units/Angles.hpp"
#include "openeaagles/graphics/Graphic.hpp"
#include "openeaagles/graphics/Texture.hpp"
#include "openeaagles/base/util/system_utils.hpp"

#include "openeaagles/gui/glut/GlutDisplay.hpp"
#include <GL/glut.h>

#include <string>
#include <cstdlib>

namespace oe {
namespace example {

// default background frame rate
const unsigned int BG_RATE = 10;

SimStation* simStation = nullptr;

// SimStation builder
SimStation* builder(const std::string& filename)
{
   // read configuration file
   unsigned int num_errors = 0;
   base::Object* obj = base::edl_parser(filename, factory, &num_errors);
   if (num_errors > 0) {
      std::cerr << "File: " << filename << ", number of errors: " << num_errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   const auto pair = dynamic_cast<base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   const auto simStation = dynamic_cast<SimStation*>(obj);
   if (simStation == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return simStation;
}

//-----------------------------------------------------------------------------
// updateDataCB() -- Station's background tasks
//-----------------------------------------------------------------------------
void updateDataCB(int msecs)
{
   glutTimerFunc(msecs, updateDataCB, msecs);

   // Current time
   const double time = base::getComputerTime();

   // Compute delta time
   static double time0 = time;   // N-1 Time
   const double dt = time - time0;
   time0 = time;

   simStation->updateData(dt);
}

//
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   std::string configFilename = "test0.edl";
   // parse arguments
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }
   simStation = builder(configFilename);

   // reset station
   simStation->event(base::Component::RESET_EVENT);

   // set timer for background tasks
   const double dt = 1.0 / static_cast<double>(BG_RATE);
   const auto msecs = static_cast<int>(dt * 1000);

   // ensure everything is reset
   simStation->updateData(dt);
   simStation->updateTC(dt);
   simStation->event(base::Component::RESET_EVENT);

   glutTimerFunc(msecs, updateDataCB, msecs);

   simStation->createTimeCriticalProcess();

   glutMainLoop();
   return 0;
}

}
}

//
int main(int argc, char* argv[])
{
   return oe::example::main(argc, argv);
}

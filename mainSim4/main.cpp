
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>

// factories
#include "../shared/xzmq/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/basic/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/instruments/factory.h"
#include "openeaagles/simulation/factory.h"
#include "openeaagles/dis/factory.h"
#include "openeaagles/otw/factory.h"

#include "MapPage.h"
#include "Station.h"
#include "Display.h"

#include <cstring>
#include <cstdlib>

namespace oe {
namespace example {

// frame rate
const int frameRate = 20;

static class Station* station = nullptr;

// timer function, in this case, the background (updateData) function
static void timerFunc(int)
{
    const double dt0 = 1.0 / static_cast<double>(frameRate);
    const unsigned int millis = static_cast<unsigned int>(dt0 * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    // Current time
    const double time = getComputerTime();

    // N-1 Time
    static double time0 = time;

    // Compute delta time
    const LCreal dt = static_cast<LCreal>(time - time0);
    time0 = time;

    basic::Timer::updateTimers(dt);
    graphics::Graphic::flashTimer(dt);
    station->updateData(dt);
}

// our class factory
static basic::Object* factory(const char* name)
{
    basic::Object* obj = nullptr;

    if (std::strcmp(name, MapPage::getFactoryName()) == 0) {
        obj = new MapPage();
    }
    else if (std::strcmp(name, Station::getFactoryName()) == 0) {
        obj = new Station();
    }
    else if (std::strcmp(name, Display::getFactoryName()) == 0) {
        obj = new Display();
    }

    // example libraries
    if (obj == nullptr) obj = xZeroMQHandlers::factory(name);

    // framework libraries
    if (obj == nullptr) obj = otw::factory(name);
    if (obj == nullptr) obj = instruments::factory(name);
    if (obj == nullptr) obj = simulation::factory(name);
    if (obj == nullptr) obj = network::dis::factory(name);
    if (obj == nullptr) obj = graphics::factory(name);
    if (obj == nullptr) obj = glut::factory(name);
    if (obj == nullptr) obj = basic::factory(name);

    return obj;
}

// station builder
static Station* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   basic::Object* obj = basic::lcParser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a basic::Pair, if so, point to object in Pair, not Pair itself
   basic::Pair* pair = dynamic_cast<basic::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   Station* station = dynamic_cast<Station*>(obj);
   if (station == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return station;
}

//
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);

   // default configuration filename
   const char* configFilename = "test.edl";

   // build a station
   station = builder(configFilename);

   // reset the Simulation
   station->event(basic::Component::RESET_EVENT);

   // set timer for the background tasks
   const double dt = 1.0/static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);

   // ensure everything is reset
   station->updateData(dt);
   station->updateTC(dt);
   station->event(basic::Component::RESET_EVENT);

   glutTimerFunc(millis, timerFunc, 1);

   // create the Time Critical Thread (updateTC())
   station->createTimeCriticalProcess();

   glutMainLoop();
   return 0;
}

} // end example namespace
} // end oe namespace

//
int main(int argc, char* argv[])
{
   return oe::example::main(argc,argv);
}

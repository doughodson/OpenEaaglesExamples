
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

#include <cstring>
#include <cstdlib>

namespace Eaagles {
namespace Example {

// frame rate
const int frameRate = 20;

static class Station* station = nullptr;

// timer function, in this case, the background (updateData) function
static void timerFunc(int)
{
    double dt0 = 1.0 / static_cast<double>(frameRate);
    unsigned int millis = static_cast<unsigned int>(dt0 * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    // Current time
    double time = getComputerTime();

    // N-1 Time
    static double time0 = time;

    // Compute delta time
    LCreal dt = static_cast<LCreal>(time - time0);
    time0 = time;

    Basic::Timer::updateTimers(dt);
    BasicGL::Graphic::flashTimer(dt);
    station->updateData(dt);
}

// our class factory
static Basic::Object* factory(const char* name)
{
    Basic::Object* obj = nullptr;

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
    if (obj == nullptr) obj = xZeroMQHandlers::Factory::createObj(name);

    // framework libraries
    if (obj == nullptr) obj = Otw::Factory::createObj(name);
    if (obj == nullptr) obj = Instruments::Factory::createObj(name);
    if (obj == nullptr) obj = Simulation::Factory::createObj(name);
    if (obj == nullptr) obj = Network::Dis::Factory::createObj(name);
    if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
    if (obj == nullptr) obj = Glut::Factory::createObj(name);
    if (obj == nullptr) obj = Basic::Factory::createObj(name);

    return obj;
}

// station builder
static Station* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   Basic::Object* obj = Basic::lcParser(filename, factory, &errors);
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
   station->event(Basic::Component::RESET_EVENT);

   // set timer for the background tasks
   double dt = 1.0/static_cast<double>(frameRate);
   unsigned int millis = static_cast<unsigned int>(dt * 1000);

   // ensure everything is reset
   station->updateData(dt);
   station->updateTC(dt);
   station->event(Basic::Component::RESET_EVENT);

   glutTimerFunc(millis, timerFunc, 1);

   // create the Time Critical Thread (updateTC())
   station->createTimeCriticalProcess();

   glutMainLoop();
   return 0;
}

} // end Example namespace
} // end Eaagles namespace

//
int main(int argc, char* argv[])
{
   return Eaagles::Example::main(argc,argv);
}


#include "openeaagles/base/Pair.h"
#include "openeaagles/base/Timers.h"
#include "openeaagles/base/edl_parser.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include <GL/glut.h>
#include "openeaagles/base/util/system.h"

// factories
#include "../shared/xzmq/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/base/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/instruments/factory.h"
#include "openeaagles/simulation/factory.h"
#include "openeaagles/networks/dis/factory.h"
#include "openeaagles/otw/factory.h"

#include "MapPage.h"
#include "Station.h"
#include "Display.h"

#include <string>
#include <cstdlib>

// frame rate
const unsigned int frameRate = 20;

Station* station = nullptr;

// timer function, in this case, the background (updateData) function
void timerFunc(int)
{
    const double dt0 = 1.0 / static_cast<double>(frameRate);
    const unsigned int millis = static_cast<unsigned int>(dt0 * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    // Current time
    const double time = oe::base::getComputerTime();

    // N-1 Time
    static double time0 = time;

    // Compute delta time
    const double dt = static_cast<double>(time - time0);
    time0 = time;

    oe::base::Timer::updateTimers(dt);
    oe::graphics::Graphic::flashTimer(dt);
    station->updateData(dt);
}

// our class factory
oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

    if ( name == MapPage::getFactoryName() )       { obj = new MapPage(); }
    else if ( name == Station::getFactoryName() )  { obj = new Station(); }
    else if ( name == Display::getFactoryName() )  { obj = new Display(); }

    // example libraries
    if (obj == nullptr)  { obj = oe::xzmq::factory(name);         }

    // framework libraries
    if (obj == nullptr)  { obj = oe::otw::factory(name);          }
    if (obj == nullptr)  { obj = oe::instruments::factory(name);  }
    if (obj == nullptr)  { obj = oe::simulation::factory(name);   }
    if (obj == nullptr)  { obj = oe::dis::factory(name);          }
    if (obj == nullptr)  { obj = oe::graphics::factory(name);     }
    if (obj == nullptr)  { obj = oe::glut::factory(name);         }
    if (obj == nullptr)  { obj = oe::base::factory(name);         }

    return obj;
}

// station builder
Station* builder(const std::string& filename)
{
   // read configuration file
   unsigned int num_errors = 0;
   oe::base::Object* obj = oe::base::edl_parser(filename, factory, &num_errors);
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
   oe::base::Pair* pair = dynamic_cast<oe::base::Pair*>(obj);
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
   std::string configFilename = "test.edl";

   // build a station
   station = builder(configFilename);

   // reset the Simulation
   station->event(oe::base::Component::RESET_EVENT);

   // set timer for the background tasks
   const double dt = 1.0 / static_cast<double>(frameRate);
   const unsigned int millis = static_cast<unsigned int>(dt * 1000);

   // ensure everything is reset
   station->updateData(dt);
   station->updateTC(dt);
   station->event(oe::base::Component::RESET_EVENT);

   glutTimerFunc(millis, timerFunc, 1);

   // create the Time Critical Thread (updateTC())
   station->createTimeCriticalProcess();

   glutMainLoop();
   return 0;
}

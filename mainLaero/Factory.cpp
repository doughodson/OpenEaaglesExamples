//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "TestStation.h"
#include "AdiDisplay.h"
#include "MapDisplay.h"
#include "MapPage.h"

// class factories
#include "../shared/xZeroMQHandlers/Factory.h"
#include "openeaagles/simulation/Factory.h"
#include "openeaagles/vehicles/Factory.h"
#include "openeaagles/sensors/Factory.h"
#include "openeaagles/dis/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/basic/Factory.h"

namespace Eaagles {
namespace Example {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = 0;

    if ( strcmp(name, TestStation::getFactoryName()) == 0 ) {
        obj = new TestStation();
    }
    else if ( strcmp(name, AdiDisplay::getFactoryName()) == 0 ) {
        obj = new AdiDisplay();
    }
    else if ( strcmp(name, MapDisplay::getFactoryName()) == 0 ) {
        obj = new MapDisplay();
    }
    else if ( strcmp(name, MapPage::getFactoryName()) == 0 ) {
        obj = new MapPage();
    }

    // Example libraries
    if (obj == 0) obj = xZeroMQHandlers::Factory::createObj(name);

    // Framework libraries
    if (obj == 0) obj = Simulation::Factory::createObj(name);
    if (obj == 0) obj = Sensor::Factory::createObj(name);
    if (obj == 0) obj = Instruments::Factory::createObj(name);
    if (obj == 0) obj = Network::Dis::Factory::createObj(name);
    if (obj == 0) obj = Vehicle::Factory::createObj(name);
    if (obj == 0) obj = BasicGL::Factory::createObj(name);
    if (obj == 0) obj = Glut::Factory::createObj(name);
    if (obj == 0) obj = Basic::Factory::createObj(name);

    return obj;
}

}  // end namespace Example
}  // end namespace Eaagles


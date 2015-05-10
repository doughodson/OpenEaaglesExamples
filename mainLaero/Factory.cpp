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
#include "openeaagles/dynamics/Factory.h"
#include "openeaagles/sensors/Factory.h"
#include "openeaagles/dis/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/basic/Factory.h"

#include <cstring>

namespace Eaagles {
namespace Example {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = nullptr;

    if ( std::strcmp(name, TestStation::getFactoryName()) == 0 ) {
        obj = new TestStation();
    }
    else if ( std::strcmp(name, AdiDisplay::getFactoryName()) == 0 ) {
        obj = new AdiDisplay();
    }
    else if ( std::strcmp(name, MapDisplay::getFactoryName()) == 0 ) {
        obj = new MapDisplay();
    }
    else if ( std::strcmp(name, MapPage::getFactoryName()) == 0 ) {
        obj = new MapPage();
    }

    // Example libraries
    if (obj == nullptr) obj = xZeroMQHandlers::Factory::createObj(name);

    // Framework libraries
    if (obj == nullptr) obj = Simulation::Factory::createObj(name);
    if (obj == nullptr) obj = Sensor::Factory::createObj(name);
    if (obj == nullptr) obj = Instruments::Factory::createObj(name);
    if (obj == nullptr) obj = Network::Dis::Factory::createObj(name);
    if (obj == nullptr) obj = Dynamics::Factory::createObj(name);
    if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
    if (obj == nullptr) obj = Glut::Factory::createObj(name);
    if (obj == nullptr) obj = Basic::Factory::createObj(name);

    return obj;
}

}  // end namespace Example
}  // end namespace Eaagles


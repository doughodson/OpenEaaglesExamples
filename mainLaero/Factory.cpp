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

namespace oe {
namespace example {

Factory::Factory()
{}

basic::Object* Factory::createObj(const char* name)
{
    basic::Object* obj = nullptr;

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
    if (obj == nullptr) obj = network::dis::Factory::createObj(name);
<<<<<<< HEAD
    if (obj == nullptr) obj = dynamics::Factory::createObj(name);
=======
    if (obj == nullptr) obj = Dynamics::Factory::createObj(name);
>>>>>>> 76e51914a3c7bcf37aa3ced2096544759ec5fe90
    if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
    if (obj == nullptr) obj = Glut::Factory::createObj(name);
    if (obj == nullptr) obj = basic::Factory::createObj(name);

    return obj;
}

}  // end namespace example
}  // end namespace oe


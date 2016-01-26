//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "TestDisplay.h"
#include "TestIoHandler.h"
#include "SimStation.h"

#include "xPanel/Factory.h"

// class factories
#include "../shared/xZeroMQHandlers/Factory.h"
#include "openeaagles/basic/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/dis/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/ioDevice/Factory.h"
#include "openeaagles/otw/Factory.h"
#include "openeaagles/sensors/Factory.h"
#include "openeaagles/simulation/Factory.h"
#include "openeaagles/dynamics/Factory.h"

#include <cstring>

namespace oe {
namespace example {

Factory::Factory()
{}

basic::Object* Factory::createObj(const char* name)
{
    basic::Object* obj = nullptr;

    if ( std::strcmp(name, SimStation::getFactoryName()) == 0 ) {
        obj = new SimStation();
    }
    else if ( std::strcmp(name, TestDisplay::getFactoryName()) == 0 ) {
        obj = new TestDisplay();
    }
    else if ( std::strcmp(name, TestIoHandler::getFactoryName()) == 0 ) {
        obj = new TestIoHandler();
    }

    // example libraries
    if (obj == nullptr) obj = xPanel::Factory::createObj(name);
    if (obj == nullptr) obj = xZeroMQHandlers::Factory::createObj(name);

    // framework libraries
    if (obj == nullptr) obj = Simulation::Factory::createObj(name);
    if (obj == nullptr) obj = instruments::Factory::createObj(name);
    if (obj == nullptr) obj = ioDevice::Factory::createObj(name);
    if (obj == nullptr) obj = instruments::Factory::createObj(name);
    if (obj == nullptr) obj = dynamics::Factory::createObj(name);
    if (obj == nullptr) obj = sensor::Factory::createObj(name);
    if (obj == nullptr) obj = otw::Factory::createObj(name);
    if (obj == nullptr) obj = network::dis::Factory::createObj(name);
    if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
    if (obj == nullptr) obj = glut::Factory::createObj(name);
    if (obj == nullptr) obj = basic::Factory::createObj(name);

    return obj;
}

}  // end namespace example
}  // end namespace oe


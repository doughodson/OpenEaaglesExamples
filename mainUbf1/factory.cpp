
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "TestDisplay.h"
#include "TestIoHandler.h"
#include "SimStation.h"

// factories
#include "xbehaviors/factory.h"
#include "xpanel/factory.h"

#include "openeaagles/base/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/dis/factory.h"
#include "openeaagles/instruments/factory.h"
#include "openeaagles/iodevice/factory.h"
#include "openeaagles/otw/factory.h"
#include "openeaagles/models/factory.h"
#include "openeaagles/simulation/factory.h"

#include <cstring>

namespace oe {
namespace example {

base::Object* factory(const char* name)
{
    base::Object* obj = nullptr;

    if ( std::strcmp(name, SimStation::getFactoryName()) == 0 ) {
        obj = new SimStation();
    }
    else if ( std::strcmp(name, TestDisplay::getFactoryName()) == 0 ) {
        obj = new TestDisplay();
    }
    else if ( std::strcmp(name, TestIoHandler::getFactoryName()) == 0 ) {
        obj = new TestIoHandler();
    }

    // Example library packages
    if (obj == nullptr) obj = xbehaviors::factory(name);
    if (obj == nullptr) obj = xpanel::factory(name);

    // Openoe packages
    if (obj == nullptr) obj = simulation::factory(name);
    if (obj == nullptr) obj = instruments::factory(name);
    if (obj == nullptr) obj = iodevice::factory(name);
    if (obj == nullptr) obj = instruments::factory(name);
    if (obj == nullptr) obj = models::factory(name);
    if (obj == nullptr) obj = otw::factory(name);
    if (obj == nullptr) obj = network::dis::factory(name);
    if (obj == nullptr) obj = graphics::factory(name);
    if (obj == nullptr) obj = glut::factory(name);
    if (obj == nullptr) obj = base::factory(name);

    return obj;
}

}
}

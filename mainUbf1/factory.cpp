
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
#include "openeaagles/networks/dis/factory.h"
#include "openeaagles/instruments/factory.h"
#include "openeaagles/iodevice/factory.h"
#include "openeaagles/otw/factory.h"
#include "openeaagles/models/factory.h"
#include "openeaagles/simulation/factory.h"

#include <string>

oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

    if ( name == SimStation::getFactoryName() ) {
        obj = new SimStation();
    }
    else if ( name == TestDisplay::getFactoryName() ) {
        obj = new TestDisplay();
    }
    else if ( name == TestIoHandler::getFactoryName() ) {
        obj = new TestIoHandler();
    }

    // Example library packages
    if (obj == nullptr) obj = oe::xbehaviors::factory(name);
    if (obj == nullptr) obj = oe::xpanel::factory(name);

    // Openoe packages
    if (obj == nullptr) obj = oe::simulation::factory(name);
    if (obj == nullptr) obj = oe::instruments::factory(name);
    if (obj == nullptr) obj = oe::iodevice::factory(name);
    if (obj == nullptr) obj = oe::instruments::factory(name);
    if (obj == nullptr) obj = oe::models::factory(name);
    if (obj == nullptr) obj = oe::otw::factory(name);
    if (obj == nullptr) obj = oe::dis::factory(name);
    if (obj == nullptr) obj = oe::graphics::factory(name);
    if (obj == nullptr) obj = oe::glut::factory(name);
    if (obj == nullptr) obj = oe::base::factory(name);

    return obj;
}

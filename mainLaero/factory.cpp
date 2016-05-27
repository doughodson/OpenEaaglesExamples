
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "TestStation.h"
#include "AdiDisplay.h"
#include "MapDisplay.h"
#include "MapPage.h"

// factories
#include "../shared/xzmq/factory.h"
#include "openeaagles/simulation/factory.h"
#include "openeaagles/models/factory.h"
#include "openeaagles/networks/dis/factory.h"
#include "openeaagles/instruments/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/base/factory.h"

#include <string>

oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

    if ( name == TestStation::getFactoryName() ) {
        obj = new TestStation();
    }
    else if ( name == AdiDisplay::getFactoryName() ) {
        obj = new AdiDisplay();
    }
    else if ( name == MapDisplay::getFactoryName() ) {
        obj = new MapDisplay();
    }
    else if ( name == MapPage::getFactoryName() ) {
        obj = new MapPage();
    }

    // Example libraries
    if (obj == nullptr) obj = oe::xzmq::factory(name);

    // Framework libraries
    if (obj == nullptr) obj = oe::simulation::factory(name);
    if (obj == nullptr) obj = oe::models::factory(name);
    if (obj == nullptr) obj = oe::instruments::factory(name);
    if (obj == nullptr) obj = oe::dis::factory(name);
    if (obj == nullptr) obj = oe::graphics::factory(name);
    if (obj == nullptr) obj = oe::glut::factory(name);
    if (obj == nullptr) obj = oe::base::factory(name);

    return obj;
}

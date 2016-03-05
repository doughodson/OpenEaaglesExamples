
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
#include "openeaagles/dis/factory.h"
#include "openeaagles/instruments/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/base/factory.h"

#include <cstring>

namespace oe {
namespace example {

base::Object* factory(const char* name)
{
    base::Object* obj = nullptr;

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
    if (obj == nullptr) obj = xzmq::factory(name);

    // Framework libraries
    if (obj == nullptr) obj = simulation::factory(name);
    if (obj == nullptr) obj = models::factory(name);
    if (obj == nullptr) obj = instruments::factory(name);
    if (obj == nullptr) obj = network::dis::factory(name);
    if (obj == nullptr) obj = graphics::factory(name);
    if (obj == nullptr) obj = glut::factory(name);
    if (obj == nullptr) obj = base::factory(name);

    return obj;
}

}
}


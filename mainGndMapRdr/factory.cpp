
#include "factory.h"

#include "openeaagles/basic/Object.h"

#include "Display.h"
#include "RealBeamRadar.h"
#include "Station.h"

// factories
#include "openeaagles/simulation/factory.h"
#include "openeaagles/terrain/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/basic/factory.h"

#include <cstring>

namespace oe {
namespace example {

basic::Object* factory(const char* name)
{
    basic::Object* obj = nullptr;

    if ( std::strcmp(name, Display::getFactoryName()) == 0 ) {
        obj = new Display();
    }
    else if ( std::strcmp(name, RealBeamRadar::getFactoryName()) == 0 ) {
        obj = new RealBeamRadar();
    }
    else if ( std::strcmp(name, TestStation::getFactoryName()) == 0 ) {
        obj = new TestStation();
    }

    if (obj == nullptr) obj = simulation::factory(name);
    if (obj == nullptr) obj = terrain::factory(name);
    if (obj == nullptr) obj = graphics::factory(name);
    if (obj == nullptr) obj = glut::factory(name);
    if (obj == nullptr) obj = basic::factory(name);

    return obj;
}

}
}

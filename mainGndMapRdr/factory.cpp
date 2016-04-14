
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "Display.h"
#include "RealBeamRadar.h"
#include "Station.h"

// factories
#include "openeaagles/simulation/factory.h"
#include "openeaagles/terrain/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/base/factory.h"

#include <string>

namespace oe {
namespace example {

base::Object* factory(const std::string& name)
{
    base::Object* obj = nullptr;

    if ( name == Display::getFactoryName() ) {
        obj = new Display();
    }
    else if ( name == RealBeamRadar::getFactoryName() ) {
        obj = new RealBeamRadar();
    }
    else if ( name == TestStation::getFactoryName() ) {
        obj = new TestStation();
    }

    if (obj == nullptr) obj = simulation::factory(name);
    if (obj == nullptr) obj = terrain::factory(name);
    if (obj == nullptr) obj = graphics::factory(name);
    if (obj == nullptr) obj = glut::factory(name);
    if (obj == nullptr) obj = base::factory(name);

    return obj;
}

}
}

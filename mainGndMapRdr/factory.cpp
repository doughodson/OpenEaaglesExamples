
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "Display.h"
#include "RealBeamRadar.h"
#include "TestStation.h"

// factories
#include "openeaagles/simulation/factory.h"
#include "openeaagles/terrain/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/base/factory.h"

#include <string>

oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

    if ( name == Display::getFactoryName() ) {
        obj = new Display();
    }
    else if ( name == RealBeamRadar::getFactoryName() ) {
        obj = new RealBeamRadar();
    }
    else if ( name == TestStation::getFactoryName() ) {
        obj = new TestStation();
    }

    if (obj == nullptr) obj = oe::simulation::factory(name);
    if (obj == nullptr) obj = oe::terrain::factory(name);
    if (obj == nullptr) obj = oe::graphics::factory(name);
    if (obj == nullptr) obj = oe::glut::factory(name);
    if (obj == nullptr) obj = oe::base::factory(name);

    return obj;
}

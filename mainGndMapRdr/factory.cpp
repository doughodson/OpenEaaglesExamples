
#include "factory.hpp"

#include "openeaagles/base/Object.hpp"

#include "Display.hpp"
#include "RealBeamRadar.hpp"
#include "TestStation.hpp"

// factories
#include "openeaagles/simulation/factory.hpp"
#include "openeaagles/models/factory.hpp"
#include "openeaagles/terrain/factory.hpp"
#include "openeaagles/graphics/factory.hpp"
#include "openeaagles/gui/glut/factory.hpp"
#include "openeaagles/base/factory.hpp"

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
    if (obj == nullptr) obj = oe::models::factory(name);
    if (obj == nullptr) obj = oe::terrain::factory(name);
    if (obj == nullptr) obj = oe::graphics::factory(name);
    if (obj == nullptr) obj = oe::glut::factory(name);
    if (obj == nullptr) obj = oe::base::factory(name);

    return obj;
}


#include "factory.hpp"

#include "openeaagles/base/Object.hpp"

#include "TestDisplay.hpp"
#include "TestStation.hpp"
#include "DspRadar.hpp"
#include "DspRwr.hpp"
#include "TdAzPtr.hpp"
#include "TdElevPtr.hpp"

#include "openeaagles/simulation/factory.hpp"
#include "openeaagles/models/factory.hpp"
#include "openeaagles/terrain/factory.hpp"
#include "openeaagles/interop/dis/factory.hpp"
#include "openeaagles/instruments/factory.hpp"
#include "openeaagles/graphics/factory.hpp"
#include "openeaagles/gui/glut/factory.hpp"
#include "openeaagles/base/factory.hpp"

#include <string>

oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

    if ( name == TestStation::getFactoryName() ) {
        obj = new TestStation();
    }
    else if ( name == TestDisplay::getFactoryName() ) {
        obj = new TestDisplay();
    }
    else if ( name == DspRadar::getFactoryName() ) {
        obj = new DspRadar();
    }
    else if ( name == DspRwr::getFactoryName() ) {
        obj = new DspRwr();
    }
    else if ( name == TdAzPtr::getFactoryName() ) {
        obj = new TdAzPtr();
    }
    else if ( name == TdElevPtr::getFactoryName() ) {
        obj = new TdElevPtr();
    }

    if (obj == nullptr) obj = oe::simulation::factory(name);
    if (obj == nullptr) obj = oe::models::factory(name);
    if (obj == nullptr) obj = oe::terrain::factory(name);
    if (obj == nullptr) obj = oe::instruments::factory(name);
    if (obj == nullptr) obj = oe::dis::factory(name);
    if (obj == nullptr) obj = oe::graphics::factory(name);
    if (obj == nullptr) obj = oe::glut::factory(name);
    if (obj == nullptr) obj = oe::base::factory(name);

    return obj;
}

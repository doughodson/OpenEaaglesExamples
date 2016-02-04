//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "TestDisplay.h"
#include "TestStation.h"
#include "DspRadar.h"
#include "DspRwr.h"
#include "TdAzPtr.h"
#include "TdElevPtr.h"

#include "openeaagles/simulation/Factory.h"
#include "openeaagles/models/factory.h"
#include "openeaagles/dis/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/graphics/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/basic/Factory.h"

#include <cstring>

namespace oe {
namespace test {

Factory::Factory()
{}

basic::Object* Factory::createObj(const char* name)
{
    basic::Object* obj = nullptr;

    if ( std::strcmp(name, TestStation::getFactoryName()) == 0 ) {
        obj = new TestStation();
    }
    else if ( std::strcmp(name, TestDisplay::getFactoryName()) == 0 ) {
        obj = new TestDisplay();
    }
    else if ( std::strcmp(name, DspRadar::getFactoryName()) == 0 ) {
        obj = new DspRadar();
    }
    else if ( std::strcmp(name, DspRwr::getFactoryName()) == 0 ) {
        obj = new DspRwr();
    }
    else if ( std::strcmp(name, TdAzPtr::getFactoryName()) == 0 ) {
        obj = new TdAzPtr();
    }
    else if ( std::strcmp(name, TdElevPtr::getFactoryName()) == 0 ) {
        obj = new TdElevPtr();
    }

    if (obj == nullptr) obj = simulation::Factory::createObj(name);
    if (obj == nullptr) obj = models::factory(name);
    if (obj == nullptr) obj = instruments::Factory::createObj(name);
    if (obj == nullptr) obj = network::dis::Factory::createObj(name);
    if (obj == nullptr) obj = graphics::Factory::createObj(name);
    if (obj == nullptr) obj = glut::Factory::createObj(name);
    if (obj == nullptr) obj = basic::Factory::createObj(name);

    return obj;
}

}  // end namespace test
}  // end namespace oe

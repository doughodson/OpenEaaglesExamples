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
#include "openeaagles/sensors/Factory.h"
#include "openeaagles/dis/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/basic/Factory.h"

namespace Eaagles {
namespace Test {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = 0;

    if ( strcmp(name, TestStation::getFactoryName()) == 0 ) {
        obj = new TestStation();
    }
    else if ( strcmp(name, TestDisplay::getFactoryName()) == 0 ) {
        obj = new TestDisplay();
    }
    else if ( strcmp(name, DspRadar::getFactoryName()) == 0 ) {
        obj = new DspRadar();
    }
    else if ( strcmp(name, DspRwr::getFactoryName()) == 0 ) {
        obj = new DspRwr();
    }
    else if ( strcmp(name, TdAzPtr::getFactoryName()) == 0 ) {
        obj = new TdAzPtr();
    }
    else if ( strcmp(name, TdElevPtr::getFactoryName()) == 0 ) {
        obj = new TdElevPtr();
    }

    if (obj == 0) obj = Simulation::Factory::createObj(name);
    if (obj == 0) obj = Sensor::Factory::createObj(name);
    if (obj == 0) obj = Instruments::Factory::createObj(name);
    if (obj == 0) obj = Network::Dis::Factory::createObj(name);
    if (obj == 0) obj = BasicGL::Factory::createObj(name);
    if (obj == 0) obj = Glut::Factory::createObj(name);
    if (obj == 0) obj = Basic::Factory::createObj(name);

    return obj;
}

}  // end namespace Test
}  // end namespace Eaagles

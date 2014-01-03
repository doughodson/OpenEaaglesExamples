//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "DataRecordTest.h"
#include "PrintMyData.h"

#include "openeaagles/basic/Factory.h"
#include "openeaagles/recorder/Factory.h"
#include "openeaagles/simulation/Factory.h"

namespace Eaagles {
namespace Test {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = 0;

    if ( strcmp(name, DataRecordTest::getFactoryName()) == 0 ) {
        obj = new DataRecordTest();
    }
    else if ( strcmp(name, PrintMyData::getFactoryName()) == 0 ) {
        obj = new PrintMyData();
    }

    else {
        if (obj == 0) obj = Simulation::Factory::createObj(name);
        if (obj == 0) obj = Basic::Factory::createObj(name);
        if (obj == 0) obj = Recorder::Factory::createObj(name);
    }

    return obj;
}

}  // end namespace Test
}  // end namespace Eaagles

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

#include <cstring>

namespace oe {
namespace test {

Factory::Factory()
{}

basic::Object* Factory::createObj(const char* name)
{
    basic::Object* obj = nullptr;

    if ( std::strcmp(name, DataRecordTest::getFactoryName()) == 0 ) {
        obj = new DataRecordTest();
    }
    else if ( std::strcmp(name, PrintMyData::getFactoryName()) == 0 ) {
        obj = new PrintMyData();
    }

    else {
        if (obj == nullptr) obj = Simulation::Factory::createObj(name);
        if (obj == nullptr) obj = basic::Factory::createObj(name);
        if (obj == nullptr) obj = Recorder::Factory::createObj(name);
    }

    return obj;
}

}  // end namespace test
}  // end namespace oe

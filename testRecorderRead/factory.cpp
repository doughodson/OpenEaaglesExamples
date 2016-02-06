
#include "factory.h"

#include "openeaagles/basic/Object.h"

#include "DataRecordTest.h"
#include "PrintMyData.h"

#include "openeaagles/basic/factory.h"
#include "openeaagles/recorder/factory.h"
#include "openeaagles/simulation/factory.h"

namespace oe {
namespace test {

basic::Object* factory(const char* name)
{
    basic::Object* obj = nullptr;

    if ( std::strcmp(name, DataRecordTest::getFactoryName()) == 0 ) {
        obj = new DataRecordTest();
    }
    else if ( std::strcmp(name, PrintMyData::getFactoryName()) == 0 ) {
        obj = new PrintMyData();
    }

    else {
        if (obj == nullptr) obj = simulation::factory(name);
        if (obj == nullptr) obj = basic::factory(name);
        if (obj == nullptr) obj = recorder::factory(name);
    }

    return obj;
}

}
}

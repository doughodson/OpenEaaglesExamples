
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "DataRecordTest.h"
#include "PrintMyData.h"

#include "openeaagles/base/factory.h"
#include "openeaagles/recorder/factory.h"
#include "openeaagles/simulation/factory.h"

#include <string>

namespace oe {
namespace test {

base::Object* factory(const std::string& name)
{
    base::Object* obj = nullptr;

    if ( name == DataRecordTest::getFactoryName() ) {
        obj = new DataRecordTest();
    }
    else if ( name == PrintMyData::getFactoryName() ) {
        obj = new PrintMyData();
    }
    else {
        if (obj == nullptr) obj = simulation::factory(name);
        if (obj == nullptr) obj = base::factory(name);
        if (obj == nullptr) obj = recorder::factory(name);
    }

    return obj;
}

}
}


#include "factory.hpp"

#include "openeaagles/base/Object.hpp"

#include "DataRecordTest.hpp"
#include "PrintMyData.hpp"

#include "openeaagles/base/factory.hpp"
#include "openeaagles/recorder/factory.hpp"
#include "openeaagles/simulation/factory.hpp"
#include "openeaagles/models/factory.hpp"

#include <string>

oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

    if ( name == DataRecordTest::getFactoryName() ) {
        obj = new DataRecordTest();
    }
    else if ( name == PrintMyData::getFactoryName() ) {
        obj = new PrintMyData();
    }
    else {
        if (obj == nullptr) obj = oe::simulation::factory(name);
        if (obj == nullptr) obj = oe::models::factory(name);
        if (obj == nullptr) obj = oe::base::factory(name);
        if (obj == nullptr) obj = oe::recorder::factory(name);
    }

    return obj;
}

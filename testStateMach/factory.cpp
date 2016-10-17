
#include "factory.hpp"

#include "openeaagles/base/Object.hpp"

#include "TestStateMachine01.hpp"
#include "TestStateMachine02.hpp"
#include "TestStateMachine03.hpp"
#include "TestStateMachine04.hpp"
#include "TestStateMachine04A.hpp"
#include "TestStateMachine04B.hpp"
#include "TestStateMachine04C.hpp"

#include "openeaagles/base/factory.hpp"

#include <string>

using namespace oe;

base::Object* factory(const std::string& name)
{
    base::Object* obj = nullptr;

    // Test #1
    if ( name == TestStateMachine01::getFactoryName() ) {
        obj = new TestStateMachine01();
    }

    // Test #2
    else if ( name == TestStateMachine02::getFactoryName() ) {
        obj = new TestStateMachine02();
    }

    // Test #3
    else if ( name == TestStateMachine03::getFactoryName() ) {
        obj = new TestStateMachine03();
    }

    // Test #4
    else if ( name == TestStateMachine04::getFactoryName() ) {
        obj = new TestStateMachine04();
    }
    else if ( name == TestStateMachine04A::getFactoryName() ) {
        obj = new TestStateMachine04A();
    }
    else if ( name == TestStateMachine04B::getFactoryName() ) {
        obj = new TestStateMachine04B();
    }
    else if ( name == TestStateMachine04C::getFactoryName() ) {
        obj = new TestStateMachine04C();
    }

    // other packages
    if (obj == nullptr) obj = base::factory(name);

    return obj;
}

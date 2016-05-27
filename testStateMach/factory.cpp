
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "TestStateMachine01.h"
#include "TestStateMachine02.h"
#include "TestStateMachine03.h"
#include "TestStateMachine04.h"
#include "TestStateMachine04A.h"
#include "TestStateMachine04B.h"
#include "TestStateMachine04C.h"

#include "openeaagles/base/factory.h"

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

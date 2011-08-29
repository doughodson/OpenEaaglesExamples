
#include "formFunc.h"

#include "TestStateMachine01.h"
#include "TestStateMachine02.h"
#include "TestStateMachine03.h"
#include "TestStateMachine04.h"
#include "TestStateMachine04A.h"
#include "TestStateMachine04B.h"
#include "TestStateMachine04C.h"

#include "openeaagles/basic/basicFF.h"


namespace Eaagles {
namespace TestStateMach {

Basic::Object* formFunc(const char* formname)
{
    Basic::Object* newform = 0;

    // Test #1
    if ( strcmp(formname, TestStateMachine01::getFormName()) == 0 ) {
        newform = new TestStateMachine01();
    }

    // Test #2
    else if ( strcmp(formname, TestStateMachine02::getFormName()) == 0 ) {
        newform = new TestStateMachine02();
    }

    // Test #3
    else if ( strcmp(formname, TestStateMachine03::getFormName()) == 0 ) {
        newform = new TestStateMachine03();
    }

    // Test #4
    else if ( strcmp(formname, TestStateMachine04::getFormName()) == 0 ) {
        newform = new TestStateMachine04();
    }
    else if ( strcmp(formname, TestStateMachine04A::getFormName()) == 0 ) {
        newform = new TestStateMachine04A();
    }
    else if ( strcmp(formname, TestStateMachine04B::getFormName()) == 0 ) {
        newform = new TestStateMachine04B();
    }
    else if ( strcmp(formname, TestStateMachine04C::getFormName()) == 0 ) {
        newform = new TestStateMachine04C();
    }

    // OpenEaagles packages
    if (newform == 0) newform = Basic::basicFormFunc(formname);

    return newform;
}

} // End TestStateMach namespace
} // End Eaagles namespace

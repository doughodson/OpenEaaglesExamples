
#include "TestObject.hpp"

#include "openeaagles/base/util/str_utils.hpp"
#include <iostream>

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestObject, "TestObject")
EMPTY_SERIALIZER(TestObject)
EMPTY_DELETEDATA(TestObject)

TestObject::TestObject()
{
    STANDARD_CONSTRUCTOR()
}

void TestObject::copyData(const TestObject& org, const bool)
{
    BaseClass::copyData(org);

    boolVal = org.boolVal;
    intVal = org.intVal;
    floatVal = org.floatVal;
    doubleVal = org.doubleVal;
    realVal = org.realVal;
    charVal = org.charVal;
}

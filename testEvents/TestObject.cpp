
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
    boolVal = false;
    intVal = 0;
    floatVal = 0.0f;
    doubleVal = 0.0;
    realVal = 0;
    base::utStrcpy(charVal, sizeof(charVal), "ASCII");
}

void TestObject::copyData(const TestObject& org, const bool)
{
    BaseClass::copyData(org);

    boolVal = org.boolVal;
    intVal = org.intVal;
    floatVal = org.floatVal;
    doubleVal = org.doubleVal;
    realVal = org.realVal;
    base::utStrcpy(charVal, sizeof(charVal), org.charVal);
}

//------------------------------------------------------------------------------
// Class: TestObject
//------------------------------------------------------------------------------
#include "TestObject.h"

// disable all deprecation warnings for now, until we fix
// they are quite annoying to see over and over again...
#if(_MSC_VER>=1400)   // VC8+
# pragma warning(disable: 4996)
#endif

namespace Eaagles {
namespace Test {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestObject, "TestObject")
EMPTY_SERIALIZER(TestObject)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
TestObject::TestObject()
{
    STANDARD_CONSTRUCTOR()
    boolVal = false;
    intVal = 0;
    floatVal = 0.0f;
    doubleVal = 0.0;
    realVal = 0;
    lcStrcpy(charVal, sizeof(charVal), "ASCII");
}

//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void TestObject::copyData(const TestObject& org, const bool)
{
    BaseClass::copyData(org);

    boolVal = org.boolVal;
    intVal = org.intVal;
    floatVal = org.floatVal;
    doubleVal = org.doubleVal;
    realVal = org.realVal;
    lcStrcpy(charVal, sizeof(charVal), org.charVal);
}

//------------------------------------------------------------------------------
// deleteData()
//------------------------------------------------------------------------------
EMPTY_DELETEDATA(TestObject)

} // End Test namespace
} // End Eaagles namespace

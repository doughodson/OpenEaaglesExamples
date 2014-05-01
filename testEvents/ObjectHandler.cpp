//------------------------------------------------------------------------------
// Class: ObjectHandler
//------------------------------------------------------------------------------
#include "ObjectHandler.h"
#include "TestObject.h"

namespace Eaagles {
namespace Test {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(ObjectHandler, "ObjectHandler")
EMPTY_SERIALIZER(ObjectHandler)

BEGIN_EVENT_HANDLER(ObjectHandler)
    ON_EVENT_OBJ(UPDATE_VALUE, onUpdateObject, TestObject)
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
ObjectHandler::ObjectHandler()
{
    STANDARD_CONSTRUCTOR()

    boolSD.empty();
    intSD.empty();
    floatSD.empty();
    doubleSD.empty();
    realSD.empty();
    charSD.empty();
}

//------------------------------------------------------------------------------
// copyData()
//------------------------------------------------------------------------------
void ObjectHandler::copyData(const ObjectHandler& org, const bool)
{
    BaseClass::copyData(org);

    boolSD.empty();
    intSD.empty();
    floatSD.empty();
    doubleSD.empty();
    realSD.empty();
    charSD.empty();
}

//------------------------------------------------------------------------------
// deleteData()
//------------------------------------------------------------------------------
EMPTY_DELETEDATA(ObjectHandler)

//------------------------------------------------------------------------------
// onUpdateObject() - bring our test object in and fill our data.
//------------------------------------------------------------------------------
bool ObjectHandler::onUpdateObject(const TestObject* const x)
{
    if (x != 0) {
        TestObject* obj = const_cast<TestObject*>(x);
        bool boolVal = obj->getBoolean();
        send("objboolean", UPDATE_VALUE, boolVal, boolSD);
        int intVal = obj->getInteger();
        send("objinteger", UPDATE_VALUE, intVal, intSD);
        float floatVal = obj->getFloat();
        send("objfloat", UPDATE_VALUE, floatVal, floatSD);
        double doubleVal = obj->getDouble();
        send("objdouble", UPDATE_VALUE, doubleVal, doubleSD);
        LCreal realVal = obj->getReal();
        send("objreal", UPDATE_VALUE, realVal, realSD);
        const char* myChar = obj->getChar();
        send("objascii", UPDATE_VALUE, myChar, charSD);
    }
            
    return true;
}

} // End Test namespace
} // End Eaagles namespace

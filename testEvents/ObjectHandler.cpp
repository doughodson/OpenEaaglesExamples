
#include "ObjectHandler.hpp"
#include "TestObject.hpp"
#include <iostream>
#include <string>

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(ObjectHandler, "ObjectHandler")
EMPTY_SERIALIZER(ObjectHandler)
EMPTY_DELETEDATA(ObjectHandler)

BEGIN_EVENT_HANDLER(ObjectHandler)
    ON_EVENT_OBJ(UPDATE_VALUE, onUpdateObject, TestObject)
END_EVENT_HANDLER()

ObjectHandler::ObjectHandler()
{
    STANDARD_CONSTRUCTOR()
}

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
// onUpdateObject() - bring our test object in and fill our data.
//------------------------------------------------------------------------------
bool ObjectHandler::onUpdateObject(const TestObject* const x)
{
    if (x != nullptr) {
        TestObject* obj = const_cast<TestObject*>(x);
        bool boolVal = obj->getBoolean();
        send("objboolean", UPDATE_VALUE, boolVal, boolSD);
        int intVal = obj->getInteger();
        send("objinteger", UPDATE_VALUE, intVal, intSD);
        float floatVal = obj->getFloat();
        send("objfloat", UPDATE_VALUE, floatVal, floatSD);
        double doubleVal = obj->getDouble();
        send("objdouble", UPDATE_VALUE, doubleVal, doubleSD);
        double realVal = obj->getReal();
        send("objreal", UPDATE_VALUE, realVal, realSD);
        const std::string& myChar = obj->getChar();
        send("objascii", UPDATE_VALUE, myChar.c_str(), charSD);
    }

    return true;
}

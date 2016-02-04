//------------------------------------------------------------------------------
// Class: ObjectHandler
// Description: This is a simple generic class that will take in a send
// command from it's parent as an object, and will then fill it's own
// private data from that object.
//------------------------------------------------------------------------------
#ifndef __oe_test_ObjectHandler_H__
#define __oe_test_ObjectHandler_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
namespace test {

class TestObject;

class ObjectHandler : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(ObjectHandler,BasicGL::Graphic)

public:
   ObjectHandler();

    bool event(const int event, basic::Object* const obj = nullptr) override;

private:
    bool onUpdateObject(const TestObject* const x);

    SendData boolSD;
    SendData intSD;
    SendData floatSD;
    SendData doubleSD;
    SendData realSD;
    SendData charSD;
};

} // End test namespace
} // End oe namespace

#endif

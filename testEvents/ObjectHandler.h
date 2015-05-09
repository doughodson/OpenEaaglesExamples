//------------------------------------------------------------------------------
// Class: ObjectHandler
// Description: This is a simple generic class that will take in a send
// command from it's parent as an object, and will then fill it's own
// private data from that object.
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_ObjectHandler_H__
#define __Eaagles_Test_ObjectHandler_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace Test {

class TestObject;

class ObjectHandler : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(ObjectHandler,BasicGL::Graphic)

public:
   ObjectHandler();

    bool event(const int event, Basic::Object* const obj = nullptr) override;

private:
    bool onUpdateObject(const TestObject* const x);

    SendData boolSD;
    SendData intSD;
    SendData floatSD;
    SendData doubleSD;
    SendData realSD;
    SendData charSD;
};

} // End Test namespace
} // End Eaagles namespace

#endif

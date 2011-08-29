//------------------------------------------------------------------------------
// Class:	Basic::Component -> ObjectHandler
// Description: This is a simple generic class that will take in a send
// command from it's parent as an object, and will then fill it's own 
// private data from that object.
//------------------------------------------------------------------------------
#ifndef	__OPENEAAGLES_TestEvents_OBJECTHANDLER_H__
#define __OPENEAAGLES_TestEvents_OBJECTHANDLER_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace TestEvents {

class TestObject;

class ObjectHandler : public BasicGL::Graphic{
    DECLARE_SUBCLASS(ObjectHandler,BasicGL::Graphic)

public:
   ObjectHandler();

    // Basic::Component interface
    virtual bool event(const int event, Basic::Object* const obj = 0);

private:
    bool onUpdateObject(const TestObject* const x);

    SendData boolSD;    
    SendData intSD;
    SendData floatSD;
    SendData doubleSD;
    SendData realSD;
    SendData charSD;
};

} // End TestEvents namespace
} // End Eaagles namespace

#endif	// __OPENEAAGLES_TestEvents_OBJECTHANDLER_H__

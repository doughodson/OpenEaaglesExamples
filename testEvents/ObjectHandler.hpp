
#ifndef __ObjectHandler_H__
#define __ObjectHandler_H__

#include "openeaagles/graphics/Graphic.hpp"

class TestObject;

//------------------------------------------------------------------------------
// Class: ObjectHandler
// Description: This is a simple generic class that will take in a send
// command from it's parent as an object, and will then fill it's own
// private data from that object.
//------------------------------------------------------------------------------
class ObjectHandler : public oe::graphics::Graphic
{
   DECLARE_SUBCLASS(ObjectHandler, oe::graphics::Graphic)

public:
   ObjectHandler();

   virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;

private:
   bool onUpdateObject(const TestObject* const x);

   SendData boolSD;
   SendData intSD;
   SendData floatSD;
   SendData doubleSD;
   SendData realSD;
   SendData charSD;
};

#endif

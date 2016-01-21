//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __oe_Example_Factory_H__
#define __oe_Example_Factory_H__

namespace oe {

namespace Basic { class Object; }

namespace Example {

class Factory
{
public:
   static Basic::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // end namespace Example
}  // end namespace oe

#endif

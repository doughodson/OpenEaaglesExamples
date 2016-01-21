
#ifndef __oe_Example_Factory_H__
#define __oe_Example_Factory_H__

namespace oe {
   namespace Basic { class Object; }

namespace Example {

//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
class Factory
{
public:
   static Basic::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // End namespace Example
}  // End namespace oe

#endif


#ifndef __Eaagles_Example_Factory_H__
#define __Eaagles_Example_Factory_H__

namespace Eaagles {
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
}  // End namespace Eaagles

#endif

//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __Eaagles_MainLaero_Factory_H__
#define __Eaagles_MainLaero_Factory_H__

namespace Eaagles {

namespace Basic { class Object; }

namespace MainLaero {

class Factory
{
public:
   static Basic::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // end namespace MainLaero
}  // end namespace Eaagles

#endif

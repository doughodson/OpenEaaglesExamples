//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __Eaagles_Sim3_Factory_H__
#define __Eaagles_Sim3_Factory_H__

namespace Eaagles {

namespace Basic { class Object; }

namespace Sim3 {

class Factory
{
public:
   static Basic::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // end namespace Sim3
}  // end namespace Eaagles

#endif

//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __Eaagles_xBehaviors_Factory_H__
#define __Eaagles_xBehaviors_Factory_H__

namespace Eaagles {

namespace Basic { class Object; }

namespace xBehaviors {

class Factory
{
public:
   static Basic::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // end namespace xBehaviors
}  // end namespace Eaagles

#endif

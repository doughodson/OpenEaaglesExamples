//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __oe_xBehaviors_Factory_H__
#define __oe_xBehaviors_Factory_H__

namespace oe {

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
}  // end namespace oe

#endif

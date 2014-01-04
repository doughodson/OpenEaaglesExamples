//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __Eaagles_xZeroMQHandlers_Factory_H__
#define __Eaagles_xZeroMQHandlers_Factory_H__

namespace Eaagles {

namespace Basic { class Object; }

namespace xZeroMQHandlers {

class Factory
{
public:
   static Basic::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // end namespace xZeroMQHandlers
}  // end namespace Eaagles

#endif

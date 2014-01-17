//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __Eaagles_xRecorder_Factory_H__
#define __Eaagles_xRecorder_Factory_H__

namespace Eaagles {

namespace Basic { class Object; }

namespace xRecorder {

class Factory
{
public:
   static Basic::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // end namespace xRecorder
}  // end namespace Eaagles

#endif

//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __oe_xRecorder_Factory_H__
#define __oe_xRecorder_Factory_H__

namespace oe {

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
}  // end namespace oe

#endif

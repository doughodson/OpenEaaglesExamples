//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __oe_xPanel_Factory_H__
#define __oe_xPanel_Factory_H__

namespace oe {

namespace basic { class Object; }

namespace xPanel {

class Factory
{
public:
   static basic::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // end namespace xPanel
}  // end namespace oe

#endif

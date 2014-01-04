//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __Eaagles_xPanel_Factory_H__
#define __Eaagles_xPanel_Factory_H__

namespace Eaagles {

namespace Basic { class Object; }

namespace xPanel {

class Factory
{
public:
   static Basic::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // end namespace xPanel
}  // end namespace Eaagles

#endif

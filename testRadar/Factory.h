//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __oe_Test_Factory_H__
#define __oe_Test_Factory_H__

namespace oe {

namespace Basic { class Object; }

namespace Test {

class Factory
{
public:
   static Basic::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // end namespace Test
}  // end namespace oe

#endif

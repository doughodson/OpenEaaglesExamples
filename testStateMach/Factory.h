//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_Factory_H__
#define __Eaagles_Test_Factory_H__

namespace Eaagles {

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
}  // end namespace Eaagles

#endif

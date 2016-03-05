//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#ifndef __oe_test_Factory_H__
#define __oe_test_Factory_H__

namespace oe {

namespace base { class Object; }

namespace test {

class Factory
{
public:
   static base::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // end namespace test
}  // end namespace oe

#endif


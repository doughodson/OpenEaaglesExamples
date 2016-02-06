
#ifndef __oe_example_Factory_H__
#define __oe_example_Factory_H__

namespace oe {
   namespace basic { class Object; }

namespace example {

//------------------------------------------------------------------------------
// Class: Factory
//
// Description: Class factory
//------------------------------------------------------------------------------
class Factory
{
public:
   static basic::Object* createObj(const char* name);

protected:
   Factory();   // prevent object creation
};

}  // End namespace example
}  // End namespace oe

#endif

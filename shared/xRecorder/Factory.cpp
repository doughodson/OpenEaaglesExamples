//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "DataRecorder.h"

namespace oe {
namespace xRecorder {

Factory::Factory()
{}

basic::Object* Factory::createObj(const char* name)
{
    basic::Object* obj = nullptr;

   if ( std::strcmp(name, DataRecorder::getFactoryName()) == 0 ) {
      obj = new DataRecorder();
   }

    return obj;
}

}  // end namespace xRecorder
}  // end namespace oe

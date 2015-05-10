//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "DataRecorder.h"

#include <cstring>

namespace Eaagles {
namespace xRecorder {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = nullptr;

   if ( std::strcmp(name, DataRecorder::getFactoryName()) == 0 ) {
      obj = new DataRecorder();
   }

    return obj;
}

}  // end namespace xRecorder
}  // end namespace Eaagles

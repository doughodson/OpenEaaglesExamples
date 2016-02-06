
#include "factory.h"

#include "openeaagles/basic/Object.h"

#include "DataRecorder.h"

namespace oe {
namespace xrecorder {

basic::Object* factory(const char* name)
{
    basic::Object* obj = nullptr;

   if ( std::strcmp(name, DataRecorder::getFactoryName()) == 0 ) {
      obj = new DataRecorder();
   }

    return obj;
}

}
}

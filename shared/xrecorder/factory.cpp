
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "DataRecorder.h"

namespace oe {
namespace xrecorder {

base::Object* factory(const char* name)
{
    base::Object* obj = nullptr;

   if ( std::strcmp(name, DataRecorder::getFactoryName()) == 0 ) {
      obj = new DataRecorder();
   }

    return obj;
}

}
}

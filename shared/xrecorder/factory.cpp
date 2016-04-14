
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "DataRecorder.h"

#include <string>

namespace oe {
namespace xrecorder {

base::Object* factory(const std::string& name)
{
    base::Object* obj = nullptr;

   if ( name == DataRecorder::getFactoryName() ) {
      obj = new DataRecorder();
   }

    return obj;
}

}
}

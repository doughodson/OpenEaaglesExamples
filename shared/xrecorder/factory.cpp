
#include "factory.hpp"

#include "openeaagles/base/Object.hpp"

#include "DataRecorder.hpp"

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

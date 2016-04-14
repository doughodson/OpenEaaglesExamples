
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "ZeroMQContext.h"
#include "ZeroMQHandler.h"

#include <string>

namespace oe {
namespace xzmq {

base::Object* factory(const std::string& name)
{
    base::Object* obj = nullptr;

    if ( name == ZeroMQContext::getFactoryName() ) {
        obj = new ZeroMQContext;
    }
    else if ( name == ZeroMQHandler::getFactoryName() ) {
        obj = new ZeroMQHandler;
    }

    return obj;
}

}
}


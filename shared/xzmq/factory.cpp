
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "ZeroMQContext.h"
#include "ZeroMQHandler.h"

#include <cstring>

namespace oe {
namespace xzmq {

base::Object* factory(const char* name)
{
    base::Object* obj = nullptr;

    if (std::strcmp (name, ZeroMQContext::getFactoryName ()) == 0) {
        obj = new ZeroMQContext;
    }
    else if (std::strcmp (name, ZeroMQHandler::getFactoryName ()) == 0) {
        obj = new ZeroMQHandler;
    }

    return obj;
}

}
}


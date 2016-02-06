
#include "factory.h"

#include "openeaagles/basic/Object.h"

#include "ZeroMQContext.h"
#include "ZeroMQHandler.h"

#include <cstring>

namespace oe {
namespace xzmq {

basic::Object* factory(const char* name)
{
    basic::Object* obj = nullptr;

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


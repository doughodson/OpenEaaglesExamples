//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "ZeroMQContext.h"
#include "ZeroMQHandler.h"

#include <cstring>

namespace oe {
namespace xZeroMQHandlers {

Factory::Factory()
{}

basic::Object* Factory::createObj(const char* name)
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

} // End xZeroMQHandlers namespace
} // End oe namespace


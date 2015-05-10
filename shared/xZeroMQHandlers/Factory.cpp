//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "ZeroMQContext.h"
#include "ZeroMQHandler.h"

#include <cstring>

namespace Eaagles {
namespace xZeroMQHandlers {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = nullptr;

    if (std::strcmp (name, ZeroMQContext::getFactoryName ()) == 0) {
        obj = new ZeroMQContext;
    }
    else if (std::strcmp (name, ZeroMQHandler::getFactoryName ()) == 0) {
        obj = new ZeroMQHandler;
    }

    return obj;
}

} // End xZeroMQHandlers namespace
} // End Eaagles namespace


//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "ZeroMQContext.h"
#include "ZeroMQHandler.h"

namespace Eaagles {
namespace xZeroMQHandlers {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = 0;

    if (strcmp (name, ZeroMQContext::getFactoryName ()) == 0) {
        obj = new ZeroMQContext;
    }
    else if (strcmp (name, ZeroMQHandler::getFactoryName ()) == 0) {
        obj = new ZeroMQHandler;
    }

    return obj;
}

} // End xZeroMQHandlers namespace
} // End Eaagles namespace


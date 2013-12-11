//------------------------------------------------------------------------------
// Class: ZeroMQHandler
//------------------------------------------------------------------------------

#include "ZeroMQHandler.h"

namespace Eaagles {
namespace xZeroMQHandlers {

//==============================================================================
// Class: ZeroMQHandler
//==============================================================================
IMPLEMENT_SUBCLASS(ZeroMQHandler, "ZeroMQHandler")

EMPTY_SLOTTABLE(ZeroMQHandler)
EMPTY_DELETEDATA(ZeroMQHandler)
EMPTY_COPYDATA(ZeroMQHandler)
EMPTY_SERIALIZER(ZeroMQHandler)

//------------------------------------------------------------------------------
// Constructors
//------------------------------------------------------------------------------
ZeroMQHandler::ZeroMQHandler()
{
    STANDARD_CONSTRUCTOR()
}


} // End xZeroMQHandlers namespace
} // End Eaagles namespace


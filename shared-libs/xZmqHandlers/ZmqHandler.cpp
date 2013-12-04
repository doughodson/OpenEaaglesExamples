//------------------------------------------------------------------------------
// Class: ZmqHandler
//------------------------------------------------------------------------------

#include "ZmqHandler.h"

namespace Eaagles {
namespace xZmqHandler {

//==============================================================================
// Class: ZmqHandler
//==============================================================================
IMPLEMENT_SUBCLASS(ZmqHandler, "ZmqHandler")

EMPTY_SLOTTABLE(ZmqHandler)
EMPTY_DELETEDATA(ZmqHandler)
EMPTY_COPYDATA(ZmqHandler)
EMPTY_SERIALIZER(ZmqHandler)

//------------------------------------------------------------------------------
// Constructors
//------------------------------------------------------------------------------
ZmqHandler::ZmqHandler()
{
    STANDARD_CONSTRUCTOR()
}


} // End xZmqHandler namespace
} // End Eaagles namespace


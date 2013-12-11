//------------------------------------------------------------------------------
// Class: ZeroMQHandler
//------------------------------------------------------------------------------
#ifndef __Eaagles_xZeroMQHandlers_ZeroMQHandler_H__
#define __Eaagles_xZeroMQHandlers_ZeroMQHandler_H__

#include "openeaagles/basic/NetHandler.h"

namespace Eaagles {
namespace xZeroMQHandlers {

//------------------------------------------------------------------------------
// Class: ZmqHandler
//------------------------------------------------------------------------------
class ZeroMQHandler : public Basic::NetHandler
{
   DECLARE_SUBCLASS(ZeroMQHandler, Basic::NetHandler)

public:
   ZeroMQHandler();


};

} // End xZeroMQHandlers namespace
} // End Eaagles namespace

#endif


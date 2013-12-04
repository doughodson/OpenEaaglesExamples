//------------------------------------------------------------------------------
// Class: ZeroMQHandler
//------------------------------------------------------------------------------
#ifndef __Eaagles_Basic_ZeroMQHandler_H__
#define __Eaagles_Basic_ZeroMQHandler_H__

#include "openeaagles/basic/NetHandler.h"

namespace Eaagles {
namespace xZeroMQHandler {

//------------------------------------------------------------------------------
// Class: ZmqHandler
//------------------------------------------------------------------------------
class ZeroMQHandler : public Basic::NetHandler
{
   DECLARE_SUBCLASS(ZeroMQHandler, Basic::NetHandler)

public:
   ZeroMQHandler();


};

} // End xZeroMQHandler namespace
} // End Eaagles namespace

#endif


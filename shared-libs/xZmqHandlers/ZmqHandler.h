//------------------------------------------------------------------------------
// Class: ZmqHandler
//------------------------------------------------------------------------------
#ifndef __Eaagles_Basic_ZmqHandler_H__
#define __Eaagles_Basic_ZmqHandler_H__

#include "openeaagles/basic/NetHandler.h"

namespace Eaagles {
namespace xZmqHandler {

//------------------------------------------------------------------------------
// Class: ZmqHandler
//------------------------------------------------------------------------------
class ZmqHandler : public Basic::NetHandler
{
   DECLARE_SUBCLASS(ZmqHandler, Basic::NetHandler)

public:
   ZmqHandler();


};

} // End xZmqHandler namespace
} // End Eaagles namespace

#endif


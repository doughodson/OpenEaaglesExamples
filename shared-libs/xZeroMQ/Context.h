//------------------------------------------------------------------------------
// Class: Context
//------------------------------------------------------------------------------
#ifndef __Eaagles_xZeroMQ_Context_H__
#define __Eaagles_xZeroMQ_Context_H__
#pragma once

#include "openeaagles/basic/Object.h"

namespace Eaagles {
   namespace Basic { class String; }

namespace xZeroMQ {

//------------------------------------------------------------------------------
// Class: Context
//
// Description: General 0MQ context
//
// Typically there is only one 0MQ context per application (process) for the
// creation of 0MQ sockets.  However, it is sometimes desirable to instatiate
// one per thread when sockets are created in that thread.  0MQ contexts are
// the ONLY object that can be used across thread boundaries (see 0MQ docs).
//------------------------------------------------------------------------------
class Context : public Basic::Object
{
   DECLARE_SUBCLASS(Context, Basic::Object)

public:
   Context ();

   virtual bool setSlotType (const Basic::String* const msg);

private:
   void initData ();
};

}  // End xZeroMQ namespace
}  // End Eaagles namespace

#endif


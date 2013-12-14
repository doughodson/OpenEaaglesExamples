//------------------------------------------------------------------------------
// Class: ZeroMQContext
//------------------------------------------------------------------------------
#ifndef __Eaagles_xZeroMQ_ZeroMQContext_H__
#define __Eaagles_xZeroMQ_ZeroMQContext_H__
#pragma once

#include "openeaagles/basic/Component.h"

namespace Eaagles {
   namespace Basic { class Boolean; class Integer; }

namespace xZeroMQ {

//------------------------------------------------------------------------------
// Class: ZeroMQContext
//
// Description: General 0MQ context
//
// Typically there is only one 0MQ context per application (process) for the
// creation of 0MQ sockets.  However, it is sometimes desirable to instatiate
// one per thread when sockets are created in that thread.  0MQ contexts are
// the ONLY object that can be used across thread boundaries (see 0MQ docs).
//
// The following slots will be provided for the creation and setup of the
// socket:
//
//    threadCount - Set the desired number of I/O threads
//    maxSockets  - Set the maximum number of sockets allowed
//    enableIPV6  - Enable IPV6 sockets
//
//------------------------------------------------------------------------------
class ZeroMQContext : public Basic::Component
{
   DECLARE_SUBCLASS(ZeroMQContext, Basic::Component)

public:
   ZeroMQContext ();

   // 0MQ context overridables
   virtual bool initContext ();
   virtual bool isInitialized () const;
   virtual bool terminateContext ();

   // Casting for the dereference operator much like Basic::String
   operator void* () { return context; }
   operator const void* () const { return context; }

   // Slots
   virtual bool setSlotThreadCount (const Basic::Integer* const msg);
   virtual bool setSlotMaxSockets (const Basic::Integer* const msg);
   virtual bool setSlotEnableIPV6 (const Basic::Boolean* const msg);

protected:
   bool setThreadCount (const int count);
   bool setMaxSockets (const int count);
   bool setEnableIPV6 (const bool use);

private:
   void initData ();

private:
   void* context;                // 0MQ context (they use void*)
   int   threadCount;            // Number of I/O threads (-1 = not set)
   int   maxSockets;             // Number of sockets (-1 = not set)
   int   enableIPV6;             // Use IPV6 sockets (0 or 1, -1 = not set)
   bool  ready;                  // The socket is initialized
};

}  // End xZeroMQ namespace
}  // End Eaagles namespace

#endif


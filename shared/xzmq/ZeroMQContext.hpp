
#ifndef __oe_xzmq_ZeroMQContext_H__
#define __oe_xzmq_ZeroMQContext_H__

#include "openeaagles/base/Component.hpp"

namespace oe {
namespace base { class Boolean; class Integer; }
namespace xzmq {

//------------------------------------------------------------------------------
// Class: ZeroMQContext
//
// Description: Manages a ZeroMQ (0MQ) context
//
// Typically there is only one ZeroMQ context per application (process) for the
// creation of ZeroMQ sockets.  However, it is sometimes desirable to instantiate
// one per thread when sockets are created in that thread.  ZeroMQ contexts are
// the ONLY objects that can be used across thread boundaries (see ZeroMQ docs).
//
// The following slots will be provided for the creation and setup of the
// socket:
//
//    threadCount - Size of ZeroMQ thread pool to handle I/O operations
//    maxSockets  - Maximum number of sockets allowed on the context
//    enableIPV6  - Enable IPV6 sockets
//
//------------------------------------------------------------------------------
class ZeroMQContext : public base::Component
{
   DECLARE_SUBCLASS(ZeroMQContext, base::Component)

public:
   ZeroMQContext();

   //
   virtual bool initContext();
   virtual bool isInitialized() const;
   virtual bool terminateContext();

   // Casting for the dereference operator much like base::String
   operator void* ()                { return context; }
   operator const void* () const    { return context; }

   // Slots
   virtual bool setSlotThreadCount(const base::Integer* const msg);
   virtual bool setSlotMaxSockets(const base::Integer* const msg);
   virtual bool setSlotEnableIPV6(const base::Boolean* const msg);

protected:
   bool setThreadCount(const int count);
   bool setMaxSockets(const int count);
   bool setEnableIPV6(const bool use);

private:
   void initData();
   
   void* context {};          // ZeroMQ context (they use void*)
   int   threadCount {-1};    // Number of I/O threads in pool (not set = -1)
   int   maxSockets {-1};     // Number of sockets (not set = -1)
   int   enableIPV6 {-1};     // Use IPV6 sockets (0 or 1, not set = -1)
   bool  ready {};            // initialized flag
};

}
}

#endif

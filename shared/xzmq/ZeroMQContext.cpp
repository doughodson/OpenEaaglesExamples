
#include "ZeroMQContext.hpp"

#include "openeaagles/base/Boolean.hpp"
#include "openeaagles/base/Integer.hpp"

#include <zmq.h>

namespace oe {
namespace xzmq {

IMPLEMENT_SUBCLASS(ZeroMQContext, "ZeroMQContext")

BEGIN_SLOTTABLE(ZeroMQContext)
   "threadCount",                // 1) Number containing the I/O thread pool count
   "maxSockets",                 // 2) Number containing the max socket count
   "enableIPV6",                 // 3) Boolean containing IPV6 valid
END_SLOTTABLE(ZeroMQContext)

BEGIN_SLOT_MAP(ZeroMQContext)
   ON_SLOT(1, setSlotThreadCount, base::Integer)
   ON_SLOT(2, setSlotMaxSockets,  base::Integer)
   ON_SLOT(3, setSlotEnableIPV6,  base::Boolean)
END_SLOT_MAP()

ZeroMQContext::ZeroMQContext()
{
   STANDARD_CONSTRUCTOR()
}

void ZeroMQContext::initData()
{
   context     = nullptr;
   threadCount = -1;
   maxSockets  = -1;
   enableIPV6  = -1;
   ready       = false;
}

void ZeroMQContext::copyData(const ZeroMQContext& org, const bool)
{
   BaseClass::copyData (org);

   threadCount = org.threadCount;
   maxSockets  = org.maxSockets;
   enableIPV6  = org.enableIPV6;
   ready       = org.ready;
}

void ZeroMQContext::deleteData()
{
   terminateContext();
}

bool ZeroMQContext::initContext()
{
   bool ok = true;

   // Create a new context
   if (ok) {
      context = zmq_ctx_new();
      if (context == nullptr)
         ok = false;
   }

   // Set context options
   if (ok && (threadCount != -1))  ok = (zmq_ctx_set(context, ZMQ_IO_THREADS,  threadCount) == 0);
   if (ok && (maxSockets  != -1))  ok = (zmq_ctx_set(context, ZMQ_MAX_SOCKETS, maxSockets)  == 0);
   if (ok && (enableIPV6  != -1))  ok = (zmq_ctx_set(context, ZMQ_IPV6,        enableIPV6)  == 0);

   // Indicate the context is ready... or not
   ready = ok;

   return ok;
}

bool ZeroMQContext::terminateContext()
{
   bool ok = false;

   // Terminate context.  All ZeroMQNetHandlers should be closed
   // before the context will successfully close.
   if (context != nullptr) {
      if (zmq_term(context) == 0) ok = true;
      else ok = false;
   }

   // Initialize context
   initData();

   return ok;
}

bool ZeroMQContext::isInitialized() const
{
   // If the context is not created automatically return false otherwise
   // return that the context is ready for use.
   if (context != nullptr) return ready;
   else return false;
}

bool ZeroMQContext::setThreadCount(int count)
{
   threadCount = count;
   return true;
}

bool ZeroMQContext::setMaxSockets(int count)
{
   maxSockets = count;
   return true;
}

bool ZeroMQContext::setEnableIPV6(bool enable)
{
   enableIPV6 = enable ? 1 : 0;
   return true;
}

// threadCount: Integer containing the I/O thread count
bool ZeroMQContext::setSlotThreadCount(const base::Integer* const msg)
{
   bool ok = false;
   if (msg != nullptr) ok = setThreadCount(*msg);
   return ok;
}

// maxSockets: Integer containing the max socket count
bool ZeroMQContext::setSlotMaxSockets(const base::Integer* const msg)
{
   bool ok = false;
   if (msg != nullptr) ok = setMaxSockets(*msg);
   return ok;
}

// enableIPV6: Boolean containing IPV6 valid
bool ZeroMQContext::setSlotEnableIPV6(const base::Boolean* const msg)
{
   bool ok = false;
   if (msg != nullptr) ok = setEnableIPV6(*msg);
   return ok;
}

std::ostream& ZeroMQContext::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
   int j = 0;
   if (!slotsOnly) {
      indent(sout, i);
      sout << "( " << getFactoryName() << std::endl;
      j = 4;
   }

   // Output the I/O thread count
   if (threadCount != -1) {
      indent(sout, i+j);
      sout << "threadCount: " << threadCount << std::endl;
   }

   // Output the max socket count
   if (maxSockets != -1) {
      indent(sout, i+j);
      sout << "maxSockets: " << maxSockets << std::endl;
   }

   // Output IPV6 enabled
   if (enableIPV6 != -1) {
      indent(sout, i+j);
      if (enableIPV6 == 1) sout << "enableIP6: true" << std::endl;
      else sout << "enableIP6: false" << std::endl;
   }

   BaseClass::serialize (sout, i+j, true);

   if (!slotsOnly) {
      indent(sout, i);
      sout << ")" << std::endl;
   }

   return sout;
}

}
}

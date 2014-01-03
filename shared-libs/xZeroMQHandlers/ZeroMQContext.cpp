//------------------------------------------------------------------------------
// Class: ZeroMQContext
//------------------------------------------------------------------------------
#include "ZeroMQContext.h"

#include "openeaagles/basic/Boolean.h"
#include "openeaagles/basic/Integer.h"

#include <zmq.h>

namespace Eaagles {
namespace xZeroMQHandlers {

//==============================================================================
// Class: ZeroMQContext
//==============================================================================
IMPLEMENT_SUBCLASS(ZeroMQContext, "ZeroMQContext")

// Slot Table
BEGIN_SLOTTABLE(ZeroMQContext)
   "threadCount",                // 1) Number containing the I/O thread pool count
   "maxSockets",                 // 2) Number containing the max socket count
   "enableIPV6",                 // 3) Boolean containing IPV6 valid
END_SLOTTABLE(ZeroMQContext)

// Map slot table to handles
BEGIN_SLOT_MAP(ZeroMQContext)
   ON_SLOT(1, setSlotThreadCount, Basic::Integer)
   ON_SLOT(2, setSlotMaxSockets,  Basic::Integer)
   ON_SLOT(3, setSlotEnableIPV6,  Basic::Boolean)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructors
//------------------------------------------------------------------------------
ZeroMQContext::ZeroMQContext()
{
   STANDARD_CONSTRUCTOR()
   initData();
}

void ZeroMQContext::initData()
{
   context     = 0;
   threadCount = -1;
   maxSockets  = -1;
   enableIPV6  = -1;
   ready       = false;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void ZeroMQContext::copyData(const ZeroMQContext& org, const bool cc)
{
   BaseClass::copyData (org);

   if (cc) {
      context = 0;
   }

   threadCount = org.threadCount;
   maxSockets  = org.maxSockets;
   enableIPV6  = org.enableIPV6;
   ready       = org.ready;
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
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
      if (context == 0)
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
   if (context != 0) {
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
   if (context != 0) return ready;
   else return false;
}

//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
// Set slot functions
//------------------------------------------------------------------------------

// threadCount: Integer containing the I/O thread count
bool ZeroMQContext::setSlotThreadCount(const Basic::Integer* const msg)
{
   bool ok = false;
   if (msg != 0) ok = setThreadCount(*msg);
   return ok;
}

// maxSockets: Integer containing the max socket count
bool ZeroMQContext::setSlotMaxSockets(const Basic::Integer* const msg)
{
   bool ok = false;
   if (msg != 0) ok = setMaxSockets(*msg);
   return ok;
}

// enableIPV6: Boolean containing IPV6 valid
bool ZeroMQContext::setSlotEnableIPV6(const Basic::Boolean* const msg)
{
   bool ok = false;
   if (msg != 0) ok = setEnableIPV6(*msg);
   return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Basic::Object* ZeroMQContext::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

//------------------------------------------------------------------------------
// serialize
//------------------------------------------------------------------------------
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

}  // End xZeroMQHandlers namespace
}  // End Eaagles namespace


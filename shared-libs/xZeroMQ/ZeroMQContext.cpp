//------------------------------------------------------------------------------
// Class: ZeroMQContext
//------------------------------------------------------------------------------
#include "ZeroMQContext.h"
#include "openeaagles/basic/Boolean.h"
#include "openeaagles/basic/Integer.h"

#include <zmq.h>


namespace Eaagles {
namespace xZeroMQ {

//==============================================================================
// Class: ZeroMQContext
//==============================================================================
IMPLEMENT_SUBCLASS(ZeroMQContext, "ZmqZeroMQContext")

// Slot Table
BEGIN_SLOTTABLE(ZeroMQContext)
   "threadCount",                // 1) Number containing the I/O thread count
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
ZeroMQContext::ZeroMQContext ()
{
   STANDARD_CONSTRUCTOR()
   initData ();
}


void ZeroMQContext::initData ()
{
   context = 0;
   threads = -1;
   sockets = -1;
   useipv6 = -1;
   ready   = false;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void ZeroMQContext::copyData (const ZeroMQContext& org, const bool cc)
{
   BaseClass::copyData (org);

   if (cc) {
      context = 0;
   }

   threads = org.threads;
   sockets = org.sockets;
   useipv6 = org.useipv6;
   ready   = org.ready;
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void ZeroMQContext::deleteData ()
{
   terminateContext ();
}

bool ZeroMQContext::initContext ()
{
   bool ok = false;

   // Create the 0MQ context using the new create function
   context = zmq_ctx_new ();

   if (context != 0) ok = true;

   // Set the 0MQ context options
   if (ok && threads != -1) ok = zmq_ctx_set (context, ZMQ_IO_THREADS, threads) == 0;
   if (ok && sockets != -1) ok = zmq_ctx_set (context, ZMQ_MAX_SOCKETS, sockets) == 0;
   if (ok && useipv6 != -1) ok = zmq_ctx_set (context, ZMQ_IPV6, useipv6) == 0;

   // Indicate the context is ready... or not
   ready = ok;

   return ok;
}

bool ZeroMQContext::terminateContext ()
{
   bool ok = false;

   // Terminate the 0MQ context.  All ZeroMQNetHandlers should be closed
   // before the context will successfully close.
   if (context != 0) {
      if (zmq_term (context) == 0) ok = true;
      else ok = false;
   }

   // Initialize the context information
   initData ();

   return ok;
}

bool ZeroMQContext::isInitialized () const
{
   // If the context is not created automatically return false otherwise
   // return that the context is ready for use.
   if (context != 0) return ready;
   else return false;
}

//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------
bool ZeroMQContext::setThreadCount (int count)
{
   threads = count;
   return true;
}

bool ZeroMQContext::setMaxSockets (int count)
{
   sockets = count;
   return true;
}

bool ZeroMQContext::setEnableIPV6 (bool enable)
{
   useipv6 = enable ? 1 : 0;
   return true;
}

//------------------------------------------------------------------------------
// Set slot functions
//------------------------------------------------------------------------------

// threadCount: Integer containing the I/O thread count
bool ZeroMQContext::setSlotThreadCount (const Basic::Integer* const msg)
{
   bool ok = false;
   if (msg != 0) ok = setThreadCount (*msg);
   return ok;
}

// maxSockets: Integer containing the max socket count
bool ZeroMQContext::setSlotMaxSockets (const Basic::Integer* const msg)
{
   bool ok = false;
   if (msg != 0) ok = setMaxSockets (*msg);
   return ok;
}

// enableIPV6: Boolean containing IPV6 valid
bool ZeroMQContext::setSlotEnableIPV6 (const Basic::Boolean* const msg)
{
   bool ok = false;
   if (msg != 0) ok = setEnableIPV6 (*msg);
   return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Basic::Object* ZeroMQContext::getSlotByIndex (const int si)
{
   return BaseClass::getSlotByIndex (si);
}

//------------------------------------------------------------------------------
// serialize
//------------------------------------------------------------------------------
std::ostream& ZeroMQContext::serialize (std::ostream& sout, const int i, const bool slotsOnly) const
{
   int j = 0;
   if (!slotsOnly) {
      indent (sout, i);
      sout << "( " << getFormName () << std::endl;
      j = 4;
   }

   // Output the I/O thread count
   if (threads != -1) {
      indent (sout, i+j);
      sout << "threadCount: " << threads << std::endl;
   }

   // Output the max socket count
   if (sockets != -1) {
      indent (sout, i+j);
      sout << "maxSockets: " << sockets << std::endl;
   }

   // Output IPV6 enabled
   if (useipv6 != -1) {
      indent (sout, i+j);
      if (useipv6 == 1) sout << "enableIP6: true" << std::endl;
      else sout << "enableIP6: false" << std::endl;
   }

   BaseClass::serialize (sout, i+j, true);

   if (!slotsOnly) {
      indent (sout, i);
      sout << ")" << std::endl;
   }

   return sout;
}

}  // End xZeroMQ namespace
}  // End Eaagles namespace


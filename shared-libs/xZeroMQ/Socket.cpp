//------------------------------------------------------------------------------
// Class: Socket
//------------------------------------------------------------------------------
#include "Socket.h"
#include "Context.h"
#include "openeaagles/basic/List.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/Number.h"
#include "openeaagles/basic/String.h"

#include <zmq.h>


namespace Eaagles {
namespace xZeroMQ {

//==============================================================================
// Class: Socket
//==============================================================================
IMPLEMENT_SUBCLASS(Socket, "ZmqSocket")

// Slot Table
BEGIN_SLOTTABLE(Socket)
   "context",              // 1) String containing the parent context's name
   "type",                 // 2) String containing the socket type
   "transport",            // 3) String containing the transport type
   "address",              // 4) String containing the local host's name or
   "port",                 // 5) Number of the port we are binding (required)
   "endpoint",             // 6) String containing the endpoint (3, 4, & 5)
   "options",              // 7) List of socket bind options
END_SLOTTABLE(Socket)

// Map slot table to handles
BEGIN_SLOT_MAP(Socket)
   ON_SLOT(1, setSlotContext,   Basic::String)
   ON_SLOT(2, setSlotType,      Basic::String)
   ON_SLOT(3, setSlotTransport, Basic::String)
   ON_SLOT(4, setSlotAddress,   Basic::String)
   ON_SLOT(5, setSlotPort,      Basic::Number)
   ON_SLOT(6, setSlotEndpoint,  Basic::String)
   ON_SLOT(7, setSlotOptions,   Basic::List)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructors
//------------------------------------------------------------------------------
s2i_t Socket::sts2i;
i2s_t Socket::sti2s;

s2i_t Socket::eps2i;
i2s_t Socket::epi2s;

Socket::Socket ()
{
   STANDARD_CONSTRUCTOR()
   initData ();

   // Initialize the valid socket types
   if (sts2i.empty ()) {
      sts2i["PAIR"]   = ZMQ_PAIR;
      sts2i["REQ"]    = ZMQ_REQ;
      sts2i["REP"]    = ZMQ_REP;
      sts2i["DEALER"] = ZMQ_DEALER;
      sts2i["ROUTER"] = ZMQ_ROUTER;
      sts2i["PUB"]    = ZMQ_PUB;
      sts2i["SUB"]    = ZMQ_SUB;
      sts2i["XPUB"]   = ZMQ_XPUB;
      sts2i["XSUB"]   = ZMQ_XSUB;
      sts2i["PUSH"]   = ZMQ_PUSH;
      sts2i["PULL"]   = ZMQ_PULL;
      sts2i["STREAM"] = ZMQ_STREAM;
   }

   if (sti2s.empty ()) {
      sti2s[ZMQ_PAIR]   = "PAIR";
      sti2s[ZMQ_REQ]    = "REQ";
      sti2s[ZMQ_REP]    = "REP";
      sti2s[ZMQ_DEALER] = "DEALER";
      sti2s[ZMQ_ROUTER] = "ROUTER";
      sti2s[ZMQ_PUB]    = "PUB";
      sti2s[ZMQ_SUB]    = "SUB";
      sti2s[ZMQ_XPUB]   = "XPUB";
      sti2s[ZMQ_XSUB]   = "XSUB";
      sti2s[ZMQ_PUSH]   = "PUSH";
      sti2s[ZMQ_PULL]   = "PULL";
      sti2s[ZMQ_STREAM] = "STREAM";
   }

   // Initialize the valid transports
   if (eps2i.empty ()) {
      eps2i["TCP"]    = TCP;
      eps2i["IPC"]    = IPC;
      eps2i["INPROC"] = INPROC;
      eps2i["PGM"]    = PGM;
      eps2i["EPGM"]   = EPGM;
   }

   if (epi2s.empty ()) {
      epi2s[TCP]    = "TCP";
      epi2s[IPC]    = "IPC";
      epi2s[INPROC] = "INPROC";
      epi2s[PGM]    = "PGM";
      epi2s[EPGM]   = "EPGM";
   }
}


void Socket::initData ()
{
   // Socket information
   context = 0;
   stype   = 0;
   socket  = 0;;

   // Endpoint information
   eptrans   = TCP;
   epaddress = "";
   epport    = 0;
   endpoint  = "";
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Socket::copyData (const Socket& org, const bool cc)
{
   BaseClass::copyData (org);

   if (cc) {
      context = 0;
      socket  = 0;
   }

   // Copy the socket information
   if (context != 0) context->unref ();
   context = org.context;
   if (context != 0) context->ref ();

   stype = org.stype;

   // Copy the endpoint information
   eptrans   = org.eptrans;
   epaddress = org.epaddress;
   epport    = org.epport;
   endpoint  = org.endpoint;
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void Socket::deleteData ()
{
   // Close the 0MQ socket
   if (socket != 0) zmq_close (socket);

   // Detach the parent context
   if (context != 0) context->unref ();

   // Finally set to initial state
   initData ();
}

//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Set slot functions
//------------------------------------------------------------------------------

// context: String containing the parent context's name
bool Socket::setSlotContext (const Basic::String* const msg)
{
   bool ok = false;
   if (msg != 0) {
      ok = true;
   }
   return ok;
}

// type: String containing the socket type
bool Socket::setSlotType (const Basic::String* const msg)
{
   bool ok = false;
   if (msg != 0) {
      ok = true;
   }
   return ok;
}

// transport: String containing the transport type
bool Socket::setSlotTransport (const Basic::String* const msg)
{
   bool ok = false;
   if (msg != 0) {
      ok = true;
   }
   return ok;
}

// adress: String containing the network address
bool Socket::setSlotAddress (const Basic::String* const msg)
{
   bool ok = false;
   if (msg != 0) {
      //if (address != 0) delete [] address;
      //address = msg->getCopyString ();
      ok = true;
   }
   return ok;
}

// port: Number of the port we are binding (required)
bool Socket::setSlotPort (const Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0) {
      int temp = msg->getInt ();
      if (temp >= 0 && temp <= 0xffff) {
         //ok = setPort (temp);
      }
   }
   return ok;
}

// options: List of socket bind options
bool Socket::setSlotOptions (const Basic::List* const msg)
{
   bool ok = false;
   if (msg != 0) {
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Basic::Object* Socket::getSlotByIndex (const int si)
{
   return BaseClass::getSlotByIndex (si);
}

//------------------------------------------------------------------------------
// serialize
//------------------------------------------------------------------------------
std::ostream& Socket::serialize (std::ostream& sout, const int i, const bool slotsOnly) const
{
   int j = 0;
   if (!slotsOnly) {
      indent (sout, i);
      sout << "( " << getFormName () << std::endl;
      j = 4;
   }

   //if (context != 0) {
   //}

   //if (type != 0) {
   //}

   //if (protocol != 0) {
   //}

   //if (address != 0) {
   //}

   //if (port != 0) {
      //indent (sout,i+j);
      //sout << "port: " << port << std::endl;
   //}

   //if (options != 0) {
   //}

   BaseClass::serialize (sout, i+j, true);

   if (!slotsOnly) {
      indent (sout, i);
      sout << ")" << std::endl;
   }

   return sout;
}

}  // End xZeroMQ namespace
}  // End Eaagles namespace


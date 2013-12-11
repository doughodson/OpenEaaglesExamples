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

#include <sstream>

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
      eps2i["NONE"]   = NONE;
      eps2i["TCP"]    = TCP;
      eps2i["IPC"]    = IPC;
      eps2i["INPROC"] = INPROC;
      eps2i["PGM"]    = PGM;
      eps2i["EPGM"]   = EPGM;
   }

   if (epi2s.empty ()) {
      epi2s[NONE]   = "NONE";
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
   ctxname = "";
   context = 0;
   stype   = -1;
   socket  = 0;
   bound   = false;

   // Endpoint information
   eptrans   = NONE;
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

   ctxname = org.ctxname;
   stype   = org.stype;
   socket  = 0;

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
   // Shutdown the connection
   closeConnection ();

   // Detach the parent context
   if (context != 0) context->unref ();

   // Finally set to initial state
   initData ();
}


//------------------------------------------------------------------------------
// NetHandler override functions
//------------------------------------------------------------------------------
bool Socket::initNetwork (const bool noWaitFlag)
{
   if (context == 0) return false;

   // Make sure we have a valid endpoint
   std::string epfa = endpoint;

   if (epfa.empty ()) {
      if (eptrans == NONE) return false;

      // Build the endpoint full definition
      std::ostringstream sstr;

      if (epaddress.empty ()) {
         sstr << epi2s[eptrans] << "://"
              << "*"
              << ":" << epport
              << std::ends;
      }
      else {
         sstr << epi2s[eptrans] << "://"
              << epaddress
              << ":" << epport
              << std::ends;
      }

      epfa = sstr.str ();
   }

   // Make sure the socket type is valid
   if (stype == -1) return false;

   // Create the socket
   socket = zmq_socket (*context, stype);

   if (socket == 0) return false;

   // Bind the socket
   if (zmq_bind (socket, epfa.c_str ()) == 0) bound = true;
   else bound = false;

   return bound;
}

bool Socket::isConnected () const
{
   if (socket == 0) return false;
   else return bound;
}

bool Socket::closeConnection ()
{
   // Close the 0MQ socket
   if (socket != 0) zmq_close (socket);

   socket = 0;
   bound  = false;

   return true;
}

bool Socket::setBlocked (const LcSocket s)
{
   return false;
}

bool Socket::setNoWait (const LcSocket s)
{
   return false;
}

bool Socket::sendData (const char* const packet, const int size)
{
   bool ok = false;
   return ok;
}

unsigned int Socket::recvData (char* const packet, const int maxSize)
{
   bool ok = false;
   return ok;
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
      // Save the name and find the context for use in the initialization
      // of the socket
      ctxname = *msg;
      ok      = true;
   }
   return ok;
}

// type: String containing the socket type
bool Socket::setSlotType (const Basic::String* const msg)
{
   bool ok = false;
   if (msg != 0) {
      // Find the token in the map and get the enumeration for use in the
      // initialization of the socket
      s2i_t::const_iterator k = sts2i.find (std::string (*msg));

      if (k != sts2i.end ()) {
         stype = k->second;
         ok    = true;
      }
   }
   return ok;
}

// transport: String containing the transport type
bool Socket::setSlotTransport (const Basic::String* const msg)
{
   bool ok = false;
   if (msg != 0) {
      // Find the token in the map and get the enumeration for use in the
      // initialization of the socket
      s2i_t::const_iterator k = eps2i.find (std::string (*msg));

      if (k != eps2i.end ()) {
         eptrans = (Transport) k->second;
         ok      = true;
      }
   }
   return ok;
}

// adress: String containing the network address
bool Socket::setSlotAddress (const Basic::String* const msg)
{
   bool ok = false;
   if (msg != 0) {
      // Save the address for use during the initialization of the socket
      epaddress = *msg;
      ok        = true;
   }
   return ok;
}

// port: Number of the port we are binding (required)
bool Socket::setSlotPort (const Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0) {
      // Make sure the port is between 0 and 65535
      int temp = msg->getInt ();
      if (temp >= 0 && temp <= 0xffff) {
         epport = temp;
         ok     = true;
      }
   }
   return ok;
}

// endpoint: String containing the endpoint (3, 4, & 5)
bool Socket::setSlotEndpoint (const Basic::String* const msg)
{
   bool ok = false;
   if (msg != 0) {
      // Save the endpoint definition and make sure the individual pieces
      // are ignored
      endpoint  = *msg;
      eptrans   = NONE;
      epaddress = "";
      epport    = 0;
      ok        = true;
   }
   return ok;
}

// options: List of socket bind options
bool Socket::setSlotOptions (const Basic::List* const msg)
{
   bool ok = false;
   if (msg != 0) {
      // Traverse the list of options and save them for use during the
      // initialization of the socket
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

   if (!ctxname.empty ()) {
      indent (sout, i+j);
      sout << "context: " << ctxname << std::endl;
   }

   // Output the socket type
   if (stype != -1) {
      indent (sout, i+j);
      sout << "type: " << sti2s[stype] << std::endl;
   }

   // Output the endpoint transport type
   if (eptrans != 0) {
      indent (sout, i+j);
      sout << "transport: " << epi2s[eptrans] << std::endl;
   }

   // Output the endpoint address
   if (!epaddress.empty ()) {
      indent (sout, i+j);
      sout << "address: " << epaddress << std::endl;
   }

   // Output the endpoint port
   if (epport != 0) {
      indent (sout, i+j);
      sout << "port: " << epport << std::endl;
   }

   // Output the full endpoint definition
   if (!endpoint.empty ()) {
      indent (sout, i+j);
      sout << "endpoint: " << endpoint << std::endl;
   }

   // Output the options list
   //if (options != 0) {
   //}

   if (!slotsOnly) {
      indent (sout, i);
      sout << ")" << std::endl;
   }

   return sout;
}

}  // End xZeroMQ namespace
}  // End Eaagles namespace


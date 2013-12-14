//------------------------------------------------------------------------------
// Class: ZeroMQHandler
//------------------------------------------------------------------------------
#include "ZeroMQHandler.h"
#include "ZeroMQContext.h"
#include "openeaagles/basic/Integer.h"
#include "openeaagles/basic/String.h"

#include <sstream>

#include <zmq.h>


namespace Eaagles {
namespace xZeroMQ {

//==============================================================================
// Class: ZeroMQHandler
//==============================================================================
IMPLEMENT_SUBCLASS(ZeroMQHandler, "ZmqZeroMQHandler")

// Slot Table
BEGIN_SLOTTABLE(ZeroMQHandler)
   "context",              // 1) String containing the parent context's name
   "socketType",           // 2) String containing the socket type
   "endPoint",             // 3) String containing the endpoint (3, 4, & 5)
   "linger",               // 4) Integer containing the linger period (ms)
   "subscribe",            // 5) String containing the message filter
   "backLog",              // 6) Integer containing the connection queue size
   "identity",             // 7) String containing the identity
   "sendBufSizeKb",        // 8) Integer containing the send buffer size in KB's
   "recvBufSizeKb",        // 9) Integer containing the receive buffer size in KB's
END_SLOTTABLE(ZeroMQHandler)

// Map slot table to handles
BEGIN_SLOT_MAP(ZeroMQHandler)
   ON_SLOT(1, setSlotContext,     Basic::String)
   ON_SLOT(2, setSlotSocketType,  Basic::String)
   ON_SLOT(3, setSlotEndpoint,    Basic::String)
   ON_SLOT(4, setSlotLinger,      Basic::Integer)
   ON_SLOT(5, setSlotSubscribe,   Basic::String)
   ON_SLOT(6, setSlotBackLog,     Basic::Integer)
   ON_SLOT(7, setSlotIdentity,    Basic::String)
   ON_SLOT(8, setSlotSendBufSize, Basic::Integer)
   ON_SLOT(9, setSlotRecvBufSize, Basic::Integer)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructors
//------------------------------------------------------------------------------
s2i_t ZeroMQHandler::sts2i;
i2s_t ZeroMQHandler::sti2s;

ZeroMQHandler::ZeroMQHandler ()
{
   STANDARD_CONSTRUCTOR()
   initData ();

   // Initialize the valid socket types
   if (sts2i.empty ()) {
      sts2i["PAIR"]    = ZMQ_PAIR;
      sts2i["REQ"]     = ZMQ_REQ;
      sts2i["REQUEST"] = ZMQ_REQ;
      sts2i["REP"]     = ZMQ_REP;
      sts2i["REPLY"]   = ZMQ_REP;
      sts2i["DEALER"]  = ZMQ_DEALER;
      sts2i["ROUTER"]  = ZMQ_ROUTER;
      sts2i["PUB"]     = ZMQ_PUB;
      sts2i["SUB"]     = ZMQ_SUB;
      sts2i["XPUB"]    = ZMQ_XPUB;
      sts2i["XSUB"]    = ZMQ_XSUB;
      sts2i["PUSH"]    = ZMQ_PUSH;
      sts2i["PULL"]    = ZMQ_PULL;
      sts2i["STREAM"]  = ZMQ_STREAM;
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
}


void ZeroMQHandler::initData ()
{
   // ZeroMQHandler information
   contextName = "";
   context     = 0;
   socketType  = -1;
   endpoint    = "";
   socket      = 0;
   linger      = -1;
   subscribe   = "";
   backLog     = -1;
   identity    = "";
   sendBufSize = -1;
   recvBufSize = -1;
   dontWait    = false;
   bound       = false;
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void ZeroMQHandler::copyData (const ZeroMQHandler& org, const bool cc)
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

   contextName = org.contextName;
   socketType  = org.socketType;
   socket      = 0;
   endpoint    = org.endpoint;
   linger      = org.linger;
   subscribe   = org.subscribe;
   backLog     = org.backLog;
   identity    = org.identity;
   sendBufSize = org.sendBufSize;
   recvBufSize = org.recvBufSize;
   dontWait    = org.dontWait;
   bound       = false;
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void ZeroMQHandler::deleteData ()
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
bool ZeroMQHandler::initNetwork (const bool noWaitFlag)
{
   // Set the no wait flag for sending/receiving
   dontWait = noWaitFlag;

   // A context, a valid socket type, and an endpoint must be present to
   // initialize the network
   if (context == 0 || socketType == -1 || endpoint.empty ()) return false;

   bool ok = false;

   // Create the socket
   socket = zmq_socket (*context, socketType);

   if (socket == 0) ok = false;

   // Set the socket options
   if (ok && linger != -1) ok = zmq_setsockopt (socket, ZMQ_LINGER, &linger, sizeof (linger));
   if (ok && !subscribe.empty ()) ok = zmq_setsockopt (socket, ZMQ_SUBSCRIBE, subscribe.c_str (), subscribe.length ());
   if (ok && backLog != -1) ok = zmq_setsockopt (socket, ZMQ_BACKLOG, &backLog, sizeof (backLog));
   if (ok && !identity.empty ()) ok = zmq_setsockopt (socket, ZMQ_IDENTITY, identity.c_str (), identity.length ());
   if (ok && sendBufSize != -1) ok = zmq_setsockopt (socket, ZMQ_SNDBUF, &sendBufSize, sizeof (sendBufSize));
   if (ok && recvBufSize != -1) ok = zmq_setsockopt (socket, ZMQ_RCVBUF, &recvBufSize, sizeof (recvBufSize));

   // Bind the socket
   if (ok && zmq_bind (socket, endpoint.c_str ()) == 0) bound = true;
   else bound = false;

   return bound;
}

bool ZeroMQHandler::isConnected () const
{
   if (socket == 0) return false;
   else return bound;
}

bool ZeroMQHandler::closeConnection ()
{
   // Close the 0MQ socket
   if (socket != 0) zmq_close (socket);

   socket = 0;
   bound  = false;

   return true;
}

bool ZeroMQHandler::setBlocked (const LcSocket s)
{
   return false;
}

bool ZeroMQHandler::setNoWait (const LcSocket s)
{
   return false;
}

bool ZeroMQHandler::sendData (const char* const packet, const int size)
{
   if (socket == 0 || !bound) return 0;

   // We set the flags here.  We are not handling multi-part messages since
   // I have not found a good way to handle them in OpenEaagles yet. But,
   // our message buffers should not be too large so it will be OK for a
   // while.
   int flags = 0;
   if (dontWait) flags = ZMQ_DONTWAIT;

   // Send the message.  The return value will be the number of bytes sent
   // or -1 on error.  Since we really do not handle errors in OpenEaagles
   // NetHandler 0 will be returned.  Again, multi-part messages are not
   // part of the sendData method.
   int result = zmq_send (socket, packet, size, flags);

   if (result < 0) result = 0;

   return (unsigned int) result;
}

unsigned int ZeroMQHandler::recvData (char* const packet, const int maxSize)
{
   if (socket == 0 || !bound) return 0;

   // We set the flags here.
   int flags = 0;
   if (dontWait) flags = ZMQ_DONTWAIT;

   // Send the message.  The return value will be the number of bytes or
   // -1 on error.  Since we really do not handle errors in OpenEaagles
   // NetHandler 0 will be returned.
   int result = zmq_recv (socket, packet, maxSize, flags);

   if (result < 0) result = 0;

   return (unsigned int) result;
}


//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------
bool ZeroMQHandler::setContext (const char* const name)
{
   contextName = name;
   return true;
}

bool ZeroMQHandler::setSocketType (const char* const type)
{
   s2i_t::const_iterator k = sts2i.find (std::string (type));

   if (k == sts2i.end ()) socketType = -1;
   else socketType = k->second;

   return socketType != -1;
}

bool ZeroMQHandler::setEndpoint (const char* const ep)
{
   endpoint = ep;
   return true;
}

bool ZeroMQHandler::setLinger (const int period)
{
   linger = period;
   return true;
}

bool ZeroMQHandler::setSubscribe (const char* const filter)
{
   subscribe = filter;
   return true;
}

bool ZeroMQHandler::setBackLog (const int count)
{
   backLog = count;
   return true;
}

bool ZeroMQHandler::setIdentity (const char* const ident)
{
   identity = ident;
   return true;
}

bool ZeroMQHandler::setSendBufSize (const int size)
{
   sendBufSize = size;
   return true;
}

bool ZeroMQHandler::setRecvBufSize (const int size)
{
   recvBufSize = size;
   return true;
}

//------------------------------------------------------------------------------
// Set slot functions
//------------------------------------------------------------------------------

// context: String containing the parent context's name
bool ZeroMQHandler::setSlotContext (const Basic::String* const msg)
{
   // Save the name and find the context for use in the initialization
   // of the socket
   bool ok = false;
   if (msg != 0) ok = setContext (*msg);
   return ok;
}

// socketType: String containing the socket type
bool ZeroMQHandler::setSlotSocketType (const Basic::String* const msg)
{
   // Find the token in the map and get the enumeration for use in the
   // initialization of the socket
   bool ok = false;
   if (msg != 0) ok = setSocketType (*msg);
   return ok;
}

// endpoint: String containing the endpoint (3, 4, & 5)
bool ZeroMQHandler::setSlotEndpoint (const Basic::String* const msg)
{
   // Save the endpoint definition for use in the initialization of
   // the socket
   bool ok = false;
   if (msg != 0) ok = setEndpoint (*msg);
   return ok;
}

// linger: Integer containing the linger period (ms)
bool ZeroMQHandler::setSlotLinger (const Basic::Integer* const msg)
{
   // Save the linger period for use in the initialization of the
   // socket
   bool ok = false;
   if (msg != 0) ok = setLinger (*msg);
   return ok;
}

// subscribe: String containing the message filter
bool ZeroMQHandler::setSlotSubscribe (const Basic::String* const msg)
{
   // Save the subscribe filter for use in the initialization of the
   // socket.
   bool ok = false;
   if (msg != 0) ok = setSubscribe (*msg);
   return ok;
}

// backLog: String containing the endpoint (3, 4, & 5)
bool ZeroMQHandler::setSlotBackLog (const Basic::Integer* const msg)
{
   // Save the connection back log count for use in the initialization
   // of the socket
   bool ok = false;
   if (msg != 0) ok = setBackLog (*msg);
   return ok;
}

// identity: String containing the identity
bool ZeroMQHandler::setSlotIdentity (const Basic::String* const msg)
{
   // Save the socket identity for use in the initialization of the
   // socket
   bool ok = false;
   if (msg != 0) ok = setIdentity (*msg);
   return ok;
}

// sendBufSizeKb: Integer containing the send buffer size in KB's
bool ZeroMQHandler::setSlotSendBufSize (const Basic::Integer* const msg)
{
   // Save the send buffer size for use in the initialization of the
   // socket
   bool ok = false;
   if (msg != 0) ok = setSendBufSize (*msg * 1024);
   return ok;
}

// recvBufSizeKb: Integer containing the receive buffer size in KB's
bool ZeroMQHandler::setSlotRecvBufSize (const Basic::Integer* const msg)
{
   // Save the receive buffer size for use in the initialization of the
   // socket
   bool ok = false;
   if (msg != 0) ok = setRecvBufSize (*msg * 1024);
   return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Basic::Object* ZeroMQHandler::getSlotByIndex (const int si)
{
   return BaseClass::getSlotByIndex (si);
}

//------------------------------------------------------------------------------
// serialize
//------------------------------------------------------------------------------
std::ostream& ZeroMQHandler::serialize (std::ostream& sout, const int i, const bool slotsOnly) const
{
   int j = 0;

   if (!slotsOnly) {
      indent (sout, i);
      sout << "( " << getFormName () << std::endl;
      j = 4;
   }

   // Output the context name
   if (!contextName.empty ()) {
      indent (sout, i+j);
      sout << "context: " << contextName << std::endl;
   }

   // Output the socket type
   if (socketType != -1) {
      indent (sout, i+j);
      sout << "socketType: " << sti2s[socketType] << std::endl;
   }

   // Output the full endpoint definition
   if (!endpoint.empty ()) {
      indent (sout, i+j);
      sout << "endpoint: " << endpoint << std::endl;
   }

   // Output the linger period
   if (linger != -1) {
      indent (sout, i+j);
      sout << "linger: " << linger << std::endl;
   }

   // Output the message filter
   if (!subscribe.empty ()) {
      indent (sout, i+j);
      sout << "subscribe: " << subscribe << std::endl;
   }

   // Output the back log count
   if (backLog != -1) {
      indent (sout, i+j);
      sout << "backLog: " << backLog << std::endl;
   }

   // Output the identity
   if (!identity.empty ()) {
      indent (sout, i+j);
      sout << "identity: " << identity << std::endl;
   }

   // Output the send buffer size in KB
   if (backLog != -1) {
      indent (sout, i+j);
      sout << "sendBufSizeKb: " << sendBufSize/1024 << std::endl;
   }

   // Output the receive buffer size in KB
   if (recvBufSize != -1) {
      indent (sout, i+j);
      sout << "recvBufSizeKb: " << recvBufSize/1024 << std::endl;
   }

   if (!slotsOnly) {
      indent (sout, i);
      sout << ")" << std::endl;
   }

   return sout;
}

}  // End xZeroMQ namespace
}  // End Eaagles namespace


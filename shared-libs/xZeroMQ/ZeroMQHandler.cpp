//------------------------------------------------------------------------------
// Class: ZeroMQHandler
//------------------------------------------------------------------------------
#include "ZeroMQHandler.h"
#include "ZeroMQContext.h"
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
END_SLOTTABLE(ZeroMQHandler)

// Map slot table to handles
BEGIN_SLOT_MAP(ZeroMQHandler)
   ON_SLOT(1, setSlotContext,    Basic::String)
   ON_SLOT(2, setSlotSocketType, Basic::String)
   ON_SLOT(3, setSlotEndpoint,   Basic::String)
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
   // A context, a valid socket type, and an endpoint must be present to
   // initialize the network
   if (context == 0 || socketType == -1 || endpoint.empty ()) return false;

   // Create the socket
   socket = zmq_socket (*context, socketType);

   if (socket == 0) return false;

   // Bind the socket
   if (zmq_bind (socket, endpoint.c_str ()) == 0) bound = true;
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
   bool ok = false;
   return ok;
}

unsigned int ZeroMQHandler::recvData (char* const packet, const int maxSize)
{
   bool ok = false;
   return ok;
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
   // Save the endpoint definition and make sure the individual pieces
   // are ignored
   bool ok = false;
   if (msg != 0) ok = setEndpoint (*msg);
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


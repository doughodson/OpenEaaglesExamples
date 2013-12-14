//------------------------------------------------------------------------------
// Class: ZeroMQHandler
//------------------------------------------------------------------------------
#ifndef __Eaagles_xZeroMQ_ZeroMQHandler_H__
#define __Eaagles_xZeroMQ_ZeroMQHandler_H__
#pragma once

#include "openeaagles/basic/NetHandler.h"

#include <map>
#include <string>

namespace Eaagles {
   namespace Basic { class String; };

namespace xZeroMQ {
   class ZeroMQContext;

   // Mapping types used to convert the enums and 0MQ constants to strings
   // and back again!
   typedef std::map <std::string, int> s2i_t;
   typedef std::map <int, std::string> i2s_t;

//------------------------------------------------------------------------------
// Class: ZeroMQHandler
//
// Description: General 0MQ socket class
//
// ZeroMQHandler defines the basic 0MQ socket interface.  It will be derived from
// the Eaagles NetHandler object so it can be used interchangeably.  It should
// be noted that 0MQ sockets can only really talk to other 0MQ sockets.  Please
// be sure that in any communications strategy both sides are 0MQ when using
// ZeroMQHandler in your application.
//
// The derivation from NetHandler is to allow this handler to be used in place
// of other NetHandler objects but 0MQ is so dissimilar that really only the
// signature is used and not the internals.
//
// ZeroMQHandlers are created in a Context and cannot be used across thread in an
// application with multiple threads.
//
// The following slots will be provided for the creation and setup of the
// socket:
//
//    context     - The context used to create the socket
//    socketType  - Socket type (REQ, REP, DEALER, ROUTER, PUB, SUB, XPUB,
//                  XSUB, PUSH, PULL, PAIR, or STREAM)
//    endpoint    - A full endpoint definition string (tcp://*:12345)
//    <options>   - The set options will each have a slot for them
//
//------------------------------------------------------------------------------
class ZeroMQHandler : public Basic::NetHandler
{
   DECLARE_SUBCLASS(ZeroMQHandler, Basic::NetHandler)

public:
   ZeroMQHandler ();

   // NetHandler overrides
   virtual bool         initNetwork (const bool noWaitFlag);
   virtual bool         isConnected () const;
   virtual bool         closeConnection ();
   virtual bool         sendData (const char* const packet, const int size);
   virtual unsigned int recvData (char* const packet, const int maxSize);

   // NetHandler overrides that have no meaning in 0MQ at this time
   virtual bool setBlocked (const LcSocket s = NET_INVALID_SOCKET);
   virtual bool setNoWait (const LcSocket s = NET_INVALID_SOCKET);

   // Slots
   virtual bool setSlotContext (const Basic::String* const msg);
   virtual bool setSlotSocketType (const Basic::String* const msg);
   virtual bool setSlotEndpoint (const Basic::String* const msg);

protected:
   bool setContext (const char* const name);
   bool setSocketType (const char* const type);
   bool setEndpoint (const char* const type);

private:
   void initData ();

private:
   static s2i_t sts2i;           // ZeroMQHandler type maps
   static i2s_t sti2s;

protected:
   ZeroMQContext* context;       // Parent context (Eaagles not 0MQ)
   std::string    contextName;   // Parent context name
   int            socketType;    // Socket type
   std::string    endpoint;      // Endpoint for binding
   void*          socket;        // 0MQ socket
   bool           bound;         // Bind was successful
};

}  // End xZeroMQ namespace
}  // End Eaagles namespace

#endif


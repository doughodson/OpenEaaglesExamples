//------------------------------------------------------------------------------
// Class: Socket
//------------------------------------------------------------------------------
#ifndef __Eaagles_xZeroMQ_Socket_H__
#define __Eaagles_xZeroMQ_Socket_H__
#pragma once

#include "openeaagles/basic/NetHandler.h"

#include <map>
#include <string>

namespace Eaagles {
   namespace Basic { class List; class Number; class List; };

namespace xZeroMQ {
   class Context;

   // Mapping types used to convert the enums and 0MQ constants to strings
   // and back again!
   typedef std::map <std::string, int> s2i_t;
   typedef std::map <int, std::string> i2s_t;

//------------------------------------------------------------------------------
// Class: Socket
//
// Description: General 0MQ socket class
//
// Socket defines the basic 0MQ socket interface.  It will be derived from
// the Eaagles NetHandler object so it can be used interchangeably.  It should
// be noted that 0MQ sockets can only really talk to other 0MQ sockets.  Please
// be sure that in any communications strategy both sides are 0MQ when using
// Socket in your application.
//
// The derivation from NetHandler is to allow this handler to be used in place
// of other NetHandler objects but 0MQ is so dissimilar that really only the
// signature is used and not the internals.
//
// Sockets are created in a Context and cannot be used across thread in an
// application with multiple threads.
//
// The following slots will be provided for the creation and setup of the
// socket:
//
//    context     - The context used to create the socket
//    type        - Socket type (REQ, REP, DEALER, ROUTER, PUB, SUB, XPUB,
//                  XSUB, PUSH, PULL, PAIR, or STREAM)
//    transport   - Socket transport type (TCP, ICP, INPROC, PGM, or EPGM)
//    address     - The valid network address for binding (can be * or blank)
//    port        - The valid port for binding
//    endpoint    - A full endpoint definition string (tcp://*:12345)
//    options     - An option list
//
//------------------------------------------------------------------------------
class Socket : public Basic::NetHandler
{
   DECLARE_SUBCLASS(Socket, Basic::NetHandler)

public:
   enum Transport {
      NONE = -1, TCP, IPC, INPROC, PGM, EPGM
   };

public:
   Socket ();

   // Nethandler overrides
   virtual bool         initNetwork (const bool noWaitFlag);
   virtual bool         isConnected () const;
   virtual bool         closeConnection ();
   virtual bool         sendData (const char* const packet, const int size);
   virtual unsigned int recvData (char* const packet, const int maxSize);

   // Nethandler overrides that have no meaning in 0MQ at this time
   virtual bool setBlocked (const LcSocket s = NET_INVALID_SOCKET);
   virtual bool setNoWait (const LcSocket s = NET_INVALID_SOCKET);

   // Slots
   virtual bool setSlotContext (const Basic::String* const msg);
   virtual bool setSlotType (const Basic::String* const msg);
   virtual bool setSlotTransport (const Basic::String* const msg);
   virtual bool setSlotAddress (const Basic::String* const msg);
   virtual bool setSlotPort (const Basic::Number* const msg);
   virtual bool setSlotEndpoint (const Basic::String* const msg);
   virtual bool setSlotOptions (const Basic::List* const msg);

private:
   void initData ();

private:
   static s2i_t sts2i;           // Socket type maps
   static i2s_t sti2s;

   static s2i_t eps2i;           // Endpoint type maps
   static i2s_t epi2s;

protected:
   Context*    context;          // Parent context (Eaagles not 0MQ)
   std::string ctxname;          // Parent context name
   int         stype;            // Socket type
   Transport   eptrans;          // Endpoint transport type
   std::string epaddress;        // Endpoint address
   uint16_t    epport;           // Endpoint port
   std::string endpoint;         // Endpoint for binding
   void*       socket;           // 0MQ socket
   bool        bound;            // Bind was successful
};

}  // End xZeroMQ namespace
}  // End Eaagles namespace

#endif


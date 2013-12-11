//------------------------------------------------------------------------------
// Class: Socket
//------------------------------------------------------------------------------
#ifndef __Eaagles_xZeroMQ_Socket_H__
#define __Eaagles_xZeroMQ_Socket_H__
#pragma once

#include "openeaagles/basic/Component.h"

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
// Sockets are created in a Context and cannot be used across thread in an
// application with multiple threads.
//
// The following slots will be provided for the creation and setup of the
// socket:
//
//    context     - The context used to create the socket
//    type        - Socket type (REQ, REP, DEALER, ROUTER, PUB, SUB, XPUB,
//                  XSUB, PUSH, PULL, PAIR, or STREAM)
//    protocol    - Socket protocol (TCP, ICP, INPROC, PGM, or EPGM)
//    address     - The valid network address for binding (can be * or blank)
//    port        - The valid port for binding
//    options     - An option list
//
//------------------------------------------------------------------------------
class Socket : public Basic::Component
{
   DECLARE_SUBCLASS(Socket, Basic::Component)

public:
   enum Transport {
      TCP, IPC, INPROC, PGM, EPGM
   };

public:
   Socket ();

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
   int         stype;            // Socket type
   Transport   eptrans;          // Endpoint transport type
   std::string epaddress;        // Endpoint address
   uint16_t    epport;           // Endpoint port
   std::string endpoint;         // Endpoint for binding
   void*       socket;           // 0MQ socket
};

}  // End xZeroMQ namespace
}  // End Eaagles namespace

#endif


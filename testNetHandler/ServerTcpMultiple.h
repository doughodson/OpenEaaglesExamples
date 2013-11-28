//------------------------------------------------------------------------------
// Class: ServerTcpMultiple
//------------------------------------------------------------------------------
#ifndef __Test_ServerTcpMultiple_H__
#define __Test_ServerTcpMultiple_H__

#include "Endpoint.h"

namespace Test {

//------------------------------------------------------------------------------
// Class:  ServerTcpMultiple
//
// Description:  
//
// Form name: ServerTcpMulti
//
//------------------------------------------------------------------------------
class ServerTcpMultiple : public Endpoint
{
   DECLARE_SUBCLASS(ServerTcpMultiple, Endpoint)

public:
   ServerTcpMultiple();

   // Component interface
   virtual void updateData(const Eaagles::LCreal dt = 0.0f);
   virtual void reset();

};

}

#endif

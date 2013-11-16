//------------------------------------------------------------------------------
// Class: ServerTcpMultiple
//------------------------------------------------------------------------------
#ifndef __TestNet_ServerTcpMultiple_H__
#define __TestNet_ServerTcpMultiple_H__

#include "NetTester.h"

namespace TestNet {

//------------------------------------------------------------------------------
// Class:  ServerTcpMultiple
//
// Description:  
//
// Form name: ServerTcpMulti
//
//------------------------------------------------------------------------------
class ServerTcpMultiple : public NetTester
{
   DECLARE_SUBCLASS(ServerTcpMultiple, NetTester)

public:
   ServerTcpMultiple();

   // Component interface
   virtual void updateData(const Eaagles::LCreal dt = 0.0f);
   virtual void reset();

};

}

#endif

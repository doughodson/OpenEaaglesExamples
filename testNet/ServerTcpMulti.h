//------------------------------------------------------------------------------
// Class: ServerTcpMulti
//------------------------------------------------------------------------------
#ifndef __ServerTcpMulti_H_6CD00C6E_35F2_4d60_8A95_267881AACF4F__
#define __ServerTcpMulti_H_6CD00C6E_35F2_4d60_8A95_267881AACF4F__

#include "NetTester.h"

namespace TestNet {

//------------------------------------------------------------------------------
// Class:  ServerTcpMulti
// Base class:  Object-> Component-> NetTester -> ServerTcpMulti
//
// Description:  
//
// Form name: ServerTcpMulti
//
// Guid: {6CD00C6E-35F2-4d60-8A95-267881AACF4F}
//------------------------------------------------------------------------------
class ServerTcpMulti : public NetTester {
   DECLARE_SUBCLASS(ServerTcpMulti,NetTester)

public:
   ServerTcpMulti();

   // Component interface
   virtual void updateData(const Eaagles::LCreal dt = 0.0f);
   virtual void reset();

};

}

#endif

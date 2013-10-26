//------------------------------------------------------------------------------
// Class: ServerSide
//------------------------------------------------------------------------------
#ifndef __TestNet_ServerSide_H__
#define __TestNet_ServerSide_H__

#include "NetTester.h"

namespace TestNet {

//------------------------------------------------------------------------------
// Class:  ServerSide
//
// Description:  
//
// Form name: ServerSide
//
//------------------------------------------------------------------------------
class ServerSide : public NetTester
{
   DECLARE_SUBCLASS(ServerSide, NetTester)

public:
   ServerSide();

   // Component interface
   virtual void updateData(const Eaagles::LCreal dt = 0.0f);
   virtual void reset();

private:
    unsigned int loopCounter;   // Loop counter 
};

}

#endif

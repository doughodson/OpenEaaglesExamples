//------------------------------------------------------------------------------
// Class: ServerSide
//------------------------------------------------------------------------------
#ifndef __Test_ServerSide_H__
#define __Test_ServerSide_H__

#include "Endpoint.h"

namespace Test {

//------------------------------------------------------------------------------
// Class: ServerSide
//
// Description:  
//
// Form name: ServerSide
//
//------------------------------------------------------------------------------
class ServerSide : public Endpoint
{
   DECLARE_SUBCLASS(ServerSide, Endpoint)

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


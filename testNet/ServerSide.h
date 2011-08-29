//------------------------------------------------------------------------------
// Class: ServerSide
//------------------------------------------------------------------------------
#ifndef __ServerSide_H_FA33F01C_CCFE_4441_BA1E_23462BAFB1D6__
#define __ServerSide_H_FA33F01C_CCFE_4441_BA1E_23462BAFB1D6__

#include "NetTester.h"

namespace TestNet {

//------------------------------------------------------------------------------
// Class:  ServerSide
// Base class:  Object-> Component-> NetTester -> ServerSide
//
// Description:  
//
// Form name: ServerSide
//
// Guid: {FA33F01C-CCFE-4441-BA1E-23462BAFB1D6}
//------------------------------------------------------------------------------
class ServerSide : public NetTester {
   DECLARE_SUBCLASS(ServerSide,NetTester)

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

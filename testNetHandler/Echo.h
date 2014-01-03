//------------------------------------------------------------------------------
// Class: Echo
//------------------------------------------------------------------------------
#ifndef __Test_Echo_H__
#define __Test_Echo_H__

#include "Endpoint.h"

namespace Test {

//------------------------------------------------------------------------------
// Class: Echo
//
// Description:  
//
// Factory name: Echo
//
//------------------------------------------------------------------------------
class Echo : public Endpoint
{
   DECLARE_SUBCLASS(Echo, Endpoint)

public:
   Echo();

   // Component interface
   virtual void updateData(const Eaagles::LCreal dt = 0.0f);
   virtual void reset();

private:
    unsigned int loopCounter;   // Loop counter 
};

}

#endif


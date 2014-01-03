//------------------------------------------------------------------------------
// Class: Echo
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_Echo_H__
#define __Eaagles_Test_Echo_H__

#include "Endpoint.h"

namespace Eaagles {
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
   virtual void updateData(const LCreal dt = 0.0f);
   virtual void reset();

private:
    unsigned int loopCounter;   // Loop counter 
};

}
}

#endif


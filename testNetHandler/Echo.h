//------------------------------------------------------------------------------
// Class: Echo
//------------------------------------------------------------------------------
#ifndef __oe_Test_Echo_H__
#define __oe_Test_Echo_H__

#include "Endpoint.h"

namespace oe {
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

   void updateData(const LCreal dt = 0.0) override;
   void reset() override;

private:
    unsigned int loopCounter;
};

}
}

#endif


//------------------------------------------------------------------------------
// Class: Echo
//------------------------------------------------------------------------------
#ifndef __oe_test_Echo_H__
#define __oe_test_Echo_H__

#include "Endpoint.h"

namespace oe {
namespace test {

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

   void updateData(const double dt = 0.0) override;
   void reset() override;

private:
    unsigned int loopCounter;
};

}
}

#endif


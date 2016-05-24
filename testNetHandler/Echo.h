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
// Factory name: Echo
//------------------------------------------------------------------------------
class Echo : public Endpoint
{
   DECLARE_SUBCLASS(Echo, Endpoint)

public:
   Echo();

   virtual void updateData(const double dt = 0.0) override;
   virtual void reset() override;

private:
   unsigned int loopCounter;
};

}
}

#endif



#ifndef __Echo_H__
#define __Echo_H__

#include "Endpoint.hpp"

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
   unsigned int loopCounter {};
};

#endif


#ifndef __Exp_H__
#define __Exp_H__

#include "Random.hpp"

namespace oe {
namespace base { class Number; }
}

//------------------------------------------------------------------------------
// Class: Exponential
// Description: Generates Random Numbers
//------------------------------------------------------------------------------
class Exp : public Random
{
   DECLARE_SUBCLASS(Exp, Random)

public:

   Exp();

   // data access functions
   virtual void setMean(const double);

   // slot table functions
   virtual bool setSlotMean(const oe::base::Number* const);

   virtual int getNum() const override;

private:
   double mean {10.0};

};

#endif

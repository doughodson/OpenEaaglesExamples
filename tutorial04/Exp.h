//------------------------------------------------------------------------------
// Class: Exponential
// Description: Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef __oe_Tutorial_Exp_H__
#define __oe_Tutorial_Exp_H__

#include "Random.h"

namespace oe {

namespace Basic { class Number; }

namespace Tutorial {

class Exp : public Random
{
   DECLARE_SUBCLASS(Exp, Random)

public:

   Exp();

   // data access functions
   virtual void setMean(const double);

   // slot table functions
   virtual bool setSlotMean(const Basic::Number* const);

   int getNum(void) const override;

private:

   double mean;

};

} // namespace Tutorial
} // namespace oe

#endif


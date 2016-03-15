//------------------------------------------------------------------------------
// Class: Exponential
// Description: Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef __oe_tutorial_Exp_H__
#define __oe_tutorial_Exp_H__

#include "Random.h"

namespace oe {

namespace base { class Number; }

namespace tutorial {

class Exp : public Random
{
   DECLARE_SUBCLASS(Exp, Random)

public:

   Exp();

   // data access functions
   virtual void setMean(const double);

   // slot table functions
   virtual bool setSlotMean(const base::Number* const);

   int getNum(void) const override;

private:

   double mean;

};

}
}

#endif


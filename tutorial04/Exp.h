//------------------------------------------------------------------------------
// Class:  Exponential
// Description:  Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef __Eaagles_Tutorial_Exp_H__
#define __Eaagles_Tutorial_Exp_H__

#include "Random.h"

namespace Eaagles {

namespace Basic { class Number; }

namespace Tutorial {

class Exp : public Random
{
  DECLARE_SUBCLASS(Exp,Random)

public:

  Exp(void);

  // data access functions
  virtual void setMean(const float);

  // slot table functions
  virtual bool setSlotMean(const Basic::Number* const);

  // Random class interface
  virtual int getNum(void) const;

private:

  float mean;

};

} // namespace Tutorial
} // namespace Eaagles

#endif


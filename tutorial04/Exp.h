//------------------------------------------------------------------------------
// Class:  Exponential
// Base class:  Object-> Random -> Exp
// Description:  Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef _EXP_INCLUDE
#define _EXP_INCLUDE

#include "Random.h"

namespace Eaagles {
  namespace Basic {
    class Number;
  }
}

namespace Eaagles {
namespace Example04 {

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

} // namespace Example04
} // namespace Eaagles

#endif


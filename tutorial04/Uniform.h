//------------------------------------------------------------------------------
// Class:  Uniform
// Base class:  Object-> Random -> Uniform
// Description:  Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef _UNIFORM_INCLUDE
#define _UNIFORM_INCLUDE

#include "Random.h"

namespace Eaagles {
  namespace Basic {
    class Number;
  }
}

namespace Eaagles {
namespace Example04 {

class Uniform : public Random
{
  DECLARE_SUBCLASS(Uniform,Random)

public:

  Uniform(void);

  // data access functions
  void setMax(const int);
  void setMin(const int);

  // slot table functions
  bool setSlotMax(const Basic::Number* const);
  bool setSlotMin(const Basic::Number* const);

  // Random class interface
  virtual int getNum(void) const;

private:
  int max;
  int min;
};

} // namespace Example04
} // namespace Eaagles

#endif

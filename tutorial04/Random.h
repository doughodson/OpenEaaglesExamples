//------------------------------------------------------------------------------
// Class:  Random
// Base class:  Object-> Random
// Description:  Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef _RANDOM_INCLUDE
#define _RANDOM_INCLUDE

#include "openeaagles/basic/Object.h"

namespace Eaagles {
  namespace Basic {
    class Number;
  }
}

namespace Eaagles {
namespace Example04 {

class Random : public Basic::Object
{
  DECLARE_SUBCLASS(Random,Basic::Object)

public:

  Random(void);

  // data access functions
  virtual int getNum(void) const =0;
  bool setSeed(const unsigned int);

  // slot table functions
  bool setSlotSeed(const Basic::Number* const);
  
};

} // namespace Example04
} // namespace Eaagles

#endif


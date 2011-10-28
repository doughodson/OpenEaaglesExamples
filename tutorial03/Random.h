//------------------------------------------------------------------------------
// Class:  Random
// Base class:  Object-> Random
// Description:  Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef _RANDOM_INCLUDE
#define _RANDOM_INCLUDE

#include "openeaagles/basic/Object.h"

namespace Eaagles {

namespace Basic { class Number; }

namespace Example03 {

class Random : public Basic::Object
{
  DECLARE_SUBCLASS(Random, Basic::Object)

public:

  Random();

  int getNum() const;
  bool setSeed(const unsigned int);

  // slot table functions
  bool setSlotSeed(const Basic::Number* const);

};

} // namespace Example03
} // namespace Eaagles

#endif

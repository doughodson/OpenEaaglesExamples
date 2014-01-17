//------------------------------------------------------------------------------
// Class:  Random
// Description:  Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef __Eaagles_Tutorial_Random_H__
#define __Eaagles_Tutorial_Random_H__

#include "openeaagles/basic/Object.h"

namespace Eaagles {

namespace Basic { class Number; }

namespace Tutorial {

class Random : public Basic::Object
{
  DECLARE_SUBCLASS(Random, Basic::Object)

public:

  Random();

  // data access functions
  virtual int getNum() const =0;
  bool setSeed(const unsigned int);

  // slot table functions
  bool setSlotSeed(const Basic::Number* const);
  
};

} // namespace Tutorial
} // namespace Eaagles

#endif

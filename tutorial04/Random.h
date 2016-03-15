//------------------------------------------------------------------------------
// Class: Random
// Description: Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef __oe_tutorial_Random_H__
#define __oe_tutorial_Random_H__

#include "openeaagles/base/Object.h"

namespace oe {

namespace base { class Number; }

namespace tutorial {

class Random : public base::Object
{
   DECLARE_SUBCLASS(Random, base::Object)

public:
   Random();

   // data access functions
   virtual int getNum() const = 0;
   bool setSeed(const unsigned int);

   // slot table functions
   bool setSlotSeed(const base::Number* const);
  
};

} // namespace tutorial
} // namespace oe

#endif

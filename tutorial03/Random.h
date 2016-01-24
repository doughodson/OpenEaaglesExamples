//------------------------------------------------------------------------------
// Class: Random
// Description: Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef __oe_Tutorial_Random_H__
#define __oe_Tutorial_Random_H__

#include "openeaagles/basic/Object.h"

namespace oe {

namespace basic { class Number; }

namespace Tutorial {

class Random : public basic::Object
{
   DECLARE_SUBCLASS(Random, basic::Object)

public:
   Random();

   int getNum() const;
   bool setSeed(const unsigned int);

   // slot table functions
   bool setSlotSeed(const basic::Number* const);

};

} // namespace Tutorial
} // namespace oe

#endif

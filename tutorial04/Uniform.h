//------------------------------------------------------------------------------
// Class: Uniform
// Description: Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef __oe_tutorial_Uniform_H__
#define __oe_tutorial_Uniform_H__

#include "Random.h"

namespace oe {

namespace base   { class Number; }

namespace tutorial {

class Uniform : public Random
{
   DECLARE_SUBCLASS(Uniform, Random)

public:
   Uniform();

   // data access functions
   void setMax(const int);
   void setMin(const int);

   // slot table functions
   bool setSlotMax(const base::Number* const);
   bool setSlotMin(const base::Number* const);

   int getNum(void) const override;

private:
   int max;
   int min;
};

} // namespace tutorial
} // namespace oe

#endif

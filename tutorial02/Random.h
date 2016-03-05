//------------------------------------------------------------------------------
// Class: Random
// Description: Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef __oe_Tutorial_Random_H__
#define __oe_Tutorial_Random_H__

#include "openeaagles/base/Object.h"

namespace oe {
namespace Tutorial {

class Random : public base::Object
{
   DECLARE_SUBCLASS(Random, base::Object)

public:
   Random();

   int getNum() const;
   void setSeed(const unsigned int);
};

} // namespace Tutorial
} // namespace oe


#endif

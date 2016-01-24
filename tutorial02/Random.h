//------------------------------------------------------------------------------
// Class: Random
// Description: Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef __oe_Tutorial_Random_H__
#define __oe_Tutorial_Random_H__

#include "openeaagles/basic/Object.h"

namespace oe {
namespace Tutorial {

class Random : public basic::Object
{
   DECLARE_SUBCLASS(Random, basic::Object)

public:
   Random();

   int getNum() const;
   void setSeed(const unsigned int);
};

} // namespace Tutorial
} // namespace oe


#endif

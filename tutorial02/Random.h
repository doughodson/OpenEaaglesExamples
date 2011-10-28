//------------------------------------------------------------------------------
// Class:  Random
// Base class:  Object-> Random
// Description:  Generates Random Numbers
//------------------------------------------------------------------------------

#ifndef _RANDOM_INCLUDE
#define _RANDOM_INCLUDE

#include "openeaagles/basic/Object.h"

namespace Eaagles {
namespace Example02 {

class Random : public Basic::Object
{
  DECLARE_SUBCLASS(Random, Basic::Object)

public:

  Random();

  int getNum() const;
  void setSeed(const unsigned int);
};

} // namespace Example02
} // namespace Eaagles


#endif

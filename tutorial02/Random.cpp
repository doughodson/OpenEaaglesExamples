//------------------------------------------------------------------------------
// Random
//------------------------------------------------------------------------------

#include "Random.h"

namespace Eaagles {
namespace Example02 {

IMPLEMENT_SUBCLASS(Random,"Random")
EMPTY_SLOTTABLE(Random)
EMPTY_SERIALIZER(Random)

#include <stdlib.h>

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Random::Random(void)
{
  STANDARD_CONSTRUCTOR()

  // seed the random number generator
  setSeed(100);
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Random::copyData(const Random& org, const bool)
{
	BaseClass::copyData(org);
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void Random::deleteData()
{
}

//------------------------------------------------------------------------------
// data access functions
//------------------------------------------------------------------------------
int Random::getNum(void) const
{
  return rand();
}

void Random::setSeed(const unsigned int seed)
{
  srand(seed);
}

} // namespace Example02
} // namespace Eaagles

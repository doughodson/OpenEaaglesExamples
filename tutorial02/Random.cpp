//------------------------------------------------------------------------------
// Random
//------------------------------------------------------------------------------

#include "Random.h"

namespace Eaagles {
namespace Tutorial {

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

   std::cout << "Random::Random() called\n";
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Random::copyData(const Random& org, const bool)
{
   BaseClass::copyData(org);

   std::cout << "Random::copyData() called\n";
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void Random::deleteData()
{
   std::cout << "Random::deleteData() called\n";
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

} // namespace Tutorial
} // namespace Eaagles


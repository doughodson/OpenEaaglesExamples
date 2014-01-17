//------------------------------------------------------------------------------
// Random
//------------------------------------------------------------------------------

#include "Random.h"
#include "openeaagles/basic/Number.h"
#include <cstdlib>

namespace Eaagles {
namespace Tutorial {

IMPLEMENT_SUBCLASS(Random,"Random")
// setup slot table
BEGIN_SLOTTABLE(Random)
    "seed",
END_SLOTTABLE(Random)
// map attributes to slots
BEGIN_SLOT_MAP(Random)
    ON_SLOT(1, setSlotSeed, Basic::Number)
END_SLOT_MAP()
// nothing to serialize
EMPTY_SERIALIZER(Random)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Random::Random(void)
{
  STANDARD_CONSTRUCTOR()

  setSeed(50);  // default random number generator seed
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
bool Random::setSeed(const unsigned int seed)
{
  srand(seed);
  return true;
}

int Random::getNum(void) const
{
  return rand();
}

//------------------------------------------------------------------------------
// slot table functions
//------------------------------------------------------------------------------
Basic::Object* Random::getSlotByIndex(const int si)
{
  return BaseClass::getSlotByIndex(si);
}

bool Random::setSlotSeed(const Basic::Number* const seed)
{
  bool ok = false;
  if(seed != 0)
    ok = setSeed(seed->getInt());
  return ok;
}

} // namespace Tutorial
} // namespace Eaagles


#include "Random.h"
#include "openeaagles/base/Number.h"
#include <cstdlib>

IMPLEMENT_SUBCLASS(Random, "Random")
// setup slot table
BEGIN_SLOTTABLE(Random)
   "seed",
END_SLOTTABLE(Random)
// map attributes to slots
BEGIN_SLOT_MAP(Random)
   ON_SLOT(1, setSlotSeed, oe::base::Number)
END_SLOT_MAP()

EMPTY_DELETEDATA(Random)
EMPTY_SERIALIZER(Random)

Random::Random()
{
  STANDARD_CONSTRUCTOR()
  setSeed(50);  // default random number generator seed
}

void Random::copyData(const Random& org, const bool)
{
  BaseClass::copyData(org);
}

bool Random::setSeed(const unsigned int seed)
{
  std::srand(seed);
  return true;
}

int Random::getNum() const
{
  return std::rand();
}

oe::base::Object* Random::getSlotByIndex(const int si)
{
  return BaseClass::getSlotByIndex(si);
}

bool Random::setSlotSeed(const oe::base::Number* const seed)
{
  bool ok = false;
  if (seed != nullptr)
    ok = setSeed(seed->getInt());
  return ok;
}

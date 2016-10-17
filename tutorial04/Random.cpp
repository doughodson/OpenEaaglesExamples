
#include "Random.hpp"
#include "openeaagles/base/Number.hpp"
#include <cstdlib>

IMPLEMENT_ABSTRACT_SUBCLASS(Random, "Random")
// setup slot table
BEGIN_SLOTTABLE(Random)
   "seed",              // random number seed value
END_SLOTTABLE(Random)
// map attributes to slots
BEGIN_SLOT_MAP(Random)
   ON_SLOT(1, setSlotSeed, oe::base::Number)
END_SLOT_MAP()
// nothing to serialize
EMPTY_SERIALIZER(Random)

Random::Random()
{
   STANDARD_CONSTRUCTOR()

   std::cout << "Random::Random() called\n";
}

void Random::copyData(const Random& org, const bool)
{
   BaseClass::copyData(org);
   std::cout << "Random::copyData() called\n";
}

void Random::deleteData()
{
   std::cout << "Random::deleteData() called\n";
}

bool Random::setSeed(const unsigned int seed)
{
   std::srand(seed);
   return true;
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


#include "Random.hpp"
#include "openeaagles/base/Number.hpp"
#include <cstdlib>
#include <iostream>

IMPLEMENT_ABSTRACT_SUBCLASS(Random, "Random")
EMPTY_SERIALIZER(Random)

BEGIN_SLOTTABLE(Random)
   "seed",              // random number seed value
END_SLOTTABLE(Random)

BEGIN_SLOT_MAP(Random)
   ON_SLOT(1, setSlotSeed, oe::base::Number)
END_SLOT_MAP()

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

bool Random::setSlotSeed(const oe::base::Number* const seed)
{
   bool ok = false;
   if (seed != nullptr)
      ok = setSeed(seed->getInt());
   return ok;
}

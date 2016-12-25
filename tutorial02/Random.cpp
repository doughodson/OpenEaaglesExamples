
#include "Random.hpp"
#include <cstdlib>
#include <iostream>

IMPLEMENT_SUBCLASS(Random, "Random")
EMPTY_SLOTTABLE(Random)
EMPTY_SERIALIZER(Random)

Random::Random()
{
   STANDARD_CONSTRUCTOR()

   // seed the random number generator
   setSeed(100);

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

int Random::getNum() const
{
   return std::rand();
}

void Random::setSeed(const unsigned int seed)
{
   std::srand(seed);
}

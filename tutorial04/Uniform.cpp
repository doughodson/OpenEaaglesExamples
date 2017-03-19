
#include "Uniform.hpp"

#include "openeaagles/base/Number.hpp"
#include <cstdlib>
#include <iostream>

IMPLEMENT_SUBCLASS(Uniform, "Uniform")
EMPTY_SERIALIZER(Uniform)

BEGIN_SLOTTABLE(Uniform)
  "min",
  "max",
END_SLOTTABLE(Uniform)

BEGIN_SLOT_MAP(Uniform)
  ON_SLOT(1, setSlotMin, oe::base::Number)
  ON_SLOT(2, setSlotMax, oe::base::Number)
END_SLOT_MAP()

Uniform::Uniform()
{
   STANDARD_CONSTRUCTOR()

   std::cout << "Uniform::Uniform() called\n";
}

void Uniform::copyData(const Uniform& org, const bool)
{
   BaseClass::copyData(org);

   max = org.max;
   min = org.min;
}

void Uniform::deleteData()
{
   std::cout << "Uniform::deleteData() called\n";
}

void Uniform::setMin(const int x)
{
   min = x;
}

void Uniform::setMax(const int x)
{
   max = x;
}

int Uniform::getNum() const
{
   return static_cast<int>((min+(max-min)*(std::rand()/(RAND_MAX+1.0))));
}

bool Uniform::setSlotMin(const oe::base::Number* const x)
{
   if (x != nullptr)
      setMin(x->getInt());
   return true;
}

bool Uniform::setSlotMax(const oe::base::Number* const x)
{
   if (x != nullptr)
      setMax(x->getInt());
   return true;
}

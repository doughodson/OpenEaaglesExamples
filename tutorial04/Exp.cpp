
#include "Exp.hpp"

#include "openeaagles/base/Number.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>

IMPLEMENT_SUBCLASS(Exp, "Exp")
EMPTY_SERIALIZER(Exp)

BEGIN_SLOTTABLE(Exp)
  "mean",
END_SLOTTABLE(Exp)

BEGIN_SLOT_MAP(Exp)
  ON_SLOT(1, setSlotMean, oe::base::Number)
END_SLOT_MAP()

Exp::Exp()
{
  STANDARD_CONSTRUCTOR()

  std::cout << "Exp::Exp() called\n";
}

void Exp::copyData(const Exp& org, const bool)
{
   BaseClass::copyData(org);
   mean = org.mean;
}

void Exp::deleteData()
{
   std::cout << "Exp::deleteData() called\n";
}

void Exp::setMean(const double x)
{
  mean = x;
}

int Exp::getNum() const
{
  const auto r = static_cast<double>(std::rand()/(RAND_MAX+1.0));
  const auto v = -static_cast<int>(mean * std::log(r));
  return v;
}

bool Exp::setSlotMean(const oe::base::Number* const mean)
{
  if (mean != nullptr)
    setMean(mean->getDouble());
  return true;
}


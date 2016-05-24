//------------------------------------------------------------------------------
// Exp
//------------------------------------------------------------------------------

#include "Exp.h"
#include "openeaagles/base/Number.h"
#include <cstdlib>
#include <cmath>

namespace oe {
namespace tutorial {

IMPLEMENT_SUBCLASS(Exp,"Exp")
// setup slot table
BEGIN_SLOTTABLE(Exp)
  "mean",
END_SLOTTABLE(Exp)
// map attributes to slots
BEGIN_SLOT_MAP(Exp)
  ON_SLOT(1, setSlotMean, base::Number)
END_SLOT_MAP()
// nothing to serialize
EMPTY_SERIALIZER(Exp)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Exp::Exp(void)
{
  STANDARD_CONSTRUCTOR()
  setMean(10.0);

  std::cout << "Exp::Exp() called\n";
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Exp::copyData(const Exp& org, const bool)
{
   BaseClass::copyData(org);
   mean = org.mean;
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void Exp::deleteData()
{
   std::cout << "Exp::deleteData() called\n";
}

//------------------------------------------------------------------------------
// data access functions
//------------------------------------------------------------------------------

void Exp::setMean(const double x)
{
  mean = x;
}

int Exp::getNum(void) const
{
  double r = static_cast<double>(std::rand()/(RAND_MAX+1.0));
  int v = -static_cast<int>(mean * std::log(r));
  return v;
}


//------------------------------------------------------------------------------
// slot functions
//------------------------------------------------------------------------------

bool Exp::setSlotMean(const base::Number* const mean)
{
  if (mean != nullptr)
    setMean(mean->getDouble());
  return true;
}

//------------------------------------------------------------------------------
// slot table functions
//------------------------------------------------------------------------------
base::Object* Exp::getSlotByIndex(const int si)
{
  return BaseClass::getSlotByIndex(si);
}

}
}

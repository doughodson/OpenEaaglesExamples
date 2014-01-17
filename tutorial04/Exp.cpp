//------------------------------------------------------------------------------
// Exp
//------------------------------------------------------------------------------

#include "Exp.h"
#include "openeaagles/basic/Number.h"
#include <cstdlib>

namespace Eaagles {
namespace Tutorial {

IMPLEMENT_SUBCLASS(Exp,"Exp")
// setup slot table
BEGIN_SLOTTABLE(Exp)
  "mean",
END_SLOTTABLE(Exp)
// map attributes to slots
BEGIN_SLOT_MAP(Exp)
  ON_SLOT(1, setSlotMean, Basic::Number)
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

void Exp::setMean(const float x)
{
  mean = x;
}

int Exp::getNum(void) const
{
  double r = (double)(rand()/(RAND_MAX+1.0));
  int v = -(int)(mean*log(r));
  return v;
}


//------------------------------------------------------------------------------
// slot functions
//------------------------------------------------------------------------------

bool Exp::setSlotMean(const Basic::Number* const mean)
{
  if(mean != 0)
    setMean(mean->getFloat());
  return true;
}

//------------------------------------------------------------------------------
// slot table functions
//------------------------------------------------------------------------------
Basic::Object* Exp::getSlotByIndex(const int si)
{
  return BaseClass::getSlotByIndex(si);
}

} // namespace Tutorial
} // namespace Eaagles

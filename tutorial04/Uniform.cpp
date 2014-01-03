//------------------------------------------------------------------------------
// Uniform
//------------------------------------------------------------------------------

#include "Uniform.h"
#include "openeaagles/basic/Number.h"
#include <cstdlib>

namespace Eaagles {
namespace Tutorial {

IMPLEMENT_SUBCLASS(Uniform,"Uniform")
// setup slot table
BEGIN_SLOTTABLE(Uniform)
  "min",
  "max",
END_SLOTTABLE(Uniform)
// map attributes to slots
BEGIN_SLOT_MAP(Uniform)
  ON_SLOT(1, setSlotMin, Basic::Number)
  ON_SLOT(2, setSlotMax, Basic::Number)
END_SLOT_MAP()
// nothing to serialize
EMPTY_SERIALIZER(Uniform)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Uniform::Uniform(void)
{
  STANDARD_CONSTRUCTOR()
  setMin(0);
  setMax(1);

  std::cout << "Uniform::Uniform() called\n";
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Uniform::copyData(const Uniform& org, const bool)
{
   BaseClass::copyData(org);

   max = org.max;
   min = org.min;
}

//------------------------------------------------------------------------------
//deleteData() -- delete member data
//------------------------------------------------------------------------------
void Uniform::deleteData()
{
   std::cout << "Uniform::deleteData() called\n";
}

//------------------------------------------------------------------------------
// data access functions
//------------------------------------------------------------------------------
void Uniform::setMin(const int x)
{
  min = x;
}

void Uniform::setMax(const int x)
{
  max = x;
}

int Uniform::getNum(void) const
{
  return (int)(min+(max-min)*(rand()/(RAND_MAX+1.0)));
}

//------------------------------------------------------------------------------
// slot table functions
//------------------------------------------------------------------------------
Basic::Object* Uniform::getSlotByIndex(const int si)
{
  return BaseClass::getSlotByIndex(si);
}

bool Uniform::setSlotMin(const Basic::Number* const x)
{
  if(x != 0)
    setMin(x->getInt());
  return true;
}

bool Uniform::setSlotMax(const Basic::Number* const x)
{
  if(x != 0)
    setMax(x->getInt());
  return true;
}

} // namespace Tutorial
} // namespace Eaagles

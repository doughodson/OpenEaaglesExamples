//------------------------------------------------------------------------------
// Class: MyComp
// Base class: Object-> MyComp
// Description: example class
//------------------------------------------------------------------------------

#ifndef _MYCOMP_INCLUDE
#define _MYCOMP_INCLUDE

#include "openeaagles/basic/Component.h"

namespace Eaagles {

namespace Basic { class String; }

namespace Example06 {

class MyComp : public Basic::Component
{
  DECLARE_SUBCLASS(MyComp, Basic::Component)

public:

  MyComp();

  // data access functions
  bool setStr(const Basic::String* const);
  const Basic::String* getStr(void) const;

  // slot table functions
  bool setSlotStr(const Basic::String* const);

  // Component class methods
  virtual void reset();
  virtual void updateTC(const LCreal dt = 0.0);
  virtual void updateData(const LCreal dt = 0.0);

private:
  const Basic::String* str;
};

} // namespace Example06
} // namespace Eaagles

#endif

//------------------------------------------------------------------------------
// Class: MyComp
// Description: example class
//------------------------------------------------------------------------------

#ifndef __Eaagles_Tutorial_MyComp_H__
#define __Eaagles_Tutorial_MyComp_H__

#include "openeaagles/basic/Component.h"

namespace Eaagles {

namespace Basic { class String; }

namespace Tutorial {

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

   void reset() override;
   void updateTC(const LCreal dt = 0.0) override;
   void updateData(const LCreal dt = 0.0) override;

protected:

   void initData();

private:

   const Basic::String* str;
};

} // namespace Tutorial
} // namespace Eaagles

#endif


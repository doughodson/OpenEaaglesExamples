//------------------------------------------------------------------------------
// Class: MyComp
// Description: example class
//------------------------------------------------------------------------------

#ifndef __oe_Tutorial_MyComp_H__
#define __oe_Tutorial_MyComp_H__

#include "openeaagles/base/Component.h"

namespace oe {

namespace base { class String; }

namespace Tutorial {

class MyComp : public base::Component
{
   DECLARE_SUBCLASS(MyComp, base::Component)

public:
   MyComp();

   // data access functions
   bool setStr(const base::String* const);
   const base::String* getStr(void) const;

   // slot table functions
   bool setSlotStr(const base::String* const);

   void reset() override;
   void updateTC(const LCreal dt = 0.0) override;
   void updateData(const LCreal dt = 0.0) override;

protected:

   void initData();

private:

   const base::String* str;
};

} // namespace Tutorial
} // namespace oe

#endif


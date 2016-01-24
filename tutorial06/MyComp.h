//------------------------------------------------------------------------------
// Class: MyComp
// Description: example class
//------------------------------------------------------------------------------

#ifndef __oe_Tutorial_MyComp_H__
#define __oe_Tutorial_MyComp_H__

#include "openeaagles/basic/Component.h"

namespace oe {

namespace basic { class String; }

namespace Tutorial {

class MyComp : public basic::Component
{
   DECLARE_SUBCLASS(MyComp, basic::Component)

public:
   MyComp();

   // data access functions
   bool setStr(const basic::String* const);
   const basic::String* getStr(void) const;

   // slot table functions
   bool setSlotStr(const basic::String* const);

   void reset() override;
   void updateTC(const LCreal dt = 0.0) override;
   void updateData(const LCreal dt = 0.0) override;

protected:

   void initData();

private:

   const basic::String* str;
};

} // namespace Tutorial
} // namespace oe

#endif


//------------------------------------------------------------------------------
// Class: MyComp
// Description: example class
//------------------------------------------------------------------------------

#ifndef __oe_tutorial_MyComp_H__
#define __oe_tutorial_MyComp_H__

#include "openeaagles/base/Component.h"

namespace oe {

namespace base { class String; }

namespace tutorial {

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

   virtual void reset() override;
   virtual void updateTC(const double dt = 0.0) override;
   virtual void updateData(const double dt = 0.0) override;

protected:

   void initData();

private:

   const base::String* str;
};

} // namespace tutorial
} // namespace oe

#endif


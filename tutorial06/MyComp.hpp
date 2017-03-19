
#ifndef __MyComp_H__
#define __MyComp_H__

#include "openeaagles/base/Component.hpp"

namespace oe {
namespace base { class String; }
}

//------------------------------------------------------------------------------
// Class: MyComp
// Description: example class
//------------------------------------------------------------------------------
class MyComp : public oe::base::Component
{
   DECLARE_SUBCLASS(MyComp, oe::base::Component)

public:
   MyComp();

   // data access functions
   bool setStr(const oe::base::String* const);
   const oe::base::String* getStr() const;

   // slot table functions
   bool setSlotStr(const oe::base::String* const);

   virtual void reset() override;
   virtual void updateTC(const double dt = 0.0) override;
   virtual void updateData(const double dt = 0.0) override;

private:
   const oe::base::String* str {};
};

#endif

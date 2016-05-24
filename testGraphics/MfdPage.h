//------------------------------------------------------------------------------
// Class: MfdPage
//
// Description: Example MFD page
//------------------------------------------------------------------------------
#ifndef __oe_example_MfdPage_H__
#define __oe_example_MfdPage_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace example {

class MfdPage : public graphics::Page {
   DECLARE_SUBCLASS(MfdPage,graphics::Page)

public:
   MfdPage();

   virtual bool onEntry() override;

   virtual bool event(const int event, base::Object* const obj = nullptr) override;
   virtual void updateData(const double dt = 0.0) override;

private:
   double rotate;
   double rotateRate;
   SendData rSD;
};

}
}

#endif

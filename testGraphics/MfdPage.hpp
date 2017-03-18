
#ifndef __MfdPage_H__
#define __MfdPage_H__

#include "openeaagles/graphics/Page.hpp"

//------------------------------------------------------------------------------
// Class: MfdPage
//
// Description: Example MFD page
//------------------------------------------------------------------------------
class MfdPage : public oe::graphics::Page
{
   DECLARE_SUBCLASS(MfdPage, oe::graphics::Page)

public:
   MfdPage();

   virtual bool onEntry() override;

   virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;
   virtual void updateData(const double dt = 0.0) override;

private:
   double rotate {};
   double rotateRate {5.0};
   SendData rSD;
};

#endif

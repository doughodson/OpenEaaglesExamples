//------------------------------------------------------------------------------
// Class: TestVVI
//
// Description: Test the gauge slider
// This page will supply test data to a generic analog tape gauge
//
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestVVI_H__
#define __oe_demo_TestVVI_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestVVI : public graphics::Page
{
   DECLARE_SUBCLASS(TestVVI, graphics::Page)

public:
   TestVVI();

   virtual void updateData(const double dt = 0) override;

private:
   double gaugePosition;       // our gauge position (inches)
   SendData gaugePositionSD;
   SendData gaugePositionROSD;
   double  gaugeRate;          // rate which are going (up or down)
};

}
}

#endif


//------------------------------------------------------------------------------
// Class: TestHsi
//
// Description: Tests our core HSI graphic
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestHsi_H__
#define __oe_demo_TestHsi_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestHsi : public graphics::Page
{
   DECLARE_SUBCLASS(TestHsi,graphics::Page)

public:
    TestHsi();

    virtual void updateData(const double dt = 0) override;

private:
    double heading;             // our heading
    SendData headingSD;
    double  headingRate;        // rate which are going (up or down)
    SendData headingROSD;
    SendData dmeROSD;           // dme
    double dme;
};

} // end of demo  namespace
} // end of oe namespace

#endif


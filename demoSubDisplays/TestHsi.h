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

class TestHsi : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestHsi,BasicGL::Page)

public:
    TestHsi();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal heading;             // our heading
    SendData headingSD;
    LCreal  headingRate;        // rate which are going (up or down)
    SendData headingROSD;
    SendData dmeROSD;           // dme
    LCreal dme;
};

} // end of demo  namespace
} // end of oe namespace

#endif


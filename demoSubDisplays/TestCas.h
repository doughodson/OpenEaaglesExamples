//------------------------------------------------------------------------------
// Class: TestCas
//
// Description: Example Analog Dial Page
// This page will supply test data to a generic calibrated air speed
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestCas_H__
#define __oe_demo_TestCas_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestCas : public graphics::Page
{
   DECLARE_SUBCLASS(TestCas, graphics::Page)

public:
    TestCas();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal tas;                     // our cas dial rotation position (1 - 900)
    SendData tasSD;
    LCreal  tasRate;                // rate which are going (up or down)
    SendData tasPointerRotationSD;  // cas pointer rotation (1 - 900)
    SendData tasROSD;
};

} // end of demo namespace
} // end of oe namespace

#endif


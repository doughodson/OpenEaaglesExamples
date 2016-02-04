//------------------------------------------------------------------------------
// Class: TestAlt
//
// Description: Tests our altitude tape instrument
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestAlt_H__
#define __oe_demo_TestAlt_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestAlt : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestAlt, BasicGL::Page)

public:
    TestAlt();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal alt;             // our heading
    SendData altSD;
    LCreal  altRate;        // rate which are going (up or down)
    SendData altROSD;
};

} // end of demo namespace
} // end of oe namespace

#endif


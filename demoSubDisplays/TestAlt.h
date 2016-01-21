//------------------------------------------------------------------------------
// Class: TestAlt
//
// Description: Tests our altitude tape instrument
//------------------------------------------------------------------------------
#ifndef __Eaagles_demo_TestAlt_H__
#define __Eaagles_demo_TestAlt_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
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
} // end of Eaagles namespace

#endif


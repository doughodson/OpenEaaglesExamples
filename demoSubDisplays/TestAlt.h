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

class TestAlt : public graphics::Page
{
   DECLARE_SUBCLASS(TestAlt, graphics::Page)

public:
    TestAlt();

    virtual void updateData(const double dt = 0) override;

private:
    double alt;             // our heading
    SendData altSD;
    double  altRate;        // rate which are going (up or down)
    SendData altROSD;
};

}
}

#endif



#ifndef __TestAlt_H__
#define __TestAlt_H__

#include "openeaagles/graphics/Page.hpp"

//------------------------------------------------------------------------------
// Class: TestAlt
//
// Description: Tests our altitude tape instrument
//------------------------------------------------------------------------------
class TestAlt : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestAlt, oe::graphics::Page)

public:
    TestAlt();

    virtual void updateData(const double dt = 0) override;

private:
    double alt;             // our heading
    SendData altSD;
    double  altRate;        // rate which are going (up or down)
    SendData altROSD;
};

#endif

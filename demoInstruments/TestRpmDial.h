
#ifndef __TestRpmDial_H__
#define __TestRpmDial_H__

#include "openeaagles/graphics/Page.h"

//------------------------------------------------------------------------------
// Class: TestRpmDial
//
// Description: Another example of using an analog dial.
//------------------------------------------------------------------------------
class TestRpmDial : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestRpmDial, oe::graphics::Page)

public:
    TestRpmDial();

    virtual void updateData(const double dt = 0) override;

private:
    double rpm;
    SendData rpmSD;
    SendData rpmROSD;       // sends our readout data (to a numeric readout)
    double  rpmRate;
};

#endif

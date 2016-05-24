//------------------------------------------------------------------------------
// Class: TestAdi
//
// Description: Tests our core ADI graphic
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestAdi_H__
#define __oe_demo_TestAdi_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestAdi : public graphics::Page
{
   DECLARE_SUBCLASS(TestAdi, graphics::Page)

public:
    TestAdi();

    virtual void updateData(const double dt = 0) override;

private:
    double pitch;           // our pitch (90 to -90)
    SendData pitchSD;
    double  pitchRate;
    double roll;            // our roll (3.14 to -3.14)
    SendData rollSD;
    double rollRate;
    double slip;            // our side slip (20 to -20)
    SendData slipSD;
    double slipRate;
};

} // end of demo namespace
} // end of oe namespace

#endif


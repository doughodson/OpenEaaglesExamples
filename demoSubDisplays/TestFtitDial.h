//------------------------------------------------------------------------------
// Class: TestFtitDial
//
// Description: Example Analog Dial Page
// This page will supply test data to the fuel temperature internal dial
//
//------------------------------------------------------------------------------
#ifndef __oe_demo_TestFtitDial_H__
#define __oe_demo_TestFtitDial_H__

#include "openeaagles/graphics/Page.h"

namespace oe {
namespace demo {

class TestFtitDial : public graphics::Page
{
   DECLARE_SUBCLASS(TestFtitDial, graphics::Page)

public:
    TestFtitDial();

    virtual void updateData(const double dt = 0) override;

private:
    double ftitRotation;        // our ftit position (0 - 1000)
    SendData ftitRotationSD;
    double  ftitRate;           // rate which are going (up or down)
    SendData ftitRotationROSD;  // for our readout
};

} // end of demo namespace
} // end of oe namespace

#endif


//------------------------------------------------------------------------------
// Class: TestFtitDial
//
// Description: Example Analog Dial Page
// This page will supply test data to the fuel temperature internal dial
//
//------------------------------------------------------------------------------
#ifndef __Eaagles_demo_TestFtitDial_H__
#define __Eaagles_demo_TestFtitDial_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace demo {

class TestFtitDial : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestFtitDial, BasicGL::Page)

public:
    TestFtitDial();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal ftitRotation;        // our ftit position (0 - 1000)
    SendData ftitRotationSD;
    LCreal  ftitRate;           // rate which are going (up or down)
    SendData ftitRotationROSD;  // for our readout
};

} // end of demo namespace
} // end of Eaagles namespace

#endif


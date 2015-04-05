//------------------------------------------------------------------------------
// Class: TestEngineDial
//
// Description: Example Analog Dial Page
// This page will supply test data to the engine dial
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestEngineDial_H__
#define __Eaagles_Demo_TestEngineDial_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestEngineDial : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestEngineDial, BasicGL::Page)

public:
    TestEngineDial();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal engineRotation;          // our engine rpm position (1 - 100)
    SendData engineRotationSD;
    SendData engineReadoutSD;       // sends our readout data (to a numeric readout)
    LCreal  engineRate;             // rate which are going (up or down)
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif


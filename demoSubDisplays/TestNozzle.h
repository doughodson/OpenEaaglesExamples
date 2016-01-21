//------------------------------------------------------------------------------
// Class: TestNozzle
//
// Description: Another example of using an analog dial.
//------------------------------------------------------------------------------
#ifndef __Eaagles_demo_TestNozzle_H__
#define __Eaagles_demo_TestNozzle_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace demo {

class TestNozzle : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestNozzle, BasicGL::Page)

public:
    TestNozzle();

    void updateData(const LCreal dt = 0) override;

private:
    LCreal nozPos;
    SendData nozPosSD;
    SendData nozPosROSD;       // sends our readout data (to a numeric readout)
    LCreal  nozRate;
};

} // end of demo namespace
} // end of Eaagles namespace

#endif


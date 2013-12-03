//------------------------------------------------------------------------------
// Class:	TestFtitDial
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestFtitDial
//
// Description:	Example Analog Dial Page 
// This page will supply test data to the fuel temperature internal dial
//
//------------------------------------------------------------------------------
#ifndef	__TestFtitDial_H__9EB5808A_388D_4da5_82E2_A8A9D39071C3
#define __TestFtitDial_H__9EB5808A_388D_4da5_82E2_A8A9D39071C3

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestFtitDial : public BasicGL::Page {
   DECLARE_SUBCLASS(TestFtitDial,BasicGL::Page)

public:
    TestFtitDial();
   
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal ftitRotation;        // our ftit position (0 - 1000) 
    SendData ftitRotationSD;
    LCreal  ftitRate;           // rate which are going (up or down)
    SendData ftitRotationROSD;  // for our readout
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif	/* __TestFtitDial_H__9EB5808A_388D_4da5_82E2_A8A9D39071C3 */


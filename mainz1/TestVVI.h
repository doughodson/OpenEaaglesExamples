//------------------------------------------------------------------------------
// Class:	TestVVI
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestVVI
//
// Description:	Test the gauge slider
// This page will supply test data to a generic analog tape gauge
//
//------------------------------------------------------------------------------
#ifndef	__TestVVI_H__F6D023C5_D5FE_4616_AB5A_73ADA7F2B225
#define __TestVVI_H__F6D023C5_D5FE_4616_AB5A_73ADA7F2B225

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Mainz1 {

class TestVVI : public BasicGL::Page {
   DECLARE_SUBCLASS(TestVVI,BasicGL::Page)

public:
   TestVVI();
   
   // Basic::Component interface
   virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal gaugePosition;       // our gauge position (inches)
    SendData gaugePositionSD;
    SendData gaugePositionROSD;
    LCreal  gaugeRate;          // rate which are going (up or down)
};

} // end of Mainz1 namespace
} // end of Eaagles namespace

#endif	/* __TestVVI_H__F6D023C5_D5FE_4616_AB5A_73ADA7F2B225 */


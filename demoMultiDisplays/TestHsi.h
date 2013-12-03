//------------------------------------------------------------------------------
// Class:	TestHsi
// Base class:	Basic::Object > BasicGL::Graphic > BasicGL::Page -> TestHsi
//
// Description:	Tests our core HSI graphic
//
//------------------------------------------------------------------------------
#ifndef	__TestHsi_H__D774B635_7313_4c7e_ACA6_17E7E4562BF2
#define __TestHsi_H__D774B635_7313_4c7e_ACA6_17E7E4562BF2

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestHsi : public BasicGL::Page {
   DECLARE_SUBCLASS(TestHsi,BasicGL::Page)

public:
    TestHsi();
   
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal heading;             // our heading 
    SendData headingSD;
    LCreal  headingRate;        // rate which are going (up or down)
    SendData headingROSD;
    SendData dmeROSD;           // dme
    LCreal dme;
};

} // end of Demo  namespace
} // end of Eaagles namespace

#endif	/* __TestHsi_H__D774B635_7313_4c7e_ACA6_17E7E4562BF2 */


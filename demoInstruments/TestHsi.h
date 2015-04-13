//------------------------------------------------------------------------------
// Class: TestHsi
//
// Description: Tests our core HSI graphic
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestHsi_H__
#define __Eaagles_Demo_TestHsi_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestHsi : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestHsi,BasicGL::Page)

public:
    TestHsi();

    void updateData(const LCreal dt = 0) override;

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

#endif


//------------------------------------------------------------------------------
// Class: TestAlt
//
// Description: Tests our altitude tape instrument
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestAlt_H__
#define __Eaagles_Demo_TestAlt_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestAlt : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestAlt,BasicGL::Page)

public:
    TestAlt();
   
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal alt;             // our heading 
    SendData altSD;
    LCreal  altRate;        // rate which are going (up or down)
    SendData altROSD;
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif


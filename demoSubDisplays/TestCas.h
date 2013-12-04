//------------------------------------------------------------------------------
// Class: TestCas
//
// Description: Example Analog Dial Page 
// This page will supply test data to a generic calibrated air speed
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestCas_H__
#define __Eaagles_Demo_TestCas_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestCas : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestCas,BasicGL::Page)

public:
    TestCas();
       
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal tas;                     // our cas dial rotation position (1 - 900)
    SendData tasSD;
    LCreal  tasRate;                // rate which are going (up or down)
    SendData tasPointerRotationSD;  // cas pointer rotation (1 - 900)
    SendData tasROSD;
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif


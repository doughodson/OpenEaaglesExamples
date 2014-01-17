//------------------------------------------------------------------------------
// Class: TestAdi2
//
// Description: Tests an MFD version of the ADI
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestAdi2_H__
#define __Eaagles_Demo_TestAdi2_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestAdi2 : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestAdi2,BasicGL::Page)

public:
    TestAdi2();
   
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0);
   
private:
    LCreal pitch;           // our pitch (90 to -90)
    SendData pitchSD;
    LCreal  pitchRate;
    LCreal roll;            // our roll (180 to -180)
    SendData rollSD;
    SendData rollBASD;      // bank angle roll value
    LCreal rollRate;
    LCreal slip;            // our side slip (20 to -20)
    SendData slipSD;
    LCreal slipRate;
    LCreal calAS;           // calibrated airspeed
    LCreal calASRate;
    SendData calASSD;
    LCreal alt;             // altitude
    SendData altSD;
    LCreal altRate;
    LCreal mag;             // magnetic heading
    SendData magSD;
    LCreal magRate;
    LCreal cdmX;            // x (pitch) value of our climb dive marker (inches)
    LCreal cdmY;            // y (slip) value of our climb dive marker (inches)
    SendData cdmXSD;
    SendData cdmYSD;
    SendData cdmRollSD;        
    SendData ghostPitchSD;  // ghost horizon pitch
    SendData ghostRollSD;   // ghost horizon roll
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif

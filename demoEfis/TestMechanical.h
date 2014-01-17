//------------------------------------------------------------------------------
// Class: TestMechanical
//
// Description: Simulates a rockwell collins type EFIS Mechanical ADI graphic
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_TestMechanical_H__
#define __Eaagles_Demo_TestMechanical_H__

#include "openeaagles/basicGL/Page.h"

namespace Eaagles {
namespace Demo {

class TestMechanical : public BasicGL::Page
{
   DECLARE_SUBCLASS(TestMechanical,BasicGL::Page)

public:
    TestMechanical();
    
    // Basic::Component interface
    virtual void updateData(const LCreal dt = 0.000000);
   
private:
    static const LCreal T1;     // heading slew rate (deg/sec)
    static const LCreal T2;     // rate of slew rate (pointer_widths/sec)

    LCreal pitch;           // actual pitch    
    SendData pitchSD;
    LCreal  pitchRate;      
    LCreal roll;            // actual roll    
    SendData rollSD;    
    LCreal rollRate;
    LCreal slip;            
    SendData slipSD;
    LCreal slipRate;
    LCreal cmdPitch;        // commanded pitch
    SendData cmdPitchSD;
    LCreal cmdRoll;         // commanded roll
    SendData cmdRollSD;
    LCreal cmdPitchRate;
    LCreal cmdRollRate;
    bool inView;            // when our commanded pitch is in view
    LCreal heading;         // heading of our ownship (for rate of turn)
    LCreal headingRate;
    bool rtFail;            // our rate of turn indicator failure flag
    // runway stuff
    bool rwFail;            // runway failure flag
    LCreal locDots;         // localizer dots
    LCreal locDotsRate;
    SendData locDotsSD;     // localizer dots
    LCreal rAlt;            // radio altitude
    LCreal rAltRate;
    SendData rAltSD;    
    // glideslope stuff
    bool gsFail;            
    LCreal gsDots;          // glideslope dots
    LCreal gsDotsRate;
    SendData gsDotsSD;
    // speed deviation stuff
    bool sdFail;
    LCreal speedDots;       // speed dots
    LCreal speedDotsRate;
    SendData speedDotsSD;
    // gaLight stuff
    int gaMode;
    LCreal gaTimer;
    // mdaLight stuff
    int mdaMode;
    LCreal mdaTimer;    
    // cmptr stuff
    bool cmptrFail;         // our computer fail flag (on = true)
    SendData cmptrFailSD;
    // GA Light stuff
    SendData gaModeSD;
    // gryo stuff
    bool gryoFail;          // our gryo fail flag (on = true)
    LCreal gryoFailTimer;  
    SendData gryoFailSD;
    SendData gsFailSD;
    SendData gsFailVisSD;
    bool isGSValid;         // is our glideslope value valid?
    bool isRWIndValid;      // is our runway data valid?
    bool isSDValid;         // validity check
    SendData mdaModeSD;
    SendData rtFailSD;
    SendData rollIndSD;     // for our roll indicator (which is a rotator)
    SendData rwFailSD;
    SendData sdFailSD;
    LCreal curRot;          // current rate of turn
    LCreal rotRate;     
    SendData curRotSD;
};

} // end of Demo namespace
} // end of Eaagles namespace

#endif

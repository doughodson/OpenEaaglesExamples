//------------------------------------------------------------------------------
// Class: RdrAlt
// 
// Description: radar altitude display and minimums.  It take the min value 
// of the radar, and will compare it to our current alt, and determine the color
// and visibility based on that value
// Inputs:
//      UPDATE_VALUE  -> actual radar alt
//      UPDATE_VALUE2 -> minimum radar alt
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_RdrAlt_H__
#define __Eaagles_Demo_RdrAlt_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace Demo {

class RdrAlt : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(RdrAlt,BasicGL::Graphic)
    
public:
    RdrAlt();
    
    // set functions
    virtual bool setRAlt(const LCreal newRA);       // Sets RADAR altitude (ft)
    virtual bool setRAltMin(const LCreal newRM);    // Sets RADAR altitude minimum (ft)
    
    // get functions
    LCreal getRadarAltFt()  { return rAlt; }
    LCreal getRdrMinAltFt() { return rAltMin; }
        
    // Component interface
    virtual void updateData(const LCreal dt = 0.0);
    virtual bool event(const int event, Basic::Object* const obj = 0);
    
private:
    // event functions
    bool onEventSetRAltRdrAlt(const Basic::Number* const x);
    bool onEventSetRAltMinRdrAlt(const Basic::Number* const x);
    
    LCreal rAlt;        // ft -- our actual radar alt
    SendData rAltSD;
    
    LCreal rAltMin;     // ft -- our minimum radar altitude setting
    SendData rAltMinSD;
};

}; // end of Demo namespace
}; // end of Eaagles namespace

#endif


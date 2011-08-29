//------------------------------------------------------------------------------
// Class:	SpdLines
// Base class: BasicGL::Graphic -> SpdLines
// 
// Description: Draws the lines for the airspeed graphic 
// Inputs:  Slots only
//------------------------------------------------------------------------------
#ifndef	__SpdLines_A2EC0759_9950_43f7_A92B_18C162C6574B
#define __SpdLines_A2EC0759_9950_43f7_A92B_18C162C6574B

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace MainFlightDisplay1 {

    class SpdLines : public BasicGL::Graphic{
    DECLARE_SUBCLASS(SpdLines,BasicGL::Graphic)
    
public:
    SpdLines();
    
    // BasicGL::Graphic interface
    virtual void drawFunc();
    
    // set functions
    virtual bool setIsAlt(const bool newIsAlt);
    virtual bool setDrawBack(const bool newDB);
    
    // get functions
    bool isAltOn()          { return isAlt; }
    bool isBackgroundOn()   { return drawBack; }
    
protected:
    // slot functions
    bool setSlotIsAlt(const Basic::Number* newIsAlt);
    bool setSlotDrawBack(const Basic::Number* newDB);
    
private:
    bool isAlt;     // are we drawing the altitude lines instead?
    bool drawBack;  // draw the background (for transparency purposes)
};

}; // end of MainFlightDisplay1 namespace
}; // end of Eaagles namespace

#endif	/* __SpdLines_A2EC0759_9950_43f7_A92B_18C162C6574B */


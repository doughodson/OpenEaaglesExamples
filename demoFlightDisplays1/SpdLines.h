//------------------------------------------------------------------------------
// Class: SpdLines
// 
// Description: Draws the lines for the airspeed graphic 
// Inputs:  Slots only
//------------------------------------------------------------------------------
#ifndef __Eaagles_Demo_SpdLines_H__
#define __Eaagles_Demo_SpdLines_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace Demo {

class SpdLines : public BasicGL::Graphic
{
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

}; // end of Demo namespace
}; // end of Eaagles namespace

#endif


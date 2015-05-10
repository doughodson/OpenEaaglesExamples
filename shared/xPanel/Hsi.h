//------------------------------------------------------------------------------
// Class: Hsi
//
// Description: simple Hsi that will rotate the compass and display readouts
// Inputs:
//      UPDATE_VALUE 1 and 2 (from rotators) -> true heading
//      UPDATE_VALUE3 -> selected heading
//      UPDATE_VALUE4 -> selected course
//      UPDATE_VALUE5 -> nav 1 bearing
//      UPDATE_VALUE6 -> nav 2 bearing
//      UPDATE_VALUE7 -> cdi dots
//      UPDATE_VALUE8 -> to from
//------------------------------------------------------------------------------
#ifndef __Eaagles_XPanel_Hsi_H__
#define __Eaagles_XPanel_Hsi_H__

#include "openeaagles/basicGL/Rotators.h"

namespace Eaagles {
namespace xPanel {

class Hsi : public BasicGL::Rotators
{
    DECLARE_SUBCLASS(Hsi,BasicGL::Rotators)

public:
    Hsi();

    // set functions
    virtual bool setSelectedHeading(const LCreal newSH);    // Sets selected heading (degs)
    virtual bool setSelectedCourse(const LCreal newC);      // Selected course (degs)
    virtual bool setNav1Brg(const LCreal newB);             // Sets Navaid 1 bearing (degs)
    virtual bool setNav2Brg(const LCreal newB);             // Sets Navaid 2 bearing (degs)
    virtual bool setCdiDots(const LCreal newCDI);           // Sets CDI deflection (dots)
    virtual bool setToFrom(const LCreal newTF);             // Sets TO/FROM value [ to(1); from(0) ]

    // get functions
    LCreal getSelHdg()  { return selHdg; }
    LCreal getSelCrs()  { return selCrs; }
    LCreal getNav1Brg() { return nav1Brg; }
    LCreal getNav2Brg() { return nav2Brg; }
    LCreal getCdiDots() { return cdiDots; }
    LCreal getToFrom()  { return toFrom; }

    void updateData(const LCreal dt = 0.0) override;
    bool event(const int event, Basic::Object* const obj = nullptr) override;

private:
    // event functions
    bool onUpdateSelHdgHsi(const Basic::Number* const x);
    bool onUpdateSelCrsHsi(const Basic::Number* const x);
    bool onUpdateNav1BrgHsi(const Basic::Number* const x);
    bool onUpdateNav2BrgHsi(const Basic::Number* const x);
    bool onUpdateCdiDotsHsi(const Basic::Number* const x);
    bool onUpdateToFromHsi(const Basic::Number* const x);

    LCreal selHdg;      // selected heading (degs)
    SendData selHdgSD;
    LCreal selCrs;      // selected course (degs)
    SendData selCrsSD;
    LCreal cdiDots;     // course deviation (dots)
    SendData cdiDotsSD;
    LCreal toFrom;      // our to from indicator ( 1 == to; 0 == from )
    SendData toFromSD;
    LCreal nav1Brg;     // our navaid 1 bearing (degs)
    LCreal nav2Brg;     // our navaid 2 bearing (degs)
    SendData nav1BrgSD;
    SendData nav2BrgSD;
    SendData selHdgROSD;
};

} // End xPanel namespace
} // End Eaagles namespace

#endif


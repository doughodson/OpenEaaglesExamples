
#ifndef __Hsi_H__
#define __Hsi_H__

#include "openeaagles/graphics/Rotators.hpp"

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
class Hsi : public oe::graphics::Rotators
{
    DECLARE_SUBCLASS(Hsi, oe::graphics::Rotators)

public:
    Hsi();

    // set functions
    virtual bool setSelectedHeading(const double newSH);    // Sets selected heading (degs)
    virtual bool setSelectedCourse(const double newC);      // Selected course (degs)
    virtual bool setNav1Brg(const double newB);             // Sets Navaid 1 bearing (degs)
    virtual bool setNav2Brg(const double newB);             // Sets Navaid 2 bearing (degs)
    virtual bool setCdiDots(const double newCDI);           // Sets CDI deflection (dots)
    virtual bool setToFrom(const double newTF);             // Sets TO/FROM value [ to(1); from(0) ]

    // get functions
    double getSelHdg()  { return selHdg; }
    double getSelCrs()  { return selCrs; }
    double getNav1Brg() { return nav1Brg; }
    double getNav2Brg() { return nav2Brg; }
    double getCdiDots() { return cdiDots; }
    double getToFrom()  { return toFrom; }

    virtual void updateData(const double dt = 0.0) override;
    virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;

private:
    // event functions
    bool onUpdateSelHdgHsi(const oe::base::Number* const x);
    bool onUpdateSelCrsHsi(const oe::base::Number* const x);
    bool onUpdateNav1BrgHsi(const oe::base::Number* const x);
    bool onUpdateNav2BrgHsi(const oe::base::Number* const x);
    bool onUpdateCdiDotsHsi(const oe::base::Number* const x);
    bool onUpdateToFromHsi(const oe::base::Number* const x);

    double selHdg {};      // selected heading (degs)
    SendData selHdgSD;
    double selCrs {};      // selected course (degs)
    SendData selCrsSD;
    double cdiDots {};     // course deviation (dots)
    SendData cdiDotsSD;
    double toFrom {-1.0};  // our to from indicator ( 1 == to; 0 == from )
    SendData toFromSD;
    double nav1Brg {};     // our navaid 1 bearing (degs)
    double nav2Brg {};     // our navaid 2 bearing (degs)
    SendData nav1BrgSD;
    SendData nav2BrgSD;
    SendData selHdgROSD;
};

#endif

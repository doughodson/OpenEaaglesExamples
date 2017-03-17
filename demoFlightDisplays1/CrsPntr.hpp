
#ifndef __CrsPntr_H__
#define __CrsPntr_H__

#include "openeaagles/graphics/Rotators.hpp"

//------------------------------------------------------------------------------
// Class: CrsPntr
//
// Description: Handles the course pointer, cdi, and to from arrow graphic.
// Inputs:
//      UPDATE_VALUE 1 and 2 (from rotators) rotate the pointer
//      UPDATE_VALUE3  -> cdi dots
//      UPDATE_VALUE4 -> to from
//------------------------------------------------------------------------------
class CrsPntr : public oe::graphics::Rotators
{
    DECLARE_SUBCLASS(CrsPntr, oe::graphics::Rotators)

public:
    CrsPntr();

    // set functions
    virtual bool setCdiDots(const double newCDD);   // Sets CDI deviation (dots)
    virtual bool setToFrom(const double newTF);     // Sets TO/FROM value [ to(1); from(0) ]
    virtual bool setNumCdiDots(const int newNCD);   // Sets number of CDI dots
    virtual bool setNumInches(const double newNI);  // Sets number of inches for CDI
    virtual bool setShowCdi(const bool newSCDI);    // Show CDI flag
    virtual bool setShowCrsPntr(const bool newSCP); // Show CRS
    virtual bool setShowToFrom(const bool newTF);   // Show To/from flag

    // get functions
    double getCdiDots()     { return cdiDots; }
    double getToFrom()      { return toFrom; }
    int getNumCdiDots()     { return numDots; }
    double getNumInches()   { return inches; }
    bool isCdiOn()          { return showCdi; }
    bool isCrsPtrOn()       { return showCrsPtr; }
    bool isToFromOn()       { return showToFrom; }

    virtual void drawFunc() override;

    virtual void updateData(const double dt = 0.0) override;
    virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;

protected:
    // slot functions
    bool setSlotNumCdiDots(const oe::base::Number* const newCDI);
    bool setSlotNumInches(const oe::base::Number* const newNI);
    bool setSlotShowCdi(const oe::base::Number* const newSCDI);
    bool setSlotShowCrsPntr(const oe::base::Number* const newSCP);
    bool setSlotShowToFrom(const oe::base::Number* const newTF);

private:
    // event functions
    bool onUpdateCdiDotsCrsPntr(const oe::base::Number* const x);
    bool onUpdateToFromCrsPntr(const oe::base::Number* const x);

    double toFrom {};          // to = 1; from = 0;  Somewhere in between is usually not visible, unless scaled to be visible
    double cdiDots {};         // course deviation dots
    int    numDots {4};        // how many dots are we using?
    double inchesPerDot {};    // how far to translate per dot
    double inches {1.76};
    bool showCdi {true};       // display the cdi?
    bool showCrsPtr {true};    // show the course pointer?
    bool showToFrom {true};    // show our to from arrow?
};

#endif

//------------------------------------------------------------------------------
// Class: Hsi
//------------------------------------------------------------------------------
#include "Hsi.h"

namespace Eaagles {
namespace xPanel {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Hsi, "Hsi")
EMPTY_SERIALIZER(Hsi)

BEGIN_EVENT_HANDLER(Hsi)
    ON_EVENT_OBJ(UPDATE_VALUE3, onUpdateSelHdgHsi, Basic::Number)    
    ON_EVENT_OBJ(UPDATE_VALUE4, onUpdateSelCrsHsi, Basic::Number)    
    ON_EVENT_OBJ(UPDATE_VALUE5, onUpdateNav1BrgHsi, Basic::Number)    
    ON_EVENT_OBJ(UPDATE_VALUE6, onUpdateNav2BrgHsi, Basic::Number)    
    ON_EVENT_OBJ(UPDATE_VALUE7, onUpdateCdiDotsHsi, Basic::Number)    
    ON_EVENT_OBJ(UPDATE_VALUE8, onUpdateToFromHsi, Basic::Number)    
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Hsi::Hsi()
{
    STANDARD_CONSTRUCTOR()
    selHdg = 0;
    selCrs = 0;
    selCrsSD.empty();
    cdiDots = 0;
    cdiDotsSD.empty();
    toFrom = -1;
    toFromSD.empty();
    nav1Brg = 0;
    nav2Brg = 0;
    nav1BrgSD.empty();
    nav2BrgSD.empty();    
    selHdgROSD.empty();
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Hsi::copyData(const Hsi& org, const bool)
{
    BaseClass::copyData(org);    
    selHdg = org.selHdg;
    selCrs = org.selCrs;
    selCrsSD.empty();
    cdiDots = org.cdiDots;
    cdiDotsSD.empty();
    toFrom = org.toFrom;
    toFromSD.empty();
    nav1Brg = org.nav1Brg;
    nav2Brg = org.nav2Brg;
    nav1BrgSD.empty();
    nav2BrgSD.empty();    
    selHdgROSD.empty();
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void Hsi::deleteData()
{
}
    
//------------------------------------------------------------------------------
// set functions
//------------------------------------------------------------------------------
bool Hsi::setSelectedHeading(const LCreal newSH)
{
    selHdg = newSH;
    return true;
}

bool Hsi::setSelectedCourse(const LCreal newC)
{
    selCrs = newC;
    return true;
}

bool Hsi::setNav1Brg(const LCreal newB)
{
    nav1Brg = newB;
    return true;
}

bool Hsi::setNav2Brg(const LCreal newB)
{
    nav2Brg = newB;
    return true;
}

bool Hsi::setCdiDots(const LCreal newCDI)
{
    cdiDots = newCDI;
    return true;
}

bool Hsi::setToFrom(const LCreal newTF)
{
    toFrom = newTF;
    return true;
}

// Event functions
bool Hsi::onUpdateSelHdgHsi(const Basic::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setSelectedHeading(x->getReal());
    return ok;
}
bool Hsi::onUpdateSelCrsHsi(const Basic::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setSelectedCourse(x->getReal());
    return ok;
}
bool Hsi::onUpdateNav1BrgHsi(const Basic::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setNav1Brg(x->getReal());
    return ok;
}
bool Hsi::onUpdateNav2BrgHsi(const Basic::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setNav2Brg(x->getReal());
    return ok;
}
bool Hsi::onUpdateCdiDotsHsi(const Basic::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setCdiDots(x->getReal());
    return ok;
}
bool Hsi::onUpdateToFromHsi(const Basic::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setToFrom(x->getReal());
    return ok;
}


//------------------------------------------------------------------------------
// updateData() -- update non time-critical threads here
//------------------------------------------------------------------------------
void Hsi::updateData(const LCreal dt)
{
    // update our baseclass first
    BaseClass::updateData(dt);
        
    // send our data down to our primary course pointer
    send("pricrsptr", UPDATE_VALUE2, selCrs, selCrsSD);
    send("pricrsptr", UPDATE_VALUE3, cdiDots, cdiDotsSD);
    send("pricrsptr", UPDATE_VALUE4, toFrom, toFromSD);
        
    // send our data down to our bearing pointers
    send("nav1brgptr", UPDATE_VALUE2, nav1Brg, nav1BrgSD);
    send("nav2brgptr", UPDATE_VALUE2, nav2Brg, nav2BrgSD);
    
    // send our selected heading it's value (just a rotator)
    send("selhdg", UPDATE_VALUE2, selHdg, selHdgSD);
    send("selhdgro", UPDATE_VALUE, selHdg, selHdgROSD);
}

}; // end of xPanel namespace
}; // end of Eaagles namespace


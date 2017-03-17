
#include "Hsi.hpp"

#include "openeaagles/base/Number.hpp"

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Hsi, "Hsi")
EMPTY_SERIALIZER(Hsi)
EMPTY_DELETEDATA(Hsi)

BEGIN_EVENT_HANDLER(Hsi)
    ON_EVENT_OBJ(UPDATE_VALUE7, onUpdateSelHdgHsi, oe::base::Number)
    ON_EVENT_OBJ(UPDATE_VALUE8, onUpdateSelCrsHsi, oe::base::Number)
    ON_EVENT_OBJ(UPDATE_VALUE9, onUpdateNav1BrgHsi, oe::base::Number)
    ON_EVENT_OBJ(USER_EVENTS + 1, onUpdateNav2BrgHsi, oe::base::Number)
    ON_EVENT_OBJ(USER_EVENTS + 2, onUpdateCdiDotsHsi, oe::base::Number)
    ON_EVENT_OBJ(USER_EVENTS + 3, onUpdateToFromHsi, oe::base::Number)
END_EVENT_HANDLER()

Hsi::Hsi()
{
    STANDARD_CONSTRUCTOR()
}

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
// set functions
//------------------------------------------------------------------------------
bool Hsi::setSelectedHeading(const double newSH)
{
    selHdg = newSH;
    return true;
}

bool Hsi::setSelectedCourse(const double newC)
{
    selCrs = newC;
    return true;
}

bool Hsi::setNav1Brg(const double newB)
{
    nav1Brg = newB;
    return true;
}

bool Hsi::setNav2Brg(const double newB)
{
    nav2Brg = newB;
    return true;
}

bool Hsi::setCdiDots(const double newCDI)
{
    cdiDots = newCDI;
    return true;
}

bool Hsi::setToFrom(const double newTF)
{
    toFrom = newTF;
    return true;
}

// Event functions
bool Hsi::onUpdateSelHdgHsi(const oe::base::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setSelectedHeading(x->getReal());
    return ok;
}
bool Hsi::onUpdateSelCrsHsi(const oe::base::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setSelectedCourse(x->getReal());
    return ok;
}
bool Hsi::onUpdateNav1BrgHsi(const oe::base::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setNav1Brg(x->getReal());
    return ok;
}
bool Hsi::onUpdateNav2BrgHsi(const oe::base::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setNav2Brg(x->getReal());
    return ok;
}
bool Hsi::onUpdateCdiDotsHsi(const oe::base::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setCdiDots(x->getReal());
    return ok;
}
bool Hsi::onUpdateToFromHsi(const oe::base::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setToFrom(x->getReal());
    return ok;
}

void Hsi::updateData(const double dt)
{
    // update our baseclass first
    BaseClass::updateData(dt);

    // send our data down to our primary course pointer
    send("pricrsptr", UPDATE_VALUE6, -selCrs, selCrsSD);
    send("pricrsptr", UPDATE_VALUE7, cdiDots, cdiDotsSD);
    send("pricrsptr", UPDATE_VALUE8, toFrom, toFromSD);

    // send our data down to our bearing pointers
    send("nav1brgptr", UPDATE_VALUE6, -nav1Brg, nav1BrgSD);
    send("nav2brgptr", UPDATE_VALUE6, -nav2Brg, nav2BrgSD);

    // send our selected heading it's value (just a rotator)
    send("selhdg", UPDATE_VALUE6, -selHdg, selHdgSD);
    send("selhdgro", UPDATE_VALUE, selHdg, selHdgROSD);
}

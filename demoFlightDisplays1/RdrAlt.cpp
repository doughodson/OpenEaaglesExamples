#include "RdrAlt.h"
#include "openeaagles/basicGL/Readouts.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basicGL/Display.h"

namespace Eaagles {
namespace Demo {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(RdrAlt, "RdrAlt")
EMPTY_SERIALIZER(RdrAlt)

// Event handler
BEGIN_EVENT_HANDLER(RdrAlt)
    ON_EVENT_OBJ(UPDATE_VALUE, onEventSetRAltRdrAlt, Basic::Number)
    ON_EVENT_OBJ(UPDATE_VALUE2, onEventSetRAltMinRdrAlt, Basic::Number)
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
RdrAlt::RdrAlt()
{
    STANDARD_CONSTRUCTOR()
    rAlt = 0.0;
    rAltMin = 0.0;
    rAltSD.empty();
    rAltMinSD.empty();
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void RdrAlt::copyData(const RdrAlt& org, const bool)
{
    BaseClass::copyData(org);
    rAlt = org.rAlt;
    rAltMin = org.rAltMin;
    rAltSD.empty();
    rAltMinSD.empty();
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void RdrAlt::deleteData()
{
}

//------------------------------------------------------------------------------
// set functions
//------------------------------------------------------------------------------
bool RdrAlt::setRAltMin(const LCreal newRM)
{
    rAltMin = newRM;
    return true;
}
bool RdrAlt::setRAlt(const LCreal newRA)
{
    rAlt = newRA;
    return true;
}

// Event functions
bool RdrAlt::onEventSetRAltRdrAlt(const Basic::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setRAlt(x->getReal());
    return ok;
}
bool RdrAlt::onEventSetRAltMinRdrAlt(const Basic::Number* const x)
{
    bool ok = false;
    if (x != nullptr) ok = setRAltMin(x->getReal());
    return ok;
}

//------------------------------------------------------------------------------
// updateData()
//------------------------------------------------------------------------------
void RdrAlt::updateData(const LCreal dt)
{
    // update our base class first
    BaseClass::updateData(dt);

    // check our min alt, and if we are lower, turn both readouts yellow,
    // else one is white and the other is magenta
    bool tooLow = false;
    if (rAlt < rAltMin) tooLow = true;

    // we have to find each readout separately, get it's individual display, and
    // change the color
    // here is the minimum readout display
    Basic::Pair* pair = findByName("rmin");
    if (pair != nullptr) {
        BasicGL::NumericReadout* r = dynamic_cast<BasicGL::NumericReadout*>(pair->object());
        if (r != nullptr) {
            Basic::Identifier* id = new Basic::Identifier("yellow");
            if (!tooLow) id->setStr("magenta");
            r->setColor(id);
            id->unref();
            //Display* d1 = r->getDisplay();

            //if (d1 != 0) {
                //if (tooLow) d1->setColor("yellow");
                //else d1->setColor("magenta");
                //r->draw();

            //}
        }
    }
    // actual radar readout
    Basic::Pair* pair2 = findByName("ralt");
    if (pair2 != nullptr) {
        BasicGL::NumericReadout* r1 = dynamic_cast<BasicGL::NumericReadout*>(pair2->object());
        if (r1 != nullptr) {
            Basic::Identifier* id = new Basic::Identifier("yellow");
            if (!tooLow) id->setStr("magenta");
            r1->setColor(id);
            id->unref();
            //Display* d2 = r1->getDisplay();
            //if (d2 != 0) {
            //    if (tooLow) d2->setColor("yellow");
            //    else d2->setColor("white");
            //    r1->draw();
            //}
        }
    }

    // send our radar alts out
    send("rmin", UPDATE_VALUE, rAltMin, rAltMinSD);
    send("ralt", UPDATE_VALUE, rAlt, rAltSD);
}

}; // end of Demo namespace
}; // end of Eaagles namespace



#include "Station.h"

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_SUBCLASS(Station,"MapTestStation")
EMPTY_SERIALIZER(Station)

BEGIN_SLOTTABLE(Station)
    "display",      // 1) sets our display
END_SLOTTABLE(Station)

BEGIN_SLOT_MAP(Station)
    ON_SLOT(1, setSlotDisplay, Glut::GlutDisplay)
END_SLOT_MAP()


//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Station::Station()
{
    STANDARD_CONSTRUCTOR()
    display = 0;
    displayInit = false;
}  

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Station::copyData(const Station& org, const bool cc)
{
    // copy base class stuff first
    BaseClass::copyData(org);

    if (cc) {
        display = 0;
        displayInit = false;
    }

    if (display != 0) {
        display->unref();
        display = 0;
    }

    if (org.display != 0) {
        display = org.display;
        display->ref();
    }

    displayInit = org.displayInit;
    
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void Station::deleteData()
{
    if (display != 0) {
        display->unref();
        display = 0;
    }
}

//------------------------------------------------------------------------------
// reset() - this is our reset event, which will be called from the mainline
// by sending the Basic::Component::RESET_EVENT token.  Here we will set up
// our display
//------------------------------------------------------------------------------
void Station::reset()
{
    if (display != 0 && !displayInit) {
        display->createWindow();
        display->focus(display);
        displayInit = true;
    }

    // this calls our Baseclass (Simulation::Station -> reset)
    BaseClass::reset();
}


//------------------------------------------------------------------------------
// setSlotDisplay() - sets our display
//------------------------------------------------------------------------------
bool Station::setSlotDisplay(Glut::GlutDisplay* dis)
{
    bool ok = false;
    // clear out our old display first
    if (display != 0) {
        display->unref();
        display = 0;
    }

    if (dis != 0) {
        display = dis;
        display->ref();
        display->container(this);
        ok = true;
    }

    return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex() - needed to be declared when we don't have an empty slottable
//------------------------------------------------------------------------------
Basic::Object* Station::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

}  // end of Example namespace
}  // end of Eaagles namespace


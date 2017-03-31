
#include "Station.hpp"

#include "openeaagles/gui/glut/GlutDisplay.hpp"

IMPLEMENT_SUBCLASS(Station, "MapTestStation")
EMPTY_SERIALIZER(Station)

BEGIN_SLOTTABLE(Station)
    "display",          // 1) sets our display
END_SLOTTABLE(Station)

BEGIN_SLOT_MAP(Station)
    ON_SLOT(1, setSlotDisplay, oe::glut::GlutDisplay)
END_SLOT_MAP()

Station::Station()
{
    STANDARD_CONSTRUCTOR()
}

void Station::copyData(const Station& org, const bool)
{
    BaseClass::copyData(org);

    if (display != nullptr) {
        display->unref();
        display = nullptr;
    }

    if (org.display != nullptr) {
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
    if (display != nullptr) {
        display->unref();
        display = nullptr;
    }
}

//------------------------------------------------------------------------------
// reset() - this is our reset event, which will be called from the mainline
// by sending the base::Component::RESET_EVENT token.  Here we will set up
// our display
//------------------------------------------------------------------------------
void Station::reset()
{
    if (display != nullptr && !displayInit) {
        display->createWindow();
        display->focus(display);
        displayInit = true;
    }

    // this calls our Baseclass (simulation::Station -> reset)
    BaseClass::reset();
}


//------------------------------------------------------------------------------
// setSlotDisplay() - sets our display
//------------------------------------------------------------------------------
bool Station::setSlotDisplay(oe::glut::GlutDisplay* dis)
{
    bool ok = false;
    // clear out our old display first
    if (display != nullptr) {
        display->unref();
        display = nullptr;
    }

    if (dis != nullptr) {
        display = dis;
        display->ref();
        display->container(this);
        ok = true;
    }

    return ok;
}


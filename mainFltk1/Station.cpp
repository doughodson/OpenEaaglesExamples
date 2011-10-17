#include "Station.h"
#include "Display.h"

#include "Fl/Fl_Window.H"
#include "Fl/Fl_Gl_Window.H"

#include "MainWindow.h"

namespace Eaagles {
namespace Fltk1 {

IMPLEMENT_SUBCLASS(Station,"Fltk1Station")
EMPTY_SERIALIZER(Station)

// slot table for this class type
BEGIN_SLOTTABLE(Station)
    "display",       //  1) set our displays
    "display2",      //  2) our second display
END_SLOTTABLE(Station)

//  Map slot table to handles 
BEGIN_SLOT_MAP(Station)
    ON_SLOT(1, setSlotDisplay, Display)
    ON_SLOT(2, setSlotDisplay2, Display)
END_SLOT_MAP()



//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Station::Station()
{
    STANDARD_CONSTRUCTOR()
    display = 0;
    init = false;
    mainWin = 0;
    display2 = 0;
}

//------------------------------------------------------------------------------
// copyData() -- copy our objects data
//------------------------------------------------------------------------------
void Station::copyData(const Station& org, const bool cc)
{
    BaseClass::copyData(org);

    if (cc) {
        display = 0;
        display2 = 0;
        mainWin = 0;
    }

    if (display != 0) {
        display->unref();
        display = 0;
    }
    if (org.display != 0) {
        display = (Display*)org.display->clone();
    }
    if (display2 != 0) {
        display2->unref();
        display2 = 0;
    }
    if (org.display2 != 0) {
        display2 = (Display*)org.display2->clone();
    }
    init = false;
}

//------------------------------------------------------------------------------
// deleteData() -- copy our objects data
//------------------------------------------------------------------------------
void Station::deleteData()
{
    if (display != 0) {
        display->unref();
        display = 0;
    }
    if (display2 != 0) {
        display2->unref();
        display2 = 0;
    }
}

//------------------------------------------------------------------------------
// reset() -- reset our values, and setup our displays if needed
//------------------------------------------------------------------------------
void Station::reset()
{
    // setup our displays.
    if (!init) {
        if (display != 0) {
            mainWin = new MainWindow(200, 200, 800, 500, "FLTK 1 Test Window");
            mainWin->resizable(mainWin);
            mainWin->setupGui(display);
            mainWin->setupGui(display2);
            init = true;
            mainWin->show();
        }
    }
}

//------------------------------------------------------------------------------
// updateData() -- 
//------------------------------------------------------------------------------
void Station::updateData(LCreal dt)
{
    BaseClass::updateData(dt);

    if (display != 0) display->updateData(dt);
    if (display2 != 0) display2->updateData(dt);
}

//------------------------------------------------------------------------------
// setSlotDisplay() - set our display
//------------------------------------------------------------------------------
bool Station::setSlotDisplay(Display* const x)
{
    if (display != 0) {
        display->unref();
        display = 0;
    }
    if (x != 0) {
        display = x;
        display->ref();
    }
    return true;
}

//------------------------------------------------------------------------------
// setSlotDisplay2() - set our 2nd display
//------------------------------------------------------------------------------
bool Station::setSlotDisplay2(Display* const x)
{
    if (display2 != 0) {
        display2->unref();
        display2 = 0;
    }
    if (x != 0) {
        display2 = x;
        display2->ref();
    }
    return true;
}


//------------------------------------------------------------------------------
// getSlotByIndex() 
//------------------------------------------------------------------------------
Basic::Object* Station::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}


}; // end Fltk1 namespace
}; // end Eaagles namespace


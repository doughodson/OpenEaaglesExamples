#include "Display.h"
#include "MapPage.h"
#include <GL/glut.h>

namespace Eaagles {
namespace Example {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Display,"MapTestDisplay")
EMPTY_SERIALIZER(Display)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Display::Display()
{
    STANDARD_CONSTRUCTOR()
    startX = 0;
    startY = 0;
    dragging = false;
    range = 0;
    rangeSD.empty();
}  

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void Display::copyData(const Display& org, const bool cc)
{
    // copy base class stuff first
    BaseClass::copyData(org);

    startX = org.startX;
    startY = org.startY;
    dragging = org.dragging;
    range = org.range;
    rangeSD.empty();
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void Display::deleteData()
{
}

// ----------------------------------------------------------------------------
// mouseEvent() override this to set our start position.
// ----------------------------------------------------------------------------
void Display::mouseEvent(const int button, const int state, const int x, const int y)
{
    BaseClass::mouseEvent(button, state, x, y);

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) dragging = false;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !dragging) dragging = true;
}

// ----------------------------------------------------------------------------
// passiveMotionEvent() .
// ----------------------------------------------------------------------------
void Display::passiveMotionEvent(const int x, const int y)
{
    BaseClass::passiveMotionEvent(x,y);
    if (!dragging) {
        startX = x;
        startY = y;
    }
}

// ----------------------------------------------------------------------------
// mouseMotionEvent() override this to move our map.
// ----------------------------------------------------------------------------
void Display::mouseMotionEvent(const int x, const int y)
{
    if (dragging) {
        MapPage* page = static_cast<MapPage*>(subpage());
        if (page != 0) {
            // get our ref lat, because we won't go passed 70 degrees lat (either way);
            double lat = page->getReferenceLatDeg();
            if (lat < 70 && lat > -70) {
                page->moveMap(startX, startY, x, y);
            }
            else {
                if (lat > 0) page->setReferenceLatDeg(65);
                else page->setReferenceLatDeg(-65);
            }

            startX = x;
            startY = y;
        }
    }

    setMouse(x, y);
}

// ----------------------------------------------------------------------------
// buttonEvent() - called when a button is pressed
// ----------------------------------------------------------------------------
void Display::buttonEvent(const int b)
{
    // range up, down
    MapPage* page = static_cast<MapPage*>(subpage());
    if (page != 0) {
        unsigned int myRange = static_cast<unsigned int>(page->getRange());
        if (b == 1000) {
            if (myRange < 320) {
                myRange += 5;
                page->setRange(myRange);
            }
        }
        else if (b == 1001) {
            if (myRange > 10) {
                myRange -= 5;
                page->setRange(myRange);
            }
        }
    }
}

// ----------------------------------------------------------------------------
// updateData() - update background data
// ----------------------------------------------------------------------------
void Display::updateData(const LCreal dt)
{
    BaseClass::updateData(dt);

    MapPage* page = static_cast<MapPage*>(subpage());
    if (page != 0) range = static_cast<int>(page->getRange());
    
    send("range", UPDATE_VALUE, range, rangeSD);
}

}  // end of Example namespace
}  // end of Eaagles namespace


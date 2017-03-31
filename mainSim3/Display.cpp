
#include "Display.hpp"
#include "MapPage.hpp"
#include <GL/glut.h>

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Display, "MapTestDisplay")
EMPTY_SERIALIZER(Display)
EMPTY_DELETEDATA(Display)

Display::Display()
{
    STANDARD_CONSTRUCTOR()
}

void Display::copyData(const Display& org, const bool)
{
    BaseClass::copyData(org);

    startX = org.startX;
    startY = org.startY;
    dragging = org.dragging;
    range = org.range;
    rangeSD.empty();
}

// ----------------------------------------------------------------------------
// sets our start position.
// ----------------------------------------------------------------------------
void Display::mouseEvent(const int button, const int state, const int x, const int y)
{
    BaseClass::mouseEvent(button, state, x, y);

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)                 { dragging = false;  }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !dragging)  { dragging = true;   }
}

void Display::passiveMotionEvent(const int x, const int y)
{
    BaseClass::passiveMotionEvent(x,y);
    if (!dragging) {
        startX = x;
        startY = y;
    }
}

void Display::mouseMotionEvent(const int x, const int y)
{
    if (dragging) {
        const auto page = static_cast<MapPage*>(subpage());
        if (page != nullptr) {
            // get our ref lat, because we won't go passed 70 degrees lat (either way);
            const double lat = page->getReferenceLatDeg();
            if (lat < 70 && lat > -70) {
                page->moveMap(startX, startY, x, y);
            } else {
                if (lat > 0) page->setReferenceLatDeg(65);
                else page->setReferenceLatDeg(-65);
            }
            startX = x;
            startY = y;
        }
    }
    setMouse(x, y);
}

void Display::buttonEvent(const int b)
{
    // range up, down
    const auto page = static_cast<MapPage*>(subpage());
    if (page != nullptr) {
        auto myRange = static_cast<unsigned int>(page->getRange());
        if (b == 1000) {
            if (myRange < 320) {
                myRange += 5;
                page->setRange(myRange);
            }
        } else if (b == 1001) {
            if (myRange > 10) {
                myRange -= 5;
                page->setRange(myRange);
            }
        }
    }
}

void Display::updateData(const double dt)
{
    BaseClass::updateData(dt);

    const auto page = static_cast<MapPage*>(subpage());
    if (page != nullptr) range = static_cast<int>(page->getRange());

    send("range", UPDATE_VALUE, range, rangeSD);
}

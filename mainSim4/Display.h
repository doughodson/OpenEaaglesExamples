// -------------------------------------------------------------------------------
// Class: Display
//
// Description:
//      Derived Display that will make our map page move.
// -------------------------------------------------------------------------------
#ifndef __Eaagles_Example_Display_H__
#define __Eaagles_Example_Display_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
namespace Example {

class Display : public Glut::GlutDisplay
{
    DECLARE_SUBCLASS(Display, Glut::GlutDisplay)

public:
    Display();

    // Display interface
    virtual void mouseMotionEvent(const int x, const int y);
    virtual void mouseEvent(const int button, const int state, const int x, const int y);
    virtual void passiveMotionEvent(const int x, const int y);
    virtual void buttonEvent(const int b);
    virtual void updateData(const LCreal dt = 0.000000);

private:
    int startX;         // startX of our last mouse position
    int startY;         // startY of our last mouse position
    bool dragging;      // are we dragging the map?
    int range;          // range of our map
    SendData rangeSD;
};

}  // end of Example namespace
}  // end of Eaagles namespace

#endif


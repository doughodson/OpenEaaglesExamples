// -------------------------------------------------------------------------------
// Class: Display
//
// Description:
//      Derived Display that will make our map page move.
// -------------------------------------------------------------------------------
#ifndef __oe_Example_Display_H__
#define __oe_Example_Display_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {
namespace Example {

class Display : public Glut::GlutDisplay
{
    DECLARE_SUBCLASS(Display, Glut::GlutDisplay)

public:
    Display();

    void mouseMotionEvent(const int x, const int y) override;
    void mouseEvent(const int button, const int state, const int x, const int y) override;
    void passiveMotionEvent(const int x, const int y) override;
    void buttonEvent(const int b) override;
    void updateData(const LCreal dt = 0.0) override;

private:
    int startX;         // startX of our last mouse position
    int startY;         // startY of our last mouse position
    bool dragging;      // are we dragging the map?
    int range;          // range of our map
    SendData rangeSD;
};

}  // end of Example namespace
}  // end of oe namespace

#endif


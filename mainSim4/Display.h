// -------------------------------------------------------------------------------
// Class: Display
//
// Description:
//      Derived Display that will make our map page move.
// -------------------------------------------------------------------------------
#ifndef __oe_example_Display_H__
#define __oe_example_Display_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {
namespace example {

class Display : public glut::GlutDisplay
{
    DECLARE_SUBCLASS(Display, glut::GlutDisplay)

public:
    Display();

    void mouseMotionEvent(const int x, const int y) override;
    void mouseEvent(const int button, const int state, const int x, const int y) override;
    void passiveMotionEvent(const int x, const int y) override;
    void buttonEvent(const int b) override;
    void updateData(const double dt = 0.0) override;

private:
    int startX;         // startX of our last mouse position
    int startY;         // startY of our last mouse position
    bool dragging;      // are we dragging the map?
    int range;          // range of our map
    SendData rangeSD;
};

}  // end of example namespace
}  // end of oe namespace

#endif


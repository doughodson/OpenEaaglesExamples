// -------------------------------------------------------------------------------
// Class: Display
//
// Description:
//      Derived Display that will simply make our map page move.
// -------------------------------------------------------------------------------
#ifndef __MAPTEST_DISPLAY_H__
#define __MAPTEST_DISPLAY_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
namespace MapTest {

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

}  // end of MapTest namespace
}  // end of Eaagles namespace

#endif



#ifndef __Display_H__
#define __Display_H__

#include "openeaagles/gui/glut/GlutDisplay.hpp"

// -------------------------------------------------------------------------------
// Class: Display
//
// Description:
//      Derived Display that will make our map page move.
// -------------------------------------------------------------------------------
class Display : public oe::glut::GlutDisplay
{
    DECLARE_SUBCLASS(Display, oe::glut::GlutDisplay)

public:
    Display();

    virtual void mouseMotionEvent(const int x, const int y) override;
    virtual void mouseEvent(const int button, const int state, const int x, const int y) override;
    virtual void passiveMotionEvent(const int x, const int y) override;
    virtual void buttonEvent(const int b) override;
    virtual void updateData(const double dt = 0.0) override;

private:
    int startX {};         // startX of our last mouse position
    int startY {};         // startY of our last mouse position
    bool dragging {};      // are we dragging the map?
    int range {};          // range of our map
    SendData rangeSD;
};

#endif

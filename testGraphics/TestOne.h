//------------------------------------------------------------------------------
// Class: TestOne
//
// Description: Move within a user defined box displaying a trail
//
//  ( def-form TestOne
//  )
//------------------------------------------------------------------------------
#ifndef __oe_example_TestOne_H__
#define __oe_example_TestOne_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
   namespace base {
      class Angle;
   }

namespace example {

class TestOne : public graphics::Graphic
{
    DECLARE_SUBCLASS(TestOne,graphics::Graphic)

public:
    TestOne();

    void getPosition(LCreal& xx, LCreal& yy) const      { xx = xPos; yy = yPos; }
    void setPosition(const LCreal xx, const LCreal yy)  { xPos = xx; yPos = yy; }
    virtual bool realSpeed(const base::Number* const rsobj);
    virtual bool setAngle(base::Angle* saobj);
    virtual bool setAngle(const base::Number* const saobj);

    LCreal leftLimit() const                { return left; }
    void leftLimit(const LCreal ll)         { left = ll; }

    LCreal rightLimit() const               { return right; }
    void rightLimit(const LCreal rr)        { right = rr; }

    LCreal bottomLimit() const              { return bottom; }
    void bottomLimit(const LCreal bb)       { bottom = bb; }

    LCreal topLimit() const                 { return top; }
    void topLimit(const LCreal tt)          { top = tt; }

    void setStartAngle(const LCreal deg);
    void setSpeed(const LCreal xx);

    void drawFunc() override;

    void updateTC(const LCreal dt = 0.0) override;
    void updateData(const LCreal dt = 0.0) override;
    bool event(const int event, base::Object* const obj = nullptr) override;
    void reset() override;

private:

    enum { maxHist = 10 };
    LCreal left, right;             // X limits
    LCreal bottom, top;             // Y limits
    LCreal xPos, yPos;              // Position
    LCreal xOld, yOld;              // Previous Position
    LCreal dx, dy;                  // Delta position
    LCreal speed;                   // Speed
    LCreal sangle;                  // Starting angle (radians)
    osg::Vec2 trail[maxHist];       // Display trail
    int    nTrails;                 // Trail size
    int    index;                   // Trail index
    base::Angle* iangle;         // Input angle
};

} // End example namespace
} // End oe namespace

#endif

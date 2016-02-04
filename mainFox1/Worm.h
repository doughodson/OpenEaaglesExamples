//------------------------------------------------------------------------------
// Class: Worm
//
// Description: Move within a user defined box displaying a trail
//
//  ( def-form Worm
//  )
//------------------------------------------------------------------------------
#ifndef __oe_example_Worm_H__
#define __oe_example_Worm_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {

namespace basic { class Angle; }

namespace example {

class Worm : public BasicGL::Graphic
{
  DECLARE_SUBCLASS(Worm, BasicGL::Graphic)

public:
  Worm();

  void getPosition(LCreal& xx, LCreal& yy) const      { xx = xPos; yy = yPos; }
  void setPosition(const LCreal xx, const LCreal yy)  { xPos = xx; yPos = yy; }

  virtual bool realSpeed(const basic::Number* const rsobj);
  virtual bool setAngle(const basic::Angle* const saobj);
  virtual bool setAngle(const basic::Number* const saobj);

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
  bool event(const int event, basic::Object* const obj = nullptr) override;
  void reset() override;

private:

  enum { maxHist = 10 };
  LCreal left, right;         // X limits
  LCreal bottom, top;         // Y limits
  LCreal xPos, yPos;          // Position
  LCreal xOld, yOld;          // Previous Position
  LCreal dx, dy;              // Delta position
  LCreal speed;               // Speed
  LCreal sangle;              // Starting angle (radians)
  osg::Vec2 trail[maxHist];   // Display trail
  int   nTrails;              // Trail size
  int   index;                // Trail index
  const basic::Angle* iangle; // Input angle

};

} // namespace example
} // namespace oe

#endif


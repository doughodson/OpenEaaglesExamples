//------------------------------------------------------------------------------
// Class:	Worm
// Base class:	Object -> Component -> Graphic -> Worm
//
// Description: Move within a user defined box displaying a trail
//
//  ( def-form Worm
//  )
//------------------------------------------------------------------------------
#ifndef _WORM_INCLUDE
#define _WORM_INCLUDE

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {

  namespace Basic {
    class Angle;
  }

namespace mainFox {

class Worm : public Eaagles::BasicGL::Graphic
{
  DECLARE_SUBCLASS(Worm, Eaagles::BasicGL::Graphic)

public:
  Worm();

  void getPosition(Eaagles::LCreal& xx, Eaagles::LCreal& yy) const      { xx = xPos; yy = yPos; }
  void setPosition(const Eaagles::LCreal xx, const Eaagles::LCreal yy)  { xPos = xx; yPos = yy; }

  virtual bool realSpeed(const Eaagles::Basic::Number* const rsobj);
  virtual bool setAngle(const Eaagles::Basic::Angle* const saobj);
  virtual bool setAngle(const Eaagles::Basic::Number* const saobj);

  Eaagles::LCreal leftLimit() const                { return left; }
  void leftLimit(const Eaagles::LCreal ll)         { left = ll; }

  Eaagles::LCreal rightLimit() const               { return right; }
  void rightLimit(const Eaagles::LCreal rr)        { right = rr; }

  Eaagles::LCreal bottomLimit() const              { return bottom; }
  void bottomLimit(const Eaagles::LCreal bb)       { bottom = bb; }

  Eaagles::LCreal topLimit() const                 { return top; }
  void topLimit(const Eaagles::LCreal tt)          { top = tt; }

  void setStartAngle(const Eaagles::LCreal deg);
  void setSpeed(const Eaagles::LCreal xx);

  // Graphic class Interface
  virtual void drawFunc();

  // Component class Interface
  virtual void updateTC(const Eaagles::LCreal dt = 0.0);
  virtual void updateData(const Eaagles::LCreal dt = 0.0);
  virtual bool event(const int event, Eaagles::Basic::Object* const obj = 0);
  virtual void reset();

private:
    
  enum { maxHist = 10 };
  Eaagles::LCreal left, right;         // X limits
  Eaagles::LCreal bottom, top;         // Y limits
  Eaagles::LCreal xPos, yPos;          // Position
  Eaagles::LCreal xOld, yOld;          // Previous Position
  Eaagles::LCreal dx, dy;              // Delta position
  Eaagles::LCreal speed;               // Speed
  Eaagles::LCreal sangle;              // Starting angle (radians)
  Eaagles::osg::Vec2 trail[maxHist];   // Display trail
  int    nTrails;                      // Trail size
  int    index;                        // Trail index
  const Eaagles::Basic::Angle* iangle; // Input angle

};

} // namespace mainFox
} // namespace Eaagles

#endif


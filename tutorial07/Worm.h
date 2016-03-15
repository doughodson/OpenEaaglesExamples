//------------------------------------------------------------------------------
// Class: Worm
//
// Description: Move within a user defined box displaying a trail
//
//  ( def-form Worm
//  )
//------------------------------------------------------------------------------
#ifndef __oe_tutorial_Worm_H__
#define __oe_tutorial_Worm_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {

namespace base { class Angle; }

namespace tutorial {

class Worm : public graphics::Graphic
{
   DECLARE_SUBCLASS(Worm, graphics::Graphic)

public:
   Worm();

   void getPosition(double& xx, double& yy) const      { xx = xPos; yy = yPos; }
   void setPosition(const double xx, const double yy)  { xPos = xx; yPos = yy; }

   virtual bool realSpeed(const base::Number* const rsobj);
   virtual bool setAngle(const base::Angle* const saobj);
   virtual bool setAngle(const base::Number* const saobj);

   double leftLimit() const                { return left; }
   void leftLimit(const double ll)         { left = ll; }

   double rightLimit() const               { return right; }
   void rightLimit(const double rr)        { right = rr; }

   double bottomLimit() const              { return bottom; }
   void bottomLimit(const double bb)       { bottom = bb; }

   double topLimit() const                 { return top; }
   void topLimit(const double tt)          { top = tt; }

   void setStartAngle(const double deg);
   void setSpeed(const double xx);

   void drawFunc() override;

   void updateTC(const double dt = 0.0) override;
   void updateData(const double dt = 0.0) override;
   bool event(const int event, base::Object* const obj = nullptr) override;
   void reset() override;

private:

   enum { maxHist = 10 };
   double left, right;         // X limits
   double bottom, top;         // Y limits
   double xPos, yPos;          // Position
   double xOld, yOld;          // Previous Position
   double dx, dy;              // Delta position
   double speed;               // Speed
   double sangle;              // Starting angle (radians)
   osg::Vec2 trail[maxHist];   // Display trail
   int    nTrails;             // Trail size
   int    index;               // Trail index
   const base::Angle* iangle; // Input angle

};

} // namespace tutorial
} // namespace oe

#endif

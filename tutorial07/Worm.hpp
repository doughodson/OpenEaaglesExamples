#ifndef __Worm_H__
#define __Worm_H__

#include "openeaagles/graphics/Graphic.hpp"
#include <array>

namespace oe {
namespace base { class Angle; class Number; }
}

//------------------------------------------------------------------------------
// Class: Worm
//
// Description: Move within a user defined box displaying a trail
//
// ( Worm selectName: 111 color: green speed: 10 startAngle: ( Degrees 30 ) )
//
//------------------------------------------------------------------------------
class Worm : public oe::graphics::Graphic
{
   DECLARE_SUBCLASS(Worm, oe::graphics::Graphic)

public:
   Worm();

   void getPosition(double& xx, double& yy) const      { xx = xPos; yy = yPos; }
   void setPosition(const double xx, const double yy)  { xPos = xx; yPos = yy; }

   virtual bool realSpeed(const oe::base::Number* const rsobj);
   virtual bool setAngle(const oe::base::Angle* const saobj);
   virtual bool setAngle(const oe::base::Number* const saobj);

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

   virtual void drawFunc() override;

   virtual void updateTC(const double dt = 0.0) override;
   virtual void updateData(const double dt = 0.0) override;
   virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;
   virtual void reset() override;

private:
   static const int MAX_HIST = 10;

   double left {-10.0}, right {10.0};            // X limits
   double bottom {-10.0}, top {10.0};            // Y limits
   double xPos {}, yPos {};                      // Position
   double xOld {}, yOld {};                      // Previous Position
   double dx {}, dy {};                          // Delta position
   double speed {10.0};                          // Speed
   double sangle {};                             // Starting angle (radians)
   std::array<oe::base::Vec2d, MAX_HIST> trail;  // Display trail
   int    nTrails {};                            // Trail size
   int    index {};                              // Trail index
   const oe::base::Angle* iangle {};             // Input angle
};

#endif


#ifndef __oe_xpanel_TdElevPtr_H__
#define __oe_xpanel_TdElevPtr_H__

#include "openeaagles/graphics/Graphic.hpp"

namespace oe {
namespace base { class Number; }
namespace xpanel {

//------------------------------------------------------------------------------
// Class: TdElevPtr
// Description: Display an elevation pointer.  Before drawing, we position the
//              pointer based our received elevation angle.  The shape of the
//              pointer is defined by our graphic subcomponents.
//
// Notes:
//    1) Elevation is in degrees.
//    2) Movement is limited to +/- 30 degrees, which is scaled to +/- 1.0 in
//       world coordinates.
//
// Factory name: TdElevPtr
// Events:
//    UPDATE_VALUE  <Number>  ! elevation angle (degs)
//------------------------------------------------------------------------------
class TdElevPtr : public graphics::Graphic
{
   DECLARE_SUBCLASS(TdElevPtr, graphics::Graphic)

public:
   TdElevPtr();

   double getElevation() const;     // degs
   bool setElevation(const double); // degs

   virtual void draw() override;

   virtual bool event(const int event, base::Object* const obj = nullptr) override;

private:
   bool onUpdateValue(const base::Number* const);

   double elev {};  // (degs)
};

}
}

#endif

//------------------------------------------------------------------------------
// Class: TdAzPtr
//------------------------------------------------------------------------------
#ifndef __oe_test_TdAzPtr_H__
#define __oe_test_TdAzPtr_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
   namespace base { class Number; }
namespace test {

//------------------------------------------------------------------------------
// Class: TdAzPtr
// Description: Display an azimuth pointer.  Before drawing, we position the
//              pointer based our received azimuth angle.  The shape of the
//              pointer is defined by our graphic subcomponents.
//
// Notes:
//    1) Azimuth is in degrees.
//    2) Movement is limited to +/- 30 degrees, which is scaled to +/- 1.0 in
//       world coordinates.
//
// Factory name: TdAzPtr
//
// Events:
//    UPDATE_VALUE  <Number>  ! azimuth angle (degs)
//------------------------------------------------------------------------------
class TdAzPtr : public graphics::Graphic
{
   DECLARE_SUBCLASS(TdAzPtr, graphics::Graphic)

public:
   TdAzPtr();

   LCreal getAzimuth() const;       // degs
   bool setAzimuth(const LCreal);   // degs

   void draw() override;

   bool event(const int event, base::Object* const obj = nullptr) override;

private:
   bool onUpdateValue(const base::Number* const msg);

   LCreal azimuth;  // (degs)
};

} // End test namespace
} // End oe namespace

#endif


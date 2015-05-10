//------------------------------------------------------------------------------
// Class: TdElevPtr
//------------------------------------------------------------------------------
#ifndef __Eaagles_XPanel_TdElevPtr_H__
#define __Eaagles_XPanel_TdElevPtr_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
   namespace Basic { class Number; }
namespace xPanel {

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
class TdElevPtr : public BasicGL::Graphic
{
   DECLARE_SUBCLASS(TdElevPtr, BasicGL::Graphic)

public:
   TdElevPtr();

   LCreal getElevation() const;     // degs
   bool setElevation(const LCreal); // degs

   void draw() override;

   bool event(const int event, Basic::Object* const obj = nullptr) override;

private:
   bool onUpdateValue(const Basic::Number* const);

   LCreal elev;  // (degs)
};

} // End xPanel namespace
} // End Eaagles namespace

#endif


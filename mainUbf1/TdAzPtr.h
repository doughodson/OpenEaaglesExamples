//------------------------------------------------------------------------------
// Class: TdAzPtr
//------------------------------------------------------------------------------
#ifndef __TdAzPtr_H_4DEB8B64_B86D_4cd2_94E0_13290A1F4BB2__
#define __TdAzPtr_H_4DEB8B64_B86D_4cd2_94E0_13290A1F4BB2__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
   namespace Basic { class Number; }
namespace MainUbf1 {

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
// Form Name: TdAzPtr
// Events:
//    UPDATE_VALUE  <Number>  ! azimuth angle (degs)
//------------------------------------------------------------------------------
class TdAzPtr : public BasicGL::Graphic
{
   DECLARE_SUBCLASS(TdAzPtr,BasicGL::Graphic)

public:
   TdAzPtr();

   LCreal getAzimuth() const;       // degs
   bool setAzimuth(const LCreal);   // degs

   // BasicGL::Graphic class functions
   virtual void draw();

   // Basic::Component class functions 
   virtual bool event(const int event, Basic::Object* const obj = 0);

private:
   bool onUpdateValue(const Basic::Number* const msg);

   LCreal azimuth;  // (degs)
};

} // End MainUbf1 namespace
} // End Eaagles namespace

#endif // __TdAzPtr_H_4DEB8B64_B86D_4cd2_94E0_13290A1F4BB2__

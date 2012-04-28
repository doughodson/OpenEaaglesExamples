//------------------------------------------------------------------------------
// Class: TdElevPtr
//------------------------------------------------------------------------------
#ifndef __TdElevPtr_H_74E7E58B_1913_4aa8_B9DD_642F30316A20__
#define __TdElevPtr_H_74E7E58B_1913_4aa8_B9DD_642F30316A20__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
   namespace Basic { class Number; }
namespace MainUbf1 {

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
// Form Name: TdElevPtr
// Events:
//    UPDATE_VALUE  <Number>  ! elevation angle (degs)
//------------------------------------------------------------------------------
class TdElevPtr : public BasicGL::Graphic
{
   DECLARE_SUBCLASS(TdElevPtr,BasicGL::Graphic)

public:
   TdElevPtr();

   LCreal getElevation() const;     // degs
   bool setElevation(const LCreal); // degs

   // BasicGL::Graphic class functions
   virtual void draw();

   // Basic::Component class functions 
   virtual bool event(const int event, Basic::Object* const obj = 0);

private:
   bool onUpdateValue(const Basic::Number* const);

   LCreal elev;  // (degs)
};

} // End MainUbf1 namespace
} // End Eaagles namespace

#endif // __TdElevPtr_H_74E7E58B_1913_4aa8_B9DD_642F30316A20__

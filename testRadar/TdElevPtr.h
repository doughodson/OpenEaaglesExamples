//------------------------------------------------------------------------------
// Class: TdElevPtr
//------------------------------------------------------------------------------
#ifndef __Eaagles_Test_TdElevPtr_H__
#define __Eaagles_Test_TdElevPtr_H__

#include "openeaagles/basicGL/Graphic.h"

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
namespace Eaagles {
   namespace Basic { class Number; }
namespace Test {

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

} // End Test namespace
} // End Eaagles namespace

#endif

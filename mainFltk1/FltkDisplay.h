
#ifndef __FltkDisplay_H__
#define __FltkDisplay_H__

#include "openeaagles/graphics/Display.h"

//-----------------------------------------------------
// Class: FltkDisplay
//-----------------------------------------------------
class FltkDisplay : public oe::graphics::Display
{
   DECLARE_SUBCLASS(FltkDisplay, oe::graphics::Display)

public:
   FltkDisplay();

   // these are our mouse states, so we can
   // keep track of our mouse state internally
   enum ButtonStates {
      MOUSE_UP = 0,
      MOUSE_DOWN = 1
   };

   // setting rotations
   virtual void setXRotation(const double x);
   virtual void setYRotation(const double y);
   virtual void setZRotation(const double z);

protected:
   void initData();

private:
   // send data for our rotations
   SendData xRotationSD;
   SendData yRotationSD;
   SendData zRotationSD;
};

#endif

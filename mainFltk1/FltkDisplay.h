//-----------------------------------------------------
// Class: FltkDisplay
//
// Description: Display that will rotate our graphics.
//-----------------------------------------------------
#ifndef __oe_example_FltkDisplay_H__
#define __oe_example_FltkDisplay_H__

#include "openeaagles/graphics/Display.h"

namespace oe {
namespace example {

class FltkDisplay : public graphics::Display
{
   DECLARE_SUBCLASS(FltkDisplay, graphics::Display)

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

}  // end example
}  // end oe

#endif

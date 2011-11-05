//-----------------------------------------------------
// Class: FltkDisplay
//
// Description: Display that will rotate our graphics.
//-----------------------------------------------------
#ifndef __Eaagles_mainFltk1_FltkDisplay_H__
#define __Eaagles_mainFltk1_FltkDisplay_H__

#include "openeaagles/basicGL/Display.h"

namespace Eaagles {
namespace mainFltk1 {

class FltkDisplay : public BasicGL::Display
{
   DECLARE_SUBCLASS(FltkDisplay, BasicGL::Display)

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

   // send datas for our rotations
   SendData xRotationSD;
   SendData yRotationSD;
   SendData zRotationSD;
};

};  // end mainFltk1
};  // end Eaagles

#endif

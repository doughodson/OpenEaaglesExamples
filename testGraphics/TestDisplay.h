
#ifndef __oe_Example_TestDisplay_H__
#define __oe_Example_TestDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {

namespace BasicGL { class Graphic; }

namespace Example {

//------------------------------------------------------------------------------
// TestDisplay
//------------------------------------------------------------------------------
class TestDisplay : public Glut::GlutDisplay
{
   DECLARE_SUBCLASS(TestDisplay, Glut::GlutDisplay)

public:
   TestDisplay();

   void drawIt() override;
   void mouseEvent(const int button, const int state, const int x, const int y) override;
   bool event(const int event, Basic::Object* const obj = nullptr) override;
   bool onFrameBufferKey();

private:
   // select/pick test
   BasicGL::Graphic* selected;
};

} // End Example namespace
} // End oe namespace

#endif


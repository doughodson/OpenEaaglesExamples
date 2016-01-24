
#ifndef __oe_example_TestDisplay_H__
#define __oe_example_TestDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {

namespace BasicGL { class Graphic; }

namespace example {

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
   bool event(const int event, basic::Object* const obj = nullptr) override;
   bool onFrameBufferKey();

private:
   // select/pick test
   BasicGL::Graphic* selected;
};

} // End example namespace
} // End oe namespace

#endif


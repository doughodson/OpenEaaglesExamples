
#ifndef __oe_example_TestDisplay_H__
#define __oe_example_TestDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {

namespace graphics { class Graphic; }

namespace example {

//------------------------------------------------------------------------------
// TestDisplay
//------------------------------------------------------------------------------
class TestDisplay : public glut::GlutDisplay
{
   DECLARE_SUBCLASS(TestDisplay, glut::GlutDisplay)

public:
   TestDisplay();

   void drawIt() override;
   void mouseEvent(const int button, const int state, const int x, const int y) override;
   bool event(const int event, base::Object* const obj = nullptr) override;
   bool onFrameBufferKey();

private:
   // select/pick test
   graphics::Graphic* selected;
};

} // End example namespace
} // End oe namespace

#endif


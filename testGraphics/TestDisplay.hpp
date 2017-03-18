
#ifndef __TestDisplay_H__
#define __TestDisplay_H__

#include "openeaagles/gui/glut/GlutDisplay.hpp"

namespace oe {
   namespace graphics { class Graphic; }
}

//------------------------------------------------------------------------------
// TestDisplay
//------------------------------------------------------------------------------
class TestDisplay : public oe::glut::GlutDisplay
{
   DECLARE_SUBCLASS(TestDisplay, oe::glut::GlutDisplay)

public:
   TestDisplay();

   virtual void drawIt() override;
   virtual void mouseEvent(const int button, const int state, const int x, const int y) override;
   virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;

   bool onFrameBufferKey();

private:
   // select/pick test
   oe::graphics::Graphic* selected {};
};

#endif

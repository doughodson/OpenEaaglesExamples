
#ifndef __TestWindow_H__
#define __TestWindow_H__

#include "fx.h"

namespace oe {
   namespace graphics { class Display; }
}

#include "openeaagles/base/safe_ptr.h"

//-------------------------------------------------------
// Class: TestWindow
// Description: Central window for the application
//-------------------------------------------------------
class TestWindow : public FXMainWindow
{
   FXDECLARE(TestWindow)

public:
   TestWindow(FXApp*, oe::graphics::Display*);
   virtual ~TestWindow();

   // initialize
   void create();

   // define additional message IDs for this window
   enum {
      ID_CANVAS = FXMainWindow::ID_LAST,
      ID_CHORE,
      ID_LAST
   };

   // message handlers
   long onExpose(FXObject*, FXSelector, void*);
   long onConfigure(FXObject*, FXSelector, void*);
   long onChore(FXObject*, FXSelector, void*);

protected:
   TestWindow()    {}

private:
   FXGLVisual* glvisual;         // OpenGL visual
   FXGLCanvas* glcanvas;         // OpenGL canvas for drawing

   oe::base::safe_ptr<oe::graphics::Display> display;

   void drawDisplay();

};

#endif

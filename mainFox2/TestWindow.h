
#ifndef __TestWindow_H__
#define __TestWindow_H__

#include "fx.h"

//-------------------------------------------------------
// Class: TestWindow
// Description: Central window for the application
//-------------------------------------------------------
class TestWindow : public FXMainWindow
{
   // macro generated code
   FXDECLARE(TestWindow)

public:
   TestWindow(FXApp*);
   virtual ~TestWindow();

   // initialize
   void create();

   void drawScene();

   // define additional message IDs for this window
   enum {
      ID_CANVAS = FXMainWindow::ID_LAST
   };

   // message handlers
   long onExpose(FXObject*, FXSelector, void*);
   long onConfigure(FXObject*, FXSelector, void*);

protected:
   TestWindow()    {}

private:
   FXGLCanvas* glcanvas;         // GL canvas for drawing
   FXGLVisual* glvisual;         // OpenGL visual

};

#endif

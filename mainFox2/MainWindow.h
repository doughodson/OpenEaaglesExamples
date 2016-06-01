
#ifndef __MainWindow_H__
#define __MainWindow_H__

#include "fx.h"

namespace oe {
   namespace graphics { class Display; }
}

#include "openeaagles/base/safe_ptr.h"

//-------------------------------------------------------
// Class: MainWindow
// Description: Central window for the application
//-------------------------------------------------------
class MainWindow : public FXMainWindow
{
   FXDECLARE(MainWindow)

public:
   MainWindow(FXApp*, oe::graphics::Display*);
   virtual ~MainWindow();

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
   MainWindow()    {}

private:
   FXGLVisual* glvisual;         // OpenGL visual
   FXGLCanvas* glcanvas;         // OpenGL canvas for drawing

   oe::base::safe_ptr<oe::graphics::Display> display;

   void drawDisplay();

};

#endif

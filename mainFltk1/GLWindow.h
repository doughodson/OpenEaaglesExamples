//-----------------------------------------------------
// Class: GLWindow
//
// Description: This is our OpenGL window where
//              drawing will be done
//-----------------------------------------------------

#ifndef __Eaagles_Example_GLWindow_H__
#define __Eaagles_Example_GLWindow_H__

#include <FL/Fl_Gl_Window.H>

namespace Eaagles {
namespace Example {

class FltkDisplay;

class GLWindow : public Fl_Gl_Window
{
public:

   GLWindow(int x,int y,int w,int h,const char *l = 0);
   GLWindow(int x,int y);
   virtual ~GLWindow();

   virtual void setDisplay(FltkDisplay* x);

   // get function(s)
   FltkDisplay* getDisplay()   { return display; }

   void draw() override;
   int handle(int x) override;
   void resize(int x, int y, int w, int h) override;

private:

   void glInit();
   bool glInitialized;     // OpenGL initialization flag

   FltkDisplay* display;
};

}
}

#endif

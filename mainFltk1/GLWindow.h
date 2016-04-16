
#ifndef __oe_example_GLWindow_H__
#define __oe_example_GLWindow_H__

#include <FL/Fl_Gl_Window.H>

namespace oe {
namespace example {

class FltkDisplay;

//-----------------------------------------------------
// Class: GLWindow
//
// Description: This is our OpenGL window where drawing will be done
//-----------------------------------------------------
class GLWindow : public Fl_Gl_Window
{
public:

   GLWindow(int x, int y, int w, int h, const char* l = nullptr);
   GLWindow(int x, int y);
   virtual ~GLWindow();

   virtual void setDisplay(FltkDisplay* x);

   // get function(s)
   FltkDisplay* getDisplay()             { return display; }

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


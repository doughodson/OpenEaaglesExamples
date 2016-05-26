
#ifndef __GLWindow_H__
#define __GLWindow_H__

#include <FL/Fl_Gl_Window.H>

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

   virtual void draw() override;
   virtual int handle(int x) override;
   virtual void resize(int x, int y, int w, int h) override;

private:

   void glInit();
   bool glInitialized;     // OpenGL initialization flag

   FltkDisplay* display;
};

#endif

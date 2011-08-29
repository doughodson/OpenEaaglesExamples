//-----------------------------------------------------
// Classname:   Fl_Gl_Window -> GLWindow
// 
// Description: Derived from Fl_Gl_Window, this is our
// openGL window that we will draw into.
//-----------------------------------------------------

#ifndef __EAAGLES_FLTK1_GLWINDOW_H__
#define __EAAGLES_FLTK1_GLWINDOW_H__

#include <Fl/Fl_Gl_Window.h>

namespace Eaagles {
namespace Fltk1 {

class Display;

class GLWindow : public Fl_Gl_Window 
{
    
public:
    GLWindow(int x,int y,int w,int h,const char *l = 0); 
    GLWindow(int x,int y);
    
    ~GLWindow();

    // set function(s)
    virtual void setDisplay(Display* x);

    // get function(s)
    Display* getDisplay()   { return display; }
    
    // Fltk interface
    virtual void draw();
    virtual int handle(int x);
    virtual void resize(int x, int y, int w, int h);

private:
    void glInit();
    bool glInitialized;     // initialize our open GL settings
    Display* display;       // our eaagles display
};

};
};

#endif // __EAAGLES_FLTK1_GLWINDOW_H__

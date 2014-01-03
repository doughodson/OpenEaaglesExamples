//-----------------------------------------------------
// Class: GLWindow
//-----------------------------------------------------
#include "GLWindow.h"
#include "FltkDisplay.h"

#include <FL/Fl.H>

// ----------------------------------------------------------------------------
// drawCallBack() - this is a static callback made from the GLWindow that tells
// us to draw while idle.
// ----------------------------------------------------------------------------
void drawCallBack(void* pData)
{
    if (pData != NULL) {
        // we know GLWindow called this.
        Eaagles::Example::GLWindow* gl = reinterpret_cast<Eaagles::Example::GLWindow*>(pData);
        if (gl != 0) gl->redraw();
    }
}

namespace Eaagles {
namespace Example {

// ----------------------------------------------------------------------------
// constructor(s) -
// ----------------------------------------------------------------------------
GLWindow::GLWindow(int x,int y,int w,int h,const char *l) : Fl_Gl_Window(x,y,w,h,l)
{
    display = 0;
    // we can make an idle callback which will call this function
    // every time there is nothing going on.  This is working
    // fine right now, but in the future we may have to scale it 
    // back and call the add_timeout function if we need more 
    // CPU power.
    //Fl::add_timeout(1/frameRate, drawCallBack, this);
    // draw whenever idle
    Fl::add_idle(drawCallBack, this);
    glInitialized = false;
}

GLWindow::GLWindow(int x,int y) : Fl_Gl_Window(x,y)
{
    display = 0;
    //Fl::add_timeout(1/frameRate, drawCallBack, this);
    Fl::add_idle(drawCallBack, this);
    glInitialized = false;
}

// ----------------------------------------------------------------------------
// destructor() - just take care of eaagles deletion here, because Fltk
// automatically destroys it's child windows upon destruction.
// ----------------------------------------------------------------------------
GLWindow::~GLWindow()
{
    if (display != 0) {
        display->unref();
        display = 0;
    }
}

// ----------------------------------------------------------------------------
// draw() - called after a redraw() command, this is where we will draw
// our Eaagles graphics.
// ----------------------------------------------------------------------------
void GLWindow::draw()
{
    if (!glInitialized) {
        glInit();
        if (display != 0) {
            int w = 0, h = 0;
            display->getViewportSize(&w, &h);
            display->reshapeIt(w, h);
        }
    }
    if (display != 0) display->drawIt();
}


// ----------------------------------------------------------------------------
// handle() - grab mouse events and pass them down as needed.
// ----------------------------------------------------------------------------
int GLWindow::handle(int x)
{
    if (display != 0) {
        // get our x and y pos
        int xPos = Fl::event_x();
        int yPos = Fl::event_y();
        int button = Fl::event_button();
        if (x == FL_PUSH) {
            display->mouseEvent(button, FltkDisplay::MOUSE_DOWN, xPos, yPos);
            // return a non-zero to ensure we will get the FL_DRAG event
            return 1;
        }
        else if (x == FL_RELEASE) display->mouseEvent(button, FltkDisplay::MOUSE_UP, xPos, yPos);
    }
    return Fl_Gl_Window::handle(x);
}

// ----------------------------------------------------------------------------
// setDisplay() - set our Eaagles display
// ----------------------------------------------------------------------------
void GLWindow::setDisplay(FltkDisplay* x)
{
    if (display != 0) {
        display->unref();
        display = 0;
    }
    if (x != 0) {
        display = x;
        display->ref();
    }
}

// ----------------------------------------------------------------------------
// resize() - update the size of our window and eaagles window.
// ----------------------------------------------------------------------------
void GLWindow::resize(int x, int y, int w, int h)
{
    Fl_Gl_Window::resize(x, y, w, h);
    if (display != 0) {
        // make our display current
        make_current();
        display->reshapeIt(w, h);
    }
}

// ----------------------------------------------------------------------------
// glInit() - called for setting up our GL settings before drawing.
// ----------------------------------------------------------------------------
void GLWindow::glInit()
{
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_DITHER);
    glDisable(GL_FOG);
    glDisable(GL_LIGHTING);
    glDisable(GL_LOGIC_OP);
    glDisable(GL_STENCIL_TEST);
    glDisable(GL_TEXTURE_1D);
    glDisable(GL_TEXTURE_2D);

    // Default pixel transfer settings
    glPixelTransferi(GL_MAP_COLOR, GL_FALSE);
    glPixelTransferi(GL_RED_SCALE, 1);
    glPixelTransferi(GL_RED_BIAS, 0);
    glPixelTransferi(GL_GREEN_SCALE, 1);
    glPixelTransferi(GL_GREEN_BIAS, 0);
    glPixelTransferi(GL_BLUE_SCALE, 1);
    glPixelTransferi(GL_BLUE_BIAS, 0);
    glPixelTransferi(GL_ALPHA_SCALE, 1);
    glPixelTransferi(GL_ALPHA_BIAS, 0);    


    // load our textures, if we have any!
    if (display != 0) display->loadTextures();
    
    glInitialized = true;
}

}
}

//-----------------------------------------------------
// Classname:   Fl_WindowMainWindow
// Namespace:   Eaagles::Fltk1 
// Description: Defines our main fltk window
//-----------------------------------------------------
#ifndef __EAAGLES_FLTK1_MAINWINDOW_H
#define __EAAGLES_FLTK1_MAINWINDOW_H

#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Roller.H>

namespace Eaagles {
namespace Fltk1 {

class GLWindow;
class Display;

class MainWindow :  public Fl_Window 
{
    
public:
    MainWindow(int x,int y,int w,int h,const char *l = 0); 
    MainWindow(int x,int y); 
    
    ~MainWindow();

    // set up our GUI
    void setupGui(Display* myDis);
    // our exit function by the 'X' key or Ctrl + 'c'
    virtual void quitApp();
    // menu item callbacks
    virtual void menuCB(const char* x);
    // roller callbacks
    virtual void setYRotation(const double x);
    virtual void setXRotation(const double x);
    virtual void setZRotation(const double x);

private:
    static const int MAX_GL_WINS = 2;
    static const int MAX_MENU_ITEMS = 2;
    GLWindow* glWins[MAX_GL_WINS];  // our GL window(s)
    Fl_Menu_Bar* menuBar;           // our menu bar
    Fl_Roller* vRoll;               // vertical roller
    Fl_Roller* hRoll;               // horizonal roller
    Fl_Roller* zRoll;               // roller around the Z-axis
    int numWins;                    // number of GL windows we have.
};    

}; // end Fltk1 namespace
}; // end Eaagles namespace

#endif // __EAAGLES_FLTK1_MAINWINDOW_H


#include "MainWindow.h"
#include "GLWindow.h"
#include "FltkDisplay.h"

#include <FL/fl_ask.H>

namespace Eaagles {
namespace Example {

// ----------------------------------------------------------------------------
// windowCallback() - called when MainWindow wants to exit
// ----------------------------------------------------------------------------
static void windowCallback(Fl_Widget*, void* data) {
    // have to handle our own exiting.
    (static_cast<MainWindow*>(data))->quitApp();
}

// roller callbacks
// ----------------------------------------------------------------------------
// hRollerCallback() - called when our Y axis roller is moved
// ----------------------------------------------------------------------------
static void hRollCallback(Fl_Widget* w, void* data) {
    Fl_Roller* r = (Fl_Roller*)w;
    if (r != 0) {
        // have to handle our own exiting.
        (static_cast<MainWindow*>(data))->setYRotation(r->value());    
    }
}

// ----------------------------------------------------------------------------
// vRollCallback() - called when our X axis roller is moved
// ----------------------------------------------------------------------------
static void vRollCallback(Fl_Widget* w, void* data) {
    Fl_Roller* r = (Fl_Roller*)w;
    if (r != 0) {
        // have to handle our own exiting.
        (static_cast<MainWindow*>(data))->setXRotation(r->value());    
    }
}

// ----------------------------------------------------------------------------
// zRollCallback() - called when our Z axis roller is moved
// ----------------------------------------------------------------------------
static void zRollCallback(Fl_Widget* w, void* data) {
    Fl_Roller* r = (Fl_Roller*)w;
    if (r != 0) {
        // have to handle our own exiting.
        (static_cast<MainWindow*>(data))->setZRotation(r->value());    
    }
}


// ----------------------------------------------------------------------------
// menuCallback() - called anytime a menu selection is made
// ----------------------------------------------------------------------------
static void menuCallback(Fl_Widget* w, void* data) {
    Fl_Menu_* m = (Fl_Menu_*)w;
    const Fl_Menu_Item* mi = m->mvalue();
    if (mi != 0) {
        (static_cast<MainWindow*>(data))->menuCB(mi->label());    
    }
}

// ----------------------------------------------------------------------------
// constructor(s) -
// ----------------------------------------------------------------------------
MainWindow::MainWindow(int x,int y,int w,int h,const char *l) : 
Fl_Window(x,y,w,h,l) 
{
    for (int i = 0; i < MAX_GL_WINS; i++) glWins[i] = 0;
    numWins = 0;
    menuBar = 0;
    vRoll = 0;
    hRoll = 0;
    zRoll = 0;
    callback(windowCallback, this);
}

MainWindow::MainWindow(int x,int y) : 
Fl_Window(x,y) 
{
    for (int i = 0; i < MAX_GL_WINS; i++) glWins[i] = 0;
    numWins = 0;
    menuBar = 0;
    vRoll = 0;
    hRoll = 0;
    zRoll = 0;
    callback(windowCallback, this);    
}

MainWindow::~MainWindow()
{
    // children are automatically deleted, so no need to delete
}

// ----------------------------------------------------------------------------
// setupGui() - setup our windows and widgets
// ----------------------------------------------------------------------------
void MainWindow::setupGui(FltkDisplay* dis)
{
    // ok, now let's setup our menu bar and items 
    menuBar = new Fl_Menu_Bar(0, 0, w(), 30);
    // setup our menu items
    menuBar->add("File/New", 0, menuCallback, this);
    menuBar->add("File/Open", 0, menuCallback, this);
    menuBar->add("Help/About", 0, menuCallback, this);

    // setup our rollers
    vRoll = new Fl_Roller(5, 120, 20, 190, "Y");
    vRoll->bounds(-100, 100);
    vRoll->step(0.005);
    vRoll->callback(vRollCallback, this);
    hRoll = new Fl_Roller(110, 415, 190, 20, "X");
    hRoll->bounds(-100, 100);
    hRoll->step(0.005);
    hRoll->type(1);
    // Lee - see if you can callback and give the GL window the callback!!
    hRoll->callback(hRollCallback, this);

    zRoll = new Fl_Roller(385, 120, 20, 190, "Z");
    zRoll->bounds(-100, 100);
    zRoll->step(0.005);
    zRoll->callback(zRollCallback, this);

    if (dis != 0) {
        if (numWins < MAX_GL_WINS) {
            int xPos = 0, yPos = 0;
            int width = 0, height = 0;
            dis->getViewportOrigin(&xPos, &yPos);
            dis->getViewportSize(&width, &height);

            // test a Fl_Gl_Window here
            glWins[numWins] = new GLWindow(xPos, yPos, width, height);
            glWins[numWins]->setDisplay(dis);
            glWins[numWins++]->parent(this);
        }
    }
}

// ----------------------------------------------------------------------------
// quitApp() - called when we are exiting the program
// ----------------------------------------------------------------------------
void MainWindow::quitApp()
{
    int ask = fl_choice("Do you really want to quit?", "Yes", "No", "Cancel");
    if (ask == 0) exit(0);
}

// ----------------------------------------------------------------------------
// menuCB() - called on any menu event
// ----------------------------------------------------------------------------
void MainWindow::menuCB(const char* x)
{
    std::cout << "Menu Callback = " << x << std::endl;
}

// ----------------------------------------------------------------------------
// setYRotation() -
// ----------------------------------------------------------------------------
void MainWindow::setYRotation(const double y)
{
    for (int i = 0; i < MAX_GL_WINS; i++) {
        if (glWins[i] != 0) {
            FltkDisplay* myDis = glWins[i]->getDisplay();
            if (myDis != 0) myDis->setYRotation(y);
        }
    }
}

// ----------------------------------------------------------------------------
// setXRotation() -
// ----------------------------------------------------------------------------
void MainWindow::setXRotation(const double x)
{
    for (int i = 0; i < MAX_GL_WINS; i++) {
        if (glWins[i] != 0) {
            FltkDisplay* myDis = glWins[i]->getDisplay();
            if (myDis != 0) myDis->setXRotation(x);
        }
    }
}

// ----------------------------------------------------------------------------
// setZRotation() -
// ----------------------------------------------------------------------------
void MainWindow::setZRotation(const double x)
{
    for (int i = 0; i < MAX_GL_WINS; i++) {
        if (glWins[i] != 0) {
            FltkDisplay* myDis = glWins[i]->getDisplay();
            if (myDis != 0) myDis->setZRotation(x);
        }
    }
}


} // end Example namespace
} // end Eaagles namespace


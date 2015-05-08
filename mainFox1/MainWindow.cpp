
#include "MainWindow.h"
#include "Application.h"
#include "FoxDisplay.h"
#include "FoxStation.h"

#include "fx3d.h"

namespace Eaagles {
namespace Example {

const int MAIN_WIN_HEIGHT = 1000;
const int MAIN_WIN_WIDTH  = 1000;

const int MY_LINE_SPACING = 100;

// Message Map
FXDEFMAP(MainWindow) MainWindowMap[] = {
   //_Message_Type__________ID_______________________________________Message_Handler__________________
   FXMAPFUNC(SEL_UPDATE,    MainWindow::ID_CANVAS,               MainWindow::onUpdateCanvas),
   FXMAPFUNC(SEL_PAINT,     MainWindow::ID_CANVAS,               MainWindow::onPaintCanvas),
   FXMAPFUNC(SEL_LEFTBUTTONRELEASE, MainWindow::ID_CANVAS,       MainWindow::onLeftBtnRelease),
   FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_START_STOP_ROTATE,    MainWindow::onStartStopRotate),
   FXMAPFUNC(SEL_COMMAND,   MainWindow::ID_START_STOP_TRANSLATE, MainWindow::onStartStopTranslate),
};

// Macro for the GLTestApp class hierarchy implementation
FXIMPLEMENT(MainWindow,FXMainWindow,MainWindowMap,ARRAYNUMBER(MainWindowMap))

MainWindow::MainWindow(Application* app) : 
   FX::FXMainWindow(app, "Fox Main Window" ,NULL, NULL, DECOR_ALL, 100, 100, MAIN_WIN_WIDTH, MAIN_WIN_HEIGHT)
{
   // establish a pointer to display
   FoxStation* station = app->getStation();
   if (station != 0) {
      display = station->getMainDisplay();
      if (display != 0) {
         display->ref();
      }
   } else {
      display = 0;
   }

   // ---
   // Create the GUI here
   // ---
   setupGUI();
}

MainWindow::~MainWindow()
{
   delete menuBar;
   if (display != 0) {  display->unref();  display = 0;  }
}

// Create and initialize
void MainWindow::create()
{
   FXMainWindow::create();
   show(PLACEMENT_DEFAULT);
   
   // load our texures and such
   if (display != 0)
      display->initialize();
}

// OpenGL canvas area has been resized
long MainWindow::onUpdateCanvas(FXObject*,FXSelector,void*)
{
   if (display != 0) {
      FX::FXint x = leftFrame->getWidth();
      FX::FXint y = leftFrame->getHeight();
      display->reshapeIt(x,y);
   }

   return 1;
}
// canvas area needs to be redrawn
long MainWindow::onPaintCanvas(FXObject*,FXSelector,void*)
{
   if (display != 0)
      display->drawIt();
   return 1;
}

// on left button release (for picking!)
long MainWindow::onLeftBtnRelease(FXObject*,FXSelector,void* ptr)
{
   if (display != 0) {
      FXEvent* ev = (FXEvent*)ptr;
      display->pick(ev->win_x, ev->win_y);
   }
   return 1;
}

// start/stop rotating the graphic!
long MainWindow::onStartStopRotate(FXObject*,FXSelector,void*)
{
   if (display != 0) {
      display->toggleRotation();
   }
   return 1;
}
// start/stop translation the graphic!
long MainWindow::onStartStopTranslate(FXObject*,FXSelector,void*)
{
   if (display != 0) {
      display->toggleTranslation();
   }
   return 1;
}

// setupGUI() -- create all of our Fox specific widgets
void MainWindow::setupGUI()
{
   // set up the menu, spring frames and other frames, and all other widgets here.  Make sure
   // to create all of your displays here, by calling the displays create() function
   // (Display->create())

   // Main bar
   menuBar = new FXMenuBar(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X);  

   // FILE menu
   {
      FXMenuPane* fileMenu = new FXMenuPane(this);
      new FXMenuTitle(menuBar, "&File", NULL, fileMenu);
      new FXMenuCommand(fileMenu, "Start/Stop Graphic Rotation", NULL, this, ID_START_STOP_ROTATE);
      new FXMenuCommand(fileMenu, "Start/Stop Graphic Translation", NULL, this, ID_START_STOP_TRANSLATE);
   }

   // now make our display areas and such
   // create our frame for holding the display
   FXHorizontalFrame* springFrame = new FXHorizontalFrame(this, LAYOUT_SIDE_LEFT|LAYOUT_FILL);
   // left frame
   leftFrame  = new FXSpring(springFrame, LAYOUT_FILL|LAYOUT_LEFT, 3);
   // right frame
   rightFrame = new FXSpring(springFrame, LAYOUT_FILL|LAYOUT_RIGHT, 1);

   // setup the right frame
   {
      FXHorizontalFrame* frame = new FXHorizontalFrame(rightFrame, LAYOUT_FILL|LAYOUT_SIDE_RIGHT);
      frame->setBackColor(FXRGB(150, 150, 150));
      new FXLabel(frame, "LABEL 1", NULL, LAYOUT_FILL_X);
      new FXButton(frame, "BUTTON", NULL, NULL, ID_MY_BUTTON, LAYOUT_FILL_X|FRAME_LINE|FRAME_THICK);
   }

   if (display != 0) {
      // this will set it's own width and height
      display->create(getApp(), leftFrame, this, ID_CANVAS, LAYOUT_FIX_HEIGHT | LAYOUT_FIX_WIDTH, 0, 0, 0, 0);
   } 
}

} // end Example namespace
} // end Eaagles namespace

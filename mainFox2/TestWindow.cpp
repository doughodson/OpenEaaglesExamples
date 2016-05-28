
#include "TestWindow.h"

#include "openeaagles/graphics/Display.h"

#include "fx.h"
#include "fx3d.h"

// frame rate (Hz)
const unsigned int frameRate = 10;
// derived delta time
const double dt_secs = 1.0 / static_cast<double>(frameRate);
const unsigned int dt_millis = static_cast<unsigned int>(dt_secs * 1000.0);

//--------------------------------------------------------------------------------
// message types in map:
//
// SEL_PAINT : must repaint window
// SEL_CONFIGURE : resize
// SEL_CHORE : background chore
//--------------------------------------------------------------------------------

// message map which assoicates messages objects received to specific member functions
FXDEFMAP(TestWindow) TestWindowMap[] = {
   //___Message_Type________ID______________________________Message_Handler_______
   FXMAPFUNC(SEL_PAINT,     TestWindow::ID_CANVAS,          TestWindow::onExpose),
   FXMAPFUNC(SEL_CONFIGURE, TestWindow::ID_CANVAS,          TestWindow::onConfigure),
   FXMAPFUNC(SEL_CHORE,     TestWindow::ID_CHORE,           TestWindow::onChore)
};

// macro generated code (class name, base class name, pointer to message map, # of entries in message map)
FXIMPLEMENT(TestWindow, FXMainWindow, TestWindowMap, ARRAYNUMBER(TestWindowMap))

TestWindow::TestWindow(FXApp* a, oe::graphics::Display* d):FXMainWindow(a, "FOX GUI Drawing an OE Display", nullptr, nullptr, DECOR_ALL, 0, 0, 800, 600), display(d)
{
   display->loadTextures();

   // right vertical frame that will contain buttons
   FXVerticalFrame* buttonFrame = new FXVerticalFrame(this, LAYOUT_SIDE_RIGHT|LAYOUT_FILL_Y, 0,0,0,0, 2,2,3,3);

   // button to exit application
   new FXButton(buttonFrame, tr("&Exit\tExit the application"), nullptr, getApp(), FXApp::ID_QUIT,FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_BOTTOM|LAYOUT_LEFT, 0,0,0,0,10,10,5,5);

   // left vertical frame that will contain an opengl canvas
   FXVerticalFrame* glcanvasFrame = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y, 0,0,0,0, 2,2,3,3);

   // subframe within drawing glcanvas
   FXComposite* glpanelFrame = new FXVerticalFrame(glcanvasFrame, FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT, 0,0,0,0, 0,0,0,0);

   // a visual that contains pixel information for opengl drawing
   glvisual = new FXGLVisual(getApp(), VISUAL_DOUBLE_BUFFER);

   // defines the area to be drawn by another object, i.e., opengl code
   glcanvas = new FXGLCanvas(glpanelFrame, glvisual, this, ID_CANVAS, LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT);
}

TestWindow::~TestWindow()
{
   getApp()->removeChore(this, ID_CHORE);
   delete glvisual;
}

void TestWindow::create()
{
   std::cout << "Info::create called\n";

   FXMainWindow::create();
   show(PLACEMENT_SCREEN);
   drawDisplay();
   getApp()->addChore(this, ID_CHORE);
}

// widget has been resized
long TestWindow::onConfigure(FXObject*, FXSelector, void*)
{
   std::cout << "Info::onConfigure called\n";

   if ( glcanvas->makeCurrent() ) {
      display->reshapeIt(glcanvas->getWidth(), glcanvas->getHeight());
      glcanvas->makeNonCurrent();
   }
   return 1;
}

// widget needs repainting
long TestWindow::onExpose(FXObject*, FXSelector, void*)
{
   std::cout << "Info::onExpose called\n";

   drawDisplay();
   return 1;
}

// chore message received, draw display, add new chore
long TestWindow::onChore(FXObject*, FXSelector, void*)
{
//   std::cout << "Info::onChore called\n";

   display->tcFrame(dt_secs);
   display->updateData(dt_secs);
   drawDisplay();
   getApp()->addChore(this, ID_CHORE);
   return 1;
}

void TestWindow::drawDisplay()
{
   // make context current
   if (glcanvas->makeCurrent()) {

      // draw our display
      display->drawIt();

      // swap if it is double-buffered
      if ( glvisual->isDoubleBuffer() ) {
         glcanvas->swapBuffers();
      }

      // make context non-current
      glcanvas->makeNonCurrent();
   }
}

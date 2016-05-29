
#include "TestWindow.h"

#include "openeaagles/graphics/Display.h"
#include "openeaagles/base/Timers.h"

#include "fx.h"
#include "fx3d.h"

//--------------------------------------------------------------------------------
// message types in map:
//
// SEL_PAINT : must repaint window
// SEL_CONFIGURE : resize
// SEL_CHORE : background chore
//--------------------------------------------------------------------------------

// message map which assoicates messages objects received to specific member functions
FXDEFMAP(TestWindow) TestWindowMap[] = {
   //________Message_Type_____ID______________________________Message_Handler_______
   FXMAPFUNC(SEL_PAINT,       TestWindow::ID_CANVAS,          TestWindow::onExpose),
   FXMAPFUNC(SEL_CONFIGURE,   TestWindow::ID_CANVAS,          TestWindow::onConfigure),
   FXMAPFUNC(SEL_CHORE,       TestWindow::ID_CHORE,           TestWindow::onChore)
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
   FXMainWindow::create();
   show(PLACEMENT_SCREEN);
   drawDisplay();
   getApp()->addChore(this, ID_CHORE);
}

// widget has been resized
long TestWindow::onConfigure(FXObject*, FXSelector, void*)
{
   if ( glcanvas->makeCurrent() ) {
      display->reshapeIt(glcanvas->getWidth(), glcanvas->getHeight());
      glcanvas->makeNonCurrent();
   }
   return 1;
}

// widget needs repainting
long TestWindow::onExpose(FXObject*, FXSelector, void*)
{
   drawDisplay();
   return 1;
}

// chore message received, draw display, add new chore
long TestWindow::onChore(FXObject*, FXSelector, void*)
{
   static FXTime lt_nsecs(FXThread::time());     // last time in nanoseconds
   const FXTime ct_nsecs = FXThread::time();     // current  time nanoseconds since Epoch (Jan 1, 1970)
   const FXTime dt_nsecs = ct_nsecs - lt_nsecs;  // delta time difference from last time
   lt_nsecs = FXThread::time();

   const double dt_msecs = static_cast<double>(dt_nsecs) / 1000000.0;
   const double dt_secs = dt_msecs / 1000.0;

//   std::cout << "dt_nsecs: " << dt_nsecs << std::endl;
//   std::cout << "dt_msecs: " << dt_msecs << std::endl;
//   std::cout << "dt_secs: " << dt_secs << std::endl;

   display->tcFrame(dt_secs);
   display->updateData(dt_secs);
   oe::base::Timer::updateTimers(dt_secs);
   oe::graphics::Graphic::flashTimer(dt_secs);
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

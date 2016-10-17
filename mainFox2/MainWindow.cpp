
#include "MainWindow.hpp"

#include "openeaagles/graphics/Display.hpp"
#include "openeaagles/base/Timers.hpp"

#include "fx.h"
#include "fx3d.h"

//--------------------------------------------------------------------------------
// message types in map:
//
// SEL_PAINT     : must repaint window
// SEL_CONFIGURE : resize
// SEL_TIMEOUT   : timeout occurred
// SEL_CHORE     : event to indicate background chore
//--------------------------------------------------------------------------------

// message map which assoicates messages objects received to specific member functions
FXDEFMAP(MainWindow) MainWindowMap[] = {
   //________Message_Type_____ID______________________________Message_Handler_______
   FXMAPFUNC(SEL_PAINT,       MainWindow::ID_CANVAS,          MainWindow::onExpose),
   FXMAPFUNC(SEL_CONFIGURE,   MainWindow::ID_CANVAS,          MainWindow::onConfigure),
   FXMAPFUNC(SEL_TIMEOUT,     MainWindow::ID_TIMEOUT,         MainWindow::onTimeout),
   FXMAPFUNC(SEL_CHORE,       MainWindow::ID_CHORE,           MainWindow::onChore),
   FXMAPFUNC(SEL_COMMAND,     MainWindow::ID_ANIMATE,         MainWindow::onCmdAnimate),
};

// macro generated code (class name, base class name, pointer to message map, # of entries in message map)
FXIMPLEMENT(MainWindow, FXMainWindow, MainWindowMap, ARRAYNUMBER(MainWindowMap))

// graphics frame rate (Hz)
const unsigned int frame_rate = 20;
// derived delta times
const double dt_secs = 1.0 / static_cast<double>(frame_rate);                  // e.g., for 20Hz, a 50ms time advance or 0.05 seconds
const unsigned int dt_msecs = static_cast<unsigned int>(dt_secs * 1000.0);     // 50 milliseconds
const unsigned int dt_nsecs = static_cast<unsigned int>(dt_secs * 1000000.0);  // 50,000 nanoseconds

MainWindow::MainWindow(FXApp* a, oe::graphics::Display* d):FXMainWindow(a, "FOX GUI Drawing an OE Display", nullptr, nullptr, DECOR_ALL, 0, 0, 800, 600), display(d)
{
   display->loadTextures();

   // right vertical frame that will contain buttons
   FXVerticalFrame* buttonFrame = new FXVerticalFrame(this, LAYOUT_SIDE_RIGHT|LAYOUT_FILL_Y, 0,0,0,0, 2,2,3,3);

   // button to start animation using timer and chore events
   new FXButton(buttonFrame, tr("Animate"),
                nullptr, this, ID_ANIMATE, FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_TOP|LAYOUT_LEFT, 0,0,0,0,10,10,5,5);

   // button to exit application
   new FXButton(buttonFrame, tr("&Exit\tExit the application"), nullptr, getApp(),
                FXApp::ID_QUIT,FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_BOTTOM|LAYOUT_LEFT, 0,0,0,0,10,10,5,5);

   // left vertical frame that will contain an opengl canvas
   FXVerticalFrame* glcanvasFrame = new FXVerticalFrame(this, LAYOUT_FILL_X|LAYOUT_FILL_Y, 0,0,0,0, 2,2,3,3);

   // subframe within drawing glcanvas
   FXComposite* glpanelFrame = new FXVerticalFrame(glcanvasFrame, FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT, 0,0,0,0, 0,0,0,0);

   // a visual that contains pixel information for opengl drawing
   glvisual = new FXGLVisual(getApp(), VISUAL_DOUBLE_BUFFER);

   // defines the area to be drawn by another object, i.e., opengl code
   glcanvas = new FXGLCanvas(glpanelFrame, glvisual, this, ID_CANVAS, LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT);
}

MainWindow::~MainWindow()
{
   // remove any outstanding timer and/or chore events
   getApp()->removeChore(this, ID_CHORE);
   getApp()->removeTimeout(this, ID_TIMEOUT);
   delete glvisual;
}

void MainWindow::create()
{
   FXMainWindow::create();
   show(PLACEMENT_SCREEN);
   drawDisplay();
}

// process event indicating widget has been resized
long MainWindow::onConfigure(FXObject*, FXSelector, void*)
{
   if ( glcanvas->makeCurrent() ) {
      display->reshapeIt(glcanvas->getWidth(), glcanvas->getHeight());
      glcanvas->makeNonCurrent();
   }
   return 1;
}

// process event to repaint widget
long MainWindow::onExpose(FXObject*, FXSelector, void*)
{
   drawDisplay();
   return 1;
}

long MainWindow::onTimeout(FXObject*, FXSelector, void*)
{
   // when timer expires, this schedules the chore (i.e., drawing) to return
   // scheduling drawing this way prevents the rest of the graphics system (i.e., events)
   // to not starve.
   getApp()->addChore(this, ID_CHORE);
   return 1;
}

// chore message received, calculate time between draws, update dynamics and redraw display
// reset timer to schedule next chore
long MainWindow::onChore(FXObject*, FXSelector, void*)
{
   static FXTime lasttime_nsecs(FXThread::time());                    // last time (in nanoseconds) this chore ran
   const FXTime currtime_nsecs = FXThread::time();                    // current  time nanoseconds since Epoch (Jan 1, 1970)
   const FXTime elapsed_nsecs = currtime_nsecs - lasttime_nsecs;      // elasped time between last call to this method
   const double elapsed_msecs = static_cast<double>(elapsed_nsecs) / 1000000.0;
   const double elapsed_secs = elapsed_msecs / 1000.0;
   lasttime_nsecs = FXThread::time();

   FXTime t_start = FXThread::time();
   display->tcFrame(elapsed_secs);
   display->updateData(elapsed_secs);
   oe::base::Timer::updateTimers(elapsed_secs);
   oe::graphics::Graphic::flashTimer(elapsed_secs);
   drawDisplay();
   FXTime t_end = FXThread::time();
   double draw_time_msecs = (t_end - t_start) / 1000000.0;   // total time spent redrawing display

   std::cout << "elapsed time msecs: " << elapsed_msecs << "\t draw time msec: "<< draw_time_msecs << std::endl;

   // set the timer so it schedules this chore again
   getApp()->addTimeout(this, ID_TIMEOUT, dt_nsecs);

   return 1;
}

// button processing routine to kick off timer, thus, start animation
long MainWindow::onCmdAnimate(FXObject*, FXSelector, void*)
{
   getApp()->addTimeout(this, ID_TIMEOUT, dt_nsecs);
   return 1;
}

void MainWindow::drawDisplay()
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

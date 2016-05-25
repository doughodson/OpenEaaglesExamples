
#include "fx.h"
#include "fx3d.h"

#include <GL/glu.h>

#include "TestWindow.h"

// timer setting (in nanoseconds)
const FXTime TIMER_INTERVAL = 100000000;

// message map which assoicates messages objects received to specific member functions
FXDEFMAP(TestWindow) TestWindowMap[] = {
   //___Message_Type________ID______________________________Message_Handler_______
   FXMAPFUNC(SEL_PAINT,     TestWindow::ID_CANVAS,          TestWindow::onExpose),
   FXMAPFUNC(SEL_CONFIGURE, TestWindow::ID_CANVAS,          TestWindow::onConfigure),
   FXMAPFUNC(SEL_COMMAND,   TestWindow::ID_SPIN,            TestWindow::onCmdSpin),
   FXMAPFUNC(SEL_UPDATE,    TestWindow::ID_SPIN,            TestWindow::onUpdSpin),
   FXMAPFUNC(SEL_COMMAND,   TestWindow::ID_SPINFAST,        TestWindow::onCmdSpinFast),
   FXMAPFUNC(SEL_UPDATE,    TestWindow::ID_SPINFAST,        TestWindow::onUpdSpinFast),
   FXMAPFUNC(SEL_COMMAND,   TestWindow::ID_STOP,            TestWindow::onCmdStop),
   FXMAPFUNC(SEL_UPDATE,    TestWindow::ID_STOP,            TestWindow::onUpdStop),
   FXMAPFUNC(SEL_UPDATE,    TestWindow::ID_SPEED,           TestWindow::onUpdSpeed),
   FXMAPFUNC(SEL_TIMEOUT,   TestWindow::ID_TIMEOUT,         TestWindow::onTimeout),
   FXMAPFUNC(SEL_CHORE,     TestWindow::ID_CHORE,           TestWindow::onChore),
   FXMAPFUNCS(SEL_COMMAND,  TestWindow::ID_MULTISAMPLE_OFF, TestWindow::ID_MULTISAMPLE_4X, TestWindow::onCmdMultiSample),
   FXMAPFUNCS(SEL_UPDATE,   TestWindow::ID_MULTISAMPLE_OFF, TestWindow::ID_MULTISAMPLE_4X, TestWindow::onUpdMultiSample),
};

// macro generated code (class name, base class name, pointer to message map, # of entries in message map)
FXIMPLEMENT(TestWindow, FXMainWindow, TestWindowMap, ARRAYNUMBER(TestWindowMap))

TestWindow::TestWindow(FXApp* a):FXMainWindow(a, "FOX GUI Drawing an OE Display", nullptr, nullptr, DECOR_ALL, 0, 0, 800, 600)
{
   // right vertical frame that will contain buttons
   FXVerticalFrame* buttonFrame = new FXVerticalFrame(this, LAYOUT_SIDE_RIGHT|LAYOUT_FILL_Y, 0,0,0,0, 2,2,3,3);

   // buttons to select the mode of spinning - timers or chores
   new FXButton(buttonFrame, tr("Spin &Timer\tSpin using interval timers\nNote the app blocks until the interal has elapsed..."),nullptr,this,ID_SPIN,FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,5,5);
   new FXButton(buttonFrame, tr("Spin &Chore\tSpin as fast as possible using chores\nNote even though the app is very responsive, it never blocks;\nthere is always something to do..."),nullptr,this,ID_SPINFAST,FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_TOP|LAYOUT_LEFT,0,0,0,0,10,10,5,5);

   // button to stop spinning
   new FXButton(buttonFrame, tr("&Stop Spin\tStop this mad spinning, I'm getting dizzy"), nullptr, this, ID_STOP, FRAME_THICK|FRAME_RAISED|LAYOUT_FILL_X|LAYOUT_TOP|LAYOUT_LEFT, 0,0,0,0,10,10,5,5);

   // group box which will contain a spinner control
   FXGroupBox* groupbox1 = new FXGroupBox(buttonFrame, tr("Speed (rts)"), GROUPBOX_NORMAL|FRAME_GROOVE|LAYOUT_FILL_X);

   // spinner control which is used to set speed
   speedcontrol = new FXRealSpinner(groupbox1, 3, &dt_rts, FXDataTarget::ID_VALUE,FRAME_SUNKEN|FRAME_THICK|LAYOUT_FILL_X);
   speedcontrol->setRange(0.1, 3.0);
   speedcontrol->setIncrement(0.1);

   // group box which will contain radio buttons to set sampling
   FXGroupBox* groupbox2 = new FXGroupBox(buttonFrame, tr("Multi Sampling"), GROUPBOX_NORMAL|FRAME_GROOVE|LAYOUT_FILL_X);
   new FXRadioButton(groupbox2, "Off", this, ID_MULTISAMPLE_OFF);
   new FXRadioButton(groupbox2, "2x", this, ID_MULTISAMPLE_2X);
   new FXRadioButton(groupbox2, "4x", this, ID_MULTISAMPLE_4X);

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

   // enables tooltips
   new FXToolTip(getApp());

   spinning = 0;
   angle = 0.0;
   rts = 1.0;
   dt_rts.connect(rts);
}

TestWindow::~TestWindow()
{
   getApp()->removeTimeout(this, ID_TIMEOUT);
   getApp()->removeChore(this, ID_CHORE);
   delete glvisual;
}

// create and initialize
void TestWindow::create()
{
   FXMainWindow::create();
   show(PLACEMENT_SCREEN);
}

// widget has been resized
long TestWindow::onConfigure(FXObject*, FXSelector, void*)
{
   if ( glcanvas->makeCurrent() ) {
      glViewport(0, 0, glcanvas->getWidth(), glcanvas->getHeight());
      glcanvas->makeNonCurrent();
   }
   return 1;
}

// Widget needs repainting
long TestWindow::onExpose(FXObject*, FXSelector, void*)
{
   drawScene();
   return 1;
}

// Rotate the boxes when a timer message is received
long TestWindow::onTimeout(FXObject*, FXSelector, void*)
{
   angle += 2.0;
   if (angle>360.0) angle -= 360.0;
   lasttime = FXThread::time();
   drawScene();
   getApp()->addTimeout(this,ID_TIMEOUT,TIMER_INTERVAL);
   return 1;
}

// rotate the boxes when a chore message is received
long TestWindow::onChore(FXObject*, FXSelector, void*)
{
   FXTime c = FXThread::time();
   FXTime d = c-lasttime;
   angle += (d/1000000000.0)*(360.0*rts);
   if (angle>360.0) angle-=360.0;
   lasttime = c;
   drawScene();
   getApp()->addChore(this, ID_CHORE);
   return 1;
}

// Start the boxes spinning
long TestWindow::onCmdSpin(FXObject*, FXSelector, void*)
{
   spinning = 1;
   getApp()->addTimeout(this, ID_TIMEOUT, TIMER_INTERVAL);
   return 1;
}

// enable or disable the spin button
long TestWindow::onUpdSpin(FXObject* sender, FXSelector, void*)
{
   FXButton* button = static_cast<FXButton*>(sender);
   spinning ? button->disable() : button->enable();
   return 1;
}

// Start the boxes spinning
long TestWindow::onCmdSpinFast(FXObject*, FXSelector, void*)
{
  spinning = 1;
  lasttime = FXThread::time();
  speedcontrol->enable();
  getApp()->addChore(this,ID_CHORE);
  return 1;
}

// enable or disable the spin button
long TestWindow::onUpdSpinFast(FXObject* sender, FXSelector,void*)
{
   FXButton* button = static_cast<FXButton*>(sender);
   spinning ? button->disable() : button->enable();
   return 1;
}

// if boxes are spinning, stop them
long TestWindow::onCmdStop(FXObject*, FXSelector, void*)
{
   getApp()->removeTimeout(this, ID_TIMEOUT);
   getApp()->removeChore(this, ID_CHORE);
   speedcontrol->disable();
   spinning = 0;
   return 1;
}

// enable or disable the stop button
long TestWindow::onUpdStop(FXObject* sender, FXSelector,void*)
{
   FXButton* button = static_cast<FXButton*>(sender);
   spinning ? button->enable() : button->disable();
   return 1;
}

// enable or disable the stop button
long TestWindow::onUpdSpeed(FXObject* sender, FXSelector,void*)
{
   if (getApp()->hasTimeout(this, ID_TIMEOUT))
      sender->handle(this, FXSEL(SEL_COMMAND, ID_DISABLE), nullptr);
   else
      sender->handle(this, FXSEL(SEL_COMMAND, ID_ENABLE), nullptr);
   return 1;
}

// draws a simple box using the given corners
void drawBox(GLfloat xmin, GLfloat ymin, GLfloat zmin, GLfloat xmax, GLfloat ymax, GLfloat zmax)
{
   glBegin(GL_TRIANGLE_STRIP);
      glNormal3f(0.0, 0.0, -1.0);
      glVertex3f(xmin, ymin, zmin);
      glVertex3f(xmin, ymax, zmin);
      glVertex3f(xmax, ymin, zmin);
      glVertex3f(xmax, ymax, zmin);
   glEnd();

   glBegin(GL_TRIANGLE_STRIP);
      glNormal3f(1.0, 0.0, 0.0);
      glVertex3f(xmax, ymin, zmin);
      glVertex3f(xmax, ymax, zmin);
      glVertex3f(xmax, ymin, zmax);
      glVertex3f(xmax, ymax, zmax);
   glEnd();

   glBegin(GL_TRIANGLE_STRIP);
      glNormal3f(0.0, 0.0, 1.0);
      glVertex3f(xmax, ymin, zmax);
      glVertex3f(xmax, ymax, zmax);
      glVertex3f(xmin, ymin, zmax);
      glVertex3f(xmin, ymax, zmax);
   glEnd();

   glBegin(GL_TRIANGLE_STRIP);
      glNormal3f(-1.0, 0.0, 0.0);
      glVertex3f(xmin, ymin, zmax);
      glVertex3f(xmin, ymax, zmax);
      glVertex3f(xmin, ymin, zmin);
      glVertex3f(xmin, ymax, zmin);
   glEnd();

   glBegin(GL_TRIANGLE_STRIP);
      glNormal3f(0.0,1.0, 0.0);
      glVertex3f(xmin, ymax, zmin);
      glVertex3f(xmin, ymax, zmax);
      glVertex3f(xmax, ymax, zmin);
      glVertex3f(xmax, ymax, zmax);
   glEnd();

   glBegin(GL_TRIANGLE_STRIP);
      glNormal3f(0.0, -1.0, 0.0);
      glVertex3f(xmax, ymin, zmax);
      glVertex3f(xmax, ymin, zmin);
      glVertex3f(xmin, ymin, zmax);
      glVertex3f(xmin, ymin, zmin);
   glEnd();
}

// draw the GL scene
void TestWindow::drawScene()
{
   const GLfloat lightPosition[] = { 15.0, 10.0, 5.0, 1.0 };
   const GLfloat lightAmbient[]  = { 0.1f, 0.1f, 0.1f, 1.0 };
   const GLfloat lightDiffuse[]  = { 0.9f, 0.9f, 0.9f, 1.0 };
   const GLfloat redMaterial[]   = { 1.0, 0.0, 0.0, 1.0 };
   const GLfloat blueMaterial[]  = { 0.0, 0.0, 1.0, 1.0 };

   GLdouble canvaswidth = glcanvas->getWidth();
   GLdouble canvasheight = glcanvas->getHeight();
   GLdouble aspect = canvasheight>0 ? canvaswidth/canvasheight : 1.0;

   // Make context current
   if (glcanvas->makeCurrent()) {

      glViewport(0,0,glcanvas->getWidth(),glcanvas->getHeight());

      glClearColor(1.0, 1.0, 1.0, 1.0);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      glEnable(GL_DEPTH_TEST);

      glDisable(GL_DITHER);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(30.0, aspect, 1.0, 100.0);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(5.0, 10.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

      glShadeModel(GL_SMOOTH);
      glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
      glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
      glEnable(GL_LIGHT0);
      glEnable(GL_LIGHTING);

      glMaterialfv(GL_FRONT, GL_AMBIENT, blueMaterial);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, blueMaterial);

      glPushMatrix();
      glRotated(angle, 0.0, 1.0, 0.0);
      drawBox(-1, -1, -1, 1, 1, 1);

      glMaterialfv(GL_FRONT, GL_AMBIENT, redMaterial);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, redMaterial);

      glPushMatrix();
      glTranslated(0.0, 1.75, 0.0);
      glRotated(angle, 0.0, 1.0, 0.0);
      drawBox(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);
      glPopMatrix();

      glPushMatrix();
      glTranslated(0.0, -1.75, 0.0);
      glRotated(angle, 0.0, 1.0, 0.0);
      drawBox(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);
      glPopMatrix();

      glPushMatrix();
      glRotated(90.0, 1.0, 0.0, 0.0);
      glTranslated(0.0, 1.75, 0.0);
      glRotated(angle, 0.0, 1.0, 0.0);
      drawBox(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);
      glPopMatrix();

      glPushMatrix();
      glRotated(90.0, -1.0, 0.0, 0.0);
      glTranslated(0.0, 1.75, 0.0);
      glRotated(angle, 0.0, 1.0, 0.0);
      drawBox(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);
      glPopMatrix();

      glPushMatrix();
      glRotated(90.0, 0.0, 0.0, 1.0);
      glTranslated(0.0, 1.75, 0.0);
      glRotated(angle, 0.0, 1.0, 0.0);
      drawBox(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);
      glPopMatrix();

      glPushMatrix();
      glRotated(90.0, 0.0, 0.0, -1.0);
      glTranslated(0.0, 1.75, 0.0);
      glRotated(angle, 0.0, 1.0, 0.0);
      drawBox(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);
      glPopMatrix();

      glPopMatrix();

      // Swap if it is double-buffered
      if ( glvisual->isDoubleBuffer() ) {
         glcanvas->swapBuffers();
      }

      // Make context non-current
      glcanvas->makeNonCurrent();
   }
}

// switch multisampling on
long TestWindow::onCmdMultiSample(FXObject* sender, FXSelector sel, void*)
{
   FXint nsamples = 0;
   switch( FXSELID(sel) ) {
      case ID_MULTISAMPLE_OFF: nsamples=0; break;
      case ID_MULTISAMPLE_2X : nsamples=2; break;
      case ID_MULTISAMPLE_4X : nsamples=4; break;
   }
   glcanvas->destroy();
   glvisual->destroy();
   glvisual->setMultiSamples(nsamples);
   glvisual->create();
   if ( glvisual->getActualMultiSamples() != nsamples ) {
      sender->handle(this, FXSEL(SEL_COMMAND, ID_DISABLE), nullptr);
   }
   glcanvas->create();
   return 1;
}

// update multisampling radio buttons
long TestWindow::onUpdMultiSample(FXObject* sender, FXSelector sel, void*)
{
   FXbool check = false;
   switch(FXSELID(sel)) {
      case ID_MULTISAMPLE_OFF: if(glvisual->getActualMultiSamples()!=2 && glvisual->getActualMultiSamples()!=4) check=true; break;
      case ID_MULTISAMPLE_2X : if(glvisual->getActualMultiSamples()==2) check=true; break;
      case ID_MULTISAMPLE_4X : if(glvisual->getActualMultiSamples()==4) check=true; break;
   }
   if (check)
      sender->handle(this, FXSEL(SEL_COMMAND, ID_CHECK), nullptr);
   else
      sender->handle(this, FXSEL(SEL_COMMAND, ID_UNCHECK), nullptr);
   return 1;
}

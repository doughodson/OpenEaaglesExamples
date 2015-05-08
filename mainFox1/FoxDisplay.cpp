
#include "FoxDisplay.h"

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basicGL/Polygon.h"

#include <GL/glu.h>

#include "fx.h"
#include "fx3d.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(FoxDisplay,"FoxDisplay")
EMPTY_SERIALIZER(FoxDisplay)

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
FoxDisplay::FoxDisplay()
{
   STANDARD_CONSTRUCTOR()
   initData();
}

void FoxDisplay::initData()
{
  glCanvas = 0;
  glVisual = 0;
  myComp = 0;
  rotate = false;
  rotAng = 0;
  rotRate = 0.05f;
  translate = false;
  trans = 0;
  transRate = 0.10f;
}

//------------------------------------------------------------------------------
// copyData() -- copy this object's data
//------------------------------------------------------------------------------
void FoxDisplay::copyData(const FoxDisplay& org, const bool cc)
{
   BaseClass::copyData(org);
   if (cc) {
      initData();
   }
   rotate = org.rotate;
   rotAng = org.rotAng;
   rotRate = org.rotRate;
   translate = org.translate;
   trans = org.trans;
   transRate = org.transRate;
}

//------------------------------------------------------------------------------
// deleteData() -- delete this object's data
//------------------------------------------------------------------------------
void FoxDisplay::deleteData()
{
   if (glVisual != 0)
      delete glVisual;
   glVisual = 0;
   glCanvas = 0;
   delete myComp;
}

//------------------------------------------------------------------------------
// bind() -- bind Fox Toolkit canvas and visual objects with this class
//------------------------------------------------------------------------------
void FoxDisplay::create(FX::FXApp* app, FX::FXComposite* const frame, FX::FXObject* tgt,
                     unsigned short selector, unsigned short opt, unsigned short x,
                     unsigned short y, unsigned short w, unsigned short h)
{
   myComp = frame;
#ifdef FOX_1_6
   glVisual = new FXGLVisual(app, VISUAL_DOUBLEBUFFER);
#else
   glVisual = new FXGLVisual(app, VISUAL_DOUBLE_BUFFER);
#endif
   glCanvas = new FXGLCanvas(frame, glVisual, tgt, selector, opt, x, y, w, h);
}

//------------------------------------------------------------------------------
// initialize() -- initialize the canvases
//------------------------------------------------------------------------------
void FoxDisplay::initialize()
{
   if (glCanvas != 0) {
      if (!glCanvas->isCurrent()) {
         glCanvas->makeCurrent();
      }
      loadTextures();
   }
}

//------------------------------------------------------------------------------
// toggleRotation()
//------------------------------------------------------------------------------
void FoxDisplay::toggleRotation()
{
   rotate = !rotate;
}

//------------------------------------------------------------------------------
// toggleTranslation()
//------------------------------------------------------------------------------
void FoxDisplay::toggleTranslation()
{
   translate = !translate;
}

//------------------------------------------------------------------------------
// updateData()
//------------------------------------------------------------------------------
void FoxDisplay::updateData(const LCreal dt)
{
   BaseClass::updateData(dt);

   // now if we are rotating, drive our rotation around (radians)
   if (rotate) {
      rotAng += rotRate;
      if (rotAng >= 6.28f) {
         rotAng = 0;
      }
   }
   if (translate) {
      trans += transRate;
      if (trans > 5.0f) {
         trans = 5.0;
         transRate = -transRate;
      }
      if (trans < -5.0f) {
         trans = -5.0f;
         transRate = -transRate;
      }
   }
}


//------------------------------------------------------------------------------
// setCanvasSize() - set our gl canvas width and height
//------------------------------------------------------------------------------
bool FoxDisplay::setCanvasSize(const float newW, const float newH)
{
   if (glCanvas != 0) {
      glCanvas->setWidth((FX::FXint)newW);
      glCanvas->setHeight((FX::FXint)newH);
   }
   return true;
}

//-----------------------------------------------------------------------------
// reshapeIt() -- default function to reshape the viewport
//-----------------------------------------------------------------------------
void FoxDisplay::reshapeIt(int, int)
{
   if (glCanvas != 0) {
      if (!glCanvas->isCurrent()) {
         glCanvas->makeCurrent();
      }
      // tell our canvas what size we are
      glCanvas->setWidth(myComp->getWidth());
      glCanvas->setHeight(myComp->getHeight());
      BaseClass::reshapeIt(glCanvas->getWidth(), glCanvas->getHeight());
   }
}

//-----------------------------------------------------------------------------
// drawIt() -- default function to draw the display
//-----------------------------------------------------------------------------
void FoxDisplay::drawIt()
{
   if (glCanvas != 0) {
      if (!glCanvas->isCurrent()) {
         glCanvas->makeCurrent();
      }
      // if we are rotating, get our graphic and rotate it
      Basic::Pair* p = (Basic::Pair*)findByType(typeid(BasicGL::Polygon));
      if (p != 0) {
         BasicGL::Polygon* g = dynamic_cast<BasicGL::Polygon*>(p->object());
         if (g != 0) {
            g->lcSaveMatrix();
            g->lcTranslate(trans, 0);
            g->lcRotate(rotAng);
            BaseClass::drawIt();
            g->lcRestoreMatrix();
         }
      }
   }
}

//------------------------------------------------------------------------------
// swapBuffers() --
//------------------------------------------------------------------------------
void FoxDisplay::swapBuffers()
{
   if (glVisual != 0 && glCanvas != 0) {
      if(glVisual->isDoubleBuffer()) glCanvas->swapBuffers();
   }
}

BasicGL::Graphic* FoxDisplay::pick(const int mouseX, const int mouseY, const int item)
{
   GLint viewport[4];

   // get our canvas and make it current
   getCanvas()->makeCurrent();
   //glGetIntegerv(GL_VIEWPORT,viewport);
   getViewport(&viewport[0], &viewport[1], &viewport[2], &viewport[3]);

   int x = mouseX;
   int y = mouseY;

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();  
   gluPickMatrix(x, y, 10, 10, viewport);
   GLdouble tl = 0, tr = 0, tb = 0, tt = 0, tn = 0, tf = 0;
   getOrtho(tl, tr, tb, tt, tn, tf);
   glOrtho(tl, tr, tb, tt, tn, tf);

   //std::cout << "viewport is " << viewport[2] << " " << viewport[3] << std::endl; 
   glMatrixMode(GL_MODELVIEW);

   GLuint sbuff[100];
   clearSelectBuffer(sbuff,100);
   glSelectBuffer(100, sbuff);

   glRenderMode(GL_SELECT);
   draw();
   glRenderMode(GL_RENDER);

   printSelectBuffer(sbuff,100);
   Graphic* selected = findSelected(sbuff,100,item);
    
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);  
   getCanvas()->makeNonCurrent();

   return selected;
}

//-----------------------------------------------------------------------------
// clearSelectBuffer() -- clears our pick select buffer
//-----------------------------------------------------------------------------
void FoxDisplay::clearSelectBuffer(GLuint sbuff[], const int size)
{
   for (int j = 0; j < size; j++) sbuff[j] = 0;
}

//-----------------------------------------------------------------------------
// findSelected() -- find the selected graphic from the 'select buffer'.
//
// 1) When item == 0, returns nearest (by depth buffer) entry.
// 2) When item < 0, returns furthest (by depth buffer) entry.
// 3) When item > 0, returns the item'th selected entry or the first entry if
//    there are less than 'item' entries
// 4) Returns zero(0) when there are no entries in the select buffer or if the
//    Graphic for the select ID is not found.
//-----------------------------------------------------------------------------
BasicGL::Graphic* FoxDisplay::findSelected(const GLuint sbuff[], const int size, const int item)
{
   BasicGL::Graphic* sel = 0;
   GLuint id = 0;

   GLuint dmin = 0;
   GLuint dmax = 0;
   int cnt = 0;
   int idx = 0;
   while (idx < size && sbuff[idx] > 0) {
      int n = sbuff[idx++];           // Number of select names
      GLuint xmin = sbuff[idx++];     // Min Depth
      GLuint xmax = sbuff[idx++];     // Max Depth
        
      // First select name only
      GLuint xId = sbuff[idx++];
      for (int i = 1; i < n; i++) { idx++; }
        
      if (cnt == 0) {
         // First item
         id = xId;
         dmin = xmin;
         dmax = xmax;
      }
      else if (item == 0 && xmin < dmin) {
         // Nearest --
         dmin = xmin;
         id = xId;
      }
      else if (item < 0 && xmax > dmax) {
         // Nearest --
         dmax = xmax;
         id = xId;
      }
      else if (item == (cnt+1)) {
         id = xId;
      }
      cnt++;
   }
    
   // Find the Graphic with this id
   if (id > 0) {
      //std::cout << "selected id = " << id << std::endl;
      Basic::Pair* pair = findBySelectName(id);
      if (pair != 0) {
         sel = dynamic_cast<BasicGL::Graphic*>(pair->object());
         if (sel != 0) {
            return sel;
         }
      }
   }
   return sel;
}

// printSelectBuffer() -- print the selection buffer
void FoxDisplay::printSelectBuffer(const GLuint sbuff[], const int size)
{
   //std::cout << "printSelectBuffer: " << std::endl;
   int idx = 0;
   while (idx < size && sbuff[idx] > 0) {
      int n = sbuff[idx++];
      std::cout << "Hit: " << n << " ( " << sbuff[idx++] << "," << sbuff[idx++] << ") Name stack = { ";
     for (int i = 0; i < n; i++) std::cout << sbuff[idx++] << " ";
     std::cout << "}" << std::endl;
   }
   //std::cout << std::endl;
}

} // end Example namespace
} // end Eaagles namespace


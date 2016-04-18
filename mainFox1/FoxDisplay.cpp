
#include "FoxDisplay.h"

#include "openeaagles/base/Pair.h"
#include "openeaagles/graphics/Polygon.h"

#include <GL/glu.h>

#include "fx.h"
#include "fx3d.h"

namespace oe {
namespace example {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(FoxDisplay, "FoxDisplay")
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
  glCanvas = nullptr;
  glVisual = nullptr;
  myComp = nullptr;
  rotate = false;
  rotAng = 0.0;
  rotRate = 0.05;
  translate = false;
  trans = 0.0;
  transRate = 0.10;
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
   if (glVisual != nullptr)
      delete glVisual;
   glVisual = nullptr;
   glCanvas = nullptr;
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
   if (glCanvas != nullptr) {
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
void FoxDisplay::updateData(const double dt)
{
   BaseClass::updateData(dt);

   // now if we are rotating, drive our rotation around (radians)
   if (rotate) {
      rotAng += rotRate;
      if (rotAng >= 6.28) {
         rotAng = 0;
      }
   }
   if (translate) {
      trans += transRate;
      if (trans > 5.0) {
         trans = 5.0;
         transRate = -transRate;
      }
      if (trans < -5.0) {
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
   if (glCanvas != nullptr) {
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
   if (glCanvas != nullptr) {
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
   if (glCanvas != nullptr) {
      if (!glCanvas->isCurrent()) {
         glCanvas->makeCurrent();
      }
      // if we are rotating, get our graphic and rotate it
      base::Pair* p = (base::Pair*)findByType(typeid(graphics::Polygon));
      if (p != nullptr) {
         graphics::Polygon* g = dynamic_cast<graphics::Polygon*>(p->object());
         if (g != nullptr) {
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
   if (glVisual != nullptr && glCanvas != nullptr) {
      if(glVisual->isDoubleBuffer()) glCanvas->swapBuffers();
   }
}

graphics::Graphic* FoxDisplay::pick(const int mouseX, const int mouseY, const int item)
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
graphics::Graphic* FoxDisplay::findSelected(const GLuint sbuff[], const int size, const int item)
{
   graphics::Graphic* sel = nullptr;
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
      base::Pair* pair = findBySelectName(id);
      if (pair != nullptr) {
         sel = dynamic_cast<graphics::Graphic*>(pair->object());
         if (sel != nullptr) {
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

}
}


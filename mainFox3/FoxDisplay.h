
#ifndef __FoxDisplay_H__
#define __FoxDisplay_H__

#include "openeaagles/graphics/Display.h"

namespace FX {
   class FXApp;
   class FXComposite;
   class FXGLCanvas;
   class FXGLVisual;
   class FXObject;
};

//------------------------------------------------------------------------------
// Class: FoxDisplay
//
// Description:  Handles the drawing of an OpenEaagles display within Fox
//------------------------------------------------------------------------------
class FoxDisplay : public oe::graphics::Display
{
   DECLARE_SUBCLASS(FoxDisplay, oe::graphics::Display)

public:

   FoxDisplay();

   // Create with the Fox toolkit
   virtual void create(FX::FXApp* app, FX::FXComposite* const frame, FX::FXObject* tgt, unsigned short selector,
         unsigned short opt, unsigned short x = 0, unsigned short y = 0, unsigned short w = 0, unsigned short h = 0);

   // initialize our display
   virtual void initialize();

   virtual void reshapeIt(int w, int h) override;
   virtual void drawIt() override;
   virtual void swapBuffers() override;

   virtual bool setCanvasSize(const float newW = 0, const float newH = 0);

   virtual void updateData(const double dt = 0.0) override;

   // mouse event to handle the pick event
   oe::graphics::Graphic* pick(const int mouseX = 0, const int mouseY = 0, const int item = -1);
   void printSelectBuffer(const GLuint sbuff[], const int size);
   void clearSelectBuffer(GLuint sbuff[], const int size);
   oe::graphics::Graphic* findSelected(const GLuint sbuff[], const int size, const int item = 0);

   FX::FXGLCanvas* getCanvas()                                          { return glCanvas; };
   FX::FXComposite* getParentWindow()                                   { return myComp;   };

   // interface for the fox main window to manipulate our graphics - YOU CAN PULL THIS OUT!
   virtual void toggleRotation();
   virtual void toggleTranslation();

protected:

   void initData();

private:

   FX::FXGLCanvas*  glCanvas;          // Fox toolkit's GL Canvas
   FX::FXGLVisual*  glVisual;          // Fox toolkit's OpenGL visual
   FX::FXComposite* myComp;            // our parent

   bool rotate;                        // is our graphic rotating
   double rotAng;                      // rotate angle
   double rotRate;                     // rotate rate
   bool translate;                     // are we translating
   double trans;                       // transform amount (units)
   double transRate;
};

#endif

//------------------------------------------------------------------------------
// Class:  Display
// Base class:  Object -> Component -> Graphic -> Page -> Display -> Eaagles::mainFox::Display
//
// Description:  This Display handles the drawing and interface of the FOX Toolikit 
// drawing method
//
//------------------------------------------------------------------------------
#ifndef __Display_H__C4BE3EBD_B9CE_4747_8908_C155A470271E
#define __Display_H__C4BE3EBD_B9CE_4747_8908_C155A470271E

#include "openeaagles/basicGL/Display.h"

namespace FX {
  class FXApp;
  class FXComposite;
  class FXGLCanvas;
  class FXGLVisual;
  class FXObject;
};

namespace Eaagles {
namespace mainFox {

class Display : public BasicGL::Display {

  DECLARE_SUBCLASS(Display,BasicGL::Display)

public:

  Display();

  // Create with the Fox toolkit
  virtual void create(FX::FXApp* app, FX::FXComposite* const frame, FX::FXObject* tgt, unsigned short selector, unsigned short opt, unsigned short x =0, unsigned short y = 0, unsigned short w = 0, unsigned short h = 0);  

  // initialize our display
  virtual void initialize();  

  // Display interface
  virtual void reshapeIt(int w, int h);
  virtual void drawIt();
  virtual void swapbuffers();
  virtual bool setCanvasSize(const float newW = 0, const float newH = 0);
    
  // Component interface
  virtual void updateData(const LCreal dt = 0.000000);
 
//  FX::FXApp* getFoxApp()  { return myApp; }

  // mouse event to handle the pick event
  Graphic* pick(const int mouseX = 0, const int mouseY = 0, const int item = -1); 
  void printSelectBuffer(const GLuint sbuff[], const int size);
  void clearSelectBuffer(GLuint sbuff[], const int size);
  BasicGL::Graphic* findSelected(const GLuint sbuff[], const int size, const int item = 0);
  FX::FXGLCanvas* getCanvas()     { return glCanvas; };
  FX::FXComposite* getParentWindow()  { return myComp; };
    
  // interface for the fox main window to manipulate our graphics - YOU CAN PULL THIS OUT!
  virtual void toggleRotation();
  virtual void toggleTranslation();

private:

  FX::FXGLCanvas*  glCanvas;          // Fox toolkit's GL Canvas
  FX::FXGLVisual*  glVisual;          // Fox toolkit's OpenGL visual
//  FX::FXApp*       myApp;             // Fox toolkit's Application pointer
  FX::FXComposite* myComp;            // our parent

  bool rotate;                        // is our graphic rotating
  LCreal rotAng;                      // rotate angle
  LCreal rotRate;                     // rotate rate
  bool translate;                     // are we translating
  LCreal trans;                       // transform amount (units)
  LCreal transRate;
};

} // end mainFox namespace
} // end Eaagles namespace

#endif	/* __Display_H__C4BE3EBD_B9CE_4747_8908_C155A470271E */


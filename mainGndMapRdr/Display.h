// ----------------------------------------------------------------------------
// Class: Display
//
// Description: Displays an image of a radar beam return
//
// Factory name: RbrDisplay
//
// Slots:
//    textureTest <Boolean>   Texture test enabled
// ----------------------------------------------------------------------------
#ifndef __Eaagles_Example_Display_H__
#define __Eaagles_Example_Display_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {

  namespace Basic { class Number; }
  namespace Simulation { class Player; class Simulation; class Station; }

namespace Example {

class Display : public Glut::GlutDisplay
{
   DECLARE_SUBCLASS(Display, Glut::GlutDisplay)

public:
   Display();

    Simulation::Player* getOwnship();
    Simulation::Simulation* getSimulation();
    Simulation::Station* getStation();

   // Slot functions
   virtual bool setSlotTextureTest(const Basic::Number* const msg);

   // GlutDisplay interface
   virtual void configure();

   // BasicGL::Graphic interface
   virtual void drawFunc(); 

private: 
   SPtr<Simulation::Station> myStation;

   bool              testTexture;      // Texture image test
   GLuint            texture;          // Texture
};

}; // end Example namespace
}; // end Eaagles namespace

#endif


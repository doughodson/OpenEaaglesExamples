// ----------------------------------------------------------------------------
// Display
// Class: Eaagles::BasicGL::GlutDisplay -> Eaagles::MainGm::Display
//
// Description: Displays an image of a radar beam return
//
// Form name: RbrDisplay
//
// Slots:
//    textureTest <Boolean>   Texture test enabled
//
// ----------------------------------------------------------------------------
#ifndef EAAGLES_MAINGNDMAPRDR_DISPLAY_H
#define EAAGLES_MAINGNDMAPRDR_DISPLAY_H

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {

  namespace Basic { class Number; }
  namespace Simulation { class Player; class Simulation; class Station; }

namespace MainGndMapRdr {

class Display : public Glut::GlutDisplay {
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

}; // end MainGm namespace
}; // end Eaagles namespace

#endif


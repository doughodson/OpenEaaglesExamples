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
#ifndef __oe_example_Display_H__
#define __oe_example_Display_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace oe {

namespace Basic { class Number; }
namespace Simulation { class Player; class Simulation; class Station; }

namespace example {

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

   virtual void configure() override;
   void drawFunc() override;

private:
   Basic::safe_ptr<Simulation::Station> myStation;

   bool   testTexture;      // Texture image test
   GLuint texture;          // Texture
};

}; // end example namespace
}; // end oe namespace

#endif


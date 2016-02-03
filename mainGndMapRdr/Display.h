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

namespace basic { class Number; }
namespace simulation { class Player; class Simulation; class Station; }

namespace example {

class Display : public glut::GlutDisplay
{
   DECLARE_SUBCLASS(Display, glut::GlutDisplay)

public:
   Display();

   simulation::Player* getOwnship();
   simulation::Simulation* getSimulation();
   simulation::Station* getStation();

   // Slot functions
   virtual bool setSlotTextureTest(const basic::Number* const msg);

   virtual void configure() override;
   void drawFunc() override;

private:
   basic::safe_ptr<simulation::Station> myStation;

   bool   testTexture;      // Texture image test
   GLuint texture;          // Texture
};

}; // end example namespace
}; // end oe namespace

#endif


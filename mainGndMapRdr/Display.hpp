
#ifndef __Display_H__
#define __Display_H__

#include "openeaagles/gui/glut/GlutDisplay.hpp"

namespace oe {
namespace base { class Number; }
namespace models { class Player; }
namespace simulation { class Simulation; class Station; }
}

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
class Display : public oe::glut::GlutDisplay
{
   DECLARE_SUBCLASS(Display, oe::glut::GlutDisplay)

public:
   Display();

   oe::models::Player* getOwnship();
   oe::simulation::Simulation* getSimulation();
   oe::simulation::Station* getStation();

   // Slot functions
   virtual bool setSlotTextureTest(const oe::base::Number* const msg);

   virtual void configure() override;
   virtual void drawFunc() override;

private:
   oe::base::safe_ptr<oe::simulation::Station> myStation;

   bool   testTexture;      // Texture image test
   GLuint texture;          // Texture
};

#endif

// ----------------------------------------------------------------------------
// Class: Display
// ----------------------------------------------------------------------------
#include "Display.h"
#include "RealBeamRadar.h"

#include "openeaagles/simulation/Player.h"
#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/simulation/Station.h"

#include "openeaagles/basic/Color.h"
#include "openeaagles/basic/Rgb.h"
#include "openeaagles/basic/Hsva.h"
#include "openeaagles/basic/Color.h"
#include "openeaagles/basic/Number.h"
#include "openeaagles/basic/String.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/units/Distances.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_SUBCLASS(Display,"RbrDisplay")
EMPTY_SERIALIZER(Display)

BEGIN_SLOTTABLE(Display)
   "textureTest",    //  1) Texture test enabled
END_SLOTTABLE(Display)

BEGIN_SLOT_MAP(Display)
   ON_SLOT( 1, setSlotTextureTest, Basic::Number)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Display::Display()
{
   STANDARD_CONSTRUCTOR()

   myStation = 0;
   testTexture = 0;
   texture = 0;
}

//------------------------------------------------------------------------------
// copyData() -- copy our objects data
//------------------------------------------------------------------------------
void Display::copyData(const Display& org, const bool cc)
{
   BaseClass::copyData(org);

   if (cc) {
      myStation = 0;
      testTexture = 0;
      texture = 0;
   }
}

//------------------------------------------------------------------------------
// deleteData() -- copy our objects data
//------------------------------------------------------------------------------
void Display::deleteData()
{
   // Free the texture
   if (texture != 0) {
      glDeleteTextures(1,&texture);
      texture = 0;
   }
}

//------------------------------------------------------------------------------
// Simulation access functions
//------------------------------------------------------------------------------
Simulation::Player* Display::getOwnship()
{
    Simulation::Player* p = 0;
    Simulation::Station* sta = getStation();
    if (sta != 0) p = sta->getOwnship();
    return p;
}

Simulation::Simulation* Display::getSimulation()
{
    Simulation::Simulation* s = 0;
    Simulation::Station* sta = getStation();
    if (sta != 0) s = sta->getSimulation();
    return s;
}

Simulation::Station* Display::getStation()
{
    if (myStation == 0) {
        Simulation::Station* s = dynamic_cast<Simulation::Station*>( findContainerByType(typeid(Simulation::Station)) );
        if (s != 0) myStation = s;
    }
    return myStation;
}

//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------

// Set texture test flag
bool Display::setSlotTextureTest(const Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0) {
      testTexture = msg->getBoolean();
      ok = true;
   }
   return ok;
}


//------------------------------------------------------------------------------
// drawFunc()
//------------------------------------------------------------------------------
void Display::drawFunc()
{
   Simulation::Player* own = getOwnship();

   const Basic::Pair* pair = 0;
   if (own != 0) pair = own->getSensorByType(typeid(RealBeamRadar));

   const RealBeamRadar* rdr = 0;
   if (pair != 0) rdr = (const RealBeamRadar*)( pair->object() );

   const GLubyte* image = 0;  // The image pixels 
   if (rdr != 0) image = rdr->getImage();

   if (image != 0) {

      // Image width  (number of columns)
      GLsizei imgWidth = rdr->getImageWidth();

      // Image height (number of rows)
      GLsizei imgHeight = rdr->getImageHeight();

      GLint pixelSize = rdr->getPixelSize();
      GLenum format = GL_RGB;
      if (pixelSize == 4) format = GL_RGBA;

      if (testTexture) {
         // ---
         // Draw using texture map
         // ---

         glEnable(GL_TEXTURE_2D);
         glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

         if (texture == 0) {
            glGenTextures(1,&texture);
         }

         glBindTexture(GL_TEXTURE_2D, texture);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
         glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

//         double start = getComputerTime();

         glTexImage2D(GL_TEXTURE_2D, 0, pixelSize, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, image);

         // B SCAN
         glBegin(GL_POLYGON);

            glTexCoord2f( 1.0f, 1.0f );
            glVertex2f(  1.0f,  1.0f );

            glTexCoord2f( 0.0f, 1.0f );
            glVertex2f( 0.0f, 1.0f );

            glTexCoord2f( 0.0f, 0.0f );
            glVertex2f(  0.0f, 0.0f );

            glTexCoord2f( 1.0f, 0.0f );
            glVertex2f( 1.0f, 0.0f );

         glEnd();

         glDisable(GL_TEXTURE_2D);
//         double end = getComputerTime();
//         double dtime = (end - start);
         //std::cout << "glTexImage2D() dtime = " << dtime << std::endl;
      }
      else {
         // ---
         // Draw using glDrawPixels()
         // ---

         glRasterPos2f(0.0, 0.0);

//         double start = getComputerTime();

         glDrawPixels(imgWidth, imgHeight, format, GL_UNSIGNED_BYTE, image);

//         double end = getComputerTime();
//         double dtime = (end - start);
         //std::cout << "glDrawPixels() dtime = " << dtime << std::endl;
      }
   }
}

//-----------------------------------------------------------------------------
// configureIt() -- function to configure the display
//-----------------------------------------------------------------------------
void Display::configure()
{
   BaseClass::configure();

   // Turn off anti-aliasing
   glDisable(GL_POINT_SMOOTH);
   glDisable(GL_LINE_SMOOTH);
   glDisable(GL_POLYGON_SMOOTH);
   glDisable(GL_BLEND);
   glBlendFunc(GL_ONE,  GL_ZERO);
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
Basic::Object* Display::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}

}; // end Example namespace
}; // end Eaagles namespace


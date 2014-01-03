// ----------------------------------------------------------------------------
// Display
//
// Description: Displays an image of a terrain database
//
// Factory name: TerrainDisplay
//
// Slots:
//    terrain        <Simulation::Terrain>  The terrain elevation database
//    minElevation   <Distance>  Minimum elevation (Distance) (default: use database max value)
//    maxElevation   <Distance>  Maximum elevation (Distance) (default: use database max value)
//    altitude       <Distance>  Reference altitude (Distance) (default: 15000 feet)
//    lookAngle      <Angle>     Antenna look angle (Angle) (default: 0 degrees)
//    beamWidth      <Angle>     Antenna Beam Width (Angle) (default: 180 degrees)
//    colorScale     <Number>    Color scale:  gray(0), color(1), green(2) (default: gray)
//    interpolate    <Boolean>   Interpolate flag (default: false)
//    shadows        <Boolean>   Shadow test enabled
//    aac            <Boolean>   Aspect Angle test enabled
//    earthCurvature <Boolean>   Earth curvature test enabled
//    textureTest    <Boolean>   Texture test enabled
//
// ----------------------------------------------------------------------------
#ifndef __Eaagles_Example_Display_H__
#define __Eaagles_Example_Display_H__

#include "openeaagles/gui/glut/GlutDisplay.h"

namespace Eaagles {
   namespace Basic { class Angle; class Distance; class Number; class Terrain; }

namespace Example {

class MainWindow;

class Display : public Glut::GlutDisplay {
   DECLARE_SUBCLASS(Display, Glut::GlutDisplay)

public:
   enum { GRAY_SCALE, COLOR_SCALE, GREEN_SCALE };

public:
   Display();

   const Basic::Terrain* getTerrain() const      { return terrain; }

   bool isMinElevValid() const { return haveMinElev; }      // Ture if the min elevation is valid
   LCreal getMinElevation() const { return minElev; }       // Returns the min elevation (meters)
   virtual bool setMinElevation(const LCreal elev);         // Sets the min elevation (meters)
   virtual bool clearMinElevation();                        // Clears the min elevation (using datafile min elevation)

   bool isMaxElevValid() const { return haveMaxElev; }      // Ture if the max elevation is valid
   LCreal getMaxElevation() const { return maxElev; }       // Returns the max elevation (meters)
   virtual bool setMaxElevation(const LCreal elev);         // Sets the max elevation (meters)
   virtual bool clearMaxElevation();                        // Clears the max elevation (using datafile max elevation)

   // Slot functions
   virtual bool setSlotTerrain(Basic::Terrain* const msg);
   virtual bool setSlotMinElevation(const Basic::Distance* const msg);
   virtual bool setSlotMaxElevation(const Basic::Distance* const msg);
   virtual bool setSlotAltitude(const Basic::Distance* const msg);
   virtual bool setSlotLookAngle(const Basic::Angle* const msg);
   virtual bool setSlotBeamWidth(const Basic::Angle* const msg);
   virtual bool setSlotColorScale(const Basic::Number* const msg);
   virtual bool setSlotInterpolate(const Basic::Number* const msg);
   virtual bool setSlotShadowsTest(const Basic::Number* const msg);
   virtual bool setSlotAacTest(const Basic::Number* const msg);
   virtual bool setSlotEarthCurvatureTest(const Basic::Number* const msg);
   virtual bool setSlotTextureTest(const Basic::Number* const msg);

   // GlutDisplay interface
   virtual void configure();

   // BasicGL::Graphic interface
   virtual void drawFunc(); 

   // Basic::Component interface
   virtual void reset();
   virtual void updateData(const LCreal dt = 0.0);

private:
   bool initImageMemory(const GLsizei width, const GLsizei height);
   bool copyImageMemory(const Display& org);
   void freeImageMemory();

   Basic::Terrain* terrain;            // Terrain data
   LCreal            maxElev;          // Max elevation (meters)
   LCreal            minElev;          // Min elevation (meters)
   LCreal            altitude;         // Ref altitude (meters)
   LCreal            lookAngle;        // Antenna look angle (degs)
   LCreal            beamWidth;        // Antenna beam width (degs)
   unsigned int      colorScale;       // Color scale index; gray(0), color(1), green(2)
   bool              haveMaxElev;      // Have a maximum elevation flag
   bool              haveMinElev;      // Have a maximum elevation flag
   bool              interpolate;      // Interpolate flag
   bool              testShadows;      // Shadow test enabled
   bool              testAac;          // AAC test enabled
   bool              testEarthCurv;    // Earth curvature test enabled
   bool              testTexture;      // Texture image test

   static const GLsizei MAX_IMAGE_WIDTH  = 2048; // maximum image width
   static const GLsizei MAX_IMAGE_HEIGHT = 2048; // maximum image height
   static const GLsizei PIXEL_SIZE = 3; // pixel size in bytes { RGB }

   GLuint            texture;          // Texture
   GLsizei           imgWidth;         // Image width  (number of columns)
   GLsizei           imgHeight;        // Image height (number of rows)
   GLubyte*          image;            // The image pixels 
                                       //   -- access individual pixels by mainImage[icol*imgWidth*PIZEL_SIZE + irow*PIZEL_SIZE]
                                       //   --   irow : [ 0 ... (imgHeight-1) ]
                                       //   --   icol : [ 0 ... (imgWidth-1) ]
};

}; // end Example namespace
}; // end Eaagles namespace

#endif


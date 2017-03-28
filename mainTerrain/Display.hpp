
#ifndef __Display_H__
#define __Display_H__

#include "openeaagles/gui/glut/GlutDisplay.hpp"
#include "openeaagles/base/units/distance_utils.hpp"

namespace oe {
namespace base { class Angle; class Distance; class Number; }
namespace terrain { class Terrain; }
}

class MainWindow;

// ----------------------------------------------------------------------------
// Display
//
// Description: Displays an image of a terrain database
//
// Factory name: TerrainDisplay
//
// Slots:
//    terrain        <terrain::Terrain>     ! The terrain elevation database
//    minElevation   <Distance>             ! Minimum elevation (Distance) (default: use database max value)
//    maxElevation   <Distance>             ! Maximum elevation (Distance) (default: use database max value)
//    altitude       <Distance>             ! Reference altitude (Distance) (default: 15000 feet)
//    lookAngle      <Angle>                ! Antenna look angle (Angle) (default: 0 degrees)
//    beamWidth      <Angle>                ! Antenna Beam Width (Angle) (default: 180 degrees)
//    colorScale     <Number>               ! Color scale:  gray(0), color(1), green(2) (default: gray)
//    interpolate    <Boolean>              ! Interpolate flag (default: false)
//    shadows        <Boolean>              ! Shadow test enabled
//    aac            <Boolean>              ! Aspect Angle test enabled
//    earthCurvature <Boolean>              ! Earth curvature test enabled
//    textureTest    <Boolean>              ! Texture test enabled
//
// ----------------------------------------------------------------------------
class Display : public oe::glut::GlutDisplay
{
   DECLARE_SUBCLASS(Display, oe::glut::GlutDisplay)

public:
   enum class ColorDepth {GRAY=0, COLOR=1, GREEN=2};

public:
   Display();

   const oe::terrain::Terrain* getTerrain() const              { return terrain; }

   bool isMinElevValid() const { return haveMinElev; }      // Ture if the min elevation is valid
   double getMinElevation() const { return minElev; }       // Returns the min elevation (meters)
   virtual bool setMinElevation(const double elev);         // Sets the min elevation (meters)
   virtual bool clearMinElevation();                        // Clears the min elevation (using datafile min elevation)

   bool isMaxElevValid() const { return haveMaxElev; }      // Ture if the max elevation is valid
   double getMaxElevation() const { return maxElev; }       // Returns the max elevation (meters)
   virtual bool setMaxElevation(const double elev);         // Sets the max elevation (meters)
   virtual bool clearMaxElevation();                        // Clears the max elevation (using datafile max elevation)

   // Slot functions
   virtual bool setSlotTerrain(oe::terrain::Terrain* const msg);
   virtual bool setSlotMinElevation(const oe::base::Distance* const msg);
   virtual bool setSlotMaxElevation(const oe::base::Distance* const msg);
   virtual bool setSlotAltitude(const oe::base::Distance* const msg);
   virtual bool setSlotLookAngle(const oe::base::Angle* const msg);
   virtual bool setSlotBeamWidth(const oe::base::Angle* const msg);
   virtual bool setSlotColorScale(const oe::base::Number* const msg);
   virtual bool setSlotInterpolate(const oe::base::Number* const msg);
   virtual bool setSlotShadowsTest(const oe::base::Number* const msg);
   virtual bool setSlotAacTest(const oe::base::Number* const msg);
   virtual bool setSlotEarthCurvatureTest(const oe::base::Number* const msg);
   virtual bool setSlotTextureTest(const oe::base::Number* const msg);

   virtual void configure() override;
   virtual void drawFunc() override;

   virtual void reset() override;
   virtual void updateData(const double dt = 0.0) override;

private:
   bool initImageMemory(const GLsizei width, const GLsizei height);
   bool copyImageMemory(const Display& org);
   void freeImageMemory();

   oe::terrain::Terrain* terrain {};                      // Terrain data

   double maxElev {15000.0 * oe::base::distance::FT2M};   // Max elevation (meters)
   double minElev {};                                     // Min elevation (meters)
   double altitude {15000.0 * oe::base::distance::FT2M};  // Ref altitude (meters)
   double lookAngle {};                                   // Antenna look angle (degs)
   double beamWidth {180.0};                              // Antenna beam width (degs)
   ColorDepth colorDepth {ColorDepth::GRAY};              // Color scale index; gray, color, green
   bool haveMaxElev {};                                   // Have a maximum elevation flag
   bool haveMinElev {};                                   // Have a maximum elevation flag
   bool interpolate {};                                   // Interpolate flag
   bool testShadows {};                                   // Shadow test enabled
   bool testAac {};                                       // AAC test enabled
   bool testEarthCurv {};                                 // Earth curvature test enabled
   bool testTexture {};                                   // Texture image test

   static const GLsizei MAX_IMAGE_WIDTH  = 2048; // maximum image width
   static const GLsizei MAX_IMAGE_HEIGHT = 2048; // maximum image height
   static const GLsizei PIXEL_SIZE = 3;          // pixel size in bytes { RGB }

   GLuint   texture {};          // Texture
   GLsizei  imgWidth {};         // Image width  (number of columns)
   GLsizei  imgHeight {};        // Image height (number of rows)
   GLubyte* image {};            // The image pixels
                                 //   -- access individual pixels by mainImage[icol*imgWidth*PIZEL_SIZE + irow*PIZEL_SIZE]
                                 //   --   irow : [ 0 ... (imgHeight-1) ]
                                 //   --   icol : [ 0 ... (imgWidth-1) ]
};

#endif

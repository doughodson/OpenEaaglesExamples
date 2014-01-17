//------------------------------------------------------------------------------
// Class: RealBeamRadar
//
// Description: Real-Beam Radar Model
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_RealBeamRadar_H__
#define __Eaagles_Example_RealBeamRadar_H__

#include "openeaagles/simulation/Radar.h"

namespace Eaagles {
   namespace Basic { class Angle; class Distance; class Number; class Terrain; }

namespace Example {

class RealBeamRadar : public Simulation::Radar
{
    DECLARE_SUBCLASS(RealBeamRadar,Simulation::Radar)

public:
    RealBeamRadar();

   const Basic::Terrain* getTerrain() const                      { return terrain; }
   virtual bool setTerrain(const Basic::Terrain* const msg);

   LCreal getAltitude() const                { return altitude; }    // Ref altitude (meters)
   LCreal getAntennaAzimuthAngle() const     { return antAzAngle; }  // Antenna look angle (degs)
   LCreal getAntennaElevationAngle() const   { return antElAngle; }  // Antenna look angle (degs)
   LCreal getBeamWidth() const               { return beamWidth; }   // Antenna beam width (degs)

   // The RADAR image pixels 
   //   -- access individual pixels by mainImage[icol*imgWidth*PIZEL_SIZE + irow*PIZEL_SIZE]
   //   --   irow : [ 0 ... (imgHeight-1) ]
   //   --   icol : [ 0 ... (imgWidth-1) ]
   const unsigned char* getImage() const { return image; }

   int getImageWidth() const  { return imgWidth; }          // RADAR Image width  (number of columns)
   int getImageHeight() const { return imgHeight; }         // RADAR Image height (number of rows)
   int getPixelSize() const   { return PIXEL_SIZE; }        // Number of components (RGBA) in each image pixel

   // Slot functions
   virtual bool setSlotInterpolate(const Basic::Number* const msg);

   // Compute earth curvature effects
   static bool computeGroundRanges(LCreal* const groundRange, const unsigned int n, const LCreal maxRngNM);
   static bool computeSlantRanges2(LCreal* const slantRange2, const unsigned int n, const LCreal* const gndRng, const LCreal altitude);
   static bool computeRangeLoss(LCreal* const rangeLoss, const unsigned int n, const LCreal* const slantRange2);
   static bool computeEarthCurvature(LCreal* const curvature, const unsigned int n, const LCreal maxRngNM, const LCreal radiusNM);

protected:

   // System class -- phase callbacks
    virtual void transmit(const LCreal dt);

private:
   bool initImageMemory(const int width, const int height);
   bool copyImageMemory(const RealBeamRadar& org);
   void freeImageMemory();

   const Basic::Terrain* terrain;      // Terrain data
   LCreal            altitude;         // Ref altitude (meters)
   LCreal            antAzAngle;       // Antenna azimuth angle (degs)
   LCreal            antElAngle;       // Antenna elevation angle (degs)
   int               ray0;             // Last ray generated
   LCreal            beamWidth;        // Antenna beam width (degs)
   bool              interpolate;      // Interpolate flag
   bool              fpass;            // First pass flag

   LCreal*           elevations;       // Terrain elevations
   bool*             validFlgs;        // Terrain elevation flag flags
   LCreal*           aacData;          // Aspect angle cosines
   bool*             maskFlgs;         // Mask flags

   LCreal            antAz;                  //
   static const int MAX_IMAGE_WIDTH  = 2048; // maximum image width
   static const int MAX_IMAGE_HEIGHT = 2048; // maximum image height
   static const int PIXEL_SIZE = 3;          // pixel size in bytes { RGB }

   int             imgWidth;         // Image width  (number of columns)
   int             imgHeight;        // Image height (number of rows)
   unsigned  char* image;            // The image pixels 
                                     //   -- access individual pixels by mainImage[icol*imgWidth*PIZEL_SIZE + irow*PIZEL_SIZE]
                                     //   --   irow : [ 0 ... (imgHeight-1) ]
                                     //   --   icol : [ 0 ... (imgWidth-1) ]
};

} // end Example namespace
} // end Eaagles namespace

#endif

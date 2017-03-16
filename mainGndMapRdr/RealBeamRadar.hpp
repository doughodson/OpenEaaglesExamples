
#ifndef __RealBeamRadar_H__
#define __RealBeamRadar_H__

#include "openeaagles/models/system/Radar.hpp"

namespace oe {
namespace base { class Angle; class Distance; class Number; }
namespace terrain { class Terrain; }
}

//------------------------------------------------------------------------------
// Class: RealBeamRadar
//
// Description: Real-Beam Radar Model
//------------------------------------------------------------------------------
class RealBeamRadar : public oe::models::Radar
{
    DECLARE_SUBCLASS(RealBeamRadar, oe::models::Radar)

public:
    RealBeamRadar();

   const oe::terrain::Terrain* getTerrain() const                      { return terrain; }
   virtual bool setTerrain(const oe::terrain::Terrain* const msg);

   double getAltitude() const                     { return altitude; }    // Ref altitude (meters)
   double getAntennaAzimuthAngle() const          { return antAzAngle; }  // Antenna look angle (degs)
   double getAntennaElevationAngle() const        { return antElAngle; }  // Antenna look angle (degs)
   virtual double getBeamWidth() const override   { return beamWidth; }   // Antenna beam width (degs)

   // The RADAR image pixels
   //   -- access individual pixels by mainImage[icol*imgWidth*PIZEL_SIZE + irow*PIZEL_SIZE]
   //   --   irow : [ 0 ... (imgHeight-1) ]
   //   --   icol : [ 0 ... (imgWidth-1) ]
   const unsigned char* getImage() const { return image; }

   int getImageWidth() const  { return imgWidth; }          // RADAR Image width  (number of columns)
   int getImageHeight() const { return imgHeight; }         // RADAR Image height (number of rows)
   int getPixelSize() const   { return PIXEL_SIZE; }        // Number of components (RGBA) in each image pixel

   // Slot functions
   virtual bool setSlotInterpolate(const oe::base::Number* const msg);

   // Compute earth curvature effects
   static bool computeGroundRanges(double* const groundRange, const unsigned int n, const double maxRngNM);
   static bool computeSlantRanges2(double* const slantRange2, const unsigned int n, const double* const gndRng, const double altitude);
   static bool computeRangeLoss(double* const rangeLoss, const unsigned int n, const double* const slantRange2);
   static bool computeEarthCurvature(double* const curvature, const unsigned int n, const double maxRngNM, const double radiusNM);

protected:
   virtual void transmit(const double dt) override;

private:
   bool initImageMemory(const int width, const int height);
   bool copyImageMemory(const RealBeamRadar& org);
   void freeImageMemory();

   const oe::terrain::Terrain* terrain;  // Terrain data
   double            altitude;               // Ref altitude (meters)
   double            antAzAngle;             // Antenna azimuth angle (degs)
   double            antElAngle;             // Antenna elevation angle (degs)
   int               ray0;                   // Last ray generated
   double            beamWidth;              // Antenna beam width (degs)
   bool              interpolate;            // Interpolate flag
   bool              fpass;                  // First pass flag

   double*           elevations;       // Terrain elevations
   bool*             validFlgs;        // Terrain elevation flag flags
   double*           aacData;          // Aspect angle cosines
   bool*             maskFlgs;         // Mask flags

//   double            antAz;                  //
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

#endif

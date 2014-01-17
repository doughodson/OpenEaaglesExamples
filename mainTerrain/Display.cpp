
#include "openeaagles/basic/Color.h"
#include "openeaagles/basic/Rgb.h"
#include "openeaagles/basic/Hsva.h"
#include "openeaagles/basic/Nav.h"
#include "openeaagles/basic/Number.h"
#include "openeaagles/basic/String.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/Terrain.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/units/Distances.h"

#include "Display.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_SUBCLASS(Display,"TerrainDisplay")
EMPTY_SERIALIZER(Display)


BEGIN_SLOTTABLE(Display)
   "terrain",        //  1) Terrain database
   "minElevation",   //  2) Minimum elevation (Distance) (default: use database max value)
   "maxElevation",   //  3) Maximum elevation (Distance) (default: use database max value)
   "altitude",       //  4) Reference altitude (Distance) (default: 15000 feet)
   "lookAngle",      //  5) Antenna look angle (Angle) (default: 0 degrees)
   "beamWidth",      //  6) Antenna Beam Width (Angle) (default: 180 degrees)
   "colorScale",     //  7) Color scale:  gray(0), color(1), green(2) (default: gray)
   "interpolate",    //  8) Interpolate flag (default: false)
   "shadows",        //  9) Shadow test enabled
   "aac",            // 10) Aspect Angle test enabled
   "earthCurvature", // 11) Earth curvature test enabled
   "textureTest",    // 12) Texture test enabled
END_SLOTTABLE(Display)

BEGIN_SLOT_MAP(Display)
   ON_SLOT( 1, setSlotTerrain,       Basic::Terrain)
   ON_SLOT( 2, setSlotMinElevation,  Basic::Distance)
   ON_SLOT( 3, setSlotMaxElevation,  Basic::Distance)
   ON_SLOT( 4, setSlotAltitude,      Basic::Distance)
   ON_SLOT( 5, setSlotLookAngle,     Basic::Angle)
   ON_SLOT( 6, setSlotBeamWidth,     Basic::Angle)
   ON_SLOT( 7, setSlotColorScale,    Basic::Number)
   ON_SLOT( 8, setSlotInterpolate,   Basic::Number)
   ON_SLOT( 9, setSlotShadowsTest,   Basic::Number)
   ON_SLOT(10, setSlotAacTest,       Basic::Number)
   ON_SLOT(11, setSlotEarthCurvatureTest, Basic::Number)
   ON_SLOT(12, setSlotTextureTest, Basic::Number)
END_SLOT_MAP()

//------------------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------------------
Display::Display()
{
   STANDARD_CONSTRUCTOR()

   terrain = 0;

   maxElev = 15000.0f * Basic::Distance::FT2M;
   minElev = 0;
   altitude = 15000.0f * Basic::Distance::FT2M;
   lookAngle = 0;
   beamWidth = 180.0f;
   colorScale = 0;
   haveMaxElev = false;
   haveMinElev = false;
   interpolate = false;
   testShadows = false;
   testAac = false;
   testEarthCurv = false;
   testTexture = false;

   // the image
   image = 0;
   imgWidth = 0;
   imgHeight = 0;
   texture = 0;
}

//------------------------------------------------------------------------------
// copyData() -- copy our objects data
//------------------------------------------------------------------------------
void Display::copyData(const Display& org, const bool cc)
{
   BaseClass::copyData(org);

   if (cc) {
      terrain = 0;
      texture = 0;
      image = 0;
   }

   if (org.terrain != 0)
      setSlotTerrain( org.terrain->clone() );
   else
      setSlotTerrain( 0 );

   maxElev = org.maxElev;
   minElev = org.minElev;
   altitude = org.altitude;
   lookAngle = org.lookAngle;
   beamWidth = org.beamWidth;

   haveMaxElev = org.haveMaxElev;
   haveMinElev = org.haveMinElev;
   colorScale = org.colorScale;
   interpolate = org.interpolate;
   testShadows = org.testShadows;
   testAac = org.testAac;
   testEarthCurv = org.testEarthCurv;
   testTexture = org.testTexture;

   copyImageMemory(org);
}

//------------------------------------------------------------------------------
// deleteData() -- copy our objects data
//------------------------------------------------------------------------------
void Display::deleteData()
{
   setSlotTerrain( 0 );
   freeImageMemory();
}

//------------------------------------------------------------------------------
// reset() -- Reset the simulation & players
//------------------------------------------------------------------------------
void Display::reset()
{
   if (terrain != 0) terrain->reset();
   BaseClass::reset();
}

//------------------------------------------------------------------------------
// set functions
//------------------------------------------------------------------------------
bool Display::setMinElevation(const LCreal elev)
{
   minElev = elev;
   haveMinElev = true;
   return true;
}

bool Display::clearMinElevation()
{
   minElev = 0;
   haveMinElev = false;
   return true;
}

bool Display::setMaxElevation(const LCreal elev)
{
   maxElev = elev;
   haveMaxElev = true;
   return true;
}

bool Display::clearMaxElevation()
{
   maxElev = 0;
   haveMaxElev = false;
   return true;
}

//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------
bool Display::setSlotTerrain(Basic::Terrain* const msg)
{
   if (terrain != 0) terrain->unref();
   terrain = msg;
   if (terrain != 0) terrain->ref();
   return true;
}

// Set min elevation
bool Display::setSlotMinElevation(const Basic::Distance* const msg)
{
   bool ok = false;
   if (msg != 0) {
      ok = setMinElevation( Basic::Meters::convertStatic(*msg) );
   }
   return ok;
}

// Set max elevation
bool Display::setSlotMaxElevation(const Basic::Distance* const msg)
{
   bool ok = false;
   if (msg != 0) {
      ok = setMaxElevation( Basic::Meters::convertStatic(*msg) );
   }
   return ok;
}

// Set max elevation
bool Display::setSlotAltitude(const Basic::Distance* const msg)
{
   bool ok = false;
   if (msg != 0) {
      altitude = Basic::Meters::convertStatic(*msg);
      ok = true;
   }
   return ok;
}

// Set antenna look angle
bool Display::setSlotLookAngle(const Basic::Angle* const msg)
{
   bool ok = false;
   if (msg != 0) {
      lookAngle = (LCreal)Basic::Degrees::convertStatic(*msg);
      ok = true;
   }
   return ok;
}

// Set beam width
bool Display::setSlotBeamWidth(const Basic::Angle* const msg)
{
   bool ok = false;
   if (msg != 0) {
      beamWidth = (LCreal)Basic::Degrees::convertStatic(*msg);
      ok = true;
   }
   return ok;
}

// Set color scale flag
bool Display::setSlotColorScale(const Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0) {
      int s = msg->getInt();
      if (s >= 0 && s <= 2) {
         colorScale = s;
         ok = true;
      }
   }
   return ok;
}

// Set interpolate flag
bool Display::setSlotInterpolate(const Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0) {
      interpolate = msg->getBoolean();
      ok = true;
   }
   return ok;
}

// Set shadow test flag
bool Display::setSlotShadowsTest(const Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0) {
      testShadows = msg->getBoolean();
      ok = true;
   }
   return ok;
}

// Set AAC test flag
bool Display::setSlotAacTest(const Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0) {
      testAac = msg->getBoolean();
      ok = true;
   }
   return ok;
}

// Set earth curvature test flag
bool Display::setSlotEarthCurvatureTest(const Basic::Number* const msg)
{
   bool ok = false;
   if (msg != 0) {
      testEarthCurv = msg->getBoolean();
      ok = true;
   }
   return ok;
}


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
// updateData() -- update background data here
//------------------------------------------------------------------------------
void Display::updateData(const LCreal dt)
{
   // Get Viewport width and height
   GLsizei vpWidth = 0;
   GLsizei vpHeight = 0;
   getViewportSize(&vpWidth, &vpHeight);

   // Generate an image when we have the terrain, a view port and we don't have an image
   if ( terrain != 0 && terrain->isDataLoaded() &&
        vpWidth > 0 && vpHeight > 0 &&
        image == 0) {

      GLsizei vpWidth = 1024; // default is texture sizes
      GLsizei vpHeight = 1024;
      if (!testTexture) {
         // When not using textures, get the viewport parameters

         // Get the maximum number of points
         GLint vpX, vpY;
         getViewport(&vpX, &vpY, &vpWidth, &vpHeight);

         // Make sure width is correct for a 4 byte alignment
         GLsizei w0 = (vpWidth*PIXEL_SIZE);
         GLsizei w4 = (w0/4)*4;  // Truncate to 4 bytes
         vpWidth = w4/PIXEL_SIZE;
      }

      // Allocate the image memory
      bool ok = initImageMemory(vpWidth, vpHeight);
      if (ok) {

         const int NUM_COLUMNS = imgWidth;
         const int NUM_ROWS = imgHeight;

         // Allocating space for 'multi-point' tests 
         LCreal* elevations = 0;
         LCreal* aacData = 0;
         bool* validFlgs = 0;
         bool* maskFlgs = 0;
         if (testShadows || testAac || testEarthCurv) {
            elevations = new LCreal[NUM_ROWS];
            aacData = new LCreal[NUM_ROWS];
            validFlgs = new bool[NUM_ROWS];
            maskFlgs = new bool[NUM_ROWS];
         }

         // Max elevation (Z) value (meters)
         LCreal maxz = terrain->getMaxElevation();
         if (isMaxElevValid()) maxz = getMaxElevation();

         // Min elevation (Z) value (meters)
         LCreal minz = terrain->getMinElevation();
         if (isMinElevValid()) minz = getMinElevation();

         // Delta altitude (meters)
//         LCreal deltaElev = maxz - minz + 1;

         // Compute delta (range of) latitude and longitude
         double deltaLat = terrain->getLatitudeNE()  - terrain->getLatitudeSW();
         double deltaLon = terrain->getLongitudeNE() - terrain->getLongitudeSW();

         // Compute center position (degs)
         double cLat = terrain->getLatitudeSW()  + deltaLat / 2.0;
         double cLon = terrain->getLongitudeSW() + deltaLon / 2.0;

         // Compute distance between points with zoom factor (degs)
         double spacingLat = deltaLat / NUM_ROWS;
         double spacingLon = deltaLon / NUM_COLUMNS;

         // Generate the earth's curvature effect
         LCreal* curvature =0;
         if (testEarthCurv) {
            curvature = new LCreal[NUM_ROWS];
            LCreal radius = (LCreal) (Basic::Nav::ERAD60 * Basic::Distance::NM2M);
            LCreal maxRng = (LCreal)(deltaLat * 60.0f * Basic::Distance::NM2M);
            for (int irow = 0; irow < NUM_ROWS; irow++) {
               LCreal curRng = maxRng * LCreal(irow)/LCreal(NUM_ROWS);
               LCreal arc = curRng / radius;
               LCreal cs = 1.0f;
               LCreal c0 = lcCos(arc);
               if (c0 != 0) cs = 1.0f/c0;
               curvature[irow] = radius * (cs  - 1.0f);
            }
         }

         const Basic::Hsva* grayTable[2];
         //                   hue     sat    value  alpha
         grayTable[0] = new Basic::Hsva(  120.0f,  0.0f,  0.0f,  1.0f );  // black0
         grayTable[1] = new Basic::Hsva(  120.0f,  0.0f,  1.0f,  1.0f ); // white0

         const Basic::Hsva* colorTable[7];
         //                  hue     sat    value  alpha
         colorTable[0] = new Basic::Hsva( 240.0f,   1.0f,  1.0f,  1.0f ); // blue
         colorTable[1] = new Basic::Hsva( 180.0f,   1.0f,  1.0f,  1.0f ); // cyan
         colorTable[2] = new Basic::Hsva( 120.0f,   1.0f,  1.0f,  1.0f ); // green
         colorTable[3] = new Basic::Hsva(  60.0f,   1.0f,  1.0f,  1.0f ); // yellow
         colorTable[4] = new Basic::Hsva(   0.0f,   1.0f,  1.0f,  1.0f ); // red
         colorTable[5] = new Basic::Hsva(  300.0f,  1.0f,  1.0f,  1.0f ); // magenta
         colorTable[6] = new Basic::Hsva(  300.0f,  0.05f, 1.0f,  1.0f ); // white0


         const Basic::Hsva* greenTable[19];
         //                   hue     sat    value  alpha
         greenTable[0]  = new Basic::Hsva(  120.0f,  1.0f,  0.0f,     1.0f );
         greenTable[1]  = new Basic::Hsva(  120.0f,  1.0f,  0.0872f,  1.0f );  
         greenTable[2]  = new Basic::Hsva(  120.0f,  1.0f,  0.1736f,  1.0f ); 
         greenTable[3]  = new Basic::Hsva(  120.0f,  1.0f,  0.2588f,  1.0f ); 
         greenTable[4]  = new Basic::Hsva(  120.0f,  1.0f,  0.3420f,  1.0f );  
         greenTable[5]  = new Basic::Hsva(  120.0f,  1.0f,  0.4226f,  1.0f );  
         greenTable[6]  = new Basic::Hsva(  120.0f,  1.0f,  0.5000f,  1.0f ); 
         greenTable[7]  = new Basic::Hsva(  120.0f,  1.0f,  0.5736f,  1.0f );  
         greenTable[8]  = new Basic::Hsva(  120.0f,  1.0f,  0.6428f,  1.0f );  
         greenTable[9]  = new Basic::Hsva(  120.0f,  1.0f,  0.7071f,  1.0f );  
         greenTable[10] = new Basic::Hsva(  120.0f,  1.0f,  0.7660f,  1.0f );  
         greenTable[11] = new Basic::Hsva(  120.0f,  1.0f,  0.8192f,  1.0f );  
         greenTable[12] = new Basic::Hsva(  120.0f,  1.0f,  0.8660f,  1.0f ); 
         greenTable[13] = new Basic::Hsva(  120.0f,  1.0f,  0.9063f,  1.0f ); 
         greenTable[14] = new Basic::Hsva(  120.0f,  1.0f,  0.9397f,  1.0f );  
         greenTable[15] = new Basic::Hsva(  120.0f,  1.0f,  0.9659f,  1.0f );  
         greenTable[16] = new Basic::Hsva(  120.0f,  1.0f,  0.9848f,  1.0f );  
         greenTable[17] = new Basic::Hsva(  120.0f,  1.0f,  0.9962f,  1.0f );  
         greenTable[18] = new Basic::Hsva(  120.0f,  1.0f,  1.0f,     1.0f );  

         std::cout << "start image generation" << std::endl;
         double start = getComputerTime();

         for (int icol = 0; icol < NUM_COLUMNS; icol++) {

//            int halfway = NUM_COLUMNS / 2;

            // the Lat/long of the southern most point
            double longitude = cLon + (icol - NUM_COLUMNS/2) * spacingLon;

            if (testShadows || testAac || testEarthCurv) {

               for (int irow = 0; irow < NUM_ROWS; irow++) {
                  elevations[irow] = 0;
                  aacData[irow] = 1.0f;
                  validFlgs[irow] = false;
                  maskFlgs[irow] = false;
               }

               // the Lat/long of the southern most point
               double latitude = cLat + (0 - NUM_ROWS/2) * spacingLat;
               LCreal maxRng = (LCreal)(deltaLat * 60.0f * Basic::Distance::NM2M);

               // Direction
               //LCreal direction = 30.0f * LCreal(icol - NUM_COLUMNS/2)/LCreal(NUM_COLUMNS/2);
               LCreal direction = 0;

               // get a strip of elevations from south to north
               unsigned int num = terrain->getElevations(elevations, validFlgs, NUM_ROWS, latitude, longitude, direction, maxRng, interpolate);

               // Apply earth curvature effects to terrain elevations
               if (testEarthCurv) {
                  for (int irow = 0; irow < NUM_ROWS; irow++) {
                     elevations[irow] -= curvature[irow];
                  }
               }

               // Generate Masks
               if (testShadows) {
                  Basic::Terrain::vbwShadowChecker(maskFlgs, elevations, validFlgs, NUM_ROWS, maxRng, altitude, lookAngle, beamWidth);
               }

               // Compute AAC data
               if (testAac) {
                  //Simulation::Terrain::aac(aacData, elevations, maskFlgs, NUM_ROWS, maxRng, altitude);
                  LCreal angle = (LCreal)(-10.0f * Basic::Angle::D2RCC);
                  osg::Vec2 vec(lcCos(angle),lcSin(angle));
                  Basic::Terrain::cLight(aacData, elevations, maskFlgs, NUM_ROWS, maxRng, vec);
               }

            }

            // Draw a line along the Y points (moving from south to north along the latitude lines)
            for (int irow = 0; irow < NUM_ROWS; irow++) {

               osg::Vec3 color(0,0,0);
               LCreal elev = 0;
               bool valid = false;

              if (testShadows || testAac || testEarthCurv) {
                  // multi-point test: get the elevation from the array
                  if (validFlgs[irow]) {
                     elev = elevations[irow];
                     valid = true;
                  }
               }
               else {
                  // Single point test: compute the latitude of this point and get the elevation
                  double latitude = cLat + (irow - NUM_ROWS/2) * spacingLat;
                  valid = terrain->getElevation(&elev, latitude, longitude, interpolate);
               }

               // If valid and not masked, convert the elevation to a color (or gray) value
               if (valid && !(testShadows && maskFlgs[irow])) {
                  if (colorScale == GRAY_SCALE)
                     Basic::Terrain::getElevationColor(elev, minz, maxz, grayTable,  2, color);
                  else if (colorScale == COLOR_SCALE)
                     Basic::Terrain::getElevationColor(elev, minz, maxz, colorTable, 7, color);
                  else if (colorScale == GREEN_SCALE)
                     Basic::Terrain::getElevationColor(elev, minz, maxz, greenTable,  19, color);
               }

               // Apply AAC data
               if (valid && testAac) {
                  color = color * aacData[irow];
               }

               //if (icol == 100) {
               //   std::cout << icol << ", " << irow << " = " << elev << " [ " << color.x() << ", " << color.y() << ", " << color.z() << " ]" << std::endl;
               //}

               // store this color
               GLsizei idx = irow*imgWidth*PIXEL_SIZE + icol*PIXEL_SIZE;
               image[idx+0] = GLubyte( 255.0 * color[0] );
               image[idx+1] = GLubyte( 255.0 * color[1] );
               image[idx+2] = GLubyte( 255.0 * color[2] );
            }
         }

         double end = getComputerTime();
         double dtime = (end - start);
         std::cout << "Image finished: time(s) = " << dtime << ", per line(us) = " << (dtime/(double)NUM_COLUMNS)*1000000.0 << std::endl;

      }

   }

   BaseClass::updateData(dt);
}

//------------------------------------------------------------------------------
// drawFunc()
//------------------------------------------------------------------------------
void Display::drawFunc()
{

   if (image != 0) {
      if (testTexture) {
         // ---
         // Draw using texture map
         // ---

         // enable textures, if we need to
         glEnable(GL_TEXTURE_2D);
         if (texture == 0) {
            glGenTextures(1,&texture);
         }

         // set our texture environment
         glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
         
         glBindTexture(GL_TEXTURE_2D, texture);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
         glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

         double start = getComputerTime();

         glTexImage2D(GL_TEXTURE_2D, 0, PIXEL_SIZE, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

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

         double end = getComputerTime();
         double dtime = (end - start);
         std::cout << "glTexImage2D() dtime = " << dtime << std::endl;
         glDisable(GL_TEXTURE_2D);
      }
      else {
         // ---
         // Draw using glDrawPixels()
         // ---

         glRasterPos2f(0.0, 0.0);

         double start = getComputerTime();

         glDrawPixels(imgWidth, imgHeight, GL_RGB, GL_UNSIGNED_BYTE, image);

         double end = getComputerTime();
         double dtime = (end - start);
         std::cout << "glDrawPixels() dtime = " << dtime << std::endl;
      }
   }
}

//-----------------------------------------------------------------------------
// configure() -- function to configure the display
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
// copy the image memory from another object
//------------------------------------------------------------------------------
bool Display::copyImageMemory(const Display& org)
{
   if (&org != 0) {
      // First free our old memory
      freeImageMemory();

      // Now allocate the new memory (if needed)
      bool ok = initImageMemory(org.imgWidth, org.imgHeight);
      if (ok) {
         for (GLsizei irow = 0; irow < imgHeight; irow++) {
            for (GLsizei icol = 0; icol < imgWidth; icol++) {
               GLsizei idx = irow*imgWidth*PIXEL_SIZE + icol*PIXEL_SIZE;
               image[idx+0] = org.image[idx+0];
               image[idx+1] = org.image[idx+1];
               image[idx+2] = org.image[idx+2];
            }
         }
      }
   }
   return true;
}


//------------------------------------------------------------------------------
// allocate and init image memory
//------------------------------------------------------------------------------
bool Display::initImageMemory(const GLsizei width, const GLsizei height)
{
   bool ok = false;
   if (width > 0  && width <= MAX_IMAGE_WIDTH && 
      height > 0 && height <= MAX_IMAGE_HEIGHT) {

      // allocate space for the image
      GLubyte* tmpImage = new GLubyte[width*height*PIXEL_SIZE];
      if (tmpImage != 0) {

         // and set our member variables
         image = tmpImage;
         imgWidth = width;
         imgHeight = height;
         ok = true;

      }
   }
   return ok;
}

//------------------------------------------------------------------------------
// free the image memory
//------------------------------------------------------------------------------
void Display::freeImageMemory()
{
   // temp pointer
   GLubyte* tmpImage = image;

   // Clear the member variables
   image = 0;
   imgWidth = 0;
   imgHeight = 0;

   // Free the memory
   if (tmpImage != 0) delete[] tmpImage;

   // Free the texture
   if (texture != 0) {
      glDeleteTextures(1,&texture);
      texture = 0;
   }
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


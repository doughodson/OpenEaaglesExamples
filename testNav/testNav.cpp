//-----------------------------------------------------------------------------
// Test Basic::Nav functions
//-----------------------------------------------------------------------------

#include "openeaagles/basic/Nav.h"

#include "openeaagles/basic/EarthModel.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/units/Distances.h"
#include <iomanip>


namespace Eaagles {
namespace TestNav {

////------------------------------------------------------------------------------
//// Local functions
////------------------------------------------------------------------------------
int showVec2(const osg::Vec2d V)
{
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << std::setw(12) << V[0] << std::endl 
             << std::setw(12) << V[1] << std::endl
             << std::endl;

   return 0;
}

int showVec3(const osg::Vec3d V)
{
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << std::setw(12) << V[0] << std::endl 
             << std::setw(12) << V[1] << std::endl
             << std::setw(12) << V[2] << std::endl
             << std::endl;

   return 0;
}

int showMatrix(const osg::Matrixd M)
{
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   //std::cout << "Matrix: " << std::endl
#if 1
   // 3x3 matrix
   std::cout << std::setw(12) << M(0,0) << std::setw(12) << M(0,1) << std::setw(12) << M(0,2) << std::endl 
             << std::setw(12) << M(1,0) << std::setw(12) << M(1,1) << std::setw(12) << M(1,2) << std::endl
             << std::setw(12) << M(2,0) << std::setw(12) << M(2,1) << std::setw(12) << M(2,2) << std::endl
#else
   // 4x4 matrix
             << std::setw(12) << M(0,0) << std::setw(12) << M(0,1) << std::setw(12) << M(0,2) << std::setw(12) << M(0,3) << std::endl 
             << std::setw(12) << M(1,0) << std::setw(12) << M(1,1) << std::setw(12) << M(1,2) << std::setw(12) << M(1,3) << std::endl
             << std::setw(12) << M(2,0) << std::setw(12) << M(2,1) << std::setw(12) << M(2,2) << std::setw(12) << M(2,3) << std::endl
             << std::setw(12) << M(3,0) << std::setw(12) << M(3,1) << std::setw(12) << M(3,2) << std::setw(12) << M(3,3) << std::endl
#endif
             << std::endl;

   return 0;
}


//------------------------------------------------------------------------------
// prototype functions
//------------------------------------------------------------------------------
void test_fbd2llE();
void test_fll2bdE();
void test_fbd2llS();
void test_fll2bdS();
void test_aer2xyz1();
void test_aer2xyz2();
void test_xyz2aer1();
void test_xyz2aer2();
void test_gbd2ll();
void test_gll2bd();
void test_gbd2llS();
void test_gll2bdS();
void test_glla2bd();
void test_glla2bdS();
void test_vbd2ll();
void test_vll2bd();

void test_computeWorldMatrix();
void test_computeRotationalMatrixDeg1();
void test_computeRotationalMatrixDeg2();
void test_computeEulerAnglesDeg();
void test_convertPosVec2LL();
void test_convertLL2PosVec();
void test_convertEcef2Geod();
void test_convertGeod2Ecef();


//------------------------------------------------------------------------------
// Test Nav class functions 
//------------------------------------------------------------------------------
int testNavFns()
{
   char ynCont = 'y';
   char ynMenu = 'y';
   
   while (ynCont != 'n') {
      if (ynMenu != 'n') {
         std::cout << "=====================================================" << std::endl;
         std::cout << "Nav test functions" << std::endl;
         std::cout << "=====================================================" << std::endl;
         
         // Direct and Inverse Methods
         std::cout << "   1)  test_fbd2llE()"                       << std::endl
                   << "   2)  test_fll2bdE()"                       << std::endl
                   << "   3)  test_fbd2llS()"                       << std::endl
                   << "   4)  test_fll2bdS()"                       << std::endl
                   << "   5)  test_aer2xyz1()"                      << std::endl
                   << "   6)  test_aer2xyz2()"                      << std::endl
                   << "   7)  test_xyz2aer1()"                      << std::endl
                   << "   8)  test_xyz2aer2()"                      << std::endl
                   << "   9)  test_gbd2ll()"                        << std::endl
                   << "  10)  test_gbd2llS()"                       << std::endl
                   << "  11)  test_gll2bd()"                        << std::endl
                   << "  12)  test_gll2bdS()"                       << std::endl
                   << "  13)  test_glla2bd()"                       << std::endl
                   << "  14)  test_glla2bdS()"                      << std::endl
                   << "  15)  test_vbd2ll()"                        << std::endl
                   << "  16)  test_vll2bd()"                        << std::endl

         // Matrix Generators
                   << "  17)  test_computeWorldMatrix()"            << std::endl
                   << "  18)  test_computeRotationalMatrixDeg1()"   << std::endl
                   << "  19)  test_computeRotationalMatrixDeg2()"   << std::endl
                   << "  20)  test_computeEulerAnglesDeg()"         << std::endl
                   << "  21)  test_convertPosVec2LL()"              << std::endl
                   << "  22)  test_convertLL2PosVec()"              << std::endl
                   << "  23)  test_convertEcef2Geod()"              << std::endl
                   << "  24)  test_convertGeod2Ecef()"              << std::endl

                   << std::endl;
      }
      
      int num = 1;
      std::cout << "Enter a Nav function test number: ";
      std::cin  >> num; 

      switch (num) {
         // Direct and Inverse Methods
         case  1: test_fbd2llE();                       break;
         case  2: test_fll2bdE();                       break;
         case  3: test_fbd2llS();                       break;
         case  4: test_fll2bdS();                       break;
         case  5: test_aer2xyz1();                      break;
         case  6: test_aer2xyz2();                      break;
         case  7: test_xyz2aer1();                      break;
         case  8: test_xyz2aer2();                      break;
         case  9: test_gbd2ll();                        break;
         case 10: test_gbd2llS();                       break;
         case 11: test_gll2bd();                        break;
         case 12: test_gll2bdS();                       break;
         case 13: test_glla2bd();                       break;
         case 14: test_glla2bdS();                      break;
         case 15: test_vbd2ll();                        break;
         case 16: test_vll2bd();                        break;
         
         // Matrix Generators
         case 17: test_computeWorldMatrix();            break;
         case 18: test_computeRotationalMatrixDeg1();   break;
         case 19: test_computeRotationalMatrixDeg2();   break;
         case 20: test_computeEulerAnglesDeg();         break;
         case 21: test_convertPosVec2LL();              break;
         case 22: test_convertLL2PosVec();              break;
         case 23: test_convertEcef2Geod();              break;
         case 24: test_convertGeod2Ecef();              break;
         
         default:
            std::cout << "Bad selection. Try again." << std::endl;
            break;
      }
      
      std::cout << "Continue?  (y/n)";
      std::cin  >> ynCont;
      if (ynCont != 'n') {
         std::cout << "Show menu? (y/n)";
         std::cin  >> ynMenu;
      }
      std::cout << std::endl;
   }

   return 0;
}


//------------------------------------------------------------------------------
// Test navigation functions
//------------------------------------------------------------------------------

//--------
// #1
//--------
void test_fbd2llE()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_fbd2llE" << std::endl << std::endl;

   double slat = 0.0;
   double slon = 0.0;
   double brng = 0.0;
   double dist = 0.0;
   double dlat = 0.0;
   double dlon = 0.0;
   const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;

   // example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "slat = 0;    // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;    // source longitude  [DEG]" << std::endl;
   std::cout << "brng = 45;   // target bearing    [DEG]" << std::endl;
   std::cout << "dist = 100;  // target distance   [NM] " << std::endl;
   std::cout << std::endl;
   
   slat = 0;  
   slon = 0;  
   brng = 45; 
   dist = 100;
   std::cout << "Basic::Nav::fbd2llE(slat, slon, brng, dist, &dlat, &dlon, pEM);" << std::endl;
   Basic::Nav::fbd2llE(slat, slon, brng, dist, &dlat, &dlon, pEM);
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> dlat = " << std::setw(10) << dlat << "  // target latitude  [DEG]" << std::endl;
   std::cout << "=> dlon = " << std::setw(10) << dlon << "  // target longitude [DEG]" << std::endl;
   std::cout << std::endl;
   
   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter source latitude   [DEG] : "; std::cin >> slat;
   std::cout << "Enter source longitude  [DEG] : "; std::cin >> slon;
   std::cout << "Enter source bearing    [DEG] : "; std::cin >> brng;
   std::cout << "Enter source distance   [NM]  : "; std::cin >> dist;
   std::cout << std::endl;

   //-----------------------------------
   // bool fbd2llE(
   //      const double slat,         // IN: Starting (reference) latitude (degs)
   //      const double slon,         // IN: Starting (reference) longitude (degs)
   //      const double brng,         // IN: True bearing (degs)
   //      const double dist,         // IN: Distance (ground range) (nm)
   //      double* const dlat,        // OUT: Destination latitude (degs)
   //      double* const dlon,        // OUT:  Destination longitude (degs)
   //      const Basic::EarthModel* const eem=0)    // IN: Optional: Pointer to earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::fbd2llE(slat, slon, brng, dist, &dlat, &dlon, pEM);

   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "dlat = " << std::setw(10) << dlat << " [DEG]" << std::endl;
   std::cout << "dlon = " << std::setw(10) << dlon << " [DEG]" << std::endl;
   std::cout << std::endl;

}

//--------
// #2
//--------
void test_fll2bdE()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_fll2bdE" << std::endl << std::endl;

   double slat = 0.0;
   double slon = 0.0;
   double dlat = 0.0;
   double dlon = 0.0;
   double brng = 0.0;
   double dist = 0.0;
   const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;
   
   // example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem: "   << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "slat = 0; // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0; // source longitude  [DEG]" << std::endl;
   std::cout << "dlat = 1; // target latitude   [DEG]" << std::endl;
   std::cout << "dlon = 1; // target longitude  [NM] " << std::endl;
   std::cout << std::endl;
   
   slat = 0;
   slon = 0;
   dlat = 1;
   dlon = 1;
   std::cout << "Basic::Nav::fll2bdE(slat, slon, dlat, dlon, &brng, &dist, pEM);" << std::endl;
   Basic::Nav::fll2bdE(slat, slon, dlat, dlon, &brng, &dist, pEM);

   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> brng = " << std::setw(10) << brng << "  // bearing  to target [DEG]" << std::endl;
   std::cout << "=> dist = " << std::setw(10) << dist << "  // distance to target [NM] " << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter source latitude   [DEG] : "; std::cin >> slat;
   std::cout << "Enter source longitude  [DEG] : "; std::cin >> slon;
   std::cout << "Enter target latitude   [DEG] : "; std::cin >> dlat;
   std::cout << "Enter target longitude  [DEG] : "; std::cin >> dlon;
   std::cout << std::endl;
      
   //-----------------------------------
   // bool fll2bdE(
   //      const double slat,         // IN: Starting (reference) latitude (degs)
   //      const double slon,         // IN: Starting (reference) longitude (degs)
   //      const double dlat,         // IN: Destination latitude (degs)
   //      const double dlon,         // IN: Destination longitude (degs)
   //      double* const brng,        // OUT: True bearing (degs)
   //      double* const dist,        // OUT: distance (ground range) (nm)
   //      const Basic::EarthModel* const eem=0)    // IN: Optional: Pointer to earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::fll2bdE(slat, slon, dlat, dlon, &brng, &dist, pEM);

   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "brng = " << std::setw(10) << brng << " [DEG]" << std::endl;
   std::cout << "dist = " << std::setw(10) << dist << " [NM] " << std::endl;
   std::cout << std::endl;

}

//--------
// #3
//--------
void test_fbd2llS()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_fbd2llS" << std::endl << std::endl;

   double slat = 0.0;
   double slon = 0.0;
   double brng = 0.0;
   double dist = 0.0;
   double dlat = 0.0;
   double dlon = 0.0;

   // example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem: "   << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "slat = 0;   // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;   // source longitude  [DEG]" << std::endl;
   std::cout << "brng = 45;  // target bearing    [DEG]" << std::endl;
   std::cout << "dist = 100; // target distance   [NM] " << std::endl;
   std::cout << std::endl;
   
   slat = 0;  
   slon = 0;  
   brng = 45; 
   dist = 100;
   std::cout << "Basic::Nav::fbd2llS(slat, slon, brng, dist, &dlat, &dlon);" << std::endl;
   Basic::Nav::fbd2llS(slat, slon, brng, dist, &dlat, &dlon);
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);   
   std::cout << "=> dlat = " << std::setw(10) << dlat << "  // target latitude   [DEG]" << std::endl;
   std::cout << "=> dlon = " << std::setw(10) << dlon << "  // target longitude  [DEG]" << std::endl;
   std::cout << std::endl;
   
   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter source latitude   [DEG] : "; std::cin >> slat;
   std::cout << "Enter source longitude  [DEG] : "; std::cin >> slon;
   std::cout << "Enter source bearing    [DEG] : "; std::cin >> brng;
   std::cout << "Enter source distance   [NM]  : "; std::cin >> dist;
   std::cout << std::endl;
      
   //-----------------------------------
   // bool fbd2llS(
   //      const double slat,         // IN: Starting (reference) latitude (degs)
   //      const double slon,         // IN: Starting (reference) longitude (degs)
   //      const double brng,         // IN: True bearing (degs)
   //      const double dist,         // IN: Distance (ground range) (nm)
   //      double* const dlat,        // OUT: Destination latitude (degs)
   //      double* const dlon)        // OUT:  Destination longitude (degs)
   //-----------------------------------   
   Basic::Nav::fbd2llS(slat, slon, brng, dist, &dlat, &dlon);

   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);   
   std::cout << "dlat = " << std::setw(10) << dlat << " [DEG]" << std::endl;
   std::cout << "dlon = " << std::setw(10) << dlon << " [DEG]" << std::endl;
   std::cout << std::endl;

}

//--------
// #4
//--------
void test_fll2bdS()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_fll2bdS" << std::endl << std::endl;

   double slat = 0.0;
   double slon = 0.0;
   double dlat = 0.0;
   double dlon = 0.0;
   double brng = 0.0;
   double dist = 0.0;
   
   // example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem: "   << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "slat = 0; // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0; // source longitude  [DEG]" << std::endl;
   std::cout << "dlat = 1; // target latitude   [DEG]" << std::endl;
   std::cout << "dlon = 1; // target longitude  [DEG]" << std::endl;
   std::cout << std::endl;
   
   slat = 0;
   slon = 0;
   dlat = 1;
   dlon = 1;
   std::cout << "Basic::Nav::fll2bdS(slat, slon, dlat, dlon, &brng, &dist);" << std::endl;
   Basic::Nav::fll2bdS(slat, slon, dlat, dlon, &brng, &dist);
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> brng = " << std::setw(10) << brng << "  // bearing  to target [DEG]" << std::endl;
   std::cout << "=> dist = " << std::setw(10) << dist << "  // distance to target [NM] " << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter source latitude   [DEG] : "; std::cin >> slat;
   std::cout << "Enter source longitude  [DEG] : "; std::cin >> slon;
   std::cout << "Enter target latitude   [DEG] : "; std::cin >> dlat;
   std::cout << "Enter target longitude  [DEG] : "; std::cin >> dlon;
   std::cout << std::endl;
      
   //-----------------------------------
   // bool fll2bdS(
   //      const double slat,         // IN: Starting (reference) latitude (degs)
   //      const double slon,         // IN: Starting (reference) longitude (degs)
   //      const double dlat,         // IN: Destination latitude (degs)
   //      const double dlon,         // IN: Destination longitude (degs)
   //      double* const brng,        // OUT: True bearing (degs)
   //      double* const dist)        // OUT: distance (ground range) (nm)
   //-----------------------------------   
   Basic::Nav::fll2bdS(slat, slon, dlat, dlon, &brng, &dist);

   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "brng = " << std::setw(10) << brng << " [DEG]" << std::endl;
   std::cout << "dist = " << std::setw(10) << dist << " [NM] " << std::endl;
   std::cout << std::endl;

}


//--------
// #5
//--------
void test_aer2xyz1()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_aer2xyz - using euler angles" << std::endl << std::endl;

   double azim = 0.0;
   double elev = 0.0;
   double ranj = 0.0;
   osg::Vec3d pos;
   
   // example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem: " << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "azim = 45;    // azimuth    [DEG]" << std::endl;
   std::cout << "elev = 30;    // elevation  [DEG]" << std::endl;
   std::cout << "ranj = 1000;  // range      [M]  " << std::endl;
   std::cout << std::endl;
   
   azim = 45;  
   elev = 30;  
   ranj = 1000;
   std::cout << "Convert azimuth and elevation to radians" << std::endl;
   std::cout << "azim *= Basic::Angle::D2RCC;  // azimuth    [RAD]" << std::endl;
   std::cout << "elev *= Basic::Angle::D2RCC;  // elevation  [RAD]" << std::endl;
   std::cout << std::endl;
   azim *= Basic::Angle::D2RCC;
   elev *= Basic::Angle::D2RCC;

   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "azim = " << std::setw(12) << azim << "  // azimuth    [RAD]  " << std::endl;
   std::cout << "elev = " << std::setw(12) << elev << "  // elevation  [RAD]  " << std::endl;
   std::cout << "ranj = " << std::setw(12) << ranj << "  // range      [M]    " << std::endl;
   std::cout << std::endl;

   std::cout << "Basic::Nav::aer2xyz(&pos, azim, elev, ranj);" << std::endl;
   Basic::Nav::aer2xyz(&pos, azim, elev, ranj);
   
   std::cout << "=> pos[0] = " << std::setw(12) << pos[0] << "  // x  [M]" << std::endl;
   std::cout << "=> pos[1] = " << std::setw(12) << pos[1] << "  // y  [M]" << std::endl;
   std::cout << "=> pos[2] = " << std::setw(12) << pos[2] << "  // z  [M]" << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter azimuth    [DEG] : "; std::cin >> azim;
   std::cout << "Enter elevation  [DEG] : "; std::cin >> elev;
   std::cout << "Enter range      [M]   : "; std::cin >> ranj;
   std::cout << std::endl;

   azim *= Basic::Angle::D2RCC;
   elev *= Basic::Angle::D2RCC;

   //-----------------------------------
   // Using euler angles
   // bool aer2xyz(
   //      osg::Vec3d* const pos,     // OUT: position vector array (NED, player centered)  [meters]
   //      const double az,           // IN:  azimuth (euler)  (radians)
   //      const double el,           // IN:  elevation (euler)  (positive up)   (radians)
   //      const double rng)          // IN:  range (euler) [meters]
   //-----------------------------------      
   Basic::Nav::aer2xyz(&pos, azim, elev, ranj);

   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "pos[0] = " << std::setw(14) << pos[0] << " [M]" << std::endl;
   std::cout << "pos[1] = " << std::setw(14) << pos[1] << " [M]" << std::endl;
   std::cout << "pos[2] = " << std::setw(14) << pos[2] << " [M]" << std::endl;
   std::cout << std::endl;
}

//--------
// #6
//--------
void test_aer2xyz2()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_aer2xyz - using body angles" << std::endl << std::endl;

   double roll  = 0.0;
   double pitch = 0.0;
   double yaw   = 0.0;
   osg::Matrixd rm;

   double azim  = 0.0;
   double elev  = 0.0;
   double ranj  = 0.0;
   osg::Vec3d pos;
   
   //-------------------------------------------------------
   // example problem
   //-------------------------------------------------------
   std::cout << "==================================" << std::endl;
   roll  = 10;
   pitch = 20;
   yaw   = 30;
   std::cout << "Compute rotation matrix (rm)" << std::endl;
   std::cout << "roll  = " << std::setw(12) << roll  << "  // roll   [DEG]" << std::endl;
   std::cout << "pitch = " << std::setw(12) << pitch << "  // pitch  [DEG]" << std::endl;
   std::cout << "yaw   = " << std::setw(12) << yaw   << "  // yaw    [DEG]" << std::endl;
   std::cout << std::endl;
   
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
   Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);
   std::cout << "=> rm = " << std::endl;
   showMatrix(rm);
   
   azim = 45;  
   elev = 30;  
   ranj = 1000;
   std::cout << "azim = " << std::setw(12) << azim  << "  // azimuth    [DEG]" << std::endl;
   std::cout << "elev = " << std::setw(12) << elev  << "  // elevation  [DEG]" << std::endl;
   std::cout << "ranj = " << std::setw(12) << ranj  << "  // range      [M]  " << std::endl;
   std::cout << std::endl;

   std::cout << "Convert azimuth and elevation to radians" << std::endl;
   azim *= Basic::Angle::D2RCC;
   elev *= Basic::Angle::D2RCC;
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "azim = " << std::setw(12) << elev  << "  // azimuth    [RAD]" << std::endl;
   std::cout << "elev = " << std::setw(12) << elev  << "  // elevation  [RAD]" << std::endl;
   std::cout << "ranj = " << std::setw(12) << ranj  << "  // range      [M]  " << std::endl;
   std::cout << std::endl;

   std::cout << "Basic::Nav::aer2xyz(&pos, rm, azim, elev, ranj);" << std::endl;
   Basic::Nav::aer2xyz(&pos, rm, azim, elev, ranj);
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> pos[0] = " << std::setw(12) << pos[0] << "  // x - north  [M]" << std::endl;
   std::cout << "=> pos[1] = " << std::setw(12) << pos[1] << "  // y - east   [M]" << std::endl;
   std::cout << "=> pos[2] = " << std::setw(12) << pos[2] << "  // z - down   [M]" << std::endl;
   std::cout << std::endl;

   //-------------------------------------------------------
   // Enter data from the keyboard
   //-------------------------------------------------------
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter roll   [DEG] : "; std::cin >> roll;
   std::cout << "Enter pitch  [DEG] : "; std::cin >> pitch;
   std::cout << "Enter yaw    [DEG  : "; std::cin >> yaw;
   std::cout << std::endl;
   
   roll  *= Basic::Angle::D2RCC;
   pitch *= Basic::Angle::D2RCC;
   yaw   *= Basic::Angle::D2RCC;
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "roll  = " << std::setw(14) << roll  << " [RAD]" << std::endl;
   std::cout << "pitch = " << std::setw(14) << pitch << " [RAD]" << std::endl;
   std::cout << "yaw   = " << std::setw(14) << yaw   << " [RAD]" << std::endl;
   std::cout << std::endl;

   std::cout << "Basic::Nav::computeRotationalMatrix(roll, pitch, yaw, &rm);" << std::endl;
   Basic::Nav::computeRotationalMatrix(roll, pitch, yaw, &rm);
   std::cout << "=> rm = " << std::endl;
   showMatrix(rm);

   std::cout << "Enter azimuth    [DEG] : "; std::cin >> azim;
   std::cout << "Enter elevation  [DEG] : "; std::cin >> elev;
   std::cout << "Enter range      [M]   : "; std::cin >> ranj;
   std::cout << std::endl;

   azim *= Basic::Angle::D2RCC;
   elev *= Basic::Angle::D2RCC;

   //-----------------------------------
   // Using body angles
   // bool aer2xyz(
   //      osg::Vec3d* const pos,     // OUT: position vector array (NED, player centered)  [meters]
   //      const osg::Matrixd& rm,    // IN:  inertial to body rotational matrix (see computeRotationalMatrix())
   //      const double az,           // IN:  azimuth (body)  (radians)
   //      const double el,           // IN:  elevation (body)  (positive up)   (radians)
   //      const double rng)          // IN:  range (body) [meters]
   //-----------------------------------
   Basic::Nav::aer2xyz(&pos, rm, azim, elev, ranj);

   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "pos[0] = " << std::setw(14) << pos[0] << " [M]" << std::endl;
   std::cout << "pos[1] = " << std::setw(14) << pos[1] << " [M]" << std::endl;
   std::cout << "pos[2] = " << std::setw(14) << pos[2] << " [M]" << std::endl;
   std::cout << std::endl;

}

//--------
// #7
//--------
void test_xyz2aer1()
{
   osg::Vec3d aer;
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;

   std::cout << "=============================================" << std::endl;
   std::cout << "test xyz2aer using euler angles" << std::endl << std::endl;

   // example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem: " << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "x = 100;  // x position [M]" << std::endl;
   std::cout << "y = 200;  // y position [M]" << std::endl;
   std::cout << "z = 300;  // z position [M]" << std::endl;
   std::cout << std::endl;
   x = 100;
   y = 200;
   z = 300;

   std::cout << "Basic::Nav::xyz2aer(&aer, x, y, z);" << std::endl;
   Basic::Nav::xyz2aer(&aer, x, y, z);
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> aer[0] = " << std::setw(12) << aer[0] << "  // azimuth    [DEG]" << std::endl;
   std::cout << "=> aer[1] = " << std::setw(12) << aer[1] << "  // elevation  [DEG]" << std::endl;
   std::cout << "=> aer[2] = " << std::setw(12) << aer[2] << "  // range      [M]"   << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "Enter x  [M] : "; std::cin >> x;
   std::cout << "Enter y  [M] : "; std::cin >> y;
   std::cout << "Enter z  [M] : "; std::cin >> z;
   std::cout << std::endl;

   //-----------------------------------
   // Computing euler angles
   // bool xyz2aer(
   //      osg::Vec3d* const aer,     // OUT: position vector  (aer)   [deg,deg,meters]
   //      const double x,            // IN:  x                        [meters]
   //      const double y,            // IN:  y                        [meters]
   //      const double z)            // IN:  z                        [meters]
   //-----------------------------------
   Basic::Nav::xyz2aer(&aer, x, y, z);
   
   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "aer[0] = " << std::setw(14) << aer[0] << " azimuth    [DEG]" << std::endl;
   std::cout << "aer[1] = " << std::setw(14) << aer[1] << " elevation  [DEG]" << std::endl;
   std::cout << "aer[2] = " << std::setw(14) << aer[2] << " range      [M]  " << std::endl;
   std::cout << std::endl;
   
}

//--------
// #8
//--------
void test_xyz2aer2()
{
   osg::Vec3d aer;
   osg::Matrixd rm;
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;
   double yaw   = 0.0;
   double pitch = 0.0;
   double roll  = 0.0;
   
   std::cout << "=============================================" << std::endl;
   std::cout << "test xyz2aer using body angles" << std::endl << std::endl;

   // example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem: " << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "x =  100;  // x - north   [M]" << std::endl;
   std::cout << "y =  200;  // y - east    [M]" << std::endl;
   std::cout << "z = -300;  // z - down    [M]" << std::endl;
   std::cout << std::endl;
   x =  100;
   y =  200;
   z = -300;

   std::cout << "Basic::Nav::xyz2aer(&aer, x, y, z);" << std::endl;
   Basic::Nav::xyz2aer(&aer, x, y, z);
   
   std::cout << "=> aer[0] = " << std::setw(12) << aer[0] << " [DEG] azimuth  " << std::endl;
   std::cout << "=> aer[1] = " << std::setw(12) << aer[1] << " [DEG] elevation" << std::endl;
   std::cout << "=> aer[2] = " << std::setw(12) << aer[2] << " [M]   range    " << std::endl;
   std::cout << std::endl;

   std::cout << "Compute a rotation matrix (rm):" << std::endl;
   std::cout << "roll  = 10;  //  [DEG] roll " << std::endl;
   std::cout << "pitch = 20;  //  [DEG] pitch" << std::endl;
   std::cout << "yaw   = 30;  //  [DEG] yaw  " << std::endl;
   std::cout << std::endl;
   roll  = 10;
   pitch = 20;
   yaw   = 30;
   
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
   Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);
   
   std::cout << "=> rm = " << std::endl;
   Basic::Nav::computeRotationalMatrixDeg(10, 20, 30, &rm);
   showMatrix(rm);
   
   std::cout << "Basic::Nav::xyz2aer(&aer, rm, x, y, z);" << std::endl;
   Basic::Nav::xyz2aer(&aer, rm, x, y, z);
   
   std::cout << "=> aer[0] = " << std::setw(12) << aer[0] << " [DEG] azimuth  " << std::endl;
   std::cout << "=> aer[1] = " << std::setw(12) << aer[1] << " [DEG] elevation" << std::endl;
   std::cout << "=> aer[2] = " << std::setw(12) << aer[2] << " [M]   range    " << std::endl;
   std::cout << std::endl;


   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter x - north  [M] : "; std::cin >> x;
   std::cout << "Enter y - east   [M] : "; std::cin >> y;
   std::cout << "Enter z - down   [M] : "; std::cin >> z;
   std::cout << std::endl;

   std::cout << "Enter roll   [DEG] : "; std::cin >> roll;
   std::cout << "Enter pitch  [DEG] : "; std::cin >> pitch;
   std::cout << "Enter yaw    [DEG  : "; std::cin >> yaw;
   std::cout << std::endl;
   
   roll  *= Basic::Angle::D2RCC;
   pitch *= Basic::Angle::D2RCC;
   yaw   *= Basic::Angle::D2RCC;
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "roll  = " << std::setw(14) << roll  << " [RAD]" << std::endl;
   std::cout << "pitch = " << std::setw(14) << pitch << " [RAD]" << std::endl;
   std::cout << "yaw   = " << std::setw(14) << yaw   << " [RAD]" << std::endl;
   std::cout << std::endl;

   std::cout << "Basic::Nav::computeRotationalMatrix(roll, pitch, yaw, &rm);" << std::endl;
   Basic::Nav::computeRotationalMatrix(roll, pitch, yaw, &rm);
   std::cout << "=> rm = " << std::endl;
   showMatrix(rm);

   //-----------------------------------
   // Computing body angles
   // bool xyz2aer(
   //      osg::Vec3d* const aer,     // OUT: position vector  (aer)   [deg,deg,meters]
   //      const osg::Matrixd& rm,    // IN:  inertial to body rotational matrix (see computeRotationalMatrix())
   //      const double x,            // IN:  x                        [meters]
   //      const double y,            // IN:  y                        [meters]
   //      const double z)            // IN:  z                        [meters]
   //-----------------------------------
   std::cout << "Basic::Nav::xyz2aer(&aer, rm, x, y, z);" << std::endl;
   Basic::Nav::xyz2aer(&aer, rm, x, y, z);

   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "aer[0] = " << std::setw(14) << aer[0] << "  [DEG]" << std::endl;
   std::cout << "aer[1] = " << std::setw(14) << aer[1] << "  [DEG]" << std::endl;
   std::cout << "aer[2] = " << std::setw(14) << aer[2] << "  [M]"   << std::endl;
   std::cout << std::endl;
   
}

//--------
// #9
//--------
void test_gbd2ll()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_gbd2llE" << std::endl << std::endl;

   double slat = 0.0;
   double slon = 0.0;
   double brng = 0.0;
   double dist = 0.0;
   double dlat = 0.0;
   double dlon = 0.0;
   const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;
   
   // example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem: "   << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "slat = 0;    // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;    // source longitude  [DEG]" << std::endl;
   std::cout << "brng = 45;   // target bearing    [DEG]" << std::endl;
   std::cout << "dist = 100;  // target distance   [NM] " << std::endl;
   std::cout << std::endl;
   slat = 0;  
   slon = 0;  
   brng = 45; 
   dist = 100;

   std::cout << "Basic::Nav::gbd2ll(slat, slon, brng, dist, &dlat, &dlon, pEM);" << std::endl;
   Basic::Nav::gbd2ll(slat, slon, brng, dist, &dlat, &dlon, pEM);
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> dlat = " << std::setw(12) << dlat << "  // [DEG] target latitude" << std::endl;
   std::cout << "=> dlon = " << std::setw(12) << dlon << "  // [DEG] target longitude" << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
   std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
   std::cout << "Enter brng  [DEG] : "; std::cin >> brng;
   std::cout << "Enter dist  [NM]  : "; std::cin >> dist;
   std::cout << std::endl;
   
   //-----------------------------------
   // bool gbd2llE(
   //      const double slat,         // IN: Starting (reference) latitude (degs)
   //      const double slon,         // IN: Starting (reference) longitude (degs)
   //      const double brng,         // IN: True bearing (degs)
   //      const double dist,         // IN: Distance (ground range) (nm)
   //      double* const dlat,        // OUT: Destination latitude (degs)
   //      double* const dlon,        // OUT: Destination longitude (degs)
   //      const Basic::EarthModel* const eem=0)    // IN: Optional:  Pointer to an earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::gbd2ll(slat, slon, brng, dist, &dlat, &dlon, pEM);
   
   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "dlat = " << std::setw(14) << dlat << " [DEG]" << std::endl;
   std::cout << "dlon = " << std::setw(14) << dlon << " [DEG]" << std::endl;
   std::cout << std::endl;
   
}

//--------
// #10
//--------
void test_gbd2llS()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_gbd2llS" << std::endl << std::endl;

   double slat = 0.0;
   double slon = 0.0;
   double brng = 0.0;
   double dist = 0.0;
   double dlat = 0.0;
   double dlon = 0.0;
   
   // example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem: "   << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "slat = 0;    // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;    // source longitude  [DEG]" << std::endl;
   std::cout << "brng = 45;   // target bearing    [DEG]" << std::endl;
   std::cout << "dist = 100;  // target distance   [NM] " << std::endl;
   std::cout << std::endl;
   slat = 0;  
   slon = 0;  
   brng = 45; 
   dist = 100;

   std::cout << "Basic::Nav::gbd2llS(slat, slon, brng, dist, &dlat, &dlon);" << std::endl;
   Basic::Nav::gbd2llS(slat, slon, brng, dist, &dlat, &dlon);
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> dlat = " << std::setw(12) << dlat << " [DEG]" << std::endl;
   std::cout << "=> dlon = " << std::setw(12) << dlon << " [DEG]" << std::endl;
   std::cout << std::endl;
   
   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
   std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
   std::cout << "Enter brng  [DEG] : "; std::cin >> brng;
   std::cout << "Enter dist  [NM]  : "; std::cin >> dist;
   std::cout << std::endl;
   
   //-----------------------------------
   // bool gbd2llS(
   //      const double slat,         // IN: Starting (reference) latitude (degs)
   //      const double slon,         // IN: Starting (reference) longitude (degs)
   //      const double brng,         // IN: True bearing (degs)
   //      const double dist,         // IN: Distance (ground range) (nm)
   //      double* const dlat,        // OUT: Destination latitude (degs)
   //      double* const dlon)        // OUT: Destination longitude (degs)
   //-----------------------------------
   Basic::Nav::gbd2llS(slat, slon, brng, dist, &dlat, &dlon);
   
   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "dlat = " << std::setw(14) << dlat << " [DEG]" << std::endl;
   std::cout << "dlon = " << std::setw(14) << dlon << " [DEG]" << std::endl;
   std::cout << std::endl;
   
}

//--------
// #11
//--------
void test_gll2bd()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_gll2bdE" << std::endl << std::endl;

   double slat = 0.0;
   double slon = 0.0;
   double dlat = 0.0;
   double dlon = 0.0;
   double brng = 0.0;
   double dist = 0.0;
   const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;

   // example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem: "   << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "slat = 0; // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0; // source longitude  [DEG]" << std::endl;
   std::cout << "dlat = 1; // target latitude   [DEG]" << std::endl;
   std::cout << "dlon = 1; // target longitude  [NM] " << std::endl;
   std::cout << std::endl;
   slat = 0;
   slon = 0;
   dlat = 1;
   dlon = 1;

   std::cout << "Basic::Nav::gll2bd(slat, slon, dlat, dlon, &brng, &dist, pEM);" << std::endl;
   Basic::Nav::gll2bd(slat, slon, dlat, dlon, &brng, &dist, pEM);
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "brng = " << std::setw(12) << brng << " [DEG]" << std::endl;
   std::cout << "dist = " << std::setw(12) << dist << " [NM]"  << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter slat [DEG] : "; std::cin >> slat;
   std::cout << "Enter slon [DEG] : "; std::cin >> slon;
   std::cout << "Enter dlat [DEG] : "; std::cin >> dlat;
   std::cout << "Enter dlon [DEG] : "; std::cin >> dlon;
   std::cout << std::endl;
   
   //-----------------------------------
   // bool gll2bd(
   //      const double slat,         // IN: Starting (reference) latitude (degs)
   //      const double slon,         // IN: Starting (reference) longitude (degs)
   //      const double dlat,         // IN: Destination latitude (degs)
   //      const double dlon,         // IN: Destination longitude (degs)
   //      double* const brng,        // OUT: True bearing (degs)
   //      double* const dist,        // OUT: distance (ground range) (nm)
   //      const Basic::EarthModel* const eem=0)    // IN: Optional:  Pointer to an earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::gll2bd(slat, slon, dlat, dlon, &brng, &dist, pEM);
   
   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "brng = " << std::setw(14) << brng << " [DEG]" << std::endl;
   std::cout << "dist = " << std::setw(14) << dist << " [NM]"  << std::endl;
   std::cout << std::endl;

}

//--------
// #12
//--------
void test_gll2bdS()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_gll2bd" << std::endl << std::endl;

   double slat = 0.0;
   double slon = 0.0;
   double dlat = 0.0;
   double dlon = 0.0;
   double brng = 0.0;
   double dist = 0.0;

   // example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem: "   << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "slat = 0;  // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;  // source longitude  [DEG]" << std::endl;
   std::cout << "dlat = 1;  // target latitude   [DEG]" << std::endl;
   std::cout << "dlon = 1;  // target longitude  [DEG]" << std::endl;
   std::cout << std::endl;
   slat = 0;
   slon = 0;
   dlat = 1;
   dlon = 1;
   
   std::cout << "Basic::Nav::gll2bdS(slat, slon, dlat, dlon, &brng, &dist);" << std::endl;
   Basic::Nav::gll2bdS(slat, slon, dlat, dlon, &brng, &dist);
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> brng = " << std::setw(12) << brng << " [DEG]" << std::endl;
   std::cout << "=> dist = " << std::setw(12) << dist << " [NM]"  << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
   std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
   std::cout << "Enter dlat  [DEG] : "; std::cin >> dlat;
   std::cout << "Enter dlon  [DEG] : "; std::cin >> dlon;
   std::cout << std::endl;

   //-----------------------------------
   // bool gll2bdS(
   //      const double slat,         // IN: Starting (reference) latitude (degs)
   //      const double slon,         // IN: Starting (reference) longitude (degs)
   //      const double dlat,         // IN: Destination latitude (degs)
   //      const double dlon,         // IN: Destination longitude (degs)
   //      double* const brng,        // OUT: True bearing (degs)
   //      double* const dist)        // OUT: distance (ground range) (nm)
   //-----------------------------------
   Basic::Nav::gll2bdS(slat, slon, dlat, dlon, &brng, &dist);

   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "brng = " << std::setw(14) << brng << " [DEG]" << std::endl;
   std::cout << "dist = " << std::setw(14) << dist << " [NM]"  << std::endl;
   std::cout << std::endl;

}

//--------
// #13
//--------
void test_glla2bd()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_glla2bd" << std::endl << std::endl;

   double slat = 0.0;
   double slon = 0.0;
   double salt = 0.0;
   double dlat = 0.0;
   double dlon = 0.0;
   double dalt = 0.0;
   const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;
   
   double brng = 0.0;
   double slantRng = 0.0;
   double dist = 0.0;
   double elev = 0.0;

   // Example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;   
   std::cout << "==================================" << std::endl;

   std::cout << "slat = 0;     // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;     // source longitude  [DEG]" << std::endl;
   std::cout << "salt = 0;     // source longitude  [M]" << std::endl;
   std::cout << "dlat = 1;     // target latitude   [DEG]" << std::endl;
   std::cout << "dlon = 1;     // target longitude  [DEG]" << std::endl;
   std::cout << "dalt = 10000; // target longitude  [M]" << std::endl;
   std::cout << std::endl;
   slat = 0;    
   slon = 0;    
   salt = 0;    
   dlat = 1;    
   dlon = 1;    
   dalt = 10000;

   std::cout << "Basic::Nav::glla2bd(slat, slon, salt, dlat, dlon, dalt,"  << std::endl;
   std::cout << "                     &brng, &slantRng, &dist, &elev);"     << std::endl;
   Basic::Nav::glla2bd(slat, slon, salt, dlat, dlon, dalt, &brng, &slantRng, &dist, &elev);
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "brng     = " << std::setw(12) << brng     << " [DEG]" << std::endl;
   std::cout << "slantRng = " << std::setw(12) << slantRng << " [NM]"  << std::endl;
   std::cout << "dist     = " << std::setw(12) << dist     << " [NM]"  << std::endl;
   std::cout << "elev     = " << std::setw(12) << elev     << " [DEG]" << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
   std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
   std::cout << "Enter salt  [M]   : "; std::cin >> salt;
   std::cout << "Enter dlat  [DEG] : "; std::cin >> dlat;
   std::cout << "Enter dlon  [DEG] : "; std::cin >> dlon;
   std::cout << "Enter dalt  [M]   : "; std::cin >> dalt;
   std::cout << std::endl;

   //-----------------------------------
   // bool glla2bd(
   //      const double slat,       // IN: Starting (reference) latitude (degs)
   //      const double slon,       // IN: Starting (reference) longitude (degs)
   //      const double salt,       // IN: Starting (reference) altitude (meters)
   //      const double dlat,       // IN: Destination latitude (degs)
   //      const double dlon,       // IN: Destination longitude (degs)
   //      const double dalt,       // IN: Destination altitude (meters)
   //      double* const brng,      // OUT: True bearing (degs)
   //      double* const slantRng,  // OUT: slant range (nm)
   //      double* const dist,      // OUT: distance (ground range) (nm)
   //      double* const elev=0,    // OUT: Optional: elevation angle (degs)
   //      const Basic::EarthModel* const eem=0)  // IN: Optional:  Pointer to an earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::glla2bd(slat, slon, salt, dlat, dlon, dalt,
                       &brng, &slantRng, &dist, &elev, pEM);

   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "brng     = " << std::setw(14) << brng     << " [DEG]" << std::endl;
   std::cout << "slantRng = " << std::setw(14) << slantRng << " [NM]"  << std::endl;
   std::cout << "dist     = " << std::setw(14) << dist     << " [NM]"  << std::endl;
   std::cout << "elev     = " << std::setw(14) << elev     << " [DEG]" << std::endl;
   std::cout << std::endl;

}

//--------
// #14
//--------
void test_glla2bdS()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_glla2bdS" << std::endl << std::endl;

   // inputs
   double slat      = 0.0;
   double slon      = 0.0;
   double salt      = 0.0;
   double dlat      = 0.0;
   double dlon      = 0.0;
   double dalt      = 0.0;

   // outputs
   double brng      = 0.0;
   double slantRng  = 0.0;
   double dist      = 0.0;
   double elev      = 0.0;

   // Example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;
   std::cout << "==================================" << std::endl;
   
   std::cout << "slat = 0;     // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;     // source longitude  [DEG]" << std::endl;
   std::cout << "salt = 0;     // source longitude  [M]"   << std::endl;
   std::cout << "dlat = 1;     // target latitude   [DEG]" << std::endl;
   std::cout << "dlon = 1;     // target longitude  [DEG]" << std::endl;
   std::cout << "dalt = 10000; // target longitude  [M]"   << std::endl;
   std::cout << std::endl;
   slat = 0.0;
   slon = 0.0;
   salt = 0.0;
   dlat = 1.0;
   dlon = 1.0;
   dalt = 10000.0;
   
   std::cout << "Basic::Nav::glla2bdS(slat, slon, salt, dlat, dlon, dalt,"  << std::endl;
   std::cout << "                     &brng, &slantRng, &dist, &elev);"     << std::endl;
   Basic::Nav::glla2bdS(slat, slon, salt, dlat, dlon, dalt, &brng, &slantRng, &dist, &elev);
   
   std::cout << "=> brng     = " << std::setw(12) << brng     << "  // bearing to target         [DEG]" << std::endl;
   std::cout << "=> slantRng = " << std::setw(12) << slantRng << "  // slant range to target     [NM]"  << std::endl;
   std::cout << "=> dist     = " << std::setw(12) << dist     << "  // ground range to target    [NM]"  << std::endl;
   std::cout << "=> elev     = " << std::setw(12) << elev     << "  // elevation angle to target [DEG]" << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
   std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
   std::cout << "Enter salt  [M]   : "; std::cin >> salt;
   std::cout << "Enter dlat  [DEG] : "; std::cin >> dlat;
   std::cout << "Enter dlon  [DEG] : "; std::cin >> dlon;
   std::cout << "Enter dalt  [M]   : "; std::cin >> dalt;
   std::cout << std::endl;

   //-----------------------------------
   // bool glla2bdS(
   //      const double slat,         // IN: Starting (reference) latitude (degs)
   //      const double slon,         // IN: Starting (reference) longitude (degs)
   //      const double salt,         // IN: Starting (reference) altitude (meters)
   //      const double dlat,         // IN: Destination latitude (degs)
   //      const double dlon,         // IN: Destination longitude (degs)
   //      const double dalt,         // IN: Destination altitude (meters)
   //      double* const brng,        // OUT: True bearing (degs)
   //      double* const slantRng,    // OUT: slant range (nm)
   //      double* const dist,        // OUT: distance (ground range) (nm)
   //      double* const elev = 0)    // OUT: (optional) elevation angle (degs)
   //-----------------------------------
   Basic::Nav::glla2bdS(slat, slon, salt, dlat, dlon, dalt,
                        &brng, &slantRng, &dist, &elev);

   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "brng     = " << std::setw(14) << brng     << " [DEG]" << std::endl;
   std::cout << "slantRng = " << std::setw(14) << slantRng << " [NM]"  << std::endl;
   std::cout << "dist     = " << std::setw(14) << dist     << " [NM]"  << std::endl;
   std::cout << "elev     = " << std::setw(14) << elev     << " [DEG]" << std::endl;
   std::cout << std::endl;

}

//--------
// #15
//--------
void test_vbd2ll()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_vbd2ll" << std::endl << std::endl;

   double slat = 0.0;
   double slon = 0.0;
   double brng = 0.0;
   double dist = 0.0;
   double dlat = 0.0;
   double dlon = 0.0;
   double brg2 = 0.0;
   const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "slat = 0;    // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;    // source longitude  [DEG]" << std::endl;
   std::cout << "brng = 45;   // target bearing    [DEG]" << std::endl;
   std::cout << "dist = 100;  // target distance   [NM] " << std::endl;
   std::cout << std::endl;
   slat = 0.0;
   slon = 0.0;
   brng = 45.0;
   dist = 100.0;
   
   std::cout << "Basic::Nav::vbd2ll(slat, slon, brng, dist, &dlat, &dlon, pEM);" << std::endl;
   Basic::Nav::vbd2ll(slat, slon, brng, dist, &dlat, &dlon, pEM);

   std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
   std::cout << "=> dlat = " << std::setw(12) << dlat << "  // target latitude  [DEG]" << std::endl;
   std::cout << "=> dlon = " << std::setw(12) << dlon << "  // target longitude [DEG]" << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter source latitude   [DEG] : "; std::cin  >> slat;
   std::cout << "Enter source longitude  [DEG] : "; std::cin  >> slon;
   std::cout << "Enter source bearing    [DEG] : "; std::cin  >> brng;
   std::cout << "Enter source distance   [NM]  : "; std::cin  >> dist;
   std::cout << std::endl;
      
   //-----------------------------------
   // bool vbd2ll(
   //      const double slat,         // IN: Starting (Reference) latitude (degs)
   //      const double slon,         // IN: Starting (Reference) longitude (degs)
   //      const double brng,         // IN: True bearing (degs)
   //      const double dist,         // IN: Distance (ground range) (nm)
   //      double* const dlat,        // OUT: Target latitude (degs)
   //      double* const dlon,        // OUT: Target longitude (degs)
   //      const Basic::EarthModel* const eem=0)    // IN: Optional: Pointer to an earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::vbd2ll(slat, slon, brng, dist, &dlat, &dlon, pEM);

   // output results
   std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
   std::cout << "dlat = " << std::setw(14) << dlat << " [DEG]" << std::endl;
   std::cout << "dlon = " << std::setw(14) << dlon << " [DEG]" << std::endl;
   std::cout << std::endl;

   // reverse test
   //Basic::Nav::vll2bd(dlat, dlon, slat, slon, &brng, &dist, &brg2, pEM);
   //std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
   //std::cout << "brng = " << std::setw(14) << brng << " [DEG]" << std::endl;
   //std::cout << "dist = " << std::setw(14) << dist << " [NM]"  << std::endl;
   //std::cout << "brg2 = " << std::setw(14) << brg2 << " [DEG]" << std::endl;
   //std::cout << std::endl;

}

//--------
// #16
//--------
void test_vll2bd()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_vll2bd" << std::endl << std::endl;

   double slat = 0.0;
   double slon = 0.0;
   double dlat = 0.0;
   double dlon = 0.0;
   double brg1 = 0.0;
   double dist = 0.0;
   double brg2 = 0.0;
   const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "slat = 0; // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0; // source longitude  [DEG]" << std::endl;
   std::cout << "dlat = 1; // target latitude   [DEG]" << std::endl;
   std::cout << "dlon = 1; // target longitude  [NM] " << std::endl;
   std::cout << std::endl;
   
   slat = 0;
   slon = 0;
   dlat = 1;
   dlon = 1;
   std::cout << "Basic::Nav::vll2bd(slat, slon, dlat, dlon, &brng, &dist, &brg2, pEM);" << std::endl;
   Basic::Nav::vll2bd(slat, slon, dlat, dlon, &brg1, &dist, &brg2, pEM);
   
   std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
   std::cout << "=> brg1 = " << std::setw(14) << brg1 << "  // bearing  source to target [DEG]" << std::endl;
   std::cout << "=> dist = " << std::setw(14) << dist << "  // distance to target [NM] "        << std::endl;
   std::cout << "=> brg2 = " << std::setw(14) << brg2 << "  // bearing  target to source [DEG]" << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:"      << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter source latitude   [DEG] : "; std::cin  >> slat;
   std::cout << "Enter source longitude  [DEG] : "; std::cin  >> slon;
   std::cout << "Enter target latitude   [DEG] : "; std::cin  >> dlat;
   std::cout << "Enter target longitude  [DEG] : "; std::cin  >> dlon;
   std::cout << std::endl;
      
   //-----------------------------------
   // bool vll2bd(
   //      const double slat,         // IN: Starting (reference) latitude (degs)
   //      const double slon,         // IN: Starting (reference) longitude (degs)
   //      const double dlat,         // IN: Destination latitude (degs)
   //      const double dlon,         // IN: Destination longitude (degs)
   //      double* const brng,        // OUT: True initial bearing (degs)
   //      double* const dist,        // OUT: geodesic distance (nm)
   //      double* const brg2=0,      // OUT: Optional: true final bearing (degs)
   //      const Basic::EarthModel* const eem=0)    // IN: Optional: Pointer to an earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::vll2bd(slat, slon, dlat, dlon, &brg1, &dist, &brg2, pEM);

   // output results
   std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
   std::cout << "brg1 = " << std::setw(14) << brg1 << " [DEG]" << std::endl;
   std::cout << "dist = " << std::setw(14) << dist << " [NM]"  << std::endl;
   std::cout << "brg2 = " << std::setw(14) << brg2 << " [DEG]" << std::endl;
   std::cout << std::endl;

   // reverse test
   //Basic::Nav::vbd2ll(dlat, dlon, brg2, dist, &slat, &slon, pEM);
   //std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
   //std::cout << "slat = " << std::setw(14) << slat << " [DEG]" << std::endl;
   //std::cout << "slon = " << std::setw(14) << slon << " [DEG]" << std::endl;
   //std::cout << std::endl;
   
}

//--------
// #17
//--------
void test_computeWorldMatrix()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_computeWorldMatrix" << std::endl << std::endl;
   
   double rlat = 0.0;
   double rlon = 0.0;
   osg::Matrixd wm;
   osg::Matrixd wmT;
   osg::Matrixd x;
   osg::Matrixd y;
   osg::Matrixd z;

   // Example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;
   std::cout << "==================================" << std::endl;
   
   rlat = 40.0;
   rlon = 50.0;
   std::cout << "rlat = 40; // reference latitude   [DEG]" << std::endl;
   std::cout << "rlon = 50; // reference longitude  [DEG]" << std::endl;
   std::cout << "Basic::Nav::computeWorldMatrix1(rlat, rlon, &wm);" << std::endl;
   std::cout << "wm = " << std::endl;
   Basic::Nav::computeWorldMatrix(rlat, rlon, &wm);
   showMatrix(wm);
   
   wmT = wm;
   wmT.transpose();
   std::cout << "wmT = " << std::endl;
   showMatrix(wmT);
   
   std::cout << "wm * wmT = " << std::endl;
   showMatrix(wm * wmT);
   
   
   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter reference latitude   [DEG] : "; std::cin  >> rlat;
   std::cout << "Enter reference longitude  [DEG] : "; std::cin  >> rlon;

   //-----------------------------------
   // bool computeWorldMatrix1(
   //      const double latD,      // IN: Reference latitude (degs)
   //      const double lonD,      // IN: Reference longitude (degs)
   //      osg::Matrixd* const wm   // OUT: Matrix
   //-----------------------------------
   Basic::Nav::computeWorldMatrix(rlat, rlon, &wm);
   
   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "wm = " << std::endl;
   showMatrix(wm);
   
   wmT = wm;
   wmT.transpose();
   std::cout << "wmT = " << std::endl;
   showMatrix(wmT);
   
   std::cout << "wm * wmT = " << std::endl;
   showMatrix(wm * wmT);
  
}

//--------
// #18
//--------
void test_computeRotationalMatrixDeg1()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_computeRotationalMatrixDeg" << std::endl << std::endl;

   // inputs
   double roll  = 0.0;
   double pitch = 0.0;
   double yaw   = 0.0;
   osg::Vec3d angles;

   // outputs
   osg::Matrixd rm;   
   osg::Vec2d scPhi;
   osg::Vec2d scTht;
   osg::Vec2d scPsi; 
   osg::Matrixd rmT;   

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;
   std::cout << "==================================" << std::endl;

   roll  = 10.0;
   pitch = 20.0;
   yaw   = 30.0;
   
   std::cout << "roll  = 10;  // roll  angle  [DEG]" << std::endl;
   std::cout << "pitch = 20;  // pitch angle  [DEG]" << std::endl;
   std::cout << "yaw   = 30;  // yaw   angle  [DEG]" << std::endl;
   std::cout << std::endl;
   
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
   Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);
   std::cout << "rm = " << std::endl;
   showMatrix(rm);
   
   rmT = rm;
   rmT.transpose();
   std::cout << "rmT = " << std::endl;
   showMatrix(rmT);
   
   std::cout << "rm * rmT = " << std::endl;
   showMatrix(rm * rmT);
 
   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter roll  angle  [DEG] : "; std::cin  >> roll;
   std::cout << "Enter pitch angle  [DEG] : "; std::cin  >> pitch;
   std::cout << "Enter yaw   angle  [DEG] : "; std::cin  >> yaw;
   std::cout << std::endl;
   
   //-----------------------------------
   // bool computeRotationalMatrixDeg(
   //      const double phiD,         // IN: roll angle (degrees)
   //      const double thetaD,       // IN: pitch angle (degrees)
   //      const double psiD,         // IN: yaw angle (degrees)
   //      osg::Matrixd* const rm,    // OUT: Rotational matrix
   //      osg::Vec2d* const scPhi=0, // OUT: Sin/Cos of phi (Optional)
   //      osg::Vec2d* const scTht=0, // OUT: Sin/Cos of theta (Optional)
   //      osg::Vec2d* const scPsi=0  // OUT: Sin/Cos of psi (Optional)
   //-----------------------------------
   std::cout << "rotational matrix from roll, pitch, yaw:" << std::endl;
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
   Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);

   std::cout << "rm = " << std::endl;
   showMatrix(rm);
   
   rmT = rm;
   rmT.transpose();
   std::cout << "rmT = " << std::endl;
   showMatrix(rmT);
   
   std::cout << "rm * rmT = " << std::endl;
   showMatrix(rm * rmT);
   
}

//--------
// #19
//--------
void test_computeRotationalMatrixDeg2()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_computeRotationalMatrixDeg" << std::endl << std::endl;

   // inputs
   double roll  = 0.0;
   double pitch = 0.0;
   double yaw   = 0.0;
   osg::Vec3d angles;

   // outputs
   osg::Matrixd rm;   
   osg::Vec2d scPhi;
   osg::Vec2d scTht;
   osg::Vec2d scPsi; 

   // Example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "roll  = 10;  // roll  angle  [DEG]" << std::endl;
   std::cout << "pitch = 20;  // pitch angle  [DEG]" << std::endl;
   std::cout << "yaw   = 30;  // yaw   angle  [DEG]" << std::endl;
   std::cout << std::endl;
   roll  = 10.0;
   pitch = 20.0;
   yaw   = 30.0;
   
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
   std::cout << "=> rm = " << std::endl;
   Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);
   showMatrix(rm);
 
   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter roll  angle  [DEG] : "; std::cin  >> roll;
   std::cout << "Enter pitch angle  [DEG] : "; std::cin  >> pitch;
   std::cout << "Enter yaw   angle  [DEG] : "; std::cin  >> yaw;
   std::cout << std::endl;
   
   //-----------------------------------
   // bool computeRotationalMatrixDeg(
   //      const double phiD,         // IN: roll angle (degrees)
   //      const double thetaD,       // IN: pitch angle (degrees)
   //      const double psiD,         // IN: yaw angle (degrees)
   //      osg::Matrixd* const rm,    // OUT: Rotational matrix
   //      osg::Vec2d* const scPhi=0, // OUT: Sin/Cos of phi (Optional)
   //      osg::Vec2d* const scTht=0, // OUT: Sin/Cos of theta (Optional)
   //      osg::Vec2d* const scPsi=0  // OUT: Sin/Cos of psi (Optional)
   //-----------------------------------
   std::cout << "rotational matrix from roll, pitch, yaw:" << std::endl;
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
   Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);
   std::cout << "rm = " << std::endl;
   showMatrix(rm);
   
   //-----------------------------------
   // bool computeRotationalMatrixDeg(
   //      const osg::Vec3d& angles,  // IN: euler angles [ phi theta psi ] (degrees)
   //      osg::Matrixd* const rm,    // OUT: Rotational matrix
   //      osg::Vec2d* const scPhi=0, // OUT: Sin/Cos of phi (Optional)
   //      osg::Vec2d* const scTht=0, // OUT: Sin/Cos of theta (Optional)
   //      osg::Vec2d* const scPsi=0  // OUT: Sin/Cos of psi (Optional)
   //-----------------------------------
   angles[0] = roll;
   angles[1] = pitch;
   angles[2] = yaw;

   std::cout << "Define angles vector:" << std::endl;
   std::cout << "angles[0] = roll;"  << std::endl;
   std::cout << "angles[1] = pitch;" << std::endl;
   std::cout << "angles[2] = yaw;"   << std::endl;
   std::cout << std::endl;
   
   std::cout << "rotational matrix from angles vector:" << std::endl;
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(angles, &rm, &scPhi, &scTht, &scPsi);" << std::endl;
   Basic::Nav::computeRotationalMatrixDeg(angles, &rm, &scPhi, &scTht, &scPsi);

   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "rm = " << std::endl;
   showMatrix(rm);
   
   std::cout << "scPhi = " << std::endl;
   showVec2(scPhi);
   std::cout << "scTht = " << std::endl;
   showVec2(scTht);
   std::cout << "scPsi = " << std::endl;
   showVec2(scPsi);
   
}

//--------
// #20
//--------
void test_computeEulerAnglesDeg()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_computeEulerAnglesDeg" << std::endl << std::endl;

   double roll  = 0.0;
   double pitch = 0.0;
   double yaw   = 0.0;
   osg::Matrixd rm;        // IN: Rotational matrix

   osg::Vec3d angles;      // OUT: euler angles (radians)
   osg::Vec2d scPhi;       // OUT: Sin/Cos of phi (Optional)
   osg::Vec2d scTht;       // OUT: Sin/Cos of theta (Optional)
   osg::Vec2d scPsi;       // OUT: Sin/Cos of psi (Optional)
   osg::Matrixd rmT;   


   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "roll  = 10;  // roll  angle  [DEG]" << std::endl;
   std::cout << "pitch = 20;  // pitch angle  [DEG]" << std::endl;
   std::cout << "yaw   = 30;  // yaw   angle  [DEG]" << std::endl;
   std::cout << std::endl;
   roll  = 10.0;
   pitch = 20.0;
   yaw   = 30.0;
   
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
   Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);
   std::cout << "=> rm = " << std::endl;
   showMatrix(rm);
   
   //rmT = rm;
   //rmT.transpose();
   //std::cout << "rmT = " << std::endl;
   //showMatrix(rmT);
   //
   //std::cout << "rm * rmT = " << std::endl;
   //showMatrix(rm * rmT);

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter roll  angle  [DEG] : "; std::cin  >> roll;
   std::cout << "Enter pitch angle  [DEG] : "; std::cin  >> pitch;
   std::cout << "Enter yaw   angle  [DEG] : "; std::cin  >> yaw;
   std::cout << std::endl;
   
   std::cout << "Compute rotational matrix from roll, pitch, yaw:" << std::endl;
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
   Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);

   std::cout << "rm = " << std::endl;
   showMatrix(rm);

   //-----------------------------------
   // Version using degrees
   // bool computeEulerAnglesDeg(
   //      const osg::Matrixd& rm,    // IN: Rotational matrix
   //      osg::Vec3d* const anglesD, // OUT: euler angles (degrees)
   //      osg::Vec2d* const scPhi=0, // OUT: Sin/Cos of phi (Optional)
   //      osg::Vec2d* const scTht=0, // OUT: Sin/Cos of theta (Optional)
   //      osg::Vec2d* const scPsi=0) // OUT: Sin/Cos of psi (Optional)
   //-----------------------------------
   std::cout << "Basic::Nav::computeEulerAnglesDeg(rm, &angles, &scPhi, &scTht, &scPsi);" << std::endl;
   Basic::Nav::computeEulerAnglesDeg(rm, &angles, &scPhi, &scTht, &scPsi);
   
   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "angles = (phi, tht, psi)'" << std::endl;
   showVec3(angles);
   
   std::cout << "scPhi = " << std::endl;
   showVec2(scPhi);
   std::cout << "scTht = " << std::endl;
   showVec2(scTht);
   std::cout << "scPsi = " << std::endl;
   showVec2(scPsi);

}

//--------
// #21
//--------
void test_convertPosVec2LL()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_convertPosVec2LL" << std::endl << std::endl;

   double rlat = 0.0;  // IN: Starting (reference) latitude  (degs)
   double rlon = 0.0;  // IN: Starting (reference) longitude (degs)
   osg::Vec3d pos;     // IN: NED position vector from ref point (meters)
   double lat = 0.0;   // OUT: Latitude  (degs)
   double lon = 0.0;   // OUT: Longitude (degs)
   double alt = 0.0;   // OUT: Altitude  (meters)

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;
   std::cout << "==================================" << std::endl;
   
   std::cout << "rlat = 40;  // reference latitude   [DEG]" << std::endl;
   std::cout << "rlon = 50;  // reference longitude  [DEG]" << std::endl;
   std::cout << std::endl;
   rlat = 40.0;
   rlon = 50.0;

   std::cout << "x = 1000  [M] : " << std::endl;
   std::cout << "y = 2000  [M] : " << std::endl;
   std::cout << "z = 3000  [M] : " << std::endl;
   std::cout << std::endl;
   pos[0] = 1000.0;
   pos[1] = 2000.0;
   pos[2] = 3000.0;

   std::cout << "Basic::Nav::convertPosVec2LL(rlat, rlon, pos, &lat, &lon, &alt);" << std::endl;
   Basic::Nav::convertPosVec2LL(rlat, rlon, pos, &lat, &lon, &alt);

   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> lat = " << std::setw(12) << lat << "  [DEG] : " << std::endl;
   std::cout << "=> lon = " << std::setw(12) << lon << "  [DEG] : " << std::endl;
   std::cout << "=> alt = " << std::setw(12) << alt << "  [M] : " << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter reference latitude   [DEG] : "; std::cin >> rlat;
   std::cout << "Enter reference longitude  [DEG] : "; std::cin >> rlon;
   std::cout << std::endl;
   
   std::cout << "Enter x  [M] : "; std::cin >> pos[0];
   std::cout << "Enter y  [M] : "; std::cin >> pos[1];
   std::cout << "Enter z  [M] : "; std::cin >> pos[2];
   std::cout << std::endl;

   //-----------------------------------
   // bool convertPosVec2LL(
   //      const double slat,         // IN: Starting (reference) latitude (degs)
   //      const double slon,         // IN: Starting (reference) longitude (degs)
   //      const osg::Vec3d& pos,     // IN: NED position vector from ref point (Meters)
   //      double* const lat,         // OUT: Latitude (degs)
   //      double* const lon,         // OUT: Longitude (degs)
   //      double* const alt)         // OUT: Altitude (meters)
   //-----------------------------------   
   Basic::Nav::convertPosVec2LL(rlat, rlon, pos, &lat, &lon, &alt);
   
   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "lat = " << std::setw(12) << lat << " [DEG]" << std::endl;
   std::cout << "lon = " << std::setw(12) << lon << " [DEG]" << std::endl;
   std::cout << "alt = " << std::setw(12) << alt << " [DEG]" << std::endl;
   std::cout << std::endl;
   
}

//--------
// #22
//--------
void test_convertLL2PosVec()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_convertLL2PosVec" << std::endl << std::endl;

   double rlat = 0.0;  // IN: Reference latitude  (degs)
   double rlon = 0.0;  // IN: Reference longitude (degs)
   double tlat = 0.0;  // IN: Target latitude     (degs)
   double tlon = 0.0;  // IN: Target longitude    (degs)
   double talt = 0.0;  // IN: Target altitude     (meters)
   osg::Vec3d pos;     // OUT: NED position vector from ref point (meters)

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "rlat = 40;" << std::endl;
   std::cout << "rlon = 50;" << std::endl;
   rlat = 40;
   rlon = 50;

   std::cout << "tlat = 41;" << std::endl;
   std::cout << "tlon = 51;" << std::endl;
   std::cout << "talt = 10000.0;" << std::endl;
   std::cout << std::endl;
   tlat = 41;
   tlon = 51;
   talt = 10000.0;
   
   std::cout << "Basic::Nav::convertLL2PosVec(rlat, rlon, tlat, tlon, talt, &pos);" << std::endl;
   Basic::Nav::convertLL2PosVec(rlat, rlon, tlat, tlon, talt, &pos);

   std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
   std::cout << "=> pos[0] = " << std::setw(12) << pos[0] << " [M]  north" << std::endl;
   std::cout << "=> pos[1] = " << std::setw(12) << pos[1] << " [M]  east" << std::endl;
   std::cout << "=> pos[2] = " << std::setw(12) << pos[2] << " [M]  down" << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:"      << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter reference latitude   [DEG] : "; std::cin >> rlat;
   std::cout << "Enter reference longitude  [DEG] : "; std::cin >> rlon;
   std::cout << std::endl;
   
   std::cout << "Enter target latitude   [M] : "; std::cin >> tlat;
   std::cout << "Enter target longitude  [M] : "; std::cin >> tlon;
   std::cout << "Enter target altitude   [M] : "; std::cin >> talt;
   std::cout << std::endl;

   //-----------------------------------
   // bool convertLL2PosVec(
   //      const double rlat,      // IN: Reference latitude  (degs)
   //      const double rlon,      // IN: Reference longitude (degs)
   //      const double tlat,      // IN: Target latitude     (degs)
   //      const double tlon,      // IN: Target longitude    (degs)
   //      const double talt,      // IN: Target altitude     (meters)
   //      osg::Vec3d* const pos)  // OUT: NED position vector from ref point (meters)
   //-----------------------------------
   Basic::Nav::convertLL2PosVec(rlat, rlon, tlat, tlon, talt, &pos);
   
   // output results
   std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
   std::cout << "pos[0] = " << std::setw(12) << pos[0] << " [M]  north" << std::endl;
   std::cout << "pos[1] = " << std::setw(12) << pos[1] << " [M]  east"  << std::endl;
   std::cout << "pos[2] = " << std::setw(12) << pos[2] << " [M]  down"  << std::endl;

}

//--------
// #23
//--------
void test_convertEcef2Geod()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_convertEcef2Geod" << std::endl << std::endl;

   // inputs
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;
   osg::Vec3d xyz;
   double XYZ[3];
   const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;
   
   // outputs
   double lat = 0.0;
   double lon = 0.0;
   double alt = 0.0;
   osg::Vec3d lla;
   double LLA[3];
   
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:"                   << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Case 1:" << std::endl;
   std::cout << "double x,y,z;" << std::endl;
   std::cout << "double lat,lon,alt;" << std::endl;
   std::cout << std::endl;
   std::cout << "x = 1000.0;  // [M]" << std::endl;
   std::cout << "y = 2000.0;  // [M]" << std::endl;
   std::cout << "z = 3000.0;  // [M]" << std::endl;
   x = 1000.0;  // [M]
   y = 2000.0;  // [M]
   z = 3000.0;  // [M]

   std::cout << std::endl;
   std::cout << "Basic::Nav::convertEcef2Geod(x, y, z, &lat, &lon, &alt, pEM);" << std::endl;
   Basic::Nav::convertEcef2Geod(x, y, z, &lat, &lon, &alt, pEM);
   std::cout << std::endl;
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> lat = " << std::setw(14) << lat << "  // [M]" << std::endl;
   std::cout << "=> lon = " << std::setw(14) << lon << "  // [M]" << std::endl;
   std::cout << "=> alt = " << std::setw(14) << alt << "  // [M]" << std::endl;
   std::cout << std::endl;
   
   xyz[0] = x;  // [M]
   xyz[1] = y;  // [M]
   xyz[2] = z;  // [M]
   std::cout << "----------------------------------" << std::endl;
   std::cout << "Case 2:" << std::endl;
   std::cout << "osg::Vec3d xyz;" << std::endl;
   std::cout << "osg::Vec3d lla;" << std::endl;
   std::cout << std::endl;
   std::cout << "xyz[0] = x;  // [M]" << std::endl;
   std::cout << "xyz[1] = y;  // [M]" << std::endl;
   std::cout << "xyz[2] = z;  // [M]" << std::endl;
   std::cout << std::endl;
   std::cout << "Basic::Nav::convertEcef2Geod(xyz, &lla, pEM);" << std::endl;
   Basic::Nav::convertEcef2Geod(xyz, &lla, pEM);
   std::cout << std::endl;
   std::cout << "=> lla[0] = " << std::setw(14) << lla[0] << "  // [DEG]" << std::endl;
   std::cout << "=> lla[1] = " << std::setw(14) << lla[1] << "  // [DEG]" << std::endl;
   std::cout << "=> lla[2] = " << std::setw(14) << lla[2] << "  // [M]"   << std::endl;
   std::cout << std::endl;
   
   XYZ[0] = x;  // [M]
   XYZ[1] = y;  // [M]
   XYZ[2] = z;  // [M]
   std::cout << "----------------------------------" << std::endl;
   std::cout << "Case 3:" << std::endl;
   std::cout << "double XYZ[3];" << std::endl;
   std::cout << "double LLA[3];" << std::endl;
   std::cout << std::endl;
   std::cout << "XYZ[0] = x;  // [M]" << std::endl;
   std::cout << "XYZ[1] = y;  // [M]" << std::endl;
   std::cout << "XYZ[2] = z;  // [M]" << std::endl;
   std::cout << std::endl;
   std::cout << "Basic::Nav::convertEcef2Geod(XYZ, &LLA, pEM);" << std::endl;
   Basic::Nav::convertEcef2Geod(XYZ, LLA, pEM);
   std::cout << std::endl;
   std::cout << "=> LLA[0] = " << std::setw(14) << LLA[0] << "  // [DEG]" << std::endl;
   std::cout << "=> LLA[1] = " << std::setw(14) << LLA[1] << "  // [DEG]" << std::endl;
   std::cout << "=> LLA[2] = " << std::setw(14) << LLA[2] << "  // [M]"   << std::endl;
   std::cout << std::endl;

   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:"      << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter x  [M] : "; std::cin >> x;
   std::cout << "Enter y  [M] : "; std::cin >> y;
   std::cout << "Enter z  [M] : "; std::cin >> z;
   std::cout << std::endl;

   // copy to xyz
   xyz[0] = x;
   xyz[1] = y;
   xyz[2] = z;
   
   // copy to XYZ
   XYZ[0] = x;
   XYZ[1] = y;
   XYZ[2] = z;
   
   //----------------------------------------------------------
   // Convert ECEF (XYZ coordinates) to Geodetic (LLA coordinates)
   //----------------------------------------------------------
   // bool convertEcef2Geod(
   //      const double x,      // IN: ECEF X component   (meters)
   //      const double y,      // IN: ECEF Y component   (meters)
   //      const double z,      // IN: ECEF Z component   (meters)
   //      double* const pLat,  // OUT: Geodetic latitude  (degrees)
   //      double* const pLon,  // OUT: Geodetic longitude (degrees)
   //      double* const pAlt,  // OUT: Geodetic altitude  (meters)
   //      const Basic::EarthModel* const pEM=0)  // IN: Optional: Pointer to earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::convertEcef2Geod(x, y, z, &lat, &lon, &alt, pEM);
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "*** single variables: x,y,z => lat,lon,alt ***" << std::endl;
   std::cout << "lat    = " << std::setw(14) << lat << " [DEG]" << std::endl;
   std::cout << "lon    = " << std::setw(14) << lon << " [DEG]" << std::endl;
   std::cout << "alt    = " << std::setw(14) << alt << " [M]" << std::endl;
   std::cout << std::endl;

   //-----------------------------------
   // Using osg::Vec3d vectors
   // bool convertEcef2Geod(
   //      const osg::Vec3d& xyz,      // IN: ECEF [ IX IY IZ ]
   //      osg::Vec3d* const lla,      // OUT: Geodetic [ ILAT ILON IALT ]
   //      const Basic::EarthModel* const pEM=0)     // IN: Optional: Pointer to earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::convertEcef2Geod(xyz, &lla, pEM);
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "*** vector: xyz => lla ***" << std::endl;
   std::cout << "lla[0] = " << std::setw(14) << lla[0] << " [DEG]" << std::endl;
   std::cout << "lla[1] = " << std::setw(14) << lla[1] << " [DEG]" << std::endl;
   std::cout << "lla[2] = " << std::setw(14) << lla[2] << " [M]" << std::endl;
   std::cout << std::endl;

   //-----------------------------------
   // Using arrays vectors
   // bool convertEcef2Geod(
   //      const double abc[3],        // IN: ECEF [ IX IY IZ ]
   //      double lla[3],              // OUT: Geodetic [ ILAT ILON IALT ]
   //      const Basic::EarthModel* const pEM=0)     // IN: Optional: Pointer to earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::convertEcef2Geod(XYZ, LLA, pEM);
   
   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "*** array: XYZ => LLA ***" << std::endl;
   std::cout << "LLA[0] = " << std::setw(14) << LLA[0] << " [DEG]" << std::endl;
   std::cout << "LLA[1] = " << std::setw(14) << LLA[1] << " [DEG]" << std::endl;
   std::cout << "LLA[2] = " << std::setw(14) << LLA[2] << " [M]" << std::endl;
   std::cout << std::endl;

}

//--------
// #24
//--------
void test_convertGeod2Ecef()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_convertGeod2Ecef" << std::endl << std::endl;

   // inputs
   double lat = 0.0;
   double lon = 0.0;
   double alt = 0.0;
   osg::Vec3d lla;
   double LLA[3];
   const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;

   // outputs
   double x = 0.0;
   double y = 0.0;
   double z = 0.0;
   osg::Vec3d xyz;
   double XYZ[3];

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Case 1:" << std::endl;
   std::cout << "double lat,lon,alt;" << std::endl;
   std::cout << "double x,y,z;" << std::endl;
   std::cout << std::endl;
   
   std::cout << "lat = 40.0;     // [DEG]" << std::endl;
   std::cout << "lon = 50.0;     // [DEG]" << std::endl;
   std::cout << "alt = 10000.0;  // [M]"   << std::endl;
   std::cout << std::endl;
   lat = 40.0;     // [DEG]
   lon = 50.0;     // [DEG]
   alt = 10000.0;  // [M]
   
   std::cout << "Basic::Nav::convertGeod2Ecef(lat, lon, alt, &x, &y, &z, pEM);" << std::endl;
   Basic::Nav::convertGeod2Ecef(lat, lon, alt, &x, &y, &z, pEM);
   std::cout << std::endl;
   
   std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
   std::cout << "=> x      = " << std::setw(14) << x << "  // [M]" << std::endl;
   std::cout << "=> y      = " << std::setw(14) << y << "  // [M]" << std::endl;
   std::cout << "=> z      = " << std::setw(14) << z << "  // [M]" << std::endl;
   std::cout << std::endl;
   
   std::cout << "----------------------------------" << std::endl;
   std::cout << "Case 2:" << std::endl;
   std::cout << "osg::Vec3d lla;" << std::endl;
   std::cout << "osg::Vec3d xyz;" << std::endl;
   std::cout << std::endl;
   
   std::cout << "lla[0] = lat;  // [DEG]" << std::endl;
   std::cout << "lla[1] = lon;  // [DEG]" << std::endl;
   std::cout << "lla[2] = alt;  // [M]"   << std::endl;
   std::cout << std::endl;
   lla[0] = lat;  // [DEG]
   lla[1] = lon;  // [DEG]
   lla[2] = alt;  // [M]
   
   std::cout << "Basic::Nav::convertGeod2Ecef(lla, &xyz, pEM);" << std::endl;
   Basic::Nav::convertGeod2Ecef(lla, &xyz, pEM);
   std::cout << std::endl;
   
   std::cout << "=> xyz[0] = " << std::setw(14) << xyz[0] << "  // [M]" << std::endl;
   std::cout << "=> xyz[1] = " << std::setw(14) << xyz[1] << "  // [M]" << std::endl;
   std::cout << "=> xyz[2] = " << std::setw(14) << xyz[2] << "  // [M]" << std::endl;
   std::cout << std::endl;
   
   std::cout << "----------------------------------" << std::endl;
   std::cout << "Case 3:" << std::endl;
   std::cout << "double LLA[3];" << std::endl;
   std::cout << "double XYZ[3];" << std::endl;
   std::cout << std::endl;
   
   std::cout << "LLA[0] = lat;  // [DEG]" << std::endl;
   std::cout << "LLA[1] = lon;  // [DEG]" << std::endl;
   std::cout << "LLA[2] = alt;  // [M]"   << std::endl;
   std::cout << std::endl;
   LLA[0] = lat;  // [DEG]
   LLA[1] = lon;  // [DEG]
   LLA[2] = alt;  // [M]
   
   std::cout << "Basic::Nav::convertGeod2Ecef(LLA, XYZ, pEM);" << std::endl;
   Basic::Nav::convertGeod2Ecef(LLA, XYZ, pEM);
   std::cout << std::endl;
   
   std::cout << "=> XYZ[0] = " << std::setw(14) << XYZ[0] << "  // [M]" << std::endl;
   std::cout << "=> XYZ[1] = " << std::setw(14) << XYZ[1] << "  // [M]" << std::endl;
   std::cout << "=> XYZ[2] = " << std::setw(14) << XYZ[2] << "  // [M]" << std::endl;
   std::cout << std::endl;


   // Enter data from the keyboard
   std::cout << "==================================" << std::endl;
   std::cout << "Enter data from the keyboard:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "Enter lat  [DEG] : "; std::cin >> lat;
   std::cout << "Enter lon  [DEG] : "; std::cin >> lon;
   std::cout << "Enter alt  [M]   : "; std::cin >> alt;
   std::cout << std::endl;
   
   // copy to lla
   lla[0] = lat;
   lla[1] = lon;
   lla[2] = alt;
   
   // copy to LLA
   LLA[0] = lat;
   LLA[1] = lon;
   LLA[2] = alt;
   
   //----------------------------------------------------------
   // Convert Geodetic (LLA coordinates) to ECEF (XYZ coordinates)
   //----------------------------------------------------------
   // bool convertGeod2Ecef(
   //      const double lat,           // IN: Geodetic latitude  (degrees)
   //      const double lon,           // IN: Geodetic longitude (degrees)
   //      const double alt,           // IN: Geodetic altitude  (meters)
   //      double* const pX,           // OUT: ECEF X component   (meters)   
   //      double* const pY,           // OUT: ECEF Y component   (meters)
   //      double* const pZ,           // OUT: ECEF Z component   (meters)
   //      const Basic::EarthModel* const pEM=0)     // IN: Optional: Pointer to earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::convertGeod2Ecef(lat, lon, alt, &x, &y, &z, pEM);

   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "*** single variables: lat,lon,alt => x,y,z ***" << std::endl;
   std::cout << "x      = " << std::setw(14) << x << " [M]" << std::endl;
   std::cout << "y      = " << std::setw(14) << y << " [M]" << std::endl;
   std::cout << "z      = " << std::setw(14) << z << " [M]" << std::endl;
   std::cout << std::endl;

   //-----------------------------------
   // Using osg::Vec3d vectors
   // bool convertGeod2Ecef(
   //      const double lla[3],        // IN: Geodetic [ ILAT ILON IALT ]
   //      double ecef[3],             // OUT: ECEF [ IX IY IZ ]
   //      const Basic::EarthModel* const pEM=0)     // IN: Optional: Pointer to earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::convertGeod2Ecef(lla, &xyz, pEM);
     
   // output results
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "*** vector: lla => xyz ***" << std::endl;
   std::cout << "xyz[0] = " << std::setw(14) << xyz[0] << " [M]" << std::endl;
   std::cout << "xyz[1] = " << std::setw(14) << xyz[1] << " [M]" << std::endl;
   std::cout << "xyz[2] = " << std::setw(14) << xyz[2] << " [M]" << std::endl;
   std::cout << std::endl;
     
   //-----------------------------------
   // Using array vectors
   // bool convertGeod2Ecef(
   //      const osg::Vec3d& lla,      // IN: Geodetic [ ILAT ILON IALT ]
   //      osg::Vec3d* const ecef,     // OUT: ECEF [ IX IY IZ ]
   //      const Basic::EarthModel* const pEM=0)     // IN: Optional: Pointer to earth model (default: WGS-84)
   //-----------------------------------
   Basic::Nav::convertGeod2Ecef(LLA, XYZ, pEM);

   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "*** array: LLA => XYZ ***" << std::endl;
   std::cout << "XYZ[0] = " << std::setw(14) << XYZ[0] << " [M]" << std::endl;
   std::cout << "XYZ[1] = " << std::setw(14) << XYZ[1] << " [M]" << std::endl;
   std::cout << "XYZ[2] = " << std::setw(14) << XYZ[2] << " [M]" << std::endl;
   std::cout << std::endl;

}


} // end namespace TestNav 
} // end namespace Eaagles

//==============================================================================
int main(int argc, char* argv[])
{
   return Eaagles::TestNav::testNavFns();

}


//-----------------------------------------------------------------------------
// Test Basic::Nav functions
//-----------------------------------------------------------------------------

#include "openeaagles/basic/Nav.h"

#include "openeaagles/basic/EarthModel.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/units/Distances.h"

#include <iostream>
#include <iomanip>


namespace Eaagles {
namespace TestNav {

// -----------------------------------------------------------------------------
// Global Variables (and Constants)
// -----------------------------------------------------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double tlat = 1.0;
   double tlon = 1.0;
   double brng = 45.0;
   double dist = 100.0;
   const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;

   int testNumber = 0;
   char ynCont = 'y';
   char ynMenu = 'y';
   char* enterYourOwnData = "Enter your own data? (y/n) : ";
   
//------------------------------------------------------------------------------
// prototype functions
//------------------------------------------------------------------------------
int showVec2(const osg::Vec2d V);
int showVec3(const osg::Vec3d V);
int showMatrix(const osg::Matrixd M);

void test01_fbd2llE();
void test02_fll2bdE();
void test03_fbd2llS();
void test04_fll2bdS();
void test05_aer2xyz();
void test06_aer2xyz();
void test07_xyz2aer();
void test08_xyz2aer();
void test09_gbd2ll();
void test10_gll2bd();
void test11_gbd2llS();
void test12_gll2bdS();
void test13_glla2bd();
void test14_glla2bdS();
void test15_vbd2ll();
void test16_vll2bd();

void test17_computeWorldMatrix();
void test18_computeEulerAnglesDeg();

void test19_computeRotationalMatrix();
void test20_computeRotationalMatrix();
void test21_computeRotationalMatrixDeg();
void test22_computeRotationalMatrixDeg();

void test23_convertPosVec2LL();
void test24_convertLL2PosVec();
void test25_convertEcef2Geod();
void test26_convertGeod2Ecef();

void test99_printAllExamples();

void displayNavTestFunctions();
void selectNavTestFunction(int n);


//------------------------------------------------------------------------------
// Test Nav class functions 
//------------------------------------------------------------------------------
int testNavFns()
{
   while (ynCont != 'n') {
      if (ynMenu != 'n') {
         displayNavTestFunctions();
      }
      
      std::cout << "Enter a Nav function test number: ";
      std::cin  >> testNumber; 

      
      switch (testNumber) {
         // Direct and Inverse Methods
         case  1: test01_fbd2llE();                      break;
         case  2: test02_fll2bdE();                      break;
         case  3: test03_fbd2llS();                      break;
         case  4: test04_fll2bdS();                      break;
         case  5: test05_aer2xyz();                      break;
         case  6: test06_aer2xyz();                      break;
         case  7: test07_xyz2aer();                      break;
         case  8: test08_xyz2aer();                      break;
         case  9: test09_gbd2ll();                       break;
         case 10: test10_gll2bd();                       break;
         case 11: test11_gbd2llS();                      break;
         case 12: test12_gll2bdS();                      break;
         case 13: test13_glla2bd();                      break;
         case 14: test14_glla2bdS();                     break;
         case 15: test15_vbd2ll();                       break;
         case 16: test16_vll2bd();                       break;

         // Matrix Generators
         case 17: test17_computeWorldMatrix();           break;
         case 18: test18_computeEulerAnglesDeg();        break;

         case 19: test19_computeRotationalMatrix();      break;
         case 20: test20_computeRotationalMatrix();      break;
         case 21: test21_computeRotationalMatrixDeg();   break;
         case 22: test22_computeRotationalMatrixDeg();   break;

         case 23: test23_convertPosVec2LL();             break;
         case 24: test24_convertLL2PosVec();             break;
         case 25: test25_convertEcef2Geod();             break;
         case 26: test26_convertGeod2Ecef();             break;

         // Print All Results
         case 99: test99_printAllExamples();             break;
         
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
// Display Nav Test Functions 
//------------------------------------------------------------------------------
void displayNavTestFunctions()
{
   std::cout << "=====================================================" << std::endl;
   std::cout << "Nav Test Functions" << std::endl;
   std::cout << "=====================================================" << std::endl;
   
   // Direct and Inverse Methods
   std::cout << "   1)  test01_fbd2llE()"                      << std::endl
             << "   2)  test02_fll2bdE()"                      << std::endl
             << "   3)  test03_fbd2llS()"                      << std::endl
             << "   4)  test04_fll2bdS()"                      << std::endl
             << "   5)  test05_aer2xyz()"                      << std::endl
             << "   6)  test06_aer2xyz()"                      << std::endl
             << "   7)  test07_xyz2aer()"                      << std::endl
             << "   8)  test08_xyz2aer()"                      << std::endl
             << "   9)  test09_gbd2ll()"                       << std::endl
             << "  10)  test10_gll2bd()"                       << std::endl
             << "  11)  test11_gbd2llS()"                      << std::endl
             << "  12)  test12_gll2bdS()"                      << std::endl
             << "  13)  test13_glla2bd()"                      << std::endl
             << "  14)  test14_glla2bdS()"                     << std::endl
             << "  15)  test15_vbd2ll()"                       << std::endl
             << "  16)  test16_vll2bd()"                       << std::endl
                                                             
   // Matrix Generators                                      
             << "  17)  test17_computeWorldMatrix()"           << std::endl
             << "  18)  test18_computeEulerAnglesDeg()"        << std::endl
             
             << "  19)  test19_computeRotationalMatrix()"      << std::endl
             << "  20)  test20_computeRotationalMatrix()"      << std::endl
             << "  21)  test21_computeRotationalMatrixDeg()"   << std::endl
             << "  22)  test22_computeRotationalMatrixDeg()"   << std::endl
             
             << "  23)  test23_convertPosVec2LL()"             << std::endl
             << "  24)  test24_convertLL2PosVec()"             << std::endl
             << "  25)  test25_convertEcef2Geod()"             << std::endl
             << "  26)  test26_convertGeod2Ecef()"             << std::endl

   // Print all example results to output file
             << "  99)  Print all examples to an output file"  << std::endl
             << std::endl;
}

//------------------------------------------------------------------------------
// Test Nav class functions 
//------------------------------------------------------------------------------
void test99_printAllExamples()
{
   test01_fbd2llE();
   test02_fll2bdE();
   test03_fbd2llS();
   test04_fll2bdS();
   test05_aer2xyz();
   test06_aer2xyz();
   test07_xyz2aer();
   test08_xyz2aer();
   test09_gbd2ll();
   test10_gll2bd();
   test11_gbd2llS();
   test12_gll2bdS();
   test13_glla2bd();
   test14_glla2bdS();
   test15_vbd2ll();
   test16_vll2bd();

   test17_computeWorldMatrix();
   test18_computeEulerAnglesDeg();

   test19_computeRotationalMatrix();
   test20_computeRotationalMatrix();
   test21_computeRotationalMatrixDeg();
   test22_computeRotationalMatrixDeg();

   test23_convertPosVec2LL();
   test24_convertLL2PosVec();
   test25_convertEcef2Geod();
   test26_convertGeod2Ecef();

}

//------------------------------------------------------------------------------
// Test navigation functions
//------------------------------------------------------------------------------

//--------
// #1
//--------
void test01_fbd2llE()
{
   std::cout << std::endl
             << "==============================================" << std::endl
             << "Example problem 1: test01_fbd2llE             " << std::endl
             << std::endl;
   
   std::cout 
   << "--------------------------------------------------------------------------" << std::endl
   << "bool fbd2llE(                                                             " << std::endl
   << "  const double  slat,                    // IN:  Source latitude     [DEG]" << std::endl
   << "  const double  slon,                    // IN:  Source longitude    [DEG]" << std::endl
   << "  const double  brng,                    // IN:  Bearing  to target  [DEG]" << std::endl
   << "  const double  dist,                    // IN:  Distance to target  [NM] " << std::endl
   << "  double* const tlat,                    // OUT: Target latitude     [DEG]" << std::endl
   << "  double* const tlon,                    // OUT: Target longitude    [DEG]" << std::endl
   << "  const Basic::EarthModel* const pEM=0)  // IN:  Pointer to earth model   " << std::endl
   << "                                         //      (default: WGS-84)        " << std::endl
   << "--------------------------------------------------------------------------" << std::endl
   << std::endl;
   
   std::cout << "INPUTS:" << std::endl;
   std::cout << "slat = 0;       // source latitude   [DEG]" << std::endl
             << "slon = 0;       // source longitude  [DEG]" << std::endl
             << "brng = 45;      // target bearing    [DEG]" << std::endl
             << "dist = 100;     // target distance   [NM] " << std::endl
             << "pEM  = wgs84;   // pointer to earth model " << std::endl
             << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl;
   std::cout << "tlat = 1.1843;  // target latitude   [DEG]" << std::endl
             << "tlon = 1.1764;  // target longitude  [DEG]" << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         double slat = 0.0;
         double slon = 0.0;
         double brng = 0.0;
         double dist = 0.0;
         double tlat = 0.0;
         double tlon = 0.0;
         const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;

         std::cout << "Enter source latitude   [DEG] : "; std::cin >> slat;
         std::cout << "Enter source longitude  [DEG] : "; std::cin >> slon;
         std::cout << "Enter target bearing    [DEG] : "; std::cin >> brng;
         std::cout << "Enter target distance   [NM]  : "; std::cin >> dist;
         std::cout << std::endl;

         Basic::Nav::fbd2llE(slat, slon, brng, dist, &tlat, &tlon, pEM);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "tlat = " << std::setw(10) << tlat << " [DEG]" << std::endl;
         std::cout << "tlon = " << std::setw(10) << tlon << " [DEG]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #2
//--------
void test02_fll2bdE()
{
   std::cout << "==============================================" << std::endl
             << "Example problem 2: test02_fll2bdE             " << std::endl
             << std::endl;

   std::cout 
   << "--------------------------------------------------------------------------" << std::endl
   << "bool fll2bdE(                                                             " << std::endl
   << "  const double  slat,                    // IN:  Source latitude     [DEG]" << std::endl
   << "  const double  slon,                    // IN:  Source longitude    [DEG]" << std::endl
   << "  double* const tlat,                    // IN:  Target latitude     [DEG]" << std::endl
   << "  double* const tlon,                    // IN:  Target longitude    [DEG]" << std::endl
   << "  const double  brng,                    // OUT: Bearing  to target  [DEG]" << std::endl
   << "  const double  dist,                    // OUT: Distance to target  [NM] " << std::endl
   << "  const Basic::EarthModel* const pEM=0)  // IN:  Pointer to earth model   " << std::endl
   << "                                         //      (default: WGS-84)        " << std::endl
   << "--------------------------------------------------------------------------" << std::endl
   << std::endl;

   std::cout << "INPUTS:" << std::endl;
   std::cout << "slat = 0;        // source latitude   [DEG]" << std::endl
             << "slon = 0;        // source longitude  [DEG]" << std::endl
             << "tlat = 1;        // target latitude   [DEG]" << std::endl
             << "tlon = 1;        // target longitude  [DEG]" << std::endl
             << "pEM  = wgs84;    // pointer to earth model " << std::endl
             << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl;
   std::cout << "brng = 45.1924;  // target bearing    [DEG]" << std::endl
             << "dist = 84.7211;  // target distance   [NM]"  << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double slat = 0.0;
         double slon = 0.0;
         double tlat = 0.0;
         double tlon = 0.0;
         double brng = 0.0;
         double dist = 0.0;
         const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;

         std::cout << "Enter source latitude   [DEG] : "; std::cin >> slat;
         std::cout << "Enter source longitude  [DEG] : "; std::cin >> slon;
         std::cout << "Enter target latitude   [DEG] : "; std::cin >> tlat;
         std::cout << "Enter target longitude  [DEG] : "; std::cin >> tlon;
         std::cout << std::endl;
            
         Basic::Nav::fll2bdE(slat, slon, tlat, tlon, &brng, &dist, pEM);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "brng = " << std::setw(10) << brng << " [DEG]" << std::endl;
         std::cout << "dist = " << std::setw(10) << dist << " [NM] " << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #3
//--------
void test03_fbd2llS()
{
   std::cout << "==============================================" << std::endl
             << "Example problem: 3) test03_fbd2llS            " << std::endl
             << std::endl;
   
   std::cout 
   << "--------------------------------------------------------------------------" << std::endl
   << "bool fbd2llS(                                                             " << std::endl
   << "  const double  slat,                    // IN:  Source latitude     [DEG]" << std::endl
   << "  const double  slon,                    // IN:  Source longitude    [DEG]" << std::endl
   << "  const double  brng,                    // IN:  Bearing  to target  [DEG]" << std::endl
   << "  const double  dist,                    // IN:  Distance to target  [NM] " << std::endl
   << "  double* const tlat,                    // OUT: Target latitude     [DEG]" << std::endl
   << "  double* const tlon)                    // OUT: Target longitude    [DEG]" << std::endl
   << "--------------------------------------------------------------------------" << std::endl
   << std::endl;

   std::cout << "INPUTS:" << std::endl;
   std::cout << "slat = 0;       // source latitude   [DEG]" << std::endl
             << "slon = 0;       // source longitude  [DEG]" << std::endl
             << "brng = 45;      // target bearing    [DEG]" << std::endl
             << "dist = 100;     // target distance   [NM] " << std::endl
             << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl;
   std::cout << "tlat = 1.1785;  // target latitude   [DEG]" << std::endl
             << "tlon = 1.1785;  // target longitude  [DEG]" << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double slat = 0.0;
         double slon = 0.0;
         double brng = 0.0;
         double dist = 0.0;
         double tlat = 0.0;
         double tlon = 0.0;

         std::cout << "Enter source latitude   [DEG] : "; std::cin >> slat;
         std::cout << "Enter source longitude  [DEG] : "; std::cin >> slon;
         std::cout << "Enter source bearing    [DEG] : "; std::cin >> brng;
         std::cout << "Enter source distance   [NM]  : "; std::cin >> dist;
         std::cout << std::endl;
            
         Basic::Nav::fbd2llS(slat, slon, brng, dist, &tlat, &tlon);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);   
         std::cout << "tlat = " << std::setw(10) << tlat << " [DEG]" << std::endl;
         std::cout << "tlon = " << std::setw(10) << tlon << " [DEG]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #4
//--------
void test04_fll2bdS()
{
   std::cout << "==============================================" << std::endl
             << "Example problem 4: test04_fll2bdS             " << std::endl
             << std::endl;

   std::cout 
   << "--------------------------------------------------------------------------" << std::endl
   << "bool fll2bdS(                                                             " << std::endl
   << "  const double  slat,                    // IN:  Source latitude     [DEG]" << std::endl
   << "  const double  slon,                    // IN:  Source longitude    [DEG]" << std::endl
   << "  double* const tlat,                    // IN:  Target latitude     [DEG]" << std::endl
   << "  double* const tlon,                    // IN:  Target longitude    [DEG]" << std::endl
   << "  const double  brng,                    // OUT: Bearing  to target  [DEG]" << std::endl
   << "  const double  dist)                    // OUT: Distance to target  [NM] " << std::endl
   << "--------------------------------------------------------------------------" << std::endl
   << std::endl;

   std::cout << "INPUTS:" << std::endl;
   std::cout << "slat = 0;        // source latitude   [DEG]" << std::endl
             << "slon = 0;        // source longitude  [DEG]" << std::endl
             << "tlat = 1;        // target latitude   [DEG]" << std::endl
             << "tlon = 1;        // target longitude  [DEG]" << std::endl
             << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl;
   std::cout << "brng = 45.0000;  // target bearing   [DEG]" << std::endl
             << "dist = 84.8528;  // target distance  [DEG]" << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double slat = 0.0;
         double slon = 0.0;
         double tlat = 0.0;
         double tlon = 0.0;
         double brng = 0.0;
         double dist = 0.0;
         
         std::cout << "Enter source latitude   [DEG] : "; std::cin >> slat;
         std::cout << "Enter source longitude  [DEG] : "; std::cin >> slon;
         std::cout << "Enter target latitude   [DEG] : "; std::cin >> tlat;
         std::cout << "Enter target longitude  [DEG] : "; std::cin >> tlon;
         std::cout << std::endl;
            
         Basic::Nav::fll2bdS(slat, slon, tlat, tlon, &brng, &dist);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "brng = " << std::setw(10) << brng << " [DEG]" << std::endl;
         std::cout << "dist = " << std::setw(10) << dist << " [NM] " << std::endl;
         std::cout << std::endl;
      }
   }
}


//--------
// #5
//--------
void test05_aer2xyz()
{
   std::cout << "=============================================" << std::endl
             << "Example problem 5: test05_aer2xyz - using euler angles" << std::endl
             << std::endl;

   std::cout
   << "--------------------------------------------------------------------------" << std::endl
   << "Using euler angles                                                        " << std::endl
   << "bool aer2xyz(                                                             " << std::endl
   << "   osg::Vec3d* const pos,  // OUT: position vector [M]   (NED, player cntr)" << std::endl
   << "   const double azim,      // IN:  azimuth         [RAD]                  " << std::endl
   << "   const double elev,      // IN:  elevation       [RAD] (positive up)    " << std::endl
   << "   const double ranj)      // IN:  range           [M]                    " << std::endl
   << "--------------------------------------------------------------------------" << std::endl
   << std::endl;
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "INPUTS:" << std::endl;
   std::cout << "azim      = 45;         // azimuth    [DEG]" << std::endl
             << "elev      = 30;         // elevation  [DEG]" << std::endl
             << "ranj      = 1000;       // range      [M]  " << std::endl
             << std::endl;
   
   std::cout << "Convert azim and elev to radians" << std::endl
             << "azim = azim * Basic::Angle::D2RCC = 0.7854 [RAD]" << std::endl
             << "elev = elev * Basic::Angle::D2RCC = 0.5236 [RAD]" << std::endl
             << std::endl;


   std::cout << "OUTPUTS:" << std::endl;
   std::cout << "=> pos[0] = " << std::setw(10) <<  612.3724 << "  // x  [M]" << std::endl
             << "=> pos[1] = " << std::setw(10) <<  612.3724 << "  // y  [M]" << std::endl
             << "=> pos[2] = " << std::setw(10) << -500.0000 << "  // z  [M]" << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double azim = 0.0;
         double elev = 0.0;
         double ranj = 0.0;
         osg::Vec3d pos;
         
         std::cout << "Enter azimuth    [DEG] : "; std::cin >> azim;
         std::cout << "Enter elevation  [DEG] : "; std::cin >> elev;
         std::cout << "Enter range      [M]   : "; std::cin >> ranj;
         std::cout << std::endl;

         azim *= Basic::Angle::D2RCC;
         elev *= Basic::Angle::D2RCC;

         std::cout << "azimuth   = 0.7854    [RAD]" << std::endl
                   << "elevation = 0.5236    [RAD]" << std::endl
                   << "range     = 1000.0000 [M]  " << std::endl
                   << std::endl;

         Basic::Nav::aer2xyz(&pos, azim, elev, ranj);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "pos[0]    = " << std::setw(14) << pos[0] << " [M]" << std::endl
                   << "pos[1]    = " << std::setw(14) << pos[1] << " [M]" << std::endl
                   << "pos[2]    = " << std::setw(14) << pos[2] << " [M]" << std::endl
                   << std::endl;
      }
   }
}

//--------
// #6
//--------
void test06_aer2xyz()
{
   std::cout << "=====================================================" << std::endl
             << "Example problem 6: test06_aer2xyz - using body angles" << std::endl
             << std::endl;

   std::cout
   << "--------------------------------------------------------------------------" << std::endl
   << "Using body angles                                                         " << std::endl
   << "bool aer2xyz(                                                             " << std::endl
   << "   osg::Vec3d* const pos,   // OUT: position vector [M]  (NED, player centered)" << std::endl
   << "   const osg::Matrixd& rm,  // IN:  inertial to body rotational matrix    " << std::endl
   << "                                    (see computeRotationalMatrix())       " << std::endl
   << "   const double azim,       // IN:  azimuth         [RAD]                 " << std::endl
   << "   const double elev,       // IN:  elevation       [RAD] (positive up)   " << std::endl
   << "   const double ranj)       // IN:  range           [M]                   " << std::endl
   << "--------------------------------------------------------------------------" << std::endl
   << std::endl;
   
   std::cout << "INPUTS:" << std::endl << std::endl;
   std::cout << "roll   = 10 [DEG]" << std::endl;
   std::cout << "pitch  = 20 [DEG]" << std::endl;
   std::cout << "yaw    = 30 [DEG]" << std::endl;
   std::cout << std::endl;
   
   std::cout << "Convert roll, pitch, and yaw to radians" << std::endl;
   std::cout << "roll   =  0.1745 [RAD]" << std::endl;
   std::cout << "pitch  =  0.3491 [RAD]" << std::endl;
   std::cout << "yaw    =  0.5236 [RAD]" << std::endl;
   std::cout << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl << std::endl;
   std::cout << "Compute rotation matrix (rm)" << std::endl;
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
   std::cout << "=> rm  = " << std::endl;
   std::cout << "     0.8138    0.4698   -0.3420" << std::endl
             << "    -0.4410    0.8826    0.1632" << std::endl
             << "     0.3785    0.0180    0.9254" << std::endl
             << std::endl;
   
   std::cout << "INPUTS:" << std::endl << std::endl;
   std::cout << "azim   =   45 [DEG]" << std::endl;
   std::cout << "elev   =   30 [DEG]" << std::endl;
   std::cout << "ranj   = 1000 [M]  " << std::endl;
   std::cout << std::endl;

   std::cout << "Convert azimuth and elevation to radians" << std::endl;
   std::cout << "azim   =    0.7854 [RAD]" << std::endl;
   std::cout << "elev   =    0.5236 [RAD]" << std::endl;
   std::cout << "range  = 1000.0000 [M]  " << std::endl;
   std::cout << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl << std::endl;
   std::cout << "Compute position vector (pos)" << std::endl;
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "pos[0] =   39.0485 [M]" << "  // north " << std::endl
             << "pos[1] =  819.1647 [M]" << "  // east  " << std::endl
             << "pos[2] = -572.2276 [M]" << "  // down  " << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double roll  = 0.0;
         double pitch = 0.0;
         double yaw   = 0.0;
         osg::Matrixd rm;

         double azim  = 0.0;
         double elev  = 0.0;
         double ranj  = 0.0;
         osg::Vec3d pos;
         
         std::cout << "Enter roll   [DEG] : "; std::cin >> roll;
         std::cout << "Enter pitch  [DEG] : "; std::cin >> pitch;
         std::cout << "Enter yaw    [DEG  : "; std::cin >> yaw;
         std::cout << std::endl;
         
         roll  *= Basic::Angle::D2RCC;
         pitch *= Basic::Angle::D2RCC;
         yaw   *= Basic::Angle::D2RCC;
         
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "roll   = " << std::setw(14) << roll  << " [RAD]" << std::endl;
         std::cout << "pitch  = " << std::setw(14) << pitch << " [RAD]" << std::endl;
         std::cout << "yaw    = " << std::setw(14) << yaw   << " [RAD]" << std::endl;
         std::cout << std::endl;

         std::cout << "Basic::Nav::computeRotationalMatrix(roll, pitch, yaw, &rm);" << std::endl;
         Basic::Nav::computeRotationalMatrix(roll, pitch, yaw, &rm);
         std::cout << "=> rm  = " << std::endl;
         showMatrix(rm);

         std::cout << "Enter azimuth    [DEG] : "; std::cin >> azim;
         std::cout << "Enter elevation  [DEG] : "; std::cin >> elev;
         std::cout << "Enter range      [M]   : "; std::cin >> ranj;
         std::cout << std::endl;

         azim *= Basic::Angle::D2RCC;
         elev *= Basic::Angle::D2RCC;

         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "azim   = " << std::setw(14) << azim << " [RAD]" << std::endl;
         std::cout << "elev   = " << std::setw(14) << elev << " [RAD]" << std::endl;
         std::cout << "ranj   = " << std::setw(14) << ranj << " [M]  " << std::endl;
         std::cout << std::endl;

         Basic::Nav::aer2xyz(&pos, rm, azim, elev, ranj);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "pos[0] = " << std::setw(14) << pos[0] << " [M]" << std::endl;
         std::cout << "pos[1] = " << std::setw(14) << pos[1] << " [M]" << std::endl;
         std::cout << "pos[2] = " << std::setw(14) << pos[2] << " [M]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #7
//--------
void test07_xyz2aer()
{
   //---------------------------------------------------------------------------
   std::cout << "====================================================" << std::endl
             << "Example problem 7: test07_xyz2aer using euler angles" << std::endl
             << std::endl;

   std::cout
   << "--------------------------------------------------------------------" << std::endl
   << "bool xyz2aer(                                                       " << std::endl
   << "   osg::Vec3d* const aer,  // OUT: position vector   [DEG, DEG, M]  " << std::endl
   << "   const double x,         // IN:  x                 [M]            " << std::endl
   << "   const double y,         // IN:  y                 [M]            " << std::endl
   << "   const double z)         // IN:  z                 [M]            " << std::endl
   << "--------------------------------------------------------------------" << std::endl
   << std::endl;

   std::cout << "INPUTS:" << std::endl << std::endl;
   std::cout << "x = 100 [M]  // x position" << std::endl
             << "y = 200 [M]  // y position" << std::endl
             << "z = 300 [M]  // z position" << std::endl
             << std::endl;

   std::cout << "Basic::Nav::xyz2aer(&aer, x, y, z);" << std::endl;
   std::cout << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl << std::endl;
   std::cout << "=> aer[0] =   63.4349  [DEG]  // azimuth   " << std::endl
             << "=> aer[1] =  -53.3008  [DEG]  // elevation " << std::endl
             << "=> aer[2] =  374.1657  [M]    // range     " << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         osg::Vec3d aer;
         double x = 0.0;
         double y = 0.0;
         double z = 0.0;

         std::cout << "Enter x [M]: "; std::cin >> x;
         std::cout << "Enter y [M]: "; std::cin >> y;
         std::cout << "Enter z [M]: "; std::cin >> z;
         std::cout << std::endl;

         Basic::Nav::xyz2aer(&aer, x, y, z);
         
         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "aer[0] = " << std::setw(14) << aer[0] << "  [DEG]  // azimuth  " << std::endl
                   << "aer[1] = " << std::setw(14) << aer[1] << "  [DEG]  // elevation" << std::endl
                   << "aer[2] = " << std::setw(14) << aer[2] << "  [M]    // range    " << std::endl
                   << std::endl;
      }
   }
}

//--------
// #8
//--------
void test08_xyz2aer()
{
   //---------------------------------------------------------------------------
   std::cout << "=============================================" << std::endl
             << "test xyz2aer using body angles" << std::endl
             << std::endl;

   std::cout << "--------------------------------------------------------------------      " << std::endl
             << "bool xyz2aer(                                                             " << std::endl
             << "   osg::Vec3d* const aer,   // OUT: position vector  (aer)   [DEG, DEG, M]" << std::endl
             << "   const osg::Matrixd& rm,  // IN:  inertial to body rotational matrix    " << std::endl
             << "                            //      (see computeRotationalMatrix())       " << std::endl
             << "   const double x,          // IN:  x                        [M]          " << std::endl
             << "   const double y,          // IN:  y                        [M]          " << std::endl
             << "   const double z)          // IN:  z                        [M]          " << std::endl
             << "--------------------------------------------------------------------      " << std::endl
             << std::endl;
   
   std::cout << "INPUTS:" << std::endl << std::endl;
   std::cout << "x =  100 [M];  // north" << std::endl
             << "y =  200 [M];  // east " << std::endl
             << "z = -300 [M];  // down " << std::endl
             << std::endl;
   
   std::cout << "roll  = 10  [DEG] " << std::endl
             << "pitch = 20  [DEG] " << std::endl
             << "yaw   = 30  [DEG] " << std::endl
             << std::endl;
   
   std::cout << "Compute the rotation matrix (rm):" << std::endl;
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
   
   std::cout << "=> rm = " << std::endl;
   std::cout << "    0.8138    0.4698   -0.3420 " << std::endl
             << "   -0.4410    0.8826    0.1632 " << std::endl
             << "    0.3785    0.0180    0.9254 " << std::endl
             << std::endl;

   std::cout << "OUTPUTS:" << std::endl << std::endl;
   std::cout << "Basic::Nav::xyz2aer(&aer, rm, x, y, z);" << std::endl
             << std::endl;
   
   std::cout << "=> aer[0] =  16.7137  [DEG]    // azimuth     " << std::endl
             << "=> aer[1] =  39.1375  [DEG]    // elevation   " << std::endl
             << "=> aer[2] = 374.1657  [M]      // range       " << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         osg::Vec3d aer;
         osg::Matrixd rm;
         double x     = 0.0;
         double y     = 0.0;
         double z     = 0.0;
         double yaw   = 0.0;
         double pitch = 0.0;
         double roll  = 0.0;
         
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
         std::cout << "roll  = " << std::setw(14) << roll  << " [RAD]" << std::endl
                   << "pitch = " << std::setw(14) << pitch << " [RAD]" << std::endl
                   << "yaw   = " << std::setw(14) << yaw   << " [RAD]" << std::endl
                   << std::endl;

         std::cout << "Basic::Nav::computeRotationalMatrix(roll, pitch, yaw, &rm);" << std::endl
                   << std::endl;
         
         Basic::Nav::computeRotationalMatrix(roll, pitch, yaw, &rm);
         
         std::cout << "=> rm = " << std::endl;
         showMatrix(rm);

         std::cout << "Basic::Nav::xyz2aer(&aer, rm, x, y, z);" << std::endl
                   << std::endl;
                   
         Basic::Nav::xyz2aer(&aer, rm, x, y, z);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "aer[0] = " << std::setw(14) << aer[0] << "  [DEG]" << std::endl
                   << "aer[1] = " << std::setw(14) << aer[1] << "  [DEG]" << std::endl
                   << "aer[2] = " << std::setw(14) << aer[2] << "  [M]"   << std::endl
                   << std::endl;
      }
   }
}

//--------
// #9
//--------
void test09_gbd2ll()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_gbd2llE" << std::endl << std::endl;

   std::cout
      << "--------------------------------------------------------------------" << std::endl
      << "bool gbd2ll(                                                        " << std::endl
      << "   const double slat,         // IN:  Source latitude  [DEG]        " << std::endl
      << "   const double slon,         // IN:  Source longitude [DEG]        " << std::endl
      << "   const double brng,         // IN:  Target bearing   [DEG]        " << std::endl
      << "   const double dist,         // IN:  Target distance  [NM]         " << std::endl
      << "   double* const tlat,        // OUT: Target latitude  [DEG]        " << std::endl
      << "   double* const tlon,        // OUT: Target longitude [DEG]        " << std::endl
      << "   const Basic::EarthModel* const eem=0)                            " << std::endl
      << "                              // IN: Earth model (default: WGS-84)  " << std::endl
      << "--------------------------------------------------------------------" << std::endl
      << std::endl;

   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "slat = 0;        // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;        // source longitude  [DEG]" << std::endl;
   std::cout << "brng = 45;       // target bearing    [DEG]" << std::endl;
   std::cout << "dist = 100;      // target distance   [NM] " << std::endl;
   std::cout << "pEM  = wgs84;    // earth model            " << std::endl;
   std::cout << std::endl;

   std::cout << "OUTPUTS:" << std::endl << std::endl;
   
   std::cout << "Basic::Nav::gbd2ll(slat, slon, brng, dist, &tlat, &tlon, pEM);" << std::endl;
      
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> tlat = " << std::setw(10) << 1.1763 << "  [DEG]  // target latitude" << std::endl;
   std::cout << "=> tlon = " << std::setw(10) << 1.1845 << "  [DEG]  // target longitude" << std::endl;
   std::cout << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double slat = 0.0;
         double slon = 0.0;
         double brng = 45.0;
         double dist = 100.0;
         double tlat = 0.0;
         double tlon = 0.0;
         const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;
         
         std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
         std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
         std::cout << "Enter brng  [DEG] : "; std::cin >> brng;
         std::cout << "Enter dist  [NM]  : "; std::cin >> dist;
         std::cout << std::endl;
         
         Basic::Nav::gbd2ll(slat, slon, brng, dist, &tlat, &tlon, pEM);
         
         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "tlat = " << std::setw(14) << tlat << " [DEG]" << std::endl;
         std::cout << "tlon = " << std::setw(14) << tlon << " [DEG]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #10
//--------
void test10_gll2bd()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test_gll2bdE" << std::endl << std::endl;

   std::cout
      << "--------------------------------------------------------------------" << std::endl
      << "bool gll2bd(                                                        " << std::endl
      << "   const double slat,     // IN:  Source latitude    [DEG]          " << std::endl
      << "   const double slon,     // IN:  Source longitude   [DEG]          " << std::endl
      << "   const double tlat,     // IN:  Target latitude    [DEG]          " << std::endl
      << "   const double tlon,     // IN:  Target longitude   [DEG]          " << std::endl
      << "   double* const brng,    // OUT: bearing            [DEG]          " << std::endl
      << "   double* const dist,    // OUT: distance           [NM]           " << std::endl
      << "   const Basic::EarthModel* const eem=0)                            " << std::endl
      << "                          // IN: Earth model (default: WGS-84)      " << std::endl
      << "--------------------------------------------------------------------" << std::endl
      << std::endl;
      
   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "slat = 0;       // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;       // source longitude  [DEG]" << std::endl;
   std::cout << "tlat = 1;       // target latitude   [DEG]" << std::endl;
   std::cout << "tlon = 1;       // target longitude  [NM] " << std::endl;
   std::cout << "pEM  = wgs84;   // pointer to earth model " << std::endl;
   std::cout << std::endl;

   std::cout << "OUTPUTS:" << std::endl << std::endl;

   std::cout << "Basic::Nav::gll2bd(slat, slon, tlat, tlon, &brng, &dist, pEM);" << std::endl;
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "brng = " << std::setw(10) << 44.8043 << " [DEG]" << std::endl;
   std::cout << "dist = " << std::setw(10) << 84.7189 << " [NM]"  << std::endl;
   std::cout << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double slat = 0.0;
         double slon = 0.0;
         double tlat = 0.0;
         double tlon = 0.0;
         double brng = 0.0;
         double dist = 0.0;
         const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;

         std::cout << "Enter slat [DEG] : "; std::cin >> slat;
         std::cout << "Enter slon [DEG] : "; std::cin >> slon;
         std::cout << "Enter tlat [DEG] : "; std::cin >> tlat;
         std::cout << "Enter tlon [DEG] : "; std::cin >> tlon;
         std::cout << std::endl;
         
         Basic::Nav::gll2bd(slat, slon, tlat, tlon, &brng, &dist, pEM);
         
         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "brng = " << std::setw(14) << brng << " [DEG]" << std::endl;
         std::cout << "dist = " << std::setw(14) << dist << " [NM]"  << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #11
//--------
void test11_gbd2llS()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test11_gbd2llS" << std::endl << std::endl;

   std::cout
      << "--------------------------------------------------------------------" << std::endl
      << "bool gbd2llS(                                                       " << std::endl
      << "   const double slat,         // IN:  Source latitude  [DEG]        " << std::endl
      << "   const double slon,         // IN:  Source longitude [DEG]        " << std::endl
      << "   const double brng,         // IN:  Target bearing   [DEG]        " << std::endl
      << "   const double dist,         // IN:  Target distance  [NM]         " << std::endl
      << "   double* const tlat,        // OUT: Target latitude [DEG]    " << std::endl
      << "   double* const tlon,        // OUT: Target longitude [DEG]   " << std::endl
      << "--------------------------------------------------------------------" << std::endl
      << std::endl;

   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "slat = 0;        // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;        // source longitude  [DEG]" << std::endl;
   std::cout << "brng = 45;       // target bearing    [DEG]" << std::endl;
   std::cout << "dist = 100;      // target distance   [NM] " << std::endl;
   std::cout << std::endl;

   std::cout << "OUTPUTS:" << std::endl << std::endl;
   
   std::cout << "Basic::Nav::gbd2llS(slat, slon, brng, dist, &tlat, &tlon);" << std::endl;
      
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> tlat = " << std::setw(10) << 1.1784 << "  [DEG]  // target latitude" << std::endl;
   std::cout << "=> tlon = " << std::setw(10) << 1.1787 << "  [DEG]  // target longitude" << std::endl;
   std::cout << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double slat = 0.0;
         double slon = 0.0;
         double brng = 0.0;
         double dist = 0.0;
         double tlat = 0.0;
         double tlon = 0.0;
         
         std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
         std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
         std::cout << "Enter brng  [DEG] : "; std::cin >> brng;
         std::cout << "Enter dist  [NM]  : "; std::cin >> dist;
         std::cout << std::endl;
         
         Basic::Nav::gbd2llS(slat, slon, brng, dist, &tlat, &tlon);
         
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "tlat = " << std::setw(14) << tlat << " [DEG]" << std::endl;
         std::cout << "tlon = " << std::setw(14) << tlon << " [DEG]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #12
//--------
void test12_gll2bdS()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test12_gll2bdS" << std::endl << std::endl;

   std::cout
      << "--------------------------------------------------------------------" << std::endl
      << "bool gll2bdS(                                                       " << std::endl
      << "   const double slat,         // IN:  source latitude   [DEG]       " << std::endl
      << "   const double slon,         // IN:  source longitude  [DEG]       " << std::endl
      << "   const double tlat,         // IN:  target latitude   [DEG]       " << std::endl
      << "   const double tlon,         // IN:  target longitude  [DEG]       " << std::endl
      << "   double* const brng,        // OUT: bearing           [DEG]       " << std::endl
      << "   double* const dist,        // OUT: distance          [NM]        " << std::endl
      << "--------------------------------------------------------------------" << std::endl
      << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "slat = 0;       // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;       // source longitude  [DEG]" << std::endl;
   std::cout << "tlat = 1;       // target latitude   [DEG]" << std::endl;
   std::cout << "tlon = 1;       // target longitude  [NM] " << std::endl;
   std::cout << std::endl;

   std::cout << "OUTPUTS:" << std::endl << std::endl;

   std::cout << "Basic::Nav::gll2bdS(slat, slon, tlat, tlon, &brng, &dist);" << std::endl;
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "brng = " << std::setw(10) << 44.9956 << " [DEG]" << std::endl;
   std::cout << "dist = " << std::setw(10) << 84.8507 << " [NM]"  << std::endl;
   std::cout << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double slat = 0.0;
         double slon = 0.0;
         double tlat = 0.0;
         double tlon = 0.0;
         double brng = 0.0;
         double dist = 0.0;
         const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;

         std::cout << "Enter slat [DEG] : "; std::cin >> slat;
         std::cout << "Enter slon [DEG] : "; std::cin >> slon;
         std::cout << "Enter tlat [DEG] : "; std::cin >> tlat;
         std::cout << "Enter tlon [DEG] : "; std::cin >> tlon;
         std::cout << std::endl;
         
         Basic::Nav::gll2bdS(slat, slon, tlat, tlon, &brng, &dist);
         
         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "brng = " << std::setw(14) << brng << " [DEG]" << std::endl;
         std::cout << "dist = " << std::setw(14) << dist << " [NM]"  << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #13
//--------
void test13_glla2bd()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test13_glla2bd" << std::endl << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Function Prototype:" << std::endl;   
   std::cout << "==================================" << std::endl;
   
   std::cout
      << "--------------------------------------------------------------------" << std::endl
      << "bool glla2bd(                                                  " << std::endl
      << "   const double slat,       // IN:  Source latitude   [DEG]    " << std::endl
      << "   const double slon,       // IN:  Source longitude  [DEG]    " << std::endl
      << "   const double salt,       // IN:  Source altitude   [M]      " << std::endl
      << "   const double tlat,       // IN:  Target latitude   [DEG]    " << std::endl
      << "   const double tlon,       // IN:  Target longitude  [DEG]    " << std::endl
      << "   const double talt,       // IN:  Target altitude   [M]      " << std::endl
      << "   double* const brng,      // OUT: bearing           [DEG]    " << std::endl
      << "   double* const slantRng,  // OUT: slant range       [NM]     " << std::endl
      << "   double* const dist,      // OUT: ground range      [NM]     " << std::endl
      << "   double* const elev=0,    // OUT: elevation angle   [DEG] (Optional)    " << std::endl
      << "   const Basic::EarthModel* const eem=0)                                  " << std::endl
      << "                            // IN:  earth model (Optional)                " << std::endl
      << "                            //      (default: &Basic::EarthModel::wgs84)  " << std::endl
      << "--------------------------------------------------------------------" << std::endl
      << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;   
   std::cout << "==================================" << std::endl;

   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "slat = 0;     // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;     // source longitude  [DEG]" << std::endl;
   std::cout << "salt = 0;     // source longitude  [M]  " << std::endl;
   std::cout << "tlat = 1;     // target latitude   [DEG]" << std::endl;
   std::cout << "tlon = 1;     // target longitude  [DEG]" << std::endl;
   std::cout << "talt = 10000; // target longitude  [M]  " << std::endl;
   std::cout << std::endl;

   std::cout << "Basic::Nav::glla2bd(slat, slon, salt, tlat, tlon, talt,"  << std::endl;
   std::cout << "                    &brng, &slantRng, &dist, &elev);"     << std::endl;
   std::cout << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl << std::endl;
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "brng     = " << std::setw(12) << 44.8043  << " [DEG]  // true bearing to target" << std::endl;
   std::cout << "slantRng = " << std::setw(12) << 84.8908  << " [NM]   // slant range to target " << std::endl;
   std::cout << "dist     = " << std::setw(12) << 84.7189  << " [NM]   // ground range to target" << std::endl;
   std::cout << "elev     = " << std::setw(12) <<  3.6468  << " [DEG]  // elevation of target   " << std::endl;
   std::cout << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double slat = 0.0;
         double slon = 0.0;
         double salt = 0.0;
         double tlat = 0.0;
         double tlon = 0.0;
         double talt = 0.0;
         double brng     = 0.0;
         double slantRng = 0.0;
         double dist     = 0.0;
         double elev     = 0.0;
         const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;  // default earth model
         
         std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
         std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
         std::cout << "Enter salt  [M]   : "; std::cin >> salt;
         std::cout << "Enter tlat  [DEG] : "; std::cin >> tlat;
         std::cout << "Enter tlon  [DEG] : "; std::cin >> tlon;
         std::cout << "Enter talt  [M]   : "; std::cin >> talt;
         std::cout << std::endl;

         Basic::Nav::glla2bd(slat, slon, salt, tlat, tlon, talt,
                             &brng, &slantRng, &dist, &elev, pEM);

         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "brng     = " << std::setw(14) << brng     << " [DEG]" << std::endl;
         std::cout << "slantRng = " << std::setw(14) << slantRng << " [NM]"  << std::endl;
         std::cout << "dist     = " << std::setw(14) << dist     << " [NM]"  << std::endl;
         std::cout << "elev     = " << std::setw(14) << elev     << " [DEG]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #14
//--------
void test14_glla2bdS()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test14_glla2bdS" << std::endl << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Function Prototype:               " << std::endl;   
   std::cout << "==================================" << std::endl;
   
   std::cout
      << "--------------------------------------------------------------------" << std::endl
      << "bool glla2bd(                                                  " << std::endl
      << "   const double slat,       // IN:  Source latitude   [DEG]    " << std::endl
      << "   const double slon,       // IN:  Source longitude  [DEG]    " << std::endl
      << "   const double salt,       // IN:  Source altitude   [M]      " << std::endl
      << "   const double tlat,       // IN:  Target latitude   [DEG]    " << std::endl
      << "   const double tlon,       // IN:  Target longitude  [DEG]    " << std::endl
      << "   const double talt,       // IN:  Target altitude   [M]      " << std::endl
      << "   double* const brng,      // OUT: bearing           [DEG]    " << std::endl
      << "   double* const slantRng,  // OUT: slant range       [NM]     " << std::endl
      << "   double* const dist,      // OUT: ground range      [NM]     " << std::endl
      << "   double* const elev=0,    // OUT: elevation angle   [DEG] (Optional) " << std::endl
      << "--------------------------------------------------------------------" << std::endl
      << std::endl;


   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;   
   std::cout << "==================================" << std::endl;

   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "slat = 0;     // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;     // source longitude  [DEG]" << std::endl;
   std::cout << "salt = 0;     // source longitude  [M]" << std::endl;
   std::cout << "tlat = 1;     // target latitude   [DEG]" << std::endl;
   std::cout << "tlon = 1;     // target longitude  [DEG]" << std::endl;
   std::cout << "talt = 10000; // target longitude  [M]" << std::endl;
   std::cout << std::endl;

   std::cout << "Basic::Nav::glla2bdS(slat, slon, salt, tlat, tlon, talt,"  << std::endl;
   std::cout << "                     &brng, &slantRng, &dist, &elev);"     << std::endl;
   std::cout << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl << std::endl;
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "brng     = " << std::setw(12) << 44.9956  << " [DEG]  // true bearing to target" << std::endl;
   std::cout << "slantRng = " << std::setw(12) << 85.0223  << " [NM]   // slant range to target " << std::endl;
   std::cout << "dist     = " << std::setw(12) << 84.8507  << " [NM]   // ground range to target" << std::endl;
   std::cout << "elev     = " << std::setw(12) <<  3.6412  << " [DEG]  // elevation of target   " << std::endl;
   std::cout << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double slat = 0.0;
         double slon = 0.0;
         double salt = 0.0;
         double tlat = 0.0;
         double tlon = 0.0;
         double talt = 0.0;
         double brng     = 0.0;
         double slantRng = 0.0;
         double dist     = 0.0;
         double elev     = 0.0;
         
         std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
         std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
         std::cout << "Enter salt  [M]   : "; std::cin >> salt;
         std::cout << "Enter tlat  [DEG] : "; std::cin >> tlat;
         std::cout << "Enter tlon  [DEG] : "; std::cin >> tlon;
         std::cout << "Enter talt  [M]   : "; std::cin >> talt;
         std::cout << std::endl;

         Basic::Nav::glla2bdS(slat, slon, salt, tlat, tlon, talt,
                              &brng, &slantRng, &dist, &elev);

         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "brng     = " << std::setw(14) << brng     << " [DEG]" << std::endl;
         std::cout << "slantRng = " << std::setw(14) << slantRng << " [NM]"  << std::endl;
         std::cout << "dist     = " << std::setw(14) << dist     << " [NM]"  << std::endl;
         std::cout << "elev     = " << std::setw(14) << elev     << " [DEG]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #15
//--------
void test15_vbd2ll()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test15_vbd2ll" << std::endl << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Function Prototype:               " << std::endl;   
   std::cout << "==================================" << std::endl;

   std::cout
      << "--------------------------------------------------------------------" << std::endl
      << "bool gbd2ll(                                                        " << std::endl
      << "   const double slat,         // IN:  Source latitude  [DEG]        " << std::endl
      << "   const double slon,         // IN:  Source longitude [DEG]        " << std::endl
      << "   const double brng,         // IN:  Target bearing   [DEG]        " << std::endl
      << "   const double dist,         // IN:  Target distance  [NM]         " << std::endl
      << "   double* const tlat,        // OUT: Target latitude  [DEG]        " << std::endl
      << "   double* const tlon,        // OUT: Target longitude [DEG]        " << std::endl
      << "   const Basic::EarthModel* const eem=0)                            " << std::endl
      << "                              // IN: Earth model (default: WGS-84)  " << std::endl
      << "--------------------------------------------------------------------" << std::endl
      << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "slat = 0;    // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0;    // source longitude  [DEG]" << std::endl;
   std::cout << "brng = 45;   // target bearing    [DEG]" << std::endl;
   std::cout << "dist = 100;  // target distance   [NM] " << std::endl;
   std::cout << std::endl;
   
   std::cout << "Basic::Nav::vbd2ll(slat, slon, brng, dist, &tlat, &tlon, pEM);" << std::endl;

   std::cout << "OUTPUTS:" << std::endl << std::endl;

   std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
   std::cout << "=> tlat = " << std::setw(12) << 1.18424220 << "  // target latitude  [DEG]" << std::endl;
   std::cout << "=> tlon = " << std::setw(12) << 1.17656578 << "  // target longitude [DEG]" << std::endl;
   std::cout << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double slat = 0.0;
         double slon = 0.0;
         double brg1 = 0.0;
         double dist = 0.0;
         double tlat = 0.0;
         double tlon = 0.0;
         double brg2 = 0.0;
         const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;

         std::cout << "Enter source latitude   [DEG] : "; std::cin  >> slat;
         std::cout << "Enter source longitude  [DEG] : "; std::cin  >> slon;
         std::cout << "Enter source bearing    [DEG] : "; std::cin  >> brg1;
         std::cout << "Enter source distance   [NM]  : "; std::cin  >> dist;
         std::cout << std::endl;
            
         Basic::Nav::vbd2ll(slat, slon, brg1, dist, &tlat, &tlon, pEM);

         // output results
         std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
         std::cout << "tlat = " << std::setw(14) << tlat << " [DEG]" << std::endl;
         std::cout << "tlon = " << std::setw(14) << tlon << " [DEG]" << std::endl;
         std::cout << std::endl;

         // reverse test
         //Basic::Nav::vll2bd(tlat, tlon, slat, slon, &brng, &dist, &brg2, pEM);
         //std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
         //std::cout << "brng = " << std::setw(14) << brng << " [DEG]" << std::endl;
         //std::cout << "dist = " << std::setw(14) << dist << " [NM]"  << std::endl;
         //std::cout << "brg2 = " << std::setw(14) << brg2 << " [DEG]" << std::endl;
         //std::cout << std::endl;
      }
   }
}

//--------
// #16
//--------
void test16_vll2bd()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test16_vll2bd" << std::endl << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Function Prototype:               " << std::endl;   
   std::cout << "==================================" << std::endl;

   std::cout
      << "--------------------------------------------------------------------" << std::endl
      << "bool vll2bd(                                                        " << std::endl
      << "   const double slat,         // IN:  Source latitude  [DEG]        " << std::endl
      << "   const double slon,         // IN:  Source longitude [DEG]        " << std::endl
      << "   const double brng,         // IN:  Target bearing   [DEG]        " << std::endl
      << "   const double dist,         // IN:  Target distance  [NM]         " << std::endl
      << "   double* const tlat,        // OUT: Target latitude  [DEG]        " << std::endl
      << "   double* const tlon,        // OUT: Target longitude [DEG]        " << std::endl
      << "   double* const brg2=0,      // OUT: Optional: true final bearing [DEG]  " << std::endl
      << "   const Basic::EarthModel* const eem=0)                                  " << std::endl
      << "                              // IN: Optional: Pointer to an earth model  " << std::endl
      << "                                     (default: WGS-84)                    " << std::endl
      << "--------------------------------------------------------------------" << std::endl
      << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "slat = 0; // source latitude   [DEG]" << std::endl;
   std::cout << "slon = 0; // source longitude  [DEG]" << std::endl;
   std::cout << "tlat = 1; // target latitude   [DEG]" << std::endl;
   std::cout << "tlon = 1; // target longitude  [NM] " << std::endl;
   std::cout << std::endl;
   
   std::cout << "Basic::Nav::vll2bd(slat, slon, tlat, tlon, &brng, &dist, &brg2, pEM);" << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl << std::endl;

   std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
   std::cout << "=> brg1 = " << std::setw(14) <<   45.18804023 << "  // bearing  source to target [DEG]" << std::endl;
   std::cout << "=> dist = " << std::setw(14) <<   84.71898935 << "  // distance to target [NM] "        << std::endl;
   std::cout << "=> brg2 = " << std::setw(14) << -134.80323268 << "  // bearing  target to source [DEG]" << std::endl;
   std::cout << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double slat = 0.0;
         double slon = 0.0;
         double tlat = 0.0;
         double tlon = 0.0;
         double brg1 = 0.0;
         double dist = 0.0;
         double brg2 = 0.0;
         const Basic::EarthModel* pEM = &Basic::EarthModel::wgs84;

         std::cout << "Enter source latitude   [DEG] : "; std::cin  >> slat;
         std::cout << "Enter source longitude  [DEG] : "; std::cin  >> slon;
         std::cout << "Enter target latitude   [DEG] : "; std::cin  >> tlat;
         std::cout << "Enter target longitude  [DEG] : "; std::cin  >> tlon;
         std::cout << std::endl;
            
         Basic::Nav::vll2bd(slat, slon, tlat, tlon, &brg1, &dist, &brg2, pEM);

         std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
         std::cout << "brg1 = " << std::setw(14) << brg1 << " [DEG]" << std::endl;
         std::cout << "dist = " << std::setw(14) << dist << " [NM]"  << std::endl;
         std::cout << "brg2 = " << std::setw(14) << brg2 << " [DEG]" << std::endl;
         std::cout << std::endl;

         // reverse test
         //Basic::Nav::vbd2ll(tlat, tlon, brg2, dist, &slat, &slon, pEM);
         //std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
         //std::cout << "slat = " << std::setw(14) << slat << " [DEG]" << std::endl;
         //std::cout << "slon = " << std::setw(14) << slon << " [DEG]" << std::endl;
         //std::cout << std::endl;
      }
   }
}

//--------
// #17
//--------
void test17_computeWorldMatrix()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test17_computeWorldMatrix" << std::endl << std::endl;
   
   std::cout << "==================================" << std::endl;
   std::cout << "Function Prototype:               " << std::endl;
   std::cout << "==================================" << std::endl;
   
   std::cout
      << "--------------------------------------------------------------------" << std::endl
      << "bool computeWorldMatrix1(                                           " << std::endl
      << "const double refLat,        // IN:  Reference latitude  [DEG]       " << std::endl
      << "const double refLon,        // IN:  Reference longitude [DEG]       " << std::endl
      << "osg::Matrixd* const wm)     // OUT: World Matrix                    " << std::endl
      << "--------------------------------------------------------------------" << std::endl
      << std::endl;
      
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;
   std::cout << "==================================" << std::endl;
   
   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "rlat = 40; // reference latitude   [DEG]" << std::endl;
   std::cout << "rlon = 50; // reference longitude  [DEG]" << std::endl;
   std::cout << std::endl;
   
   std::cout << "Basic::Nav::computeWorldMatrix1(refLat, refLon, &wm);" << std::endl;
   std::cout << std::endl;

   std::cout << "OUTPUTS:" << std::endl << std::endl;

   osg::Matrixd worldMatrix;
   worldMatrix(0,0) = -0.4132;
   worldMatrix(0,1) = -0.4924;
   worldMatrix(0,2) =  0.7660;
   worldMatrix(1,0) = -0.7660;
   worldMatrix(1,1) =  0.6428;
   worldMatrix(1,2) =  0.0000;
   worldMatrix(2,0) = -0.4924;
   worldMatrix(2,1) = -0.5868;
   worldMatrix(2,2) = -0.6428;
   
   std::cout << "worldMatrix = " << std::endl;
   showMatrix(worldMatrix);
   

   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double rlat = 0.0;
         double rlon = 0.0;
         osg::Matrixd wm;

         std::cout << "Enter reference latitude   [DEG] : "; std::cin  >> rlat;
         std::cout << "Enter reference longitude  [DEG] : "; std::cin  >> rlon;
         std::cout << std::endl;

         Basic::Nav::computeWorldMatrix(rlat, rlon, &wm);
         
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "wm = " << std::endl;
         showMatrix(wm);
      }
   }
}

//--------
// #18
//--------
void test18_computeEulerAnglesDeg()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test18_computeEulerAnglesDeg" << std::endl << std::endl;

   //-----------------------------------
   // Version using degrees
   // bool computeEulerAnglesDeg(
   //    const osg::Matrixd& rm,    // IN: Rotational matrix
   //    osg::Vec3d* const anglesD, // OUT: euler angles [DEG]
   //    osg::Vec2d* const scPhi=0, // OUT: Sin/Cos of phi (Optional)
   //    osg::Vec2d* const scTht=0, // OUT: Sin/Cos of theta (Optional)
   //    osg::Vec2d* const scPsi=0) // OUT: Sin/Cos of psi (Optional)
   //-----------------------------------

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;
   std::cout << "==================================" << std::endl;
   std::cout << std::endl;

   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "roll  = 10;  // roll  angle  [DEG]" << std::endl;
   std::cout << "pitch = 20;  // pitch angle  [DEG]" << std::endl;
   std::cout << "yaw   = 30;  // yaw   angle  [DEG]" << std::endl;
   std::cout << std::endl;

   std::cout << "OUTPUTS:" << std::endl << std::endl;
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;

   osg::Matrixd rotationMatrix;
   rotationMatrix(0,0) = -0.4132;
   rotationMatrix(0,1) = -0.4924;
   rotationMatrix(0,2) =  0.7660;
   rotationMatrix(1,0) = -0.7660;
   rotationMatrix(1,1) =  0.6428;
   rotationMatrix(1,2) =  0.0000;
   rotationMatrix(2,0) = -0.4924;
   rotationMatrix(2,1) = -0.5868;
   rotationMatrix(2,2) = -0.6428;
   
   std::cout << "rotationMatrix = " << std::endl;

   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double roll  = 0.0;
         double pitch = 0.0;
         double yaw   = 0.0;
         osg::Matrixd rm;        // IN: Rotational matrix

         osg::Vec3d angles;      // OUT: euler angles (radians)
         osg::Vec2d scPhi;       // OUT: Sin/Cos of phi (Optional)
         osg::Vec2d scTht;       // OUT: Sin/Cos of theta (Optional)
         osg::Vec2d scPsi;       // OUT: Sin/Cos of psi (Optional)
         osg::Matrixd rmT;   

         std::cout << "Enter roll  angle  [DEG] : "; std::cin  >> roll;
         std::cout << "Enter pitch angle  [DEG] : "; std::cin  >> pitch;
         std::cout << "Enter yaw   angle  [DEG] : "; std::cin  >> yaw;
         std::cout << std::endl;
         
         std::cout << "Compute rotational matrix from roll, pitch, yaw:" << std::endl;
         std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
         Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);

         std::cout << "rm = " << std::endl;
         showMatrix(rm);

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
   }
}

//--------
// #19
//--------
void test19_computeRotationalMatrix()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test19_computeRotationalMatrix" << std::endl << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Function Prototype:               " << std::endl;
   std::cout << "==================================" << std::endl;
   
   std::cout
      << "bool computeRotationalMatrixDeg(                                    " << std::endl
      << "   const double phi,          // IN:  roll    [RAD]                 " << std::endl
      << "   const double theta,        // IN:  pitch   [RAD]                 " << std::endl
      << "   const double psi,          // IN:  yaw     [RAD]                 " << std::endl
      << "   osg::Matrixd* const rm,    // OUT: Rotational matrix             " << std::endl
      << "   osg::Vec2d* const scPhi=0, // OUT: Sin/Cos of phi   (Optional)   " << std::endl
      << "   osg::Vec2d* const scTht=0, // OUT: Sin/Cos of theta (Optional)   " << std::endl
      << "   osg::Vec2d* const scPsi=0) // OUT: Sin/Cos of psi   (Optional)   " << std::endl
      << std::endl;
      
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "roll  = 0.2 [RAD]  // roll  ~= 11.4592 [DEG]" << std::endl;
   std::cout << "pitch = 0.4 [RAD]  // pitch ~= 22.9183 [DEG]" << std::endl;
   std::cout << "yaw   = 0.6 [RAD]  // yaw   ~= 34.3775 [DEG]" << std::endl;
   std::cout << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl << std::endl;

   osg::Matrixd rotMatrix;
   rotMatrix(0,0) =  0.7602;
   rotMatrix(0,1) =  0.5201;
   rotMatrix(0,2) = -0.3894;
   rotMatrix(1,0) = -0.4895;
   rotMatrix(1,1) =  0.8526;
   rotMatrix(1,2) =  0.1830;
   rotMatrix(2,0) =  0.4272;
   rotMatrix(2,1) =  0.0515;
   rotMatrix(2,2) =  0.9027;
   
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rotMatrix);" << std::endl;
   
   std::cout << "rotationalMatrix = " << std::endl;
   showMatrix(rotMatrix);
 

   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

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

         std::cout << "Enter roll   [RAD] : "; std::cin  >> roll;
         std::cout << "Enter pitch  [RAD] : "; std::cin  >> pitch;
         std::cout << "Enter yaw    [RAD] : "; std::cin  >> yaw;
         std::cout << std::endl;
         
         std::cout << "Compute rotational matrix from roll, pitch, yaw:" << std::endl;
         std::cout << std::endl;
         
         std::cout << "Basic::Nav::computeRotationalMatrix(roll, pitch, yaw, &rm);" << std::endl;
         Basic::Nav::computeRotationalMatrix(roll, pitch, yaw, &rm);

         std::cout << "rm = " << std::endl;
         showMatrix(rm);
      }
   }
}

//--------
// #20
//--------
void test20_computeRotationalMatrix()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test20_computeRotationalMatrix" << std::endl << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Function Prototype:               " << std::endl;
   std::cout << "==================================" << std::endl;
   
   std::cout
      << "bool computeRotationalMatrix(                                       " << std::endl
      << "   const double phi,          // IN:  roll   [RAD]                  " << std::endl
      << "   const double theta,        // IN:  pitch  [RAD]                  " << std::endl
      << "   const double psi,          // IN:  yaw    [RAD]                  " << std::endl
      << "   osg::Matrixd* const rm,    // OUT: Rotational matrix             " << std::endl
      << "   osg::Vec2d* const scPhi=0, // OUT: Sin/Cos of phi (Optional)     " << std::endl
      << "   osg::Vec2d* const scTht=0, // OUT: Sin/Cos of theta (Optional)   " << std::endl
      << "   osg::Vec2d* const scPsi=0  // OUT: Sin/Cos of psi (Optional)     " << std::endl
      << std::endl;

   // Example problem
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "roll  = 0.2 [RAD]  // roll  ~= 11.4592 [DEG]" << std::endl;
   std::cout << "pitch = 0.4 [RAD]  // pitch ~= 22.9183 [DEG]" << std::endl;
   std::cout << "yaw   = 0.6 [RAD]  // yaw   ~= 34.3775 [DEG]" << std::endl;
   std::cout << std::endl;
   
   osg::Matrixd rotMatrix;
   rotMatrix(0,0) =  0.7602;
   rotMatrix(0,1) =  0.5201;
   rotMatrix(0,2) = -0.3894;
   rotMatrix(1,0) = -0.4895;
   rotMatrix(1,1) =  0.8526;
   rotMatrix(1,2) =  0.1830;
   rotMatrix(2,0) =  0.4272;
   rotMatrix(2,1) =  0.0515;
   rotMatrix(2,2) =  0.9027;
   
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rotMatrix);" << std::endl;
   std::cout << "=> rotMatrix = " << std::endl;

   std::cout << "rotationalMatrix = " << std::endl;   
   showMatrix(rotMatrix);
 

   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

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

         std::cout << "Enter roll  angle  [RAD] : "; std::cin  >> roll;
         std::cout << "Enter pitch angle  [RAD] : "; std::cin  >> pitch;
         std::cout << "Enter yaw   angle  [RAD] : "; std::cin  >> yaw;
         std::cout << std::endl;
         
         std::cout << "rotational matrix from roll, pitch, yaw:" << std::endl;
         std::cout << "Basic::Nav::computeRotationalMatrix(roll, pitch, yaw, &rm);" << std::endl;
         Basic::Nav::computeRotationalMatrix(roll, pitch, yaw, &rm);
         std::cout << "rm = " << std::endl;
         showMatrix(rm);
               
         angles[0] = roll;
         angles[1] = pitch;
         angles[2] = yaw;

         std::cout << "Define angles vector:" << std::endl;
         std::cout << "angles[0] = roll;"  << std::endl;
         std::cout << "angles[1] = pitch;" << std::endl;
         std::cout << "angles[2] = yaw;"   << std::endl;
         std::cout << std::endl;
         
         std::cout << "rotational matrix from angles vector:" << std::endl;
         std::cout << "Basic::Nav::computeRotationalMatrix(angles, &rm, &scPhi, &scTht, &scPsi);" << std::endl;
         Basic::Nav::computeRotationalMatrix(angles, &rm, &scPhi, &scTht, &scPsi);

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
   }
}

//--------
// #21
//--------
void test21_computeRotationalMatrixDeg()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test21_computeRotationalMatrixDeg" << std::endl << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Function Prototype:               " << std::endl;
   std::cout << "==================================" << std::endl;
   std::cout
      << "bool computeRotationalMatrixDeg(                                    " << std::endl
      << "   const double phi,          // IN:  roll    [DEG]                 " << std::endl
      << "   const double theta,        // IN:  pitch   [DEG]                 " << std::endl
      << "   const double psi,          // IN:  yaw     [DEG]                 " << std::endl
      << "   osg::Matrixd* const rm,    // OUT: Rotational matrix             " << std::endl
      << "   osg::Vec2d* const scPhi=0, // OUT: Sin/Cos of phi (Optional)     " << std::endl
      << "   osg::Vec2d* const scTht=0, // OUT: Sin/Cos of theta (Optional)   " << std::endl
      << "   osg::Vec2d* const scPsi=0) // OUT: Sin/Cos of psi (Optional)     " << std::endl
      << std::endl;
      
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "roll  = 10;  // roll  angle  [DEG]" << std::endl;
   std::cout << "pitch = 20;  // pitch angle  [DEG]" << std::endl;
   std::cout << "yaw   = 30;  // yaw   angle  [DEG]" << std::endl;
   std::cout << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl << std::endl;

   osg::Matrixd rotMatrix;
   rotMatrix(0,0) =  0.8138;
   rotMatrix(0,1) =  0.4698;
   rotMatrix(0,2) = -0.3420;
   rotMatrix(1,0) = -0.4410;
   rotMatrix(1,1) =  0.8826;
   rotMatrix(1,2) =  0.1632;
   rotMatrix(2,0) =  0.3785;
   rotMatrix(2,1) =  0.0180;
   rotMatrix(2,2) =  0.9254;
   
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rotMatrix);" << std::endl;
   
   std::cout << "rotationalMatrix = " << std::endl;
   showMatrix(rotMatrix);
 

   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

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

         std::cout << "Enter roll   [DEG] : "; std::cin  >> roll;
         std::cout << "Enter pitch  [DEG] : "; std::cin  >> pitch;
         std::cout << "Enter yaw    [DEG] : "; std::cin  >> yaw;
         std::cout << std::endl;
         
         std::cout << "Compute rotational matrix from roll, pitch, yaw:" << std::endl;
         std::cout << std::endl;
         
         std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
         Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);

         std::cout << "rm = " << std::endl;
         showMatrix(rm);
      }
   }
}

//--------
// #22
//--------
void test22_computeRotationalMatrixDeg()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test22_computeRotationalMatrixDeg" << std::endl << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Function Prototype:               " << std::endl;
   std::cout << "==================================" << std::endl;
   
   std::cout
      << "bool computeRotationalMatrixDeg(                                    " << std::endl
      << "   const double phiD,         // IN: roll   [DEG]                   " << std::endl
      << "   const double thetaD,       // IN: pitch  [DEG]                   " << std::endl
      << "   const double psiD,         // IN: yaw    [DEG]                   " << std::endl
      << "   osg::Matrixd* const rm,    // OUT: Rotational matrix             " << std::endl
      << "   osg::Vec2d* const scPhi=0, // OUT: Sin/Cos of phi (Optional)     " << std::endl
      << "   osg::Vec2d* const scTht=0, // OUT: Sin/Cos of theta (Optional)   " << std::endl
      << "   osg::Vec2d* const scPsi=0  // OUT: Sin/Cos of psi (Optional)     " << std::endl
      << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "roll  = 10;  // roll  angle  [DEG]" << std::endl;
   std::cout << "pitch = 20;  // pitch angle  [DEG]" << std::endl;
   std::cout << "yaw   = 30;  // yaw   angle  [DEG]" << std::endl;
   std::cout << std::endl;
   
   osg::Matrixd rotMatrix;
   rotMatrix(0,0) =  0.8138;
   rotMatrix(0,1) =  0.4698;
   rotMatrix(0,2) = -0.3420;
   rotMatrix(1,0) = -0.4410;
   rotMatrix(1,1) =  0.8826;
   rotMatrix(1,2) =  0.1632;
   rotMatrix(2,0) =  0.3785;
   rotMatrix(2,1) =  0.0180;
   rotMatrix(2,2) =  0.9254;
   
   std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rotMatrix);" << std::endl;
   
   std::cout << "rotationalMatrix = " << std::endl;
   showMatrix(rotMatrix);
    

   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

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

         std::cout << "Enter roll  angle  [DEG] : "; std::cin  >> roll;
         std::cout << "Enter pitch angle  [DEG] : "; std::cin  >> pitch;
         std::cout << "Enter yaw   angle  [DEG] : "; std::cin  >> yaw;
         std::cout << std::endl;
         
         std::cout << "rotational matrix from roll, pitch, yaw:" << std::endl;
         std::cout << "Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
         Basic::Nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);
         std::cout << "rm = " << std::endl;
         showMatrix(rm);
            
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
   }
}

//--------
// #23
//--------
void test23_convertPosVec2LL()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test23_convertPosVec2LL" << std::endl << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Function Prototype:               " << std::endl;
   std::cout << "==================================" << std::endl;
   
   std::cout
      << "bool convertPosVec2LL(                                                   " << std::endl
      << "   const double slat,      // IN: Starting (reference) latitude [DEG]    " << std::endl
      << "   const double slon,      // IN: Starting (reference) longitude [DEG]   " << std::endl
      << "   const osg::Vec3d& pos,  // IN: NED position vector from ref point [M] " << std::endl
      << "   double* const lat,      // OUT: Latitude [DEG]                        " << std::endl
      << "   double* const lon,      // OUT: Longitude [DEG]                       " << std::endl
      << "   double* const alt)      // OUT: Altitude [M]                          " << std::endl
      << std::endl;
      
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;
   std::cout << "==================================" << std::endl;
   
   std::cout << "rlat = 40;  // reference latitude  [DEG]" << std::endl;
   std::cout << "rlon = 50;  // reference longitude [DEG]" << std::endl;
   std::cout << std::endl;

   std::cout << "x = 1000  [M] : " << std::endl;
   std::cout << "y = 2000  [M] : " << std::endl;
   std::cout << "z = 3000  [M] : " << std::endl;
   std::cout << std::endl;

   std::cout << "Basic::Nav::convertPosVec2LL(rlat, rlon, pos, &lat, &lon, &alt);" << std::endl;

   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> lat = " << std::setw(12) << 0.0 << "  [DEG] : " << std::endl;
   std::cout << "=> lon = " << std::setw(12) << 0.0 << "  [DEG] : " << std::endl;
   std::cout << "=> alt = " << std::setw(12) << 0.0 << "  [M] : " << std::endl;
   std::cout << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double rlat = 0.0;  // IN: Starting (reference) latitude  (degs)
         double rlon = 0.0;  // IN: Starting (reference) longitude (degs)
         osg::Vec3d pos;     // IN: NED position vector from ref point (meters)
         
         double lat = 0.0;   // OUT: Latitude  (degs)
         double lon = 0.0;   // OUT: Longitude (degs)
         double alt = 0.0;   // OUT: Altitude  (meters)

         std::cout << "Enter reference latitude   [DEG] : "; std::cin >> rlat;
         std::cout << "Enter reference longitude  [DEG] : "; std::cin >> rlon;
         std::cout << std::endl;
         
         std::cout << "Enter x  [M] : "; std::cin >> pos[0];
         std::cout << "Enter y  [M] : "; std::cin >> pos[1];
         std::cout << "Enter z  [M] : "; std::cin >> pos[2];
         std::cout << std::endl;

         Basic::Nav::convertPosVec2LL(rlat, rlon, pos, &lat, &lon, &alt);
         
         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "lat = " << std::setw(12) << lat << " [DEG]" << std::endl;
         std::cout << "lon = " << std::setw(12) << lon << " [DEG]" << std::endl;
         std::cout << "alt = " << std::setw(12) << alt << " [DEG]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #24
//--------
void test24_convertLL2PosVec()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test24_convertLL2PosVec" << std::endl << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Function Prototype:               " << std::endl;
   std::cout << "==================================" << std::endl;
   
   std::cout
      << "bool convertLL2PosVec(                                        " << std::endl
      << "  const double rlat,      // IN: Reference latitude   [DEG]   " << std::endl
      << "  const double rlon,      // IN: Reference longitude  [DEG]   " << std::endl
      << "  const double tlat,      // IN: Target latitude      [DEG]   " << std::endl
      << "  const double tlon,      // IN: Target longitude     [DEG]   " << std::endl
      << "  const double talt,      // IN: Target altitude      [M]     " << std::endl
      << "  osg::Vec3d* const pos)  // OUT: NED position vector [M,M,M] " << std::endl
      << std::endl;
      
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:" << std::endl;
   std::cout << "==================================" << std::endl;

   std::cout << "rlat = 40;" << std::endl;
   std::cout << "rlon = 50;" << std::endl;

   std::cout << "tlat = 41;" << std::endl;
   std::cout << "tlon = 51;" << std::endl;
   std::cout << "talt = 5000.0;" << std::endl;
   std::cout << std::endl;
   
   std::cout << "Basic::Nav::convertLL2PosVec(rlat, rlon, tlat, tlon, talt, &pos);" << std::endl;

   std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
   std::cout << "=> pos[0] = " << std::setw(12) << 111120.00 << " [M]  north" << std::endl;
   std::cout << "=> pos[1] = " << std::setw(12) <<  85122.86 << " [M]  east " << std::endl;
   std::cout << "=> pos[2] = " << std::setw(12) <<  -5000.00 << " [M]  down " << std::endl;
   std::cout << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

         double rlat = 0.0;  // IN: Reference latitude  [DEG]
         double rlon = 0.0;  // IN: Reference longitude [DEG]
         double tlat = 0.0;  // IN: Target latitude     [DEG]
         double tlon = 0.0;  // IN: Target longitude    [DEG]
         double talt = 0.0;  // IN: Target altitude     [M]  
         osg::Vec3d pos;     // OUT: NED position vector from ref point [M,M,M]

         std::cout << "Enter reference latitude   [DEG] : "; std::cin >> rlat;
         std::cout << "Enter reference longitude  [DEG] : "; std::cin >> rlon;
         std::cout << std::endl;
         
         std::cout << "Enter target latitude   [M] : "; std::cin >> tlat;
         std::cout << "Enter target longitude  [M] : "; std::cin >> tlon;
         std::cout << "Enter target altitude   [M] : "; std::cin >> talt;
         std::cout << std::endl;

         Basic::Nav::convertLL2PosVec(rlat, rlon, tlat, tlon, talt, &pos);
         
         // output results
         std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
         std::cout << "pos[0] = " << std::setw(12) << pos[0] << " [M]  north" << std::endl;
         std::cout << "pos[1] = " << std::setw(12) << pos[1] << " [M]  east"  << std::endl;
         std::cout << "pos[2] = " << std::setw(12) << pos[2] << " [M]  down"  << std::endl;
      }
   }
}

//--------
// #25
//--------
void test25_convertEcef2Geod()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test25_convertEcef2Geod" << std::endl << std::endl;

   std::cout
   << "============================================================  " << std::endl
   << "Function Prototype:                                           " << std::endl
   << "Convert ECEF coordinates (XYZ) to Geodetic coordinates (LLA)  " << std::endl
   << "============================================================  " << std::endl;

   std::cout
   << "bool convertEcef2Geod(                                        " << std::endl
   << "   const double x,      // IN:  ECEF X component    [M]       " << std::endl
   << "   const double y,      // IN:  ECEF Y component    [M]       " << std::endl
   << "   const double z,      // IN:  ECEF Z component    [M]       " << std::endl
   << "   double* const pLat,  // OUT: Geodetic latitude   [DEG]     " << std::endl
   << "   double* const pLon,  // OUT: Geodetic longitude  [DEG]     " << std::endl
   << "   double* const pAlt,  // OUT: Geodetic altitude   [DEG]     " << std::endl
   << "   const Basic::EarthModel* const pEM=0) // IN: Optional: Pointer to earth model (Default : WGS-84)" << std::endl
   << std::endl;
   
   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;
   std::cout << "==================================" << std::endl;
   std::cout << std::endl;
   
   std::cout << "----------------------------------------------------------------------" << std::endl;
   std::cout << "Case 1:" << std::endl;
   std::cout << "double x,y,z;" << std::endl;
   std::cout << "double lat,lon,alt;" << std::endl;
   std::cout << std::endl;
   
   std::cout << "INPUTS:" << std::endl << std::endl;
   //Nav::WGS84_A  = 6378137.0;
   std::cout << "x = 4000000.0;  // [M]" << std::endl;
   std::cout << "y = 4000000.0;  // [M]" << std::endl;
   std::cout << "z = 4000000.0;  // [M]" << std::endl;
   std::cout << std::endl;

   std::cout << "OUTPUTS:" << std::endl << std::endl;
   std::cout << "Basic::Nav::convertEcef2Geod(x, y, z, &lat, &lon, &alt, pEM);" << std::endl;
   std::cout << std::endl;
   
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << "=> lat    = " << std::setw(14) <<     35.4314 << "  // [DEG]" << std::endl;
   std::cout << "=> lon    = " << std::setw(14) <<     45.0000 << "  // [DEG]" << std::endl;
   std::cout << "=> alt    = " << std::setw(14) << 557215.8470 << "  // [M]" << std::endl;
   std::cout << std::endl;
   
   std::cout
   << "bool convertEcef2Geod(                                                          " << std::endl
   << "   const osg::Vec3d& xyz,                 // IN:  ECEF     [ IX   IY   IZ ]     " << std::endl
   << "   osg::Vec3d* const lla,                 // OUT: Geodetic [ ILAT ILON IALT ]   " << std::endl
   << "   const Basic::EarthModel* const pEM=0)  // IN:  Optional: Pointer to earth model (default: WGS-84) " << std::endl
   << std::endl;
   
   std::cout << "----------------------------------------------------------------------" << std::endl;
   std::cout << "INPUTS:" << std::endl << std::endl;
   std::cout << "Case 2:" << std::endl;
   std::cout << "osg::Vec3d xyz;" << std::endl;
   std::cout << "osg::Vec3d lla;" << std::endl;
   std::cout << std::endl;
   
   std::cout << "xyz[0] = x;  // [M]" << std::endl;
   std::cout << "xyz[1] = y;  // [M]" << std::endl;
   std::cout << "xyz[2] = z;  // [M]" << std::endl;
   std::cout << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl << std::endl;
   std::cout << "Basic::Nav::convertEcef2Geod(xyz, &lla, pEM);" << std::endl;
   std::cout << std::endl;
   std::cout << "=> lla[0] = " << std::setw(14) <<     35.4314 << "  // [DEG]" << std::endl;
   std::cout << "=> lla[1] = " << std::setw(14) <<     45.0000 << "  // [DEG]" << std::endl;
   std::cout << "=> lla[2] = " << std::setw(14) << 557215.8470 << "  // [M]"   << std::endl;
   std::cout << std::endl;
   
   //XYZ[0] = x;  // [M]
   //XYZ[1] = y;  // [M]
   //XYZ[2] = z;  // [M]
   
   std::cout << "----------------------------------------------------------------------" << std::endl;
   std::cout << "INPUTS:" << std::endl << std::endl;

   std::cout << "Case 3:" << std::endl;
   std::cout << "double XYZ[3];" << std::endl;
   std::cout << "double LLA[3];" << std::endl;
   std::cout << std::endl;
   
   std::cout << "XYZ[0] = x;  // [M]" << std::endl;
   std::cout << "XYZ[1] = y;  // [M]" << std::endl;
   std::cout << "XYZ[2] = z;  // [M]" << std::endl;
   std::cout << std::endl;
   std::cout << "Basic::Nav::convertEcef2Geod(XYZ, &LLA, pEM);" << std::endl;
   std::cout << std::endl;
   
   std::cout << "OUTPUTS:" << std::endl << std::endl;
   std::cout << "=> LLA[0] = " << std::setw(14) <<     35.4314 << "  // [DEG]" << std::endl;
   std::cout << "=> LLA[1] = " << std::setw(14) <<     45.0000 << "  // [DEG]" << std::endl;
   std::cout << "=> LLA[2] = " << std::setw(14) << 557215.8470 << "  // [M]"   << std::endl;
   std::cout << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

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
         
         Basic::Nav::convertEcef2Geod(x, y, z, &lat, &lon, &alt, pEM);
         
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "*** single variables: x,y,z => lat,lon,alt ***" << std::endl;
         std::cout << "lat    = " << std::setw(14) << lat << " [DEG]" << std::endl;
         std::cout << "lon    = " << std::setw(14) << lon << " [DEG]" << std::endl;
         std::cout << "alt    = " << std::setw(14) << alt << " [M]" << std::endl;
         std::cout << std::endl;

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
         //      const double XYZ[3],                    // IN:  ECEF     [ IX   IY   IZ ]
         //      double LLA[3],                          // OUT: Geodetic [ ILAT ILON IALT ]
         //      const Basic::EarthModel* const pEM=0)   // IN: Optional: Pointer to earth model (default: WGS-84)
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
   }
}

//--------
// #26
//--------
void test26_convertGeod2Ecef()
{
   std::cout << "=============================================" << std::endl;
   std::cout << "test26_convertGeod2Ecef" << std::endl << std::endl;

   std::cout << "==================================" << std::endl;
   std::cout << "Example problem:                  " << std::endl;
   std::cout << "==================================" << std::endl;
   std::cout << std::endl;
   
   std::cout << "----------------------------------------------------------------------" << std::endl;
   std::cout << "Case 1:" << std::endl;
   std::cout << std::endl;
   
   std::cout
   << "bool convertGeod2Ecef(                                                          " << std::endl
   << "   const double  lat,                    // IN:  Geodetic latitude  [DEG]       " << std::endl
   << "   const double  lon,                    // IN:  Geodetic longitude [DEG]       " << std::endl
   << "   const double  alt,                    // IN:  Geodetic altitude  [M]         " << std::endl
   << "   double* const pX,                     // OUT: ECEF X component   [M]         " << std::endl
   << "   double* const pY,                     // OUT: ECEF Y component   [M]         " << std::endl
   << "   double* const pZ,                     // OUT: ECEF Z component   [M]         " << std::endl
   << "   const Basic::EarthModel* const pEM=0) // IN: Optional: Pointer to earth model (default: WGS-84)" << std::endl
   << std::endl;
   
   std::cout << "lat    = 40.0;  // [DEG]" << std::endl;
   std::cout << "lon    = 50.0;  // [DEG]" << std::endl;
   std::cout << "alt    =  0.0;  // [M]  " << std::endl;
   std::cout << std::endl;
   
   std::cout << "Basic::Nav::convertGeod2Ecef(lat, lon, alt, &x, &y, &z, pEM);" << std::endl;
   std::cout << std::endl;
   
   std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
   std::cout << "=> x      = " << std::setw(14) << 3144971.82 << "  // [M]" << std::endl;
   std::cout << "=> y      = " << std::setw(14) << 3748031.47 << "  // [M]" << std::endl;
   std::cout << "=> z      = " << std::setw(14) << 4077985.57 << "  // [M]" << std::endl;
   std::cout << std::endl;
   
   std::cout << "----------------------------------------------------------------------" << std::endl;
   std::cout << "Case 2:" << std::endl;
   std::cout << std::endl;
   
   std::cout
   << "bool convertGeod2Ecef(                                                          " << std::endl
   << "   const double lla[3],                  // IN:  Geodetic [ ILAT ILON IALT ]    " << std::endl
   << "   double       xyz[3],                  // OUT: ECEF     [ IX   IY   IZ ]      " << std::endl
   << "   const Basic::EarthModel* const pEM=0) // IN:  Optional: Pointer to earth model (Default : WGS-84)" << std::endl                      
   << std::endl;
   
   std::cout << "lla[0] = lat;  // [DEG]" << std::endl;
   std::cout << "lla[1] = lon;  // [DEG]" << std::endl;
   std::cout << "lla[2] = alt;  // [M]"   << std::endl;
   std::cout << std::endl;
   
   std::cout << "Basic::Nav::convertGeod2Ecef(lla, &xyz, pEM);" << std::endl;
   std::cout << std::endl;
   
   std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
   std::cout << "=> xyz[0] = " << std::setw(14) << 3144971.82 << "  // [M]" << std::endl;
   std::cout << "=> xyz[1] = " << std::setw(14) << 3748031.47 << "  // [M]" << std::endl;
   std::cout << "=> xyz[2] = " << std::setw(14) << 4077985.57 << "  // [M]" << std::endl;
   std::cout << std::endl;
   
   std::cout << "----------------------------------------------------------------------" << std::endl;
   std::cout << "Case 3:" << std::endl << std::endl;

   std::cout
   << "bool convertGeod2Ecef(                                                       " << std::endl
   << "   const osg::Vec3d& lla,                // IN:  Geodetic [ ILAT ILON IALT ] " << std::endl
   << "   osg::Vec3d* const ecef,               // OUT: ECEF     [ IX   IY   IZ ]   " << std::endl
   << "   const Basic::EarthModel* const pEM=0) // IN: Optional: Pointer to earth model (default: WGS-84)" << std::endl
   << std::endl;
   
   std::cout << "LLA[0] = lat;  // [DEG]" << std::endl;
   std::cout << "LLA[1] = lon;  // [DEG]" << std::endl;
   std::cout << "LLA[2] = alt;  // [M]"   << std::endl;
   std::cout << std::endl;
   
   std::cout << "Basic::Nav::convertGeod2Ecef(LLA, XYZ, pEM);" << std::endl;
   std::cout << std::endl;
   
   std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
   std::cout << "=> XYZ[0] = " << std::setw(14) << 3144971.82 << "  // [M]" << std::endl;
   std::cout << "=> XYZ[1] = " << std::setw(14) << 3748031.47 << "  // [M]" << std::endl;
   std::cout << "=> XYZ[2] = " << std::setw(14) << 4077985.57 << "  // [M]" << std::endl;
   std::cout << std::endl;


   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;   
      std::cout << std::endl;

      if (ynCont != 'n') {

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

         std::cout << "Enter latitude  [DEG] : "; std::cin >> lat;
         std::cout << "Enter longitude [DEG] : "; std::cin >> lon;
         std::cout << "Enter altitude  [M]   : "; std::cin >> alt;
         std::cout << std::endl;
         
         // copy to lla
         lla[0] = lat;
         lla[1] = lon;
         lla[2] = alt;
         
         // copy to LLA
         LLA[0] = lat;
         LLA[1] = lon;
         LLA[2] = alt;
         
         Basic::Nav::convertGeod2Ecef(lat, lon, alt, &x, &y, &z, pEM);

         std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
         std::cout << "*** double variables: lat,lon,alt => x,y,z ***" << std::endl;
         std::cout << "x      = " << std::setw(14) << x << " [M]" << std::endl;
         std::cout << "y      = " << std::setw(14) << y << " [M]" << std::endl;
         std::cout << "z      = " << std::setw(14) << z << " [M]" << std::endl;
         std::cout << std::endl;

         Basic::Nav::convertGeod2Ecef(lla, &xyz, pEM);
           
         // output results
         std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
         std::cout << "*** osg::vec3d vector: lla => xyz ***" << std::endl;
         std::cout << "xyz[0] = " << std::setw(14) << xyz[0] << " [M]" << std::endl;
         std::cout << "xyz[1] = " << std::setw(14) << xyz[1] << " [M]" << std::endl;
         std::cout << "xyz[2] = " << std::setw(14) << xyz[2] << " [M]" << std::endl;
         std::cout << std::endl;
           
         Basic::Nav::convertGeod2Ecef(LLA, XYZ, pEM);

         std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
         std::cout << "*** double array: LLA => XYZ ***" << std::endl;
         std::cout << "XYZ[0] = " << std::setw(14) << XYZ[0] << " [M]" << std::endl;
         std::cout << "XYZ[1] = " << std::setw(14) << XYZ[1] << " [M]" << std::endl;
         std::cout << "XYZ[2] = " << std::setw(14) << XYZ[2] << " [M]" << std::endl;
         std::cout << std::endl;
      }
   }
}


//------------------------------------------------------------------------------
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


} // end namespace TestNav 
} // end namespace Eaagles

//==============================================================================
int main(int argc, char* argv[])
{
   return Eaagles::TestNav::testNavFns();

}


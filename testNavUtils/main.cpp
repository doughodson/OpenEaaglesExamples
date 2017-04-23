//-----------------------------------------------------------------------------
// Tests navigation routines
//-----------------------------------------------------------------------------

#include "openeaagles/base/EarthModel.hpp"
#include "openeaagles/base/units/Distances.hpp"
#include "openeaagles/base/util/nav_utils.hpp"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace oe;

// -----------------------------------------------------------------------------
// Global Variables (and Constants)
// -----------------------------------------------------------------------------
//static double slat = 0.0;
//static double slon = 0.0;
//static double tlat = 1.0;
//static double tlon = 1.0;
static double brng = 45.0;
//static double dist = 100.0;
static const base::EarthModel* pEM = &base::EarthModel::wgs84;

static int testNumber = 0;
static char ynCont = 'y';
//static char ynMenu = 'y';
static const char* enterYourOwnData = "Enter your own data? (y/n) : ";

//------------------------------------------------------------------------------
// prototype functions
//------------------------------------------------------------------------------
int showVec2(const base::Vec2d V);
int showVec3(const base::Vec3d V);
int displayMatrix(const base::Matrixd M);

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

void test23_convertPosVec2llE();
void test24_convertLL2PosVecE();
void test25_convertEcef2Geod();
void test26_convertGeod2Ecef();
void test27_convertUtm();

void test99_printAllExamples();

void displayNavTestFunctions();
void selectNavTestFunction(int n);

//------------------------------------------------------------------------------
// Test navigation functions
//------------------------------------------------------------------------------
int testNavFns()
{
   while (ynCont != 'n') {
         displayNavTestFunctions();

      std::cout << "Enter a Nav function test number: ";
      std::cin  >> testNumber;

      switch (testNumber) {
         // Direct and Inverse Methods
         case  0: std::exit(0);
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

         case 23: test23_convertPosVec2llE();             break;
         case 24: test24_convertLL2PosVecE();             break;
         case 25: test25_convertEcef2Geod();             break;
         case 26: test26_convertGeod2Ecef();             break;

         case 27: test27_convertUtm();                   break;

         // Print All Results
         case 99: test99_printAllExamples();             break;

         default:
            std::cout << "Bad selection. Try again." << std::endl;
            break;
      }

      std::cout << "Continue?  (y/n)";
      std::cin  >> ynCont;
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
   std::cout << "   0)  exit()"                              << std::endl
             << "   1)  test fbd2llE()"                      << std::endl
             << "   2)  test fll2bdE()"                      << std::endl
             << "   3)  test fbd2llS()"                      << std::endl
             << "   4)  test fll2bdS()"                      << std::endl
             << "   5)  test aer2xyz()"                      << std::endl
             << "   6)  test aer2xyz()"                      << std::endl
             << "   7)  test xyz2aer()"                      << std::endl
             << "   8)  test xyz2aer()"                      << std::endl
             << "   9)  test gbd2ll()"                       << std::endl
             << "  10)  test gll2bd()"                       << std::endl
             << "  11)  test gbd2llS()"                      << std::endl
             << "  12)  test gll2bdS()"                      << std::endl
             << "  13)  test glla2bd()"                      << std::endl
             << "  14)  test glla2bdS()"                     << std::endl
             << "  15)  test vbd2ll()"                       << std::endl
             << "  16)  test vll2bd()"                       << std::endl

   // Matrix Generators
             << "  17)  test computeWorldMatrix()"           << std::endl
             << "  18)  test computeEulerAnglesDeg()"        << std::endl

             << "  19)  test computeRotationalMatrix()"      << std::endl
             << "  20)  test computeRotationalMatrix()"      << std::endl
             << "  21)  test computeRotationalMatrixDeg()"   << std::endl
             << "  22)  test computeRotationalMatrixDeg()"   << std::endl

             << "  23)  test convertPosVec2llE()"             << std::endl
             << "  24)  test convertLL2PosVecE()"             << std::endl
             << "  25)  test convertEcef2Geod()"             << std::endl
             << "  26)  test convertGeod2Ecef()"             << std::endl
             << "  27)  test UTM conversion"                 << std::endl

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

   test23_convertPosVec2llE();
   test24_convertLL2PosVecE();
   test25_convertEcef2Geod();
   test26_convertGeod2Ecef();

   test27_convertUtm();
}


//------------------------------------------------------------------------------
// TEST NAVIGATION FUNCTIONS
//------------------------------------------------------------------------------

//--------
// #1
//--------
void test01_fbd2llE()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << std::endl
             << "=====================================================" << std::endl
             << "Example problem 1: test01_fbd2llE                    " << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool fbd2llE("  << std::endl
             << "       const double slat,             // IN:  source latitude          [DEG]" << std::endl
             << "       const double slon,             // IN:  source longitude         [DEG]" << std::endl
             << "       const double brg,              // IN:  True bearing             [DEG]" << std::endl
             << "       const double dist,             // IN:  Distance (ground range)   [NM]" << std::endl
             << "       double* const tlat,            // OUT: target latitude          [DEG]" << std::endl
             << "       double* const tlon,            // OUT: target longitude         [DEG]" << std::endl
             << "       const EarthModel* const em=0); // IN:  Pointer to an optional earth  " << std::endl
             << "                                              earth model (default: WGS-84) " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage: " << std::endl
             << "  base::nav::fbd2llE(slat,slon,brng,dist,&tlat,&tlon,pEM)" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double brng = 45.0;
   double dist = 100.0;
   double tlat = 0.0;
   double tlon = 0.0;

   const base::EarthModel* pEM = &base::EarthModel::wgs84;
   const double TGT_LAT = 1.1843;
   const double TGT_LON = 1.1764;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs:" << std::endl
             << "  slat = " << std::setw(10) << slat    << "  // source latitude   [DEG]" << std::endl
             << "  slon = " << std::setw(10) << slon    << "  // source longitude  [DEG]" << std::endl
             << "  brng = " << std::setw(10) << brng    << "  // target bearing    [DEG]" << std::endl
             << "  dist = " << std::setw(10) << dist    << "  // target distance    [NM]" << std::endl
             << "  pEM  = " << std::setw(10) << "wgs84" << "  // earth model pointer    " << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results:" << std::endl;
   std::cout << "  tlat = " << std::setw(10) << TGT_LAT << " [DEG]" << std::endl
             << "  tlon = " << std::setw(10) << TGT_LON << " [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // calculate actual results
   //-----------------------------------
   base::nav::fbd2llE(slat,slon,brng,dist,&tlat,&tlon,pEM);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results:" << std::endl
             << "  tlat = " << std::setw(10) << tlat << " [DEG]" << std::endl
             << "  tlon = " << std::setw(10) << tlon << " [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors:" << std::endl
             << "  tlat error = " << std::setw(10) << tlat - TGT_LAT << std::endl
             << "  tlon error = " << std::setw(10) << tlon - TGT_LON << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         slat = 0.0;
         slon = 0.0;
         brng = 0.0;
         dist = 0.0;
         tlat = 0.0;
         tlon = 0.0;

         std::cout << "Enter source latitude   [DEG] : "; std::cin >> slat;
         std::cout << "Enter source longitude  [DEG] : "; std::cin >> slon;
         std::cout << "Enter target bearing    [DEG] : "; std::cin >> brng;
         std::cout << "Enter target distance    [NM] : "; std::cin >> dist;
         std::cout << std::endl;

         base::nav::fbd2llE(slat, slon, brng, dist, &tlat, &tlon, pEM);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "  tlat = " << std::setw(10) << tlat << " [DEG]" << std::endl;
         std::cout << "  tlon = " << std::setw(10) << tlon << " [DEG]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #2
//--------
void test02_fll2bdE()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "Example problem 2: test02_fll2bdE                    " << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool fll2bdE(" << std::endl
             << "  const double slat,           // IN:  source latitude         [DEG]"  << std::endl
             << "  const double slon,           // IN:  source longitude        [DEG]"  << std::endl
             << "  const double tlat,           // IN:  target latitude         [DEG]"  << std::endl
             << "  const double tlon,           // IN:  target longitude        [DEG]"  << std::endl
             << "  double* const brg,           // OUT: True bearing            [DEG]"  << std::endl
             << "  double* const dist,          // OUT: distance (ground range)  [NM]"  << std::endl
             << "  const EarthModel* const em=0 // IN:  Pointer to an optional       "  << std::endl
             << "                               //      earth model (default: WGS-84)"  << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage: " << std::endl
             << "  base::nav::fll2bdE(slat,slon,tlat,tlon,&brng,&dist,pEM)" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double tlat = 1.0;
   double tlon = 1.0;
   double brng = 0.0;
   double dist = 0.0;
   const base::EarthModel* pEM = &base::EarthModel::wgs84;

   const double TGT_BRNG = 45.1924;
   const double TGT_DIST = 84.7211;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs:" << std::endl
             << "  slat = " << std::setw(10) << slat    << "  // source latitude   [DEG]" << std::endl
             << "  slon = " << std::setw(10) << slon    << "  // source longitude  [DEG]" << std::endl
             << "  tlat = " << std::setw(10) << tlat    << "  // target latitude   [DEG]" << std::endl
             << "  tlon = " << std::setw(10) << tlon    << "  // target longitude  [DEG]" << std::endl
             << "  pEM  = " << std::setw(10) << "wgs84" << "  // pointer to earth model " << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results:" << std::endl
             << "  brng = " << std::setw(10) << TGT_BRNG << "  // target bearing   [DEG]" << std::endl
             << "  dist = " << std::setw(10) << TGT_DIST << "  // target distance   [NM]" << std::endl
             << std::endl;

   //-----------------------------------
   // calculate actual results
   //-----------------------------------
   base::nav::fll2bdE(slat,slon,tlat,tlon,&brng,&dist,pEM);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results:" << std::endl
             << "  brng = " << std::setw(10) << brng << std::endl
             << "  dist = " << std::setw(10) << dist << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors:" << std::endl;
   std::cout << "  brng error = " << std::setw(10) << brng - TGT_BRNG << std::endl
             << "  dist error = " << std::setw(10) << dist - TGT_DIST << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         slat = 0.0;
         slon = 0.0;
         tlat = 0.0;
         tlon = 0.0;
         brng = 0.0;
         dist = 0.0;

         std::cout << "Enter source latitude   [DEG] : "; std::cin >> slat;
         std::cout << "Enter source longitude  [DEG] : "; std::cin >> slon;
         std::cout << "Enter target latitude   [DEG] : "; std::cin >> tlat;
         std::cout << "Enter target longitude  [DEG] : "; std::cin >> tlon;
         std::cout << std::endl;

         base::nav::fll2bdE(slat, slon, tlat, tlon, &brng, &dist, pEM);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "brng = " << std::setw(10) << brng << " [DEG]" << std::endl;
         std::cout << "dist = " << std::setw(10) << dist << "  [NM]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #3
//--------
void test03_fbd2llS()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "Example problem: 3) test03_fbd2llS            " << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool fll2bdS(" << std::endl
             << "       const double slat,   // IN:  source latitude          [DEG]" << std::endl
             << "       const double slon,   // IN:  source longitude         [DEG]" << std::endl
             << "       const double tlat,   // IN:  target latitude          [DEG]" << std::endl
             << "       const double tlon,   // IN:  target longitude         [DEG]" << std::endl
             << "       double* const brg,   // OUT: True bearing             [DEG]" << std::endl
             << "       double* const dist); // OUT: distance (ground range)   [NM]" << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage: " << std::endl
             << "  base::nav::fbd2llS(slat,slon,brng,dist,&tlat,&tlon);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double brng = 45.0;
   double dist = 100.0;
   double tlat = 0.0;
   double tlon = 0.0;

   const double TGT_LAT = 1.1785;
   const double TGT_LON = 1.1785;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs:" << std::endl
             << "  slat = " << std::setw(10) << slat << "  // source latitude   [DEG]" << std::endl
             << "  slon = " << std::setw(10) << slon << "  // source longitude  [DEG]" << std::endl
             << "  brng = " << std::setw(10) << brng << "  // target bearing    [DEG]" << std::endl
             << "  dist = " << std::setw(10) << dist << "  // target distance    [NM]" << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results:" << std::endl;
   std::cout << "  tlat = " << std::setw(10) << TGT_LAT << std::endl
             << "  tlon = " << std::setw(10) << TGT_LON << std::endl
             << std::endl;

   //-----------------------------------
   // calculate actual results
   //-----------------------------------
   base::nav::fbd2llS(slat,slon,brng,dist,&tlat,&tlon);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results:" << std::endl
             << "  brng = " << std::setw(10) << brng << "  // target latitude   [DEG]" << std::endl
             << "  dist = " << std::setw(10) << dist << "  // target longitude  [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors:" << std::endl
             << "  tlat error = " << std::setw(10) << tlat - TGT_LAT << std::endl
             << "  tlon error = " << std::setw(10) << tlon - TGT_LON << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
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
         std::cout << "Enter source distance    [NM] : "; std::cin >> dist;
         std::cout << std::endl;

         base::nav::fbd2llS(slat, slon, brng, dist, &tlat, &tlon);

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
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "Example problem 4: test04_fll2bdS             " << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool fll2bdS(        " << std::endl
             << "       const double slat,  // IN:  source latitude           [DEG]" << std::endl
             << "       const double slon,  // IN:  source longitude          [DEG]" << std::endl
             << "       const double tlat,  // IN:  target latitude           [DEG]" << std::endl
             << "       const double tlon,  // IN:  target longitude          [DEG]" << std::endl
             << "       double* const brg,  // OUT: true bearing              [DEG]" << std::endl
             << "       double* const dist  // OUT: distance (ground range)    [NM]" << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage: " << std::endl
             << "  base::nav::fll2bdS(slat,slon,tlat,tlon,&brng,&dist,pEM)" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double tlat = 1.0;
   double tlon = 1.0;
   double brng = 0.0;
   double dist = 0.0;

   const double TGT_BRNG = 45.0;
   const double TGT_DIST = 84.8528;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs:" << std::endl
             << "  slat = " << std::setw(10) << slat     << "  // source latitude   [DEG]" << std::endl
             << "  slon = " << std::setw(10) << slon     << "  // source longitude  [DEG]" << std::endl
             << "  tlat = " << std::setw(10) << tlat     << "  // target latitude   [DEG]" << std::endl
             << "  tlon = " << std::setw(10) << tlon     << "  // target longitude  [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results:" << std::endl;
   std::cout << "  brng = " << std::setw(10) << TGT_BRNG << "  // target bearing    [DEG]" << std::endl
             << "  dist = " << std::setw(10) << TGT_DIST << "  // target distance    [NM]" << std::endl
             << std::endl;

   //-----------------------------------
   // calculate actual results
   //-----------------------------------
   base::nav::fll2bdS(slat,slon,tlat,tlon,&brng,&dist);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results:" << std::endl;
   std::cout << "  brng = " << std::setw(10) << brng << std::endl
             << "  dist = " << std::setw(10) << dist << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors:" << std::endl;
   std::cout << "  brng error = " << std::setw(10) << brng - TGT_BRNG << std::endl
             << "  dist error = " << std::setw(10) << dist - TGT_DIST << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         slat = 0.0;
         slon = 0.0;
         tlat = 0.0;
         tlon = 0.0;
         brng = 0.0;
         dist = 0.0;

         std::cout << "Enter source latitude   [DEG] : "; std::cin >> slat;
         std::cout << "Enter source longitude  [DEG] : "; std::cin >> slon;
         std::cout << "Enter target latitude   [DEG] : "; std::cin >> tlat;
         std::cout << "Enter target longitude  [DEG] : "; std::cin >> tlon;
         std::cout << std::endl;

         base::nav::fll2bdS(slat, slon, tlat, tlon, &brng, &dist);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "brng = " << std::setw(10) << brng << " [DEG]" << std::endl;
         std::cout << "dist = " << std::setw(10) << dist << "  [NM]" << std::endl;
         std::cout << std::endl;
      }
   }
}


//--------
// #5
//--------
void test05_aer2xyz()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "Example problem 5: test05_aer2xyz - using euler angles" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool aer2xyz( " << std::endl
             << "       base::Vec3d* const pos,  // OUT: position vector array (NED, player centered) [M]              " << std::endl
             << "       const double azim,       // IN:  azimuth (body)                               [RAD]            " << std::endl
             << "       const double elev,       // IN:  elevation (body)  (positive up)              [RAD]            " << std::endl
             << "       const double ranj)       // IN:  range                                        [M]              " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage: " << std::endl
             << "  base::nav::aer2xyz(&pos, azim, elev, ranj);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double azim = 45.0;
   double elev = 30.0;
   double ranj = 1000.0;
   base::Vec3d pos;

   const double XPOS = 612.3724;
   const double YPOS = 612.3724;
   const double ZPOS = -500.0;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs:" << std::endl
             << "  azim   = " << std::setw(10) << azim << "  // azimuth    [DEG]" << std::endl
             << "  elev   = " << std::setw(10) << elev << "  // elevation  [DEG]" << std::endl
             << "  ranj   = " << std::setw(10) << ranj << "  // range      [M]  " << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results:" << std::endl
             << "  pos[0] = " << std::setw(10) << XPOS << "  // x  [M]" << std::endl
             << "  pos[1] = " << std::setw(10) << YPOS << "  // y  [M]" << std::endl
             << "  pos[2] = " << std::setw(10) << ZPOS << "  // z  [M]" << std::endl
             << std::endl;

   //-----------------------------------
   // convert azim and elev to radians
   //-----------------------------------
   azim *= base::angle::D2RCC;
   elev *= base::angle::D2RCC;

   //-----------------------------------
   // calculate position
   //-----------------------------------
   base::nav::aer2xyz(&pos,azim,elev,ranj);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results:" << std::endl;
   std::cout << "  pos[0] = " << std::setw(10) <<  pos[0] << "  // x  [M]" << std::endl
             << "  pos[1] = " << std::setw(10) <<  pos[1] << "  // y  [M]" << std::endl
             << "  pos[2] = " << std::setw(10) <<  pos[2] << "  // z  [M]" << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors:" << std::endl;
   std::cout << "  pos[0] error = " << std::setw(10) << pos[0] - XPOS << std::endl
             << "  pos[1] error = " << std::setw(10) << pos[1] - YPOS << std::endl
             << "  pos[2] error = " << std::setw(10) << pos[2] - ZPOS << std::endl
             << std::endl;

   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         double azim = 0.0;
         double elev = 0.0;
         double ranj = 0.0;
         base::Vec3d pos;

         std::cout << "Enter azimuth    [DEG] : "; std::cin >> azim;
         std::cout << "Enter elevation  [DEG] : "; std::cin >> elev;
         std::cout << "Enter range      [M]   : "; std::cin >> ranj;
         std::cout << std::endl;

         azim *= base::angle::D2RCC;
         elev *= base::angle::D2RCC;

         std::cout << "azimuth   = 0.7854    [RAD]" << std::endl
                   << "elevation = 0.5236    [RAD]" << std::endl
                   << "range     = 1000.0000 [M]  " << std::endl
                   << std::endl;

         base::nav::aer2xyz(&pos, azim, elev, ranj);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "pos[0]    = " << std::setw(12) << pos[0] << " [M]" << std::endl
                   << "pos[1]    = " << std::setw(12) << pos[1] << " [M]" << std::endl
                   << "pos[2]    = " << std::setw(12) << pos[2] << " [M]" << std::endl
                   << std::endl;
      }
   }
}

//--------
// #6
//--------
void test06_aer2xyz()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "Example problem 6: test06_aer2xyz - using body angles" << std::endl
             << std::endl;

   //-----------------------------------
   // begin phase 1 - calculate rotation matrix
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Phase 1: Calculate a rotation matrix"                    << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:"                               << std::endl
             << "  bool computeRotationalMatrixDeg("                    << std::endl
             << "       const base::Vec3d& angles,    // IN:  [ phi theta psi ]  [DEG]  " << std::endl
             << "       base::Matrixd* const rm,      // OUT: Matrix                    " << std::endl
             << "       base::Vec2d* const scPhi=0,   // OUT: Sin/Cos of phi   (opt)    " << std::endl
             << "       base::Vec2d* const scTht=0,   // OUT: Sin/Cos of theta (opt)    " << std::endl
             << "       base::Vec2d* const scPsi=0);  // OUT: Sin/Cos of psi   (opt)    " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage: "                                  << std::endl
             << "  base::nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double roll  = 10.0;
   double pitch = 20.0;
   double yaw   = 30.0;
   base::Matrixd rm;

   const double NORTH =   39.0485;
   const double EAST  =  819.1647;
   const double DOWN  = -572.2276;


   double azim  = 45.0;
   double elev  = 30.0;
   double ranj  = 1000.0;
   base::Vec3d pos;

   base::Matrixd ER;
   ER(0,0) =  0.8138;
   ER(0,1) =  0.4698;
   ER(0,2) = -0.3420;
   ER(1,0) = -0.4410;
   ER(1,1) =  0.8826;
   ER(1,2) =  0.1632;
   ER(2,0) =  0.3785;
   ER(2,1) =  0.0180;
   ER(2,2) =  0.9254;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs for rotation matrix
   //-----------------------------------
   std::cout << "Test Inputs for rotation matrix:" << std::endl
             << "roll   = " << roll  << "  [DEG]"  << std::endl
             << "pitch  = " << pitch << "  [DEG]"  << std::endl
             << "yaw    = " << yaw   << "  [DEG]"  << std::endl
             << std::endl;

   //-----------------------------------
   // Calculate rotation matrix using...
   //   base::nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);
   //-----------------------------------
   base::nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);

   //-----------------------------------
   // show calculated rotation matrix
   //-----------------------------------
   std::cout << "  expected rotation matrix" << std::endl;
   std::cout << "  E(rm) = " << std::endl;
   displayMatrix(ER);

   std::cout << "  calculated rotation matrix" << std::endl;
   std::cout << "  rm = " << std::endl;
   displayMatrix(rm);

   std::cout << "Errors = rm - E(rm):" << std::endl;
   displayMatrix(rm - ER);

   //-----------------------------------
   // begin phase 2 - calculate position
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Phase 2: Calculate Position (pos)"                     << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool aer2xyz( " << std::endl
             << "       base::Vec3d* const pos,   // OUT: position vector array (NED, player centered) [M]              " << std::endl
             << "       const base::Matrixd& rm,  // IN:  NED to body rotational matrix (see computeRotationalMatrix()) " << std::endl
             << "       const double azim,        // IN:  azimuth (body)                               [RAD]            " << std::endl
             << "       const double elev,        // IN:  elevation (body)  (positive up)              [RAD]            " << std::endl
             << "       const double ranj)        // IN:  range                                        [M]              " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage: " << std::endl
             << "  base::nav::aer2xyz(&pos, rm, azim, elev, ranj);" << std::endl
             << std::endl;

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "Test Inputs:" << std::endl
             << "rm matrix = "    << std::endl;
             displayMatrix(rm);
   std::cout << "azim   = " << std::setw(10) << azim << "  [DEG]" << std::endl
             << "elev   = " << std::setw(10) << elev << "  [DEG]" << std::endl
             << "ranj   = " << std::setw(10) << ranj << "  [M]  " << std::endl
             << std::endl;

   //-----------------------------------
   // Convert azimuth and elevation from degrees to radians
   //-----------------------------------
   azim *= base::angle::D2RCC;
   elev *= base::angle::D2RCC;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Position Vector (Expected Results):" << std::endl
             << "pos[0] = " << std::setw(10) << NORTH  << "  [M]  // north " << std::endl
             << "pos[1] = " << std::setw(10) << EAST   << "  [M]  // east  " << std::endl
             << "pos[2] = " << std::setw(10) << DOWN   << "  [M]  // down  " << std::endl
             << std::endl;

   //-----------------------------------
   // calculate actual results
   //-----------------------------------
   base::nav::aer2xyz(&pos, rm, azim, elev, ranj);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Position Vector (Actual Results):" << std::endl
             << "pos[0] = " << std::setw(10) << pos[0] << "  [M]  // north " << std::endl
             << "pos[1] = " << std::setw(10) << pos[1] << "  [M]  // east  " << std::endl
             << "pos[2] = " << std::setw(10) << pos[2] << "  [M]  // down  " << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Position Vector (Errors):" << std::endl
             << std::setw(10) << pos[0] - NORTH << std::endl
             << std::setw(10) << pos[1] - EAST  << std::endl
             << std::setw(10) << pos[2] - DOWN  << std::endl
             << std::endl;

   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         double roll  = 0.0;
         double pitch = 0.0;
         double yaw   = 0.0;
         base::Matrixd rm;

         double azim  = 0.0;
         double elev  = 0.0;
         double ranj  = 0.0;
         base::Vec3d pos;

         std::cout << "Enter roll   [DEG] : "; std::cin >> roll;
         std::cout << "Enter pitch  [DEG] : "; std::cin >> pitch;
         std::cout << "Enter yaw    [DEG  : "; std::cin >> yaw;
         std::cout << std::endl;

         roll  *= base::angle::D2RCC;
         pitch *= base::angle::D2RCC;
         yaw   *= base::angle::D2RCC;

         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "roll   = " << std::setw(12) << roll  << " [RAD]" << std::endl;
         std::cout << "pitch  = " << std::setw(12) << pitch << " [RAD]" << std::endl;
         std::cout << "yaw    = " << std::setw(12) << yaw   << " [RAD]" << std::endl;
         std::cout << std::endl;

         std::cout << "base::nav::computeRotationalMatrix(roll, pitch, yaw, &rm);" << std::endl;
         base::nav::computeRotationalMatrix(roll, pitch, yaw, &rm);
         std::cout << "=> rm  = " << std::endl;
         displayMatrix(rm);

         std::cout << "Enter azimuth    [DEG] : "; std::cin >> azim;
         std::cout << "Enter elevation  [DEG] : "; std::cin >> elev;
         std::cout << "Enter range      [M]   : "; std::cin >> ranj;
         std::cout << std::endl;

         azim *= base::angle::D2RCC;
         elev *= base::angle::D2RCC;

         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "azim   = " << std::setw(12) << azim << " [RAD]" << std::endl;
         std::cout << "elev   = " << std::setw(12) << elev << " [RAD]" << std::endl;
         std::cout << "ranj   = " << std::setw(12) << ranj << " [M]  " << std::endl;
         std::cout << std::endl;

         base::nav::aer2xyz(&pos, rm, azim, elev, ranj);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "pos[0] = " << std::setw(12) << pos[0] << " [M]" << std::endl;
         std::cout << "pos[1] = " << std::setw(12) << pos[1] << " [M]" << std::endl;
         std::cout << "pos[2] = " << std::setw(12) << pos[2] << " [M]" << std::endl;
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
   // introduction
   //---------------------------------------------------------------------------

   std::cout << "====================================================" << std::endl
             << "Example problem 7: test07_xyz2aer using euler angles" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:"  << std::endl
             << "bool xyz2aer("  << std::endl
             << "   base::Vec3d* const aer, // OUT: azim,elev,rang   [DEG, DEG, M]  "  << std::endl
             << "   const double x,         // IN:  x                [M]            "  << std::endl
             << "   const double y,         // IN:  y                [M]            "  << std::endl
             << "   const double z)         // IN:  z                [M]            "  << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "base::nav::xyz2aer(&aer, x, y, z);" << std::endl
             << std::endl;

   //-------------------------
   // declare function parameters
   //-------------------------
   base::Vec3d aer;
   double x = 100.0;
   double y = 200.0;
   double z = 300.0;

   const double AZIM =  63.4349;
   const double ELEV = -53.3008;
   const double RANJ = 374.1657;

   //-------------------------
   // set output formats
   //-------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);


   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs:" << std::endl
             << "x = " << x << "  [M]  // x position" << std::endl
             << "y = " << y << "  [M]  // y position" << std::endl
             << "z = " << z << "  [M]  // z position" << std::endl
             << std::endl;

   //-----------------------------------
   // compute the aer vector (azim,elev,ranj)
   //-----------------------------------
   std::cout << "Compute aer Vector:" << std::endl
             << std::endl;

   base::nav::xyz2aer(&aer, x, y, z);

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results (azim,elev,ranj):" << std::endl
             << "  AZIM   = " << std::setw(10) << AZIM   << "  [DEG]  // azim" << std::endl
             << "  ELEV   = " << std::setw(10) << ELEV   << "  [DEG]  // elev" << std::endl
             << "  RANJ   = " << std::setw(10) << RANJ   << "    [M]  // ranj" << std::endl
             << std::endl;

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results (azim,elev,ranj):" << std::endl
             << "  aer[0] = " << std::setw(10) << aer[0] << "  [DEG]  // azim " << std::endl
             << "  aer[1] = " << std::setw(10) << aer[1] << "  [DEG]  // elev " << std::endl
             << "  aer[2] = " << std::setw(10) << aer[2] << "    [M]  // ranj " << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors:" << std::endl
             << "  azim error = " << std::setw(10) << aer[0] - AZIM << std::endl
             << "  elev error = " << std::setw(10) << aer[1] - ELEV << std::endl
             << "  ranj error = " << std::setw(10) << aer[2] - RANJ << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         x = 0.0;
         y = 0.0;
         z = 0.0;

         //-----------------------------------
         // input x,y,z from keyboard
         //-----------------------------------
         std::cout << "Enter x [M]: "; std::cin >> x;
         std::cout << "Enter y [M]: "; std::cin >> y;
         std::cout << "Enter z [M]: "; std::cin >> z;
         std::cout << std::endl;

         base::nav::xyz2aer(&aer, x, y, z);

         //-----------------------------------
         // show output results
         //-----------------------------------
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "aer[0] = " << std::setw(12) << aer[0] << "  [DEG]  // azimuth  " << std::endl
                   << "aer[1] = " << std::setw(12) << aer[1] << "  [DEG]  // elevation" << std::endl
                   << "aer[2] = " << std::setw(12) << aer[2] << "  [M]    // range    " << std::endl
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
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "test xyz2aer using body angles" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:"  << std::endl
             << "  bool xyz2aer(" << std::endl
             << "       base::Vec3d* const aer,   // OUT: position vector  [DEG, DEG, M]      " << std::endl
             << "       const base::Matrixd& rm,  // IN:  inertial to body rotational matrix  " << std::endl
             << "                                 //      (see computeRotationalMatrix())     " << std::endl
             << "       const double x,           // IN:  x                        [M]        " << std::endl
             << "       const double y,           // IN:  y                        [M]        " << std::endl
             << "       const double z)           // IN:  z                        [M]        " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage: "                                  << std::endl
             << "  base::nav::xyz2aer(aer, rm, x, y, z);"              << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   base::Vec3d aer;
   base::Matrixd rm;
   double roll  =  10.0;
   double pitch =  20.0;
   double yaw   =  30.0;
   double x     =  100.0;
   double y     =  200.0;
   double z     = -300.0;

   const double AZIM =  16.7137;  // [DEG]
   const double ELEV =  39.1375;  // [DEG]
   const double RANJ = 374.1657;  // [M]
   base::Matrixd erm;
   erm(0,0) =  0.8138;
   erm(0,1) =  0.4698;
   erm(0,2) = -0.3420;
   erm(1,0) = -0.4410;
   erm(1,1) =  0.8826;
   erm(1,2) =  0.1632;
   erm(2,0) =  0.3785;
   erm(2,1) =  0.0180;
   erm(2,2) =  0.9254;


   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show function parameters
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs:" << std::endl
             << "  roll  =   10  [DEG]       " << std::endl
             << "  pitch =   20  [DEG]       " << std::endl
             << "  yaw   =   30  [DEG]       " << std::endl
             << "  x     =  100    [M] north " << std::endl
             << "  y     =  200    [M] east  " << std::endl
             << "  z     = -300    [M] down  " << std::endl
             << std::endl;

   //-----------------------------------
   // compute the rotation matrix
   //-----------------------------------
   std::cout << "Compute the rotation matrix (rm):" << std::endl
             << "base::nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl
             << std::endl;

   base::nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);


   //-----------------------------------
   // show expected rotation matrix
   //-----------------------------------
   std::cout << "Expected Rotation Matrix:" << std::endl
             << "  erm = " << std::endl;
             displayMatrix(erm);

             //<< "    0.8138    0.4698   -0.3420 " << std::endl
             //<< "   -0.4410    0.8826    0.1632 " << std::endl
             //<< "    0.3785    0.0180    0.9254 " << std::endl
             //<< std::endl;

   //-----------------------------------
   // show actual rotation matrix
   //-----------------------------------
   std::cout << "Actual Rotation Matrix:" << std::endl
             << "  rm = " << std::endl;
             displayMatrix(rm);

   //-----------------------------------
   // show rotation matrix errors
   //-----------------------------------
   std::cout << "Errors = rm - erm = " << std::endl;
             displayMatrix(rm - erm);


   //-----------------------------------
   // compute the aer vector (azim,elev,ranj)
   //-----------------------------------
   std::cout << "Compute aer vector" << std::endl
             << "base::nav::xyz2aer(&aer, rm, x, y, z);" << std::endl
             << std::endl;

   base::nav::xyz2aer(&aer, rm, x, y, z);

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results:" << std::endl
             << "  AZIM   = " << std::setw(12) << AZIM   << " [DEG] azimuth   " << std::endl
             << "  ELEV   = " << std::setw(12) << ELEV   << " [DEG] elevation " << std::endl
             << "  RANJ   = " << std::setw(12) << RANJ   << " [M]   range     " << std::endl
             << std::endl;

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results" << std::endl
             << "  aer[0] = " << std::setw(12) << aer[0] << " [DEG] azimuth   " << std::endl
             << "  aer[1] = " << std::setw(12) << aer[1] << " [DEG] elevation " << std::endl
             << "  aer[2] = " << std::setw(12) << aer[2] << " [M]   range     " << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors:" << std::endl
             << "  aer[0] - AZIM = " << std::setw(10) << aer[0] - AZIM << std::endl
             << "  aer[1] - ELEV = " << std::setw(10) << aer[1] - ELEV << std::endl
             << "  aer[2] - RANJ = " << std::setw(10) << aer[2] - RANJ << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         x     = 0.0;
         y     = 0.0;
         z     = 0.0;
         yaw   = 0.0;
         pitch = 0.0;
         roll  = 0.0;

         std::cout << "Enter x - north  [M] : "; std::cin >> x;
         std::cout << "Enter y - east   [M] : "; std::cin >> y;
         std::cout << "Enter z - down   [M] : "; std::cin >> z;
         std::cout << std::endl;

         std::cout << "Enter roll   [DEG] : "; std::cin >> roll;
         std::cout << "Enter pitch  [DEG] : "; std::cin >> pitch;
         std::cout << "Enter yaw    [DEG  : "; std::cin >> yaw;
         std::cout << std::endl;

         roll  *= base::angle::D2RCC;
         pitch *= base::angle::D2RCC;
         yaw   *= base::angle::D2RCC;

         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "roll  = " << std::setw(12) << roll  << " [RAD]" << std::endl
                   << "pitch = " << std::setw(12) << pitch << " [RAD]" << std::endl
                   << "yaw   = " << std::setw(12) << yaw   << " [RAD]" << std::endl
                   << std::endl;

         std::cout << "base::nav::computeRotationalMatrix(roll, pitch, yaw, &rm);" << std::endl
                   << std::endl;

         base::nav::computeRotationalMatrix(roll, pitch, yaw, &rm);

         std::cout << "=> rm = " << std::endl;
         displayMatrix(rm);

         std::cout << "base::nav::xyz2aer(&aer, rm, x, y, z);" << std::endl
                   << std::endl;

         base::nav::xyz2aer(&aer, rm, x, y, z);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "aer[0] = " << std::setw(12) << aer[0] << "  [DEG]" << std::endl
                   << "aer[1] = " << std::setw(12) << aer[1] << "  [DEG]" << std::endl
                   << "aer[2] = " << std::setw(12) << aer[2] << "  [M]"   << std::endl
                   << std::endl;
      }
   }
}

//--------
// #9
//--------
void test09_gbd2ll()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=============================================" << std::endl
             << "test_gbd2llE" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "bool gbd2ll(" << std::endl
             << "   const double slat,     // IN:  Source latitude  [DEG]" << std::endl
             << "   const double slon,     // IN:  Source longitude [DEG]" << std::endl
             << "   const double brng,     // IN:  Target bearing   [DEG]" << std::endl
             << "   const double dist,     // IN:  Target distance   [NM]" << std::endl
             << "   double* const tlat,    // OUT: Target latitude  [DEG]" << std::endl
             << "   double* const tlon,    // OUT: Target longitude [DEG]" << std::endl
             << "   const base::EarthModel* const eem=0)                " << std::endl
             << "                          // IN: Earth model (default: WGS-84)" << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "base::nav::gbd2ll(slat,slon,brng,dist,&tlat,&tlon,eem); " << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double brng = 45.0;
   double dist = 100.0;
   double tlat = 0.0;
   double tlon = 0.0;
   const base::EarthModel* pEM = &base::EarthModel::wgs84;

   const double TLAT = 1.1763;
   const double TLON = 1.1845;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);


   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs:                               " << std::endl
             << "  slat = 0;      // source latitude   [DEG]" << std::endl
             << "  slon = 0;      // source longitude  [DEG]" << std::endl
             << "  brng = 45;     // target bearing    [DEG]" << std::endl
             << "  dist = 100;    // target distance    [NM]" << std::endl
             << "  pEM  = wgs84;  // earth model            " << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results:" << std::endl
             << "  TLAT = " << std::setw(10) << TLAT << "  [DEG]" << std::endl
             << "  TLON = " << std::setw(10) << TLON << "  [DEG]" << std::endl
             << std::endl;


   //-----------------------------------
   // calculate actual results
   //-----------------------------------
   base::nav::gbd2ll(slat, slon, brng, dist, &tlat, &tlon, pEM);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results:" << std::endl
             << "  tlat = " << std::setw(10) << tlat << "  [DEG]" << std::endl
             << "  tlon = " << std::setw(10) << tlon << "  [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors:" << std::endl
             << "  tlat - TLAT = " << std::setw(10) << tlat - TLAT << "  [DEG]" << std::endl
             << "  tlon - TLON = " << std::setw(10) << tlon - TLON << "  [DEG]" << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         // reset parameters
         slat = 0.0;
         slon = 0.0;
         brng = 0.0;
         dist = 0.0;
         tlat = 0.0;
         tlon = 0.0;

         // enter own data from keyboard
         std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
         std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
         std::cout << "Enter brng  [DEG] : "; std::cin >> brng;
         std::cout << "Enter dist   [NM] : "; std::cin >> dist;
         std::cout << std::endl;

         // compute results
         base::nav::gbd2ll(slat, slon, brng, dist, &tlat, &tlon, pEM);

         // show results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "tlat = " << std::setw(12) << tlat << " [DEG]" << std::endl;
         std::cout << "tlon = " << std::setw(12) << tlon << " [DEG]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #10
//--------
void test10_gll2bd()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------

   std::cout << "=============================================" << std::endl;
   std::cout << "test_gll2bdE" << std::endl << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "bool gll2bd( " << std::endl
             << "   const double slat,     // IN:  Source latitude    [DEG]" << std::endl
             << "   const double slon,     // IN:  Source longitude   [DEG]" << std::endl
             << "   const double tlat,     // IN:  Target latitude    [DEG]" << std::endl
             << "   const double tlon,     // IN:  Target longitude   [DEG]" << std::endl
             << "   double* const brng,    // OUT: bearing            [DEG]" << std::endl
             << "   double* const dist,    // OUT: distance            [NM]" << std::endl
             << "   const base::EarthModel* const eem=0)                  " << std::endl
             << "                          // IN: Earth model (dflt: WGS-84)" << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "base::nav::gll2bd(slat,slon,tlat,tlon,&brng,&dist,eem); " << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double tlat = 1.0;
   double tlon = 1.0;
   double brng = 0.0;
   double dist = 0.0;
   const base::EarthModel* pEM = &base::EarthModel::wgs84;

   const double BRNG = 44.8043;  // [DEG]
   const double DIST = 84.7189;  //  [NM]

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);


   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "  slat = 0;      // source latitude   [DEG]" << std::endl
             << "  slon = 0;      // source longitude  [DEG]" << std::endl
             << "  tlat = 1;      // target latitude   [DEG]" << std::endl
             << "  tlon = 1;      // target longitude   [NM]" << std::endl
             << "  pEM  = wgs84;  // pointer to earth model " << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results:" << std::endl
             << "  BRNG = " << std::setw(10) << BRNG << "  [DEG]" << std::endl
             << "  DIST = " << std::setw(10) << DIST << "   [NM]" << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::gll2bd(slat, slon, tlat, tlon, &brng, &dist, pEM);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results:" << std::endl
             << "  brng = " << std::setw(10) << brng << "  [DEG]" << std::endl
             << "  dist = " << std::setw(10) << dist << "   [NM]" << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors:" << std::endl
             << "  brng - BRNG = " << std::setw(10) << (brng - BRNG) << "  [DEG]" << std::endl
             << "  dist - DIST = " << std::setw(10) << (dist - DIST) << "  [DEG]" << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
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
         const base::EarthModel* pEM = &base::EarthModel::wgs84;

         std::cout << "Enter slat [DEG] : "; std::cin >> slat;
         std::cout << "Enter slon [DEG] : "; std::cin >> slon;
         std::cout << "Enter tlat [DEG] : "; std::cin >> tlat;
         std::cout << "Enter tlon [DEG] : "; std::cin >> tlon;
         std::cout << std::endl;

         base::nav::gll2bd(slat, slon, tlat, tlon, &brng, &dist, pEM);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "brng = " << std::setw(12) << brng << "  [DEG]" << std::endl;
         std::cout << "dist = " << std::setw(12) << dist << "   [NM]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #11
//--------
void test11_gbd2llS()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=============================================" << std::endl;
   std::cout << "test11_gbd2llS" << std::endl << std::endl;


   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "bool gbd2llS( " << std::endl
             << "   const double slat,    // IN:  Source latitude  [DEG]" << std::endl
             << "   const double slon,    // IN:  Source longitude [DEG]" << std::endl
             << "   const double brng,    // IN:  Target bearing   [DEG]" << std::endl
             << "   const double dist,    // IN:  Target distance   [NM]" << std::endl
             << "   double* const tlat,   // OUT: Target latitude  [DEG]" << std::endl
             << "   double* const tlon,   // OUT: Target longitude [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "base::nav::gbd2llS(slat, slon, brng, dist, &tlat, &tlon);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double brng = 45.0;
   double dist = 100.0;
   double tlat = 0.0;
   double tlon = 0.0;

   const double TLAT = 1.1784;
   const double TLON = 1.1787;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "slat = 0;     // source latitude   [DEG]             " << std::endl
             << "slon = 0;     // source longitude  [DEG]             " << std::endl
             << "brng = 45;    // target bearing    [DEG]             " << std::endl
             << "dist = 100;   // target distance    [NM]             " << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl
             << "  TLAT = " << std::setw(10) << TLAT << "  [DEG]  // target latitude" << std::endl
             << "  TLON = " << std::setw(10) << TLON << "  [DEG]  // target longitude" << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::gbd2llS(slat, slon, brng, dist, &tlat, &tlon);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl
             << "  tlat = " << std::setw(10) << tlat << "  [DEG]  // target latitude" << std::endl
             << "  tlon = " << std::setw(10) << tlon << "  [DEG]  // target longitude" << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl
             << "  tlat error = " << std::setw(10) << tlat - TLAT << std::endl
             << "  tlon error = " << std::setw(10) << tlon - TLON << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         // reset function parameters
         slat = 0.0;
         slon = 0.0;
         brng = 0.0;
         dist = 0.0;
         tlat = 0.0;
         tlon = 0.0;

         std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
         std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
         std::cout << "Enter brng  [DEG] : "; std::cin >> brng;
         std::cout << "Enter dist   [NM] : "; std::cin >> dist;
         std::cout << std::endl;

         base::nav::gbd2llS(slat, slon, brng, dist, &tlat, &tlon);

         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "tlat = " << std::setw(12) << tlat << " [DEG]" << std::endl;
         std::cout << "tlon = " << std::setw(12) << tlon << " [DEG]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #12
//--------
void test12_gll2bdS()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=============================================" << std::endl;
   std::cout << "test12_gll2bdS" << std::endl << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "bool gll2bdS(                                                       " << std::endl
             << "   const double slat,         // IN:  source latitude   [DEG]       " << std::endl
             << "   const double slon,         // IN:  source longitude  [DEG]       " << std::endl
             << "   const double tlat,         // IN:  target latitude   [DEG]       " << std::endl
             << "   const double tlon,         // IN:  target longitude  [DEG]       " << std::endl
             << "   double* const brng,        // OUT: bearing           [DEG]       " << std::endl
             << "   double* const dist,        // OUT: distance           [NM]       " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "base::nav::gll2bdS(slat, slon, tlat, tlon, &brng, &dist);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double tlat = 1.0;
   double tlon = 1.0;
   double brng = 0.0;
   double dist = 0.0;
//   const base::EarthModel* pEM = &base::EarthModel::wgs84;

   const double BRNG = 44.9956;
   const double DIST = 84.8507;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "slat = 0;   // source latitude   [DEG]" << std::endl
             << "slon = 0;   // source longitude  [DEG]" << std::endl
             << "tlat = 1;   // target latitude   [DEG]" << std::endl
             << "tlon = 1;   // target longitude   [NM]" << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl
             << "BRNG = " << std::setw(10) << BRNG << "  [DEG]" << std::endl
             << "DIST = " << std::setw(10) << DIST << "   [NM]" << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::gll2bdS(slat, slon, tlat, tlon, &brng, &dist);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl
             << "brng = " << std::setw(10) << brng << "  [DEG]" << std::endl
             << "dist = " << std::setw(10) << dist << "   [NM]" << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl
             << "brng error = " << std::setw(10) << brng - BRNG << "  [DEG]" << std::endl
             << "dist error = " << std::setw(10) << dist - DIST << "   [NM]" << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         // reset function parameters
         slat = 0.0;
         slon = 0.0;
         tlat = 0.0;
         tlon = 0.0;
         brng = 0.0;
         dist = 0.0;

         std::cout << "Enter slat [DEG] : "; std::cin >> slat;
         std::cout << "Enter slon [DEG] : "; std::cin >> slon;
         std::cout << "Enter tlat [DEG] : "; std::cin >> tlat;
         std::cout << "Enter tlon [DEG] : "; std::cin >> tlon;
         std::cout << std::endl;

         base::nav::gll2bdS(slat, slon, tlat, tlon, &brng, &dist);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "brng = " << std::setw(12) << brng << "  [DEG]" << std::endl;
         std::cout << "dist = " << std::setw(12) << dist << "   [NM]"  << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #13
//--------
void test13_glla2bd()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=============================================" << std::endl
             << "test13_glla2bd" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "bool glla2bd( " << std::endl
             << "   const double slat,       // IN:  Source latitude   [DEG]         " << std::endl
             << "   const double slon,       // IN:  Source longitude  [DEG]         " << std::endl
             << "   const double salt,       // IN:  Source altitude     [M]         " << std::endl
             << "   const double tlat,       // IN:  Target latitude   [DEG]         " << std::endl
             << "   const double tlon,       // IN:  Target longitude  [DEG]         " << std::endl
             << "   const double talt,       // IN:  Target altitude     [M]         " << std::endl
             << "   double* const brng,      // OUT: bearing           [DEG]         " << std::endl
             << "   double* const srng,      // OUT: slant range        [NM]         " << std::endl
             << "   double* const dist,      // OUT: ground range       [NM]         " << std::endl
             << "   double* const elev=0,    // OUT: elevation angle   [DEG] (opt)   " << std::endl
             << "   const base::EarthModel* const eem=0)                            " << std::endl
             << "                            // IN:  earth model (Optional)          " << std::endl
             << "                            //      dflt: &base::EarthModel::wgs84 " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "base::nav::glla2bd(slat, slon, salt, tlat, tlon, talt," << std::endl
             << "                    &brng, &srng, &dist, &elev, eem);  " << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double salt = 0.0;
   double tlat = 1.0;
   double tlon = 1.0;
   double talt = 10000.0;
   double brng = 0.0;
   double srng = 0.0;
   double dist = 0.0;
   double elev = 0.0;
   const base::EarthModel* pEM = &base::EarthModel::wgs84;  // default earth model

   const double BRNG = 44.8043;
   const double SRNG = 84.8908;
   const double DIST = 84.7189;
   const double ELEV =  3.6468;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "slat = 0;                         // source latitude   [DEG]" << std::endl
             << "slon = 0;                         // source longitude  [DEG]" << std::endl
             << "salt = 0;                         // source longitude  [M]  " << std::endl
             << "tlat = 1;                         // target latitude   [DEG]" << std::endl
             << "tlon = 1;                         // target longitude  [DEG]" << std::endl
             << "talt = 10000;                     // target longitude  [M]  " << std::endl
             << "eem  = &base::EarthModel::wgs84; // earth model (Optional) " << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl
             << "BRNG = " << std::setw(12) << BRNG << "  [DEG]  // target true bearing" << std::endl
             << "SRNG = " << std::setw(12) << SRNG << "   [NM]  // target slant range " << std::endl
             << "DIST = " << std::setw(12) << DIST << "   [NM]  // target ground range" << std::endl
             << "ELEV = " << std::setw(12) << ELEV << "  [DEG]  // target elevation   " << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::glla2bd(slat, slon, salt, tlat, tlon, talt,
                       &brng, &srng, &dist, &elev);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl
             << "brng = " << std::setw(12) << brng << "  [DEG]  // target true bearing" << std::endl
             << "srng = " << std::setw(12) << srng << "   [NM]  // target slant range " << std::endl
             << "dist = " << std::setw(12) << dist << "   [NM]  // target ground range" << std::endl
             << "elev = " << std::setw(12) << elev << "  [DEG]  // target elevation   " << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl
             << "brng error = " << std::setw(12) << brng - BRNG << std::endl
             << "srng error = " << std::setw(12) << srng - SRNG << std::endl
             << "dist error = " << std::setw(12) << dist - DIST << std::endl
             << "elev error = " << std::setw(12) << elev - ELEV << std::endl
             << std::endl;



   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         slat = 0.0;
         slon = 0.0;
         salt = 0.0;
         tlat = 0.0;
         tlon = 0.0;
         talt = 0.0;
         brng = 0.0;
         srng = 0.0;
         dist = 0.0;
         elev = 0.0;

         std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
         std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
         std::cout << "Enter salt  [M]   : "; std::cin >> salt;
         std::cout << "Enter tlat  [DEG] : "; std::cin >> tlat;
         std::cout << "Enter tlon  [DEG] : "; std::cin >> tlon;
         std::cout << "Enter talt  [M]   : "; std::cin >> talt;
         std::cout << std::endl;

         base::nav::glla2bd(slat, slon, salt, tlat, tlon, talt,
                             &brng, &srng, &dist, &elev, pEM);

         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "brng = " << std::setw(12) << brng << "  [DEG]" << std::endl;
         std::cout << "srng = " << std::setw(12) << srng << "   [NM]" << std::endl;
         std::cout << "dist = " << std::setw(12) << dist << "   [NM]" << std::endl;
         std::cout << "elev = " << std::setw(12) << elev << "  [DEG]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #14
//--------
void test14_glla2bdS()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=============================================" << std::endl
             << "test14_glla2bdS" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "bool glla2bd( " << std::endl
             << "     const double slat,     // IN:  Source latitude   [DEG]       " << std::endl
             << "     const double slon,     // IN:  Source longitude  [DEG]       " << std::endl
             << "     const double salt,     // IN:  Source altitude     [M]       " << std::endl
             << "     const double tlat,     // IN:  Target latitude   [DEG]       " << std::endl
             << "     const double tlon,     // IN:  Target longitude  [DEG]       " << std::endl
             << "     const double talt,     // IN:  Target altitude     [M]       " << std::endl
             << "     double* const brng,    // OUT: bearing           [DEG]       " << std::endl
             << "     double* const srng,    // OUT: slant range        [NM]       " << std::endl
             << "     double* const dist,    // OUT: ground range      [NM]        " << std::endl
             << "     double* const elev=0,  // OUT: elevation angle   [DEG] (opt) " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "base::nav::glla2bdS(slat, slon, salt, tlat, tlon, talt," << std::endl
             << "                     &brng, &srng, &dist, &elev);"    << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double salt = 0.0;
   double tlat = 1.0;
   double tlon = 1.0;
   double talt = 10000.0;
   double brng    = 0.0;
   double srng    = 0.0;
   double dist    = 0.0;
   double elev    = 0.0;

   const double BRNG = 44.9956;
   const double SRNG = 85.0223;
   const double DIST = 84.8507;
   const double ELEV =  3.6412;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "slat = 0;     // source latitude   [DEG]" << std::endl
             << "slon = 0;     // source longitude  [DEG]" << std::endl
             << "salt = 0;     // source altitude   [M]  " << std::endl
             << "tlat = 1;     // target latitude   [DEG]" << std::endl
             << "tlon = 1;     // target longitude  [DEG]" << std::endl
             << "talt = 10000; // target altitude   [M]  " << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl
             << "BRNG = " << std::setw(12) << BRNG << " [DEG]  // true bearing to target" << std::endl
             << "SRNG = " << std::setw(12) << SRNG << "  [NM]  // slant range to target " << std::endl
             << "DIST = " << std::setw(12) << DIST << "  [NM]  // ground range to target" << std::endl
             << "ELEV = " << std::setw(12) << ELEV << " [DEG]  // elevation of target   " << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::glla2bdS(slat, slon, salt, tlat, tlon, talt,
                        &brng, &srng, &dist, &elev);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl
             << "brng = " << std::setw(12) << brng << " [DEG]  // true bearing to target" << std::endl
             << "srng = " << std::setw(12) << srng << "  [NM]  // slant range to target " << std::endl
             << "dist = " << std::setw(12) << dist << "  [NM]  // ground range to target" << std::endl
             << "elev = " << std::setw(12) << elev << " [DEG]  // elevation of target   " << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl
             << "brng error = " << std::setw(12) << brng - BRNG << std::endl
             << "srng error = " << std::setw(12) << srng - SRNG << std::endl
             << "dist error = " << std::setw(12) << dist - DIST << std::endl
             << "elev error = " << std::setw(12) << elev - ELEV << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         slat = 0.0;
         slon = 0.0;
         salt = 0.0;
         tlat = 0.0;
         tlon = 0.0;
         talt = 0.0;
         brng     = 0.0;
         srng     = 0.0;
         dist     = 0.0;
         elev     = 0.0;

         std::cout << "Enter slat  [DEG] : "; std::cin >> slat;
         std::cout << "Enter slon  [DEG] : "; std::cin >> slon;
         std::cout << "Enter salt  [M]   : "; std::cin >> salt;
         std::cout << "Enter tlat  [DEG] : "; std::cin >> tlat;
         std::cout << "Enter tlon  [DEG] : "; std::cin >> tlon;
         std::cout << "Enter talt  [M]   : "; std::cin >> talt;
         std::cout << std::endl;

         base::nav::glla2bdS(slat, slon, salt, tlat, tlon, talt,
                              &brng, &srng, &dist, &elev);

         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "brng = " << std::setw(12) << brng << "  [DEG]" << std::endl;
         std::cout << "srng = " << std::setw(12) << srng << "   [NM]" << std::endl;
         std::cout << "dist = " << std::setw(12) << dist << "   [NM]" << std::endl;
         std::cout << "elev = " << std::setw(12) << elev << "  [DEG]" << std::endl;
         std::cout << std::endl;
      }
   }
}

//--------
// #15
//--------
void test15_vbd2ll()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=============================================" << std::endl
             << "test15_vbd2ll" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "bool gbd2ll( " << std::endl
             << "   const double slat,       // IN:  Source latitude  [DEG] " << std::endl
             << "   const double slon,       // IN:  Source longitude [DEG] " << std::endl
             << "   const double brng,       // IN:  Target bearing   [DEG] " << std::endl
             << "   const double dist,       // IN:  Target distance   [NM] " << std::endl
             << "   double* const tlat,      // OUT: Target latitude  [DEG] " << std::endl
             << "   double* const tlon,      // OUT: Target longitude [DEG] " << std::endl
             << "   const base::EarthModel* const eem=0)                   " << std::endl
             << "                            // IN:  Earth model (dflt: WGS-84) " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "base::nav::vbd2ll(slat, slon, brng, dist, &tlat, &tlon, pEM);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double brg1 = 45.0;
   double dist = 100.0;
   double tlat = 0.0;
   double tlon = 0.0;
//   double brg2 = 0.0;
   const base::EarthModel* pEM = &base::EarthModel::wgs84;

   const double TLAT = 1.18424220;
   const double TLON = 1.17656578;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "slat = 0;    // source latitude   [DEG]" << std::endl
             << "slon = 0;    // source longitude  [DEG]" << std::endl
             << "brng = 45;   // target bearing    [DEG]" << std::endl
             << "dist = 100;  // target distance    [NM]" << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl
             << "  TLAT = " << std::setw(14) << TLAT << "  // target latitude  [DEG]" << std::endl
             << "  TLON = " << std::setw(14) << TLON << "  // target longitude [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::vbd2ll(slat, slon, brng, dist, &tlat, &tlon, pEM);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl
             << "  tlat = " << std::setw(14) << tlat << "  // target latitude  [DEG]" << std::endl
             << "  tlon = " << std::setw(14) << tlon << "  // target longitude [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl
             << "  tlat error = " << std::setw(14) << tlat - TLAT << std::endl
             << "  tlon error = " << std::setw(14) << tlon - TLON << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         slat = 0.0;
         slon = 0.0;
         brg1 = 0.0;
         dist = 0.0;
         tlat = 0.0;
         tlon = 0.0;
//         brg2 = 0.0;

         std::cout << "Enter source latitude   [DEG] : "; std::cin  >> slat;
         std::cout << "Enter source longitude  [DEG] : "; std::cin  >> slon;
         std::cout << "Enter source bearing    [DEG] : "; std::cin  >> brg1;
         std::cout << "Enter source distance    [NM] : "; std::cin  >> dist;
         std::cout << std::endl;

         base::nav::vbd2ll(slat, slon, brg1, dist, &tlat, &tlon, pEM);

         // output results
         std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
         std::cout << "tlat = " << std::setw(14) << tlat << "  [DEG]" << std::endl;
         std::cout << "tlon = " << std::setw(14) << tlon << "  [DEG]" << std::endl;
         std::cout << std::endl;

         // reverse test
         //base::nav::vll2bd(tlat, tlon, slat, slon, &brng, &dist, &brg2, pEM);
         //std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
         //std::cout << "brng = " << std::setw(14) << brng << " [DEG]" << std::endl;
         //std::cout << "dist = " << std::setw(14) << dist << "  [NM]" << std::endl;
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
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "test16_vll2bd" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "bool vll2bd( " << std::endl
             << "     const double slat,         // IN:  Source latitude   [DEG]       " << std::endl
             << "     const double slon,         // IN:  Source longitude  [DEG]       " << std::endl
             << "     const double brng,         // IN:  Target bearing    [DEG]       " << std::endl
             << "     const double dist,         // IN:  Target distance    [NM]       " << std::endl
             << "     double* const tlat,        // OUT: Target latitude   [DEG]       " << std::endl
             << "     double* const tlon,        // OUT: Target longitude  [DEG]       " << std::endl
             << "     double* const brg2=0,      // OUT: final bearing     [DEG] (opt) " << std::endl
             << "     const base::EarthModel* const eem=0)                            " << std::endl
             << "                                // IN: Pointer to an earth model (opt)" << std::endl
             << "                                       (default: WGS-84)              " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "base::nav::vll2bd(slat, slon, tlat, tlon, &brg1, &dist, &brg2, pEM);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double slat = 0.0;
   double slon = 0.0;
   double tlat = 1.0;
   double tlon = 1.0;
   double brg1 = 0.0;
   double dist = 0.0;
   double brg2 = 0.0;
   const base::EarthModel* pEM = &base::EarthModel::wgs84;

   const double BRG1 =   45.18804023;
   const double DIST =   84.71898935;
   const double BRG2 = -134.80323268;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "slat = 0; // source latitude   [DEG]" << std::endl
             << "slon = 0; // source longitude  [DEG]" << std::endl
             << "tlat = 1; // target latitude   [DEG]" << std::endl
             << "tlon = 1; // target longitude   [NM]" << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl
             << "  BRG1 = " << std::setw(14) << BRG1 << "  // bearing  source to target  [DEG]" << std::endl
             << "  DIST = " << std::setw(14) << DIST << "  // distance to target          [NM]" << std::endl
             << "  BRG2 = " << std::setw(14) << BRG2 << "  // bearing  target to source  [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::vll2bd(slat, slon, tlat, tlon, &brg1, &dist, &brg2, pEM);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl
             << "  brg1 = " << std::setw(14) << brg1 << "  // bearing  source to target  [DEG]" << std::endl
             << "  dist = " << std::setw(14) << dist << "  // distance to target          [NM]" << std::endl
             << "  brg2 = " << std::setw(14) << brg2 << "  // bearing  target to source  [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl
             << "  brg1 error = " << std::setw(14) << brg1 - BRG1 << std::endl
             << "  dist error = " << std::setw(14) << dist - DIST << std::endl
             << "  brg2 error = " << std::setw(14) << brg2 - BRG2 << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         slat = 0.0;
         slon = 0.0;
         tlat = 0.0;
         tlon = 0.0;
         brg1 = 0.0;
         dist = 0.0;
         brg2 = 0.0;

         std::cout << "Enter source latitude   [DEG] : "; std::cin  >> slat;
         std::cout << "Enter source longitude  [DEG] : "; std::cin  >> slon;
         std::cout << "Enter target latitude   [DEG] : "; std::cin  >> tlat;
         std::cout << "Enter target longitude  [DEG] : "; std::cin  >> tlon;
         std::cout << std::endl;

         base::nav::vll2bd(slat, slon, tlat, tlon, &brg1, &dist, &brg2, pEM);

         std::cout << std::setprecision(8) << std::setiosflags(std::ios::fixed);
         std::cout << "brg1 = " << std::setw(14) << brg1 << "  [DEG]" << std::endl;
         std::cout << "dist = " << std::setw(14) << dist << "   [NM]"  << std::endl;
         std::cout << "brg2 = " << std::setw(14) << brg2 << "  [DEG]" << std::endl;
         std::cout << std::endl;

         // reverse test
         //base::nav::vbd2ll(tlat, tlon, brg2, dist, &slat, &slon, pEM);
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
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "test17_computeWorldMatrix" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool computeWorldMatrix( " << std::endl
             << "     const double refLat,      // IN:  Reference latitude  [DEG] " << std::endl
             << "     const double refLon,      // IN:  Reference longitude [DEG] " << std::endl
             << "     base::Matrixd* const wm)  // OUT: World Matrix              " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "  base::nav::computeWorldMatrix(rlat, rlon, &wm);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double rlat = 40.0;
   double rlon = 50.0;
   base::Matrixd wm;

   base::Matrixd worldMatrix;
   worldMatrix(0,0) = -0.4132;
   worldMatrix(0,1) = -0.4924;
   worldMatrix(0,2) =  0.7660;
   worldMatrix(1,0) = -0.7660;
   worldMatrix(1,1) =  0.6428;
   worldMatrix(1,2) =  0.0000;
   worldMatrix(2,0) = -0.4924;
   worldMatrix(2,1) = -0.5868;
   worldMatrix(2,2) = -0.6428;


   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "  refLat = 40; // reference latitude   [DEG]" << std::endl
             << "  refLon = 50; // reference longitude  [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results:  " << std::endl
             << "  worldMatrix(0,0) = " << std::setw(12) << worldMatrix(0,0) << std::endl
             << "  worldMatrix(0,1) = " << std::setw(12) << worldMatrix(0,1) << std::endl
             << "  worldMatrix(0,2) = " << std::setw(12) << worldMatrix(0,2) << std::endl
             << "  worldMatrix(1,0) = " << std::setw(12) << worldMatrix(1,0) << std::endl
             << "  worldMatrix(1,1) = " << std::setw(12) << worldMatrix(1,1) << std::endl
             << "  worldMatrix(1,2) = " << std::setw(12) << worldMatrix(1,2) << std::endl
             << "  worldMatrix(2,0) = " << std::setw(12) << worldMatrix(2,0) << std::endl
             << "  worldMatrix(2,1) = " << std::setw(12) << worldMatrix(2,1) << std::endl
             << "  worldMatrix(2,2) = " << std::setw(12) << worldMatrix(2,2) << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::computeWorldMatrix(rlat, rlon, &wm);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl
             << "  wm(0,0) = " << std::setw(12) << wm(0,0) << std::endl
             << "  wm(0,1) = " << std::setw(12) << wm(0,1) << std::endl
             << "  wm(0,2) = " << std::setw(12) << wm(0,2) << std::endl
             << "  wm(1,0) = " << std::setw(12) << wm(1,0) << std::endl
             << "  wm(1,1) = " << std::setw(12) << wm(1,1) << std::endl
             << "  wm(1,2) = " << std::setw(12) << wm(1,2) << std::endl
             << "  wm(2,0) = " << std::setw(12) << wm(2,0) << std::endl
             << "  wm(2,1) = " << std::setw(12) << wm(2,1) << std::endl
             << "  wm(2,2) = " << std::setw(12) << wm(2,2) << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl;
   displayMatrix(wm - worldMatrix);


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         double rlat = 0.0;
         double rlon = 0.0;
         base::Matrixd wm;

         std::cout << "Enter reference latitude   [DEG] : "; std::cin  >> rlat;
         std::cout << "Enter reference longitude  [DEG] : "; std::cin  >> rlon;
         std::cout << std::endl;

         base::nav::computeWorldMatrix(rlat, rlon, &wm);

         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "wm = " << std::endl;
         displayMatrix(wm);
      }
   }
}

//--------
// #18
//--------
void test18_computeEulerAnglesDeg()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "test18_computeEulerAnglesDeg" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype: " << std::endl
             << "  bool computeEulerAnglesDeg( " << std::endl
             << "       const base::Matrixd& rm,     // IN: Rotational matrix            " << std::endl
             << "       base::Vec3d* const anglesD,  // OUT: euler angles [DEG]          " << std::endl
             << "       base::Vec2d* const scPhi=0,  // OUT: Sin/Cos of phi (Optional)   " << std::endl
             << "       base::Vec2d* const scTht=0,  // OUT: Sin/Cos of theta (Optional) " << std::endl
             << "       base::Vec2d* const scPsi=0)  // OUT: Sin/Cos of psi (Optional)   " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "  base::nav::computeEulerAnglesDeg(rm, &angles, &scPhi, &scTht, &scPsi);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double roll  = 0.0;
   double pitch = 0.0;
   double yaw   = 0.0;
   base::Matrixd rm;        // IN: Rotational matrix
   base::Vec3d angles;      // OUT: euler angles (radians)
   base::Vec2d scPhi;       // OUT: Sin/Cos of phi   (Optional)
   base::Vec2d scTht;       // OUT: Sin/Cos of theta (Optional)
   base::Vec2d scPsi;       // OUT: Sin/Cos of psi   (Optional)

   const double ROLL  = 10.0;
   const double PITCH = 20.0;
   const double YAW   = 30.0;

   const double SIN_PHI = std::sin(ROLL  * base::angle::D2RCC);
   const double COS_PHI = std::cos(ROLL  * base::angle::D2RCC);
   const double SIN_THT = std::sin(PITCH * base::angle::D2RCC);
   const double COS_THT = std::cos(PITCH * base::angle::D2RCC);
   const double SIN_PSI = std::sin(YAW   * base::angle::D2RCC);
   const double COS_PSI = std::cos(YAW   * base::angle::D2RCC);

   base::Matrixd testRotationMatrix;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl;

   //-----------------------------------
   // compute rotation matrix from euler angles
   //-----------------------------------
   std::cout << "  Construct a test rotation matrix from the following euler angles: " << std::endl
             << "  const double ROLL  = " << ROLL  << ";" << std::endl
             << "  const double PITCH = " << PITCH << ";" << std::endl
             << "  const double YAW   = " << YAW   << ";" << std::endl
             << std::endl;

   base::nav::computeRotationalMatrixDeg(ROLL, PITCH, YAW, &testRotationMatrix);

   std::cout << "  testRotationMatrix = " << std::endl;
             displayMatrix(testRotationMatrix);

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl
             << "  ROLL      = " << std::setw(12) << ROLL  << std::endl
             << "  PITCH     = " << std::setw(12) << PITCH << std::endl
             << "  YAW       = " << std::setw(12) << YAW   << std::endl
             << "  SIN_PHI   = " << std::setw(12) << SIN_PHI << std::endl
             << "  COS_PHI   = " << std::setw(12) << COS_PHI << std::endl
             << "  SIN_THT   = " << std::setw(12) << SIN_THT << std::endl
             << "  COS_THT   = " << std::setw(12) << COS_THT << std::endl
             << "  SIN_PSI   = " << std::setw(12) << SIN_PSI << std::endl
             << "  COS_PSI   = " << std::setw(12) << COS_PSI << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::computeEulerAnglesDeg(testRotationMatrix, &angles, &scPhi, &scTht, &scPsi);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl
             << "  angles[0] = " << std::setw(12) << angles[0] << std::endl
             << "  angles[1] = " << std::setw(12) << angles[1] << std::endl
             << "  angles[2] = " << std::setw(12) << angles[2] << std::endl
             << "  scPhi[0]  = " << std::setw(12) << scPhi[0] << std::endl
             << "  scPhi[1]  = " << std::setw(12) << scPhi[1] << std::endl
             << "  scTht[0]  = " << std::setw(12) << scTht[0] << std::endl
             << "  scTht[1]  = " << std::setw(12) << scTht[1] << std::endl
             << "  scPsi[0]  = " << std::setw(12) << scPsi[0] << std::endl
             << "  scPsi[1]  = " << std::setw(12) << scPsi[1] << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl
             << "  angles[0] = " << std::setw(12) << angles[0] - ROLL    << std::endl
             << "  angles[1] = " << std::setw(12) << angles[1] - PITCH   << std::endl
             << "  angles[2] = " << std::setw(12) << angles[2] - YAW     << std::endl
             << "  scPhi[0]  = " << std::setw(12) << scPhi[0]  - SIN_PHI << std::endl
             << "  scPhi[1]  = " << std::setw(12) << scPhi[1]  - COS_PHI << std::endl
             << "  scTht[0]  = " << std::setw(12) << scTht[0]  - SIN_THT << std::endl
             << "  scTht[1]  = " << std::setw(12) << scTht[1]  - COS_THT << std::endl
             << "  scPsi[0]  = " << std::setw(12) << scPsi[0]  - SIN_PSI << std::endl
             << "  scPsi[1]  = " << std::setw(12) << scPsi[1]  - COS_PSI << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         // reset inputs
         roll  = 0.0;
         pitch = 0.0;
         yaw   = 0.0;

         std::cout << "Enter roll  angle  [DEG] : "; std::cin  >> roll;
         std::cout << "Enter pitch angle  [DEG] : "; std::cin  >> pitch;
         std::cout << "Enter yaw   angle  [DEG] : "; std::cin  >> yaw;
         std::cout << std::endl;

         std::cout << "Compute rotational matrix from roll, pitch, yaw:" << std::endl
                   << std::endl;

         std::cout << "base::nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl
                   << std::endl;

         base::nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);

         std::cout << "rm = " << std::endl;
         displayMatrix(rm);

         std::cout << "base::nav::computeEulerAnglesDeg(rm, &angles, &scPhi, &scTht, &scPsi);" << std::endl
                   << std::endl;

         base::nav::computeEulerAnglesDeg(rm, &angles, &scPhi, &scTht, &scPsi);

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
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "test19_computeRotationalMatrix" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool computeRotationalMatrix( " << std::endl
             << "       const double phi,            // IN:  roll    [RAD]                 " << std::endl
             << "       const double theta,          // IN:  pitch   [RAD]                 " << std::endl
             << "       const double psi,            // IN:  yaw     [RAD]                 " << std::endl
             << "       base::Matrixd* const rm,     // OUT: Rotational matrix             " << std::endl
             << "       base::Vec2d* const scPhi=0,  // OUT: Sin/Cos of phi   (Optional)   " << std::endl
             << "       base::Vec2d* const scTht=0,  // OUT: Sin/Cos of theta (Optional)   " << std::endl
             << "       base::Vec2d* const scPsi=0)  // OUT: Sin/Cos of psi   (Optional)   " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "  base::nav::computeRotationalMatrix(roll, pitch, yaw, &rm, &scPhi, &scTht, &scPsi);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   // inputs
   double roll  = 0.2;  // [RAD]
   double pitch = 0.4;  // [RAD]
   double yaw   = 0.6;  // [RAD]
   base::Vec3d angles;

   // outputs
   base::Matrixd rm;
   base::Vec2d scPhi;
   base::Vec2d scTht;
   base::Vec2d scPsi;

   const double ROLL    = 0.2;
   const double PITCH   = 0.4;
   const double YAW     = 0.6;

   base::Matrixd testRotMatrix;
   testRotMatrix(0,0) =  0.7602;
   testRotMatrix(0,1) =  0.5201;
   testRotMatrix(0,2) = -0.3894;
   testRotMatrix(1,0) = -0.4895;
   testRotMatrix(1,1) =  0.8526;
   testRotMatrix(1,2) =  0.1830;
   testRotMatrix(2,0) =  0.4272;
   testRotMatrix(2,1) =  0.0515;
   testRotMatrix(2,2) =  0.9027;

   const double SIN_PHI = std::sin(ROLL);
   const double COS_PHI = std::cos(ROLL);
   const double SIN_THT = std::sin(PITCH);
   const double COS_THT = std::cos(PITCH);
   const double SIN_PSI = std::sin(YAW);
   const double COS_PSI = std::cos(YAW);

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "  roll  = " << roll  << "  [RAD]  // roll  ~= 11.4592 [DEG]" << std::endl
             << "  pitch = " << pitch << "  [RAD]  // pitch ~= 22.9183 [DEG]" << std::endl
             << "  yaw   = " << yaw   << "  [RAD]  // yaw   ~= 34.3775 [DEG]" << std::endl
             << std::endl;

   //-----------------------------------

   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl;

   std::cout << "  testRotMatrix = " << std::endl;
   displayMatrix(testRotMatrix);

   std::cout << "  scPhi[0]  = " << std::setw(12) << SIN_PHI << std::endl
             << "  scPhi[1]  = " << std::setw(12) << COS_PHI << std::endl
             << "  scTht[0]  = " << std::setw(12) << SIN_THT << std::endl
             << "  scTht[1]  = " << std::setw(12) << COS_THT << std::endl
             << "  scPsi[0]  = " << std::setw(12) << SIN_PSI << std::endl
             << "  scPsi[1]  = " << std::setw(12) << COS_PSI << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::computeRotationalMatrix(roll, pitch, yaw, &rm, &scPhi, &scTht, &scPsi);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl;

   std::cout << "  rm = " << std::endl;
   displayMatrix(rm);

   std::cout << "  scPhi[0]  = " << std::setw(12) << scPhi[0] << std::endl
             << "  scPhi[1]  = " << std::setw(12) << scPhi[1] << std::endl
             << "  scTht[0]  = " << std::setw(12) << scTht[0] << std::endl
             << "  scTht[1]  = " << std::setw(12) << scTht[1] << std::endl
             << "  scPsi[0]  = " << std::setw(12) << scPsi[0] << std::endl
             << "  scPsi[1]  = " << std::setw(12) << scPsi[1] << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl;

   std::cout << "  rm error = " << std::endl;
   displayMatrix(rm - testRotMatrix);

   std::cout << "  scPhi[0] error = " << std::setw(12) << scPhi[0] - SIN_PHI << std::endl
             << "  scPhi[1] error = " << std::setw(12) << scPhi[1] - COS_PHI << std::endl
             << "  scTht[0] error = " << std::setw(12) << scTht[0] - SIN_THT << std::endl
             << "  scTht[1] error = " << std::setw(12) << scTht[1] - COS_THT << std::endl
             << "  scPsi[0] error = " << std::setw(12) << scPsi[0] - SIN_PSI << std::endl
             << "  scPsi[1] error = " << std::setw(12) << scPsi[1] - COS_PSI << std::endl
             << std::endl;

   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         // reset inputs
         double roll  = 0.0;
         double pitch = 0.0;
         double yaw   = 0.0;

         std::cout << "Enter roll   [RAD] : "; std::cin  >> roll;
         std::cout << "Enter pitch  [RAD] : "; std::cin  >> pitch;
         std::cout << "Enter yaw    [RAD] : "; std::cin  >> yaw;
         std::cout << std::endl;

         std::cout << "Compute rotational matrix from roll, pitch, yaw:" << std::endl;
         std::cout << std::endl;

         std::cout << "base::nav::computeRotationalMatrix(roll, pitch, yaw, &rm);" << std::endl;
         base::nav::computeRotationalMatrix(roll, pitch, yaw, &rm);

         std::cout << "rm = " << std::endl;
         displayMatrix(rm);
      }
   }
}

//--------
// #20
//--------
void test20_computeRotationalMatrix()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "test20_computeRotationalMatrix" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool computeRotationalMatrix( " << std::endl
             << "       const base::Vec3d& angles,   // IN: euler angles (radians)  " << std::endl
             << "       base::Matrixd* const rm,     // OUT: Rotational matrix      " << std::endl
             << "       base::Vec2d* const scPhi=0,  // OUT: Sin/Cos of phi   (Opt) " << std::endl
             << "       base::Vec2d* const scTht=0,  // OUT: Sin/Cos of theta (Opt) " << std::endl
             << "       base::Vec2d* const scPsi=0)  // OUT: Sin/Cos of psi   (Opt) " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "  base::nav::computeRotationalMatrix(angles, &rm, &scPhi, &scTht, &scPsi);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   // inputs
   base::Vec3d angles;
   angles[0] = 0.2;  // [RAD]
   angles[1] = 0.4;  // [RAD]
   angles[2] = 0.6;  // [RAD]

   // outputs
   base::Matrixd rm;
   base::Vec2d scPhi;
   base::Vec2d scTht;
   base::Vec2d scPsi;

   const double ROLL    = 0.2;
   const double PITCH   = 0.4;
   const double YAW     = 0.6;

   base::Matrixd testRotMatrix;
   testRotMatrix(0,0) =  0.7602;
   testRotMatrix(0,1) =  0.5201;
   testRotMatrix(0,2) = -0.3894;
   testRotMatrix(1,0) = -0.4895;
   testRotMatrix(1,1) =  0.8526;
   testRotMatrix(1,2) =  0.1830;
   testRotMatrix(2,0) =  0.4272;
   testRotMatrix(2,1) =  0.0515;
   testRotMatrix(2,2) =  0.9027;

   const double SIN_PHI = std::sin(ROLL);
   const double COS_PHI = std::cos(ROLL);
   const double SIN_THT = std::sin(PITCH);
   const double COS_THT = std::cos(PITCH);
   const double SIN_PSI = std::sin(YAW);
   const double COS_PSI = std::cos(YAW);

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "  angles[0] = " << angles[0] << "  [RAD]  // roll  ~= 11.4592 [DEG]" << std::endl
             << "  angles[1] = " << angles[1] << "  [RAD]  // pitch ~= 22.9183 [DEG]" << std::endl
             << "  angles[2] = " << angles[2] << "  [RAD]  // yaw   ~= 34.3775 [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl;

   std::cout << "  testRotMatrix = " << std::endl;
   displayMatrix(testRotMatrix);

   std::cout << "  scPhi[0]  = " << std::setw(12) << SIN_PHI << std::endl
             << "  scPhi[1]  = " << std::setw(12) << COS_PHI << std::endl
             << "  scTht[0]  = " << std::setw(12) << SIN_THT << std::endl
             << "  scTht[1]  = " << std::setw(12) << COS_THT << std::endl
             << "  scPsi[0]  = " << std::setw(12) << SIN_PSI << std::endl
             << "  scPsi[1]  = " << std::setw(12) << COS_PSI << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::computeRotationalMatrix(angles, &rm, &scPhi, &scTht, &scPsi);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl;

   std::cout << "  rm = " << std::endl;
   displayMatrix(rm);

   std::cout << "  scPhi[0]  = " << std::setw(12) << scPhi[0] << std::endl
             << "  scPhi[1]  = " << std::setw(12) << scPhi[1] << std::endl
             << "  scTht[0]  = " << std::setw(12) << scTht[0] << std::endl
             << "  scTht[1]  = " << std::setw(12) << scTht[1] << std::endl
             << "  scPsi[0]  = " << std::setw(12) << scPsi[0] << std::endl
             << "  scPsi[1]  = " << std::setw(12) << scPsi[1] << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl;

   std::cout << "  rm error = " << std::endl;
   displayMatrix(rm - testRotMatrix);

   std::cout << "  scPhi[0] error = " << std::setw(12) << scPhi[0] - SIN_PHI << std::endl
             << "  scPhi[1] error = " << std::setw(12) << scPhi[1] - COS_PHI << std::endl
             << "  scTht[0] error = " << std::setw(12) << scTht[0] - SIN_THT << std::endl
             << "  scTht[1] error = " << std::setw(12) << scTht[1] - COS_THT << std::endl
             << "  scPsi[0] error = " << std::setw(12) << scPsi[0] - SIN_PSI << std::endl
             << "  scPsi[1] error = " << std::setw(12) << scPsi[1] - COS_PSI << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         // inputs
         double roll  = 0.0;
         double pitch = 0.0;
         double yaw   = 0.0;
         base::Vec3d angles;

         // outputs
         base::Matrixd rm;
         base::Vec2d scPhi;
         base::Vec2d scTht;
         base::Vec2d scPsi;

         std::cout << "Enter roll  angle  [RAD] : "; std::cin  >> roll;
         std::cout << "Enter pitch angle  [RAD] : "; std::cin  >> pitch;
         std::cout << "Enter yaw   angle  [RAD] : "; std::cin  >> yaw;
         std::cout << std::endl;

         std::cout << "rotational matrix from roll, pitch, yaw:" << std::endl;
         std::cout << "base::nav::computeRotationalMatrix(roll, pitch, yaw, &rm);" << std::endl;
         base::nav::computeRotationalMatrix(roll, pitch, yaw, &rm);
         std::cout << "rm = " << std::endl;
         displayMatrix(rm);

         angles[0] = roll;
         angles[1] = pitch;
         angles[2] = yaw;

         std::cout << "Define angles vector:" << std::endl;
         std::cout << "angles[0] = roll;"  << std::endl;
         std::cout << "angles[1] = pitch;" << std::endl;
         std::cout << "angles[2] = yaw;"   << std::endl;
         std::cout << std::endl;

         std::cout << "rotational matrix from angles vector:" << std::endl;
         std::cout << "base::nav::computeRotationalMatrix(angles, &rm, &scPhi, &scTht, &scPsi);" << std::endl;
         base::nav::computeRotationalMatrix(angles, &rm, &scPhi, &scTht, &scPsi);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "rm = " << std::endl;
         displayMatrix(rm);

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
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "test21_computeRotationalMatrixDeg" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool computeRotationalMatrixDeg( " << std::endl
             << "       const double phi,            // IN:  roll    [DEG]                 " << std::endl
             << "       const double theta,          // IN:  pitch   [DEG]                 " << std::endl
             << "       const double psi,            // IN:  yaw     [DEG]                 " << std::endl
             << "       base::Matrixd* const rm,     // OUT: Rotational matrix             " << std::endl
             << "       base::Vec2d* const scPhi=0,  // OUT: Sin/Cos of phi   (Optional)   " << std::endl
             << "       base::Vec2d* const scTht=0,  // OUT: Sin/Cos of theta (Optional)   " << std::endl
             << "       base::Vec2d* const scPsi=0)  // OUT: Sin/Cos of psi   (Optional)   " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "  base::nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm, &scPhi, &scTht, &scPsi);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   // inputs
   double roll  = 10.0;  // [RAD]
   double pitch = 20.0;  // [RAD]
   double yaw   = 30.0;  // [RAD]
   base::Vec3d angles;

   // outputs
   base::Matrixd rm;
   base::Vec2d scPhi;
   base::Vec2d scTht;
   base::Vec2d scPsi;

   const double ROLL    = 10.0;
   const double PITCH   = 20.0;
   const double YAW     = 30.0;

   base::Matrixd testRotMatrix;

   testRotMatrix(0,0) =  0.8138;
   testRotMatrix(0,1) =  0.4698;
   testRotMatrix(0,2) = -0.3420;
   testRotMatrix(1,0) = -0.4410;
   testRotMatrix(1,1) =  0.8826;
   testRotMatrix(1,2) =  0.1632;
   testRotMatrix(2,0) =  0.3785;
   testRotMatrix(2,1) =  0.0180;
   testRotMatrix(2,2) =  0.9254;

   const double SIN_PHI = std::sin(ROLL  * base::angle::D2RCC);
   const double COS_PHI = std::cos(ROLL  * base::angle::D2RCC);
   const double SIN_THT = std::sin(PITCH * base::angle::D2RCC);
   const double COS_THT = std::cos(PITCH * base::angle::D2RCC);
   const double SIN_PSI = std::sin(YAW   * base::angle::D2RCC);
   const double COS_PSI = std::cos(YAW   * base::angle::D2RCC);

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "  roll  = " << roll  << "  [DEG]" << std::endl
             << "  pitch = " << pitch << "  [DEG]" << std::endl
             << "  yaw   = " << yaw   << "  [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl;

   std::cout << "  testRotMatrix = " << std::endl;
   displayMatrix(testRotMatrix);

   std::cout << "  scPhi[0]  = " << std::setw(12) << SIN_PHI << std::endl
             << "  scPhi[1]  = " << std::setw(12) << COS_PHI << std::endl
             << "  scTht[0]  = " << std::setw(12) << SIN_THT << std::endl
             << "  scTht[1]  = " << std::setw(12) << COS_THT << std::endl
             << "  scPsi[0]  = " << std::setw(12) << SIN_PSI << std::endl
             << "  scPsi[1]  = " << std::setw(12) << COS_PSI << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm, &scPhi, &scTht, &scPsi);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl;

   std::cout << "  rm = " << std::endl;
   displayMatrix(rm);

   std::cout << "  scPhi[0]  = " << std::setw(12) << scPhi[0] << std::endl
             << "  scPhi[1]  = " << std::setw(12) << scPhi[1] << std::endl
             << "  scTht[0]  = " << std::setw(12) << scTht[0] << std::endl
             << "  scTht[1]  = " << std::setw(12) << scTht[1] << std::endl
             << "  scPsi[0]  = " << std::setw(12) << scPsi[0] << std::endl
             << "  scPsi[1]  = " << std::setw(12) << scPsi[1] << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl;

   std::cout << "  rm error = " << std::endl;
   displayMatrix(rm - testRotMatrix);

   std::cout << "  scPhi[0] error = " << std::setw(12) << scPhi[0] - SIN_PHI << std::endl
             << "  scPhi[1] error = " << std::setw(12) << scPhi[1] - COS_PHI << std::endl
             << "  scTht[0] error = " << std::setw(12) << scTht[0] - SIN_THT << std::endl
             << "  scTht[1] error = " << std::setw(12) << scTht[1] - COS_THT << std::endl
             << "  scPsi[0] error = " << std::setw(12) << scPsi[0] - SIN_PSI << std::endl
             << "  scPsi[1] error = " << std::setw(12) << scPsi[1] - COS_PSI << std::endl
             << std::endl;

   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         // reset inputs
         double roll  = 0.0;
         double pitch = 0.0;
         double yaw   = 0.0;

         std::cout << "Enter roll   [DEG] : "; std::cin  >> roll;
         std::cout << "Enter pitch  [DEG] : "; std::cin  >> pitch;
         std::cout << "Enter yaw    [DEG] : "; std::cin  >> yaw;
         std::cout << std::endl;

         std::cout << "Compute rotational matrix from roll, pitch, yaw:" << std::endl;
         std::cout << std::endl;

         std::cout << "base::nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);" << std::endl;
         base::nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm, &scPhi, &scTht, &scPsi);

         std::cout << "rm = " << std::endl;
         displayMatrix(rm);

         std::cout << "  scPhi[0]  = " << std::setw(12) << scPhi[0] << std::endl
                   << "  scPhi[1]  = " << std::setw(12) << scPhi[1] << std::endl
                   << "  scTht[0]  = " << std::setw(12) << scTht[0] << std::endl
                   << "  scTht[1]  = " << std::setw(12) << scTht[1] << std::endl
                   << "  scPsi[0]  = " << std::setw(12) << scPsi[0] << std::endl
                   << "  scPsi[1]  = " << std::setw(12) << scPsi[1] << std::endl
                   << std::endl;
      }
   }
}

//--------
// #22
//--------
void test22_computeRotationalMatrixDeg()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "test22_computeRotationalMatrixDeg" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool computeRotationalMatrixDeg( " << std::endl
             << "       const base::Vec3d& angles,   // IN: euler angles  [DEG]     " << std::endl
             << "       base::Matrixd* const rm,     // OUT: Rotational matrix      " << std::endl
             << "       base::Vec2d* const scPhi=0,  // OUT: Sin/Cos of phi   (Opt) " << std::endl
             << "       base::Vec2d* const scTht=0,  // OUT: Sin/Cos of theta (Opt) " << std::endl
             << "       base::Vec2d* const scPsi=0)  // OUT: Sin/Cos of psi   (Opt) " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "  base::nav::computeRotationalMatrixDeg(angles, &rm, &scPhi, &scTht, &scPsi);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   const double ROLL    = 10.0;
   const double PITCH   = 20.0;
   const double YAW     = 30.0;

   const double SIN_PHI = std::sin(ROLL  * base::angle::D2RCC);
   const double COS_PHI = std::cos(ROLL  * base::angle::D2RCC);
   const double SIN_THT = std::sin(PITCH * base::angle::D2RCC);
   const double COS_THT = std::cos(PITCH * base::angle::D2RCC);
   const double SIN_PSI = std::sin(YAW   * base::angle::D2RCC);
   const double COS_PSI = std::cos(YAW   * base::angle::D2RCC);

   // inputs
   base::Vec3d angles;
   angles[0] = 10.0;  // [DEG]
   angles[1] = 20.0;  // [DEG]
   angles[2] = 30.0;  // [DEG]

   // outputs
   base::Matrixd rm;
   base::Vec2d scPhi;
   base::Vec2d scTht;
   base::Vec2d scPsi;

   base::Matrixd testRotMatrix;
   testRotMatrix(0,0) =  0.8138;
   testRotMatrix(0,1) =  0.4698;
   testRotMatrix(0,2) = -0.3420;
   testRotMatrix(1,0) = -0.4410;
   testRotMatrix(1,1) =  0.8826;
   testRotMatrix(1,2) =  0.1632;
   testRotMatrix(2,0) =  0.3785;
   testRotMatrix(2,1) =  0.0180;
   testRotMatrix(2,2) =  0.9254;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "  angles[0] = " << angles[0] << "  [DEG]" << std::endl
             << "  angles[1] = " << angles[1] << "  [DEG]" << std::endl
             << "  angles[2] = " << angles[2] << "  [DEG]" << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl;

   std::cout << "  testRotMatrix = " << std::endl;
   displayMatrix(testRotMatrix);

   std::cout << "  scPhi[0]  = " << std::setw(12) << SIN_PHI << std::endl
             << "  scPhi[1]  = " << std::setw(12) << COS_PHI << std::endl
             << "  scTht[0]  = " << std::setw(12) << SIN_THT << std::endl
             << "  scTht[1]  = " << std::setw(12) << COS_THT << std::endl
             << "  scPsi[0]  = " << std::setw(12) << SIN_PSI << std::endl
             << "  scPsi[1]  = " << std::setw(12) << COS_PSI << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::computeRotationalMatrixDeg(angles, &rm, &scPhi, &scTht, &scPsi);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl;

   std::cout << "  rm = " << std::endl;
   displayMatrix(rm);

   std::cout << "  scPhi[0]  = " << std::setw(12) << scPhi[0] << std::endl
             << "  scPhi[1]  = " << std::setw(12) << scPhi[1] << std::endl
             << "  scTht[0]  = " << std::setw(12) << scTht[0] << std::endl
             << "  scTht[1]  = " << std::setw(12) << scTht[1] << std::endl
             << "  scPsi[0]  = " << std::setw(12) << scPsi[0] << std::endl
             << "  scPsi[1]  = " << std::setw(12) << scPsi[1] << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl;

   std::cout << "  rm error = " << std::endl;
   displayMatrix(rm - testRotMatrix);

   std::cout << "  scPhi[0] error = " << std::setw(12) << scPhi[0] - SIN_PHI << std::endl
             << "  scPhi[1] error = " << std::setw(12) << scPhi[1] - COS_PHI << std::endl
             << "  scTht[0] error = " << std::setw(12) << scTht[0] - SIN_THT << std::endl
             << "  scTht[1] error = " << std::setw(12) << scTht[1] - COS_THT << std::endl
             << "  scPsi[0] error = " << std::setw(12) << scPsi[0] - SIN_PSI << std::endl
             << "  scPsi[1] error = " << std::setw(12) << scPsi[1] - COS_PSI << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         // inputs
         double roll  = 0.0;
         double pitch = 0.0;
         double yaw   = 0.0;
         base::Vec3d angles;

         // outputs
         base::Matrixd rm;
         base::Vec2d scPhi;
         base::Vec2d scTht;
         base::Vec2d scPsi;

         std::cout << "Enter roll  angle  [DEG] : "; std::cin  >> roll;
         std::cout << "Enter pitch angle  [DEG] : "; std::cin  >> pitch;
         std::cout << "Enter yaw   angle  [DEG] : "; std::cin  >> yaw;
         std::cout << std::endl;

         angles[0] = roll;
         angles[1] = pitch;
         angles[2] = yaw;

         std::cout << "rotational matrix from roll, pitch, yaw:" << std::endl;
         std::cout << "base::nav::computeRotationalMatrixDeg(angles, &rm, &scPhi, &scTht, &scPsi);" << std::endl;
         base::nav::computeRotationalMatrixDeg(roll, pitch, yaw, &rm);
         std::cout << "rm = " << std::endl;
         displayMatrix(rm);

         angles[0] = roll;
         angles[1] = pitch;
         angles[2] = yaw;

         std::cout << "Define angles vector:" << std::endl;
         std::cout << "angles[0] = roll;"  << std::endl;
         std::cout << "angles[1] = pitch;" << std::endl;
         std::cout << "angles[2] = yaw;"   << std::endl;
         std::cout << std::endl;

         std::cout << "rotational matrix from angles vector:" << std::endl;
         std::cout << "base::nav::computeRotationalMatrixDeg(angles, &rm, &scPhi, &scTht, &scPsi);" << std::endl;
         base::nav::computeRotationalMatrixDeg(angles, &rm, &scPhi, &scTht, &scPsi);

         // output results
         std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
         std::cout << "rm = " << std::endl;
         displayMatrix(rm);

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
void test23_convertPosVec2llE()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=============================================" << std::endl
             << "test23_convertPosVec2llE" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool convertPosVec2llE( " << std::endl
             << "       const double slat,       // IN: source latitude     [DEG] " << std::endl
             << "       const double slon,       // IN: source longitude    [DEG] " << std::endl
             << "       const base::Vec3d& pos,  // IN: NED position vector   [M] " << std::endl
             << "       double* const lat,       // OUT: Latitude           [DEG] " << std::endl
             << "       double* const lon,       // OUT: Longitude          [DEG] " << std::endl
             << "       double* const alt)       // OUT: Altitude             [M] " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "  base::nav::convertPosVec2llE(rlat, rlon, pos, &lat, &lon, &alt);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double rlat = 40.0;  // IN: source (reference) latitude  [DEG]
   double rlon = 50.0;  // IN: source (reference) longitude [DEG]

   base::Vec3d pos;     // IN: NED position vector from ref point (meters)
   pos[0] = 1000.0;     //     North  [M]
   pos[1] = 2000.0;     //     East   [M]
   pos[2] = 3000.0;     //     Down   [M]

   double lat = 0.0;    // OUT: Latitude  [DEG]
   double lon = 0.0;    // OUT: Longitude [DEG]
   double alt = 0.0;    // OUT: Altitude    [M]

   const double LAT =    40.0090;
   const double LON =    50.0234;
   const double ALT = -3000.0000;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs:        " << std::endl
             << "  rlat = 40;   [DEG]" << std::endl
             << "  rlon = 50;   [DEG]" << std::endl
             << "  x    = 1000    [M]" << std::endl
             << "  y    = 2000    [M]" << std::endl
             << "  z    = 3000    [M]" << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl
             << "  lat = " << std::setw(12) << LAT << "  [DEG]" << std::endl
             << "  lon = " << std::setw(12) << LON << "  [DEG]" << std::endl
             << "  alt = " << std::setw(12) << ALT << "    [M]" << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::convertPosVec2llE(rlat, rlon, pos, &lat, &lon, &alt);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl
             << "  lat = " << std::setw(12) << lat << "  [DEG]" << std::endl
             << "  lon = " << std::setw(12) << lon << "  [DEG]" << std::endl
             << "  alt = " << std::setw(12) << alt << "    [M]" << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl
             << "  lat error = " << std::setw(12) << lat - LAT << std::endl
             << "  lon error = " << std::setw(12) << lon - LON << std::endl
             << "  alt error = " << std::setw(12) << alt - ALT << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         // reset inputs
         rlat = 0.0;  // IN: source (reference) latitude  [DEG]
         rlon = 0.0;  // IN: source (reference) longitude [DEG]

         lat = 0.0;   // OUT: Latitude  [DEG]
         lon = 0.0;   // OUT: Longitude [DEG]
         alt = 0.0;   // OUT: Altitude  [M]

         std::cout << "Enter reference latitude   [DEG] : "; std::cin >> rlat;
         std::cout << "Enter reference longitude  [DEG] : "; std::cin >> rlon;
         std::cout << std::endl;

         std::cout << "Enter x  [M] : "; std::cin >> pos[0];
         std::cout << "Enter y  [M] : "; std::cin >> pos[1];
         std::cout << "Enter z  [M] : "; std::cin >> pos[2];
         std::cout << std::endl;

         base::nav::convertPosVec2llE(rlat, rlon, pos, &lat, &lon, &alt);

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
void test24_convertLL2PosVecE()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=============================================" << std::endl
             << "test24_convertLL2PosVecE" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototype:" << std::endl
             << "  bool convertLL2PosVecE( " << std::endl
             << "       const double rlat,       // IN: Reference latitude   [DEG]   " << std::endl
             << "       const double rlon,       // IN: Reference longitude  [DEG]   " << std::endl
             << "       const double tlat,       // IN: Target latitude      [DEG]   " << std::endl
             << "       const double tlon,       // IN: Target longitude     [DEG]   " << std::endl
             << "       const double talt,       // IN: Target altitude      [M]     " << std::endl
             << "       base::Vec3d* const pos)  // OUT: NED position vector [M,M,M] " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "  base::nav::convertLL2PosVecE(rlat, rlon, tlat, tlon, talt, &pos);" << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double rlat =   40.0;  // IN: Reference latitude    [DEG]
   double rlon =   50.0;  // IN: Reference longitude   [DEG]

   double tlat =   41.0;  // IN: Target latitude       [DEG]
   double tlon =   51.0;  // IN: Target longitude      [DEG]
   double talt = 5000.0;  // IN: Target altitude       [M]

   base::Vec3d pos;       // OUT: NED position vector  [M,M,M]

   //const double NORTH = 111120.0000;
   //const double EAST  =  85122.8585;
   //const double DOWN  =  -5000.0000;
   const double NORTH = 111034.6326;
   const double EAST  =  85393.8570;
   const double DOWN  =  -5000.0000;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "  rlat = " << std::setw(12) << rlat << "  [DEG]" << std::endl
             << "  rlon = " << std::setw(12) << rlon << "  [DEG]" << std::endl
             << std::endl
             << "  tlat = " << std::setw(12) << tlat << "  [M]" << std::endl
             << "  tlon = " << std::setw(12) << tlon << "  [M]" << std::endl
             << "  talt = " << std::setw(12) << talt << "  [M]" << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl
             << "  pos[0] = " << std::setw(12) << NORTH << " [M]  north" << std::endl
             << "  pos[1] = " << std::setw(12) << EAST  << " [M]  east " << std::endl
             << "  pos[2] = " << std::setw(12) << DOWN  << " [M]  down " << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::convertLL2PosVecE(rlat, rlon, tlat, tlon, talt, &pos);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "Actual Results: " << std::endl
             << "  pos[0] = " << std::setw(12) << pos[0] << " [M]  north" << std::endl
             << "  pos[1] = " << std::setw(12) << pos[1] << " [M]  east " << std::endl
             << "  pos[2] = " << std::setw(12) << pos[2] << " [M]  down " << std::endl
             << std::endl;

   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "Errors: " << std::endl
             << "  pos[0] error = " << std::setw(12) << pos[0] - NORTH << std::endl
             << "  pos[1] error = " << std::setw(12) << pos[1] - EAST  << std::endl
             << "  pos[2] error = " << std::setw(12) << pos[2] - DOWN  << std::endl
             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         // reset inputs
         rlat = 0.0;
         rlon = 0.0;
         tlat = 0.0;
         tlon = 0.0;
         talt = 0.0;

         std::cout << "Enter reference latitude   [DEG] : "; std::cin >> rlat;
         std::cout << "Enter reference longitude  [DEG] : "; std::cin >> rlon;
         std::cout << std::endl;

         std::cout << "Enter target latitude   [M] : "; std::cin >> tlat;
         std::cout << "Enter target longitude  [M] : "; std::cin >> tlon;
         std::cout << "Enter target altitude   [M] : "; std::cin >> talt;
         std::cout << std::endl;

         base::nav::convertLL2PosVecE(rlat, rlon, tlat, tlon, talt, &pos);

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
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------
   std::cout << "=====================================================" << std::endl
             << "test25_convertEcef2Geod" << std::endl
             << std::endl;

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------                        " << std::endl
             << "Nav Function Prototype: Convert ECEF (XYZ) to Geodetic (LLA)                 " << std::endl
             << "-----------------------------------------------------                        " << std::endl
             << "  Using type double single variables                                         " << std::endl
             << "    bool convertEcef2Geod(                                                   " << std::endl
             << "         const double x,                // IN:  ECEF X component    [M]      " << std::endl
             << "         const double y,                // IN:  ECEF Y component    [M]      " << std::endl
             << "         const double z,                // IN:  ECEF Z component    [M]      " << std::endl
             << "         double* const plat,            // OUT: Geodetic latitude   [DEG]    " << std::endl
             << "         double* const plon,            // OUT: Geodetic longitude  [DEG]    " << std::endl
             << "         double* const palt,            // OUT: Geodetic altitude   [DEG]    " << std::endl
             << "         const EarthModel* const em=0); // IN:  Pointer to an optional       " << std::endl
             << "                                                earth model (dflt: WGS-84)   " << std::endl
             << "                                                                             " << std::endl
             << "  Using base::Vec3d vectors                                                  " << std::endl
             << "    bool convertEcef2Geod(                                                   " << std::endl
             << "         const base::Vec3d& xyz,         // IN:  ECEF [IX IY IZ]             " << std::endl
             << "         base::Vec3d* const plla,        // OUT: Geodetic [ILAT ILON IALT]   " << std::endl
             << "         const EarthModel* const em=0); // IN:  Pointer to an optional       " << std::endl
             << "                                                earth model (dflt: WGS-84)   " << std::endl
             << "                                                                             " << std::endl
             << "  Using array vectors                                                        " << std::endl
             << "    bool convertEcef2Geod(                                                   " << std::endl
             << "         const double xyz[3],           // IN:  ECEF [IX IY IZ]              " << std::endl
             << "         double lla[3],                 // OUT: Geodetic [ILAT ILON IALT]    " << std::endl
             << "         const EarthModel* const em=0); // IN:  Pointer to an optional       " << std::endl
             << "                                                earth model (dflt: WGS-84)   " << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl
             << "  base::nav::convertEcef2Geod(x, y, z, &lat, &lon, &alt, pEM); " << std::endl
             << "  base::nav::convertEcef2Geod(xyz, &lla, pEM);                 " << std::endl
             << "  base::nav::convertEcef2Geod(xyz, lla, pEM);                  " << std::endl
             << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double x {4000000.0};
   double y {4000000.0};
   double z {4000000.0};
   double lat {};
   double lon {};
   double alt {};

   base::Vec3d xyz(x, y, z);
   base::Vec3d lla;

   double XYZ[3] {x, y, z};
   double LLA[3] {};

   //base::Vec3d result(35.4314, 45.0000, 557215.8470);  // expected result (x, y, z)
   const double LAT {35.4314};
   const double LON {45.0000};
   const double ALT {557215.8470};

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Test Inputs: " << std::endl
             << "  x = xyz[0] = XYZ[0] = " << x << "  // [M]" << std::endl
             << "  y = xyz[1] = XYZ[1] = " << y << "  // [M]" << std::endl
             << "  z = xyz[2] = XYZ[2] = " << z << "  // [M]" << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Expected Results: " << std::endl
             << "  lat = lla[0] = LLA[0] = " << std::setw(12) << LAT << "  // [DEG]" << std::endl
             << "  lon = lla[0] = LLA[0] = " << std::setw(12) << LON << "  // [DEG]" << std::endl
             << "  alt = lla[0] = LLA[0] = " << std::setw(12) << ALT << "  // [M]  " << std::endl
             << std::endl;

   //-----------------------------------
   // compute actual results
   //-----------------------------------
   base::nav::convertEcef2Geod(x, y, z, &lat, &lon, &alt, pEM);
   base::nav::convertEcef2Geod(xyz, &lla, pEM);
   base::nav::convertEcef2Geod(XYZ, LLA, pEM);

   //-----------------------------------
   // show actual results
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Actual Results: " << std::endl
             << "  lat    = " << std::setw(12) << lat    << std::endl
             << "  lon    = " << std::setw(12) << lon    << std::endl
             << "  alt    = " << std::setw(12) << alt    << std::endl
             << std::endl
             << "  lla[0] = " << std::setw(12) << lla[0] << std::endl
             << "  lla[1] = " << std::setw(12) << lla[1] << std::endl
             << "  lla[2] = " << std::setw(12) << lla[2] << std::endl
             << std::endl
             << "  LLA[0] = " << std::setw(12) << LLA[0] << std::endl
             << "  LLA[1] = " << std::setw(12) << LLA[1] << std::endl
             << "  LLA[2] = " << std::setw(12) << LLA[2] << std::endl
             << std::endl;


   //-----------------------------------
   // show errors between actual and expected results
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Errors: " << std::endl
             << "  lat    error = " << std::setw(12) << (lat - LAT)    << std::endl
             << "  lon    error = " << std::setw(12) << (lon - LON)    << std::endl
             << "  alt    error = " << std::setw(12) << (alt - ALT)    << std::endl
             << std::endl
             << "  lla[0] error = " << std::setw(12) << (lla[0] - LAT) << std::endl
             << "  lla[1] error = " << std::setw(12) << (lla[1] - LON) << std::endl
             << "  lla[2] error = " << std::setw(12) << (lla[2] - ALT) << std::endl
             << std::endl
             << "  LLA[0] error = " << std::setw(12) << (LLA[0] - LAT) << std::endl
             << "  LLA[1] error = " << std::setw(12) << (LLA[1] - LON) << std::endl
             << "  LLA[2] error = " << std::setw(12) << (LLA[2] - ALT) << std::endl
             << std::endl;

   //std::cout << "----------------------------------------------------------------------" << std::endl
   //          << "Form 1:" << std::endl
   //          << "base::nav::convertEcef2Geod(x, y, z, &lat, &lon, &alt, pEM);" << std::endl
   //          << std::endl;

   //
   //std::cout << "----------------------------------------------------------------------" << std::endl
   //          << "Form 2:" << std::endl
   //          << "base::Vec3d xyz;" << std::endl
   //          << "base::Vec3d lla;" << std::endl
   //          << "base::nav::convertEcef2Geod(xyz, &lla, pEM);" << std::endl
   //          << std::endl;

   //
   //   std::cout << "Results:" << std::endl
   //
   //std::cout << "----------------------------------------------------------------------" << std::endl
   //          << "Form 3:" << std::endl << std::endl
   //          << "double XYZ[3];" << std::endl
   //          << "double LLA[3];" << std::endl
   //          << "base::nav::convertEcef2Geod(XYZ, LLA, pEM);" << std::endl
   //          << std::endl;

   //
   //   std::cout << "Results:" << std::endl
   //             << std::endl;


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         // inputs
         double lat = 0.0;
         double lon = 0.0;
         double alt = 0.0;
         base::Vec3d lla;
         double LLA[3];
         const base::EarthModel* pEM = &base::EarthModel::wgs84;

         // outputs
         double x = 0.0;
         double y = 0.0;
         double z = 0.0;
         base::Vec3d xyz;
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

         base::nav::convertEcef2Geod(x, y, z, &lat, &lon, &alt, pEM);

         std::cout << "*** double variables: lat,lon,alt => x,y,z ***" << std::endl
                   << "x      = " << std::setw(12) << x << " [M]" << std::endl
                   << "y      = " << std::setw(12) << y << " [M]" << std::endl
                   << "z      = " << std::setw(12) << z << " [M]" << std::endl
                   << std::endl;

         base::nav::convertEcef2Geod(xyz, &lla, pEM);

         // output results
         std::cout << "*** base::vec3d vector: lla => xyz ***" << std::endl
                   << "xyz[0] = " << std::setw(12) << xyz[0] << " [M]" << std::endl
                   << "xyz[1] = " << std::setw(12) << xyz[1] << " [M]" << std::endl
                   << "xyz[2] = " << std::setw(12) << xyz[2] << " [M]" << std::endl
                   << std::endl;

         base::nav::convertEcef2Geod(XYZ, LLA, pEM);

         std::cout << "*** double array: LLA => XYZ ***" << std::endl
                   << "XYZ[0] = " << std::setw(12) << XYZ[0] << " [M]" << std::endl
                   << "XYZ[1] = " << std::setw(12) << XYZ[1] << " [M]" << std::endl
                   << "XYZ[2] = " << std::setw(12) << XYZ[2] << " [M]" << std::endl
                   << std::endl;
      }
   }
}


//--------
// #26
//--------
void test26_convertGeod2Ecef()
{
   //---------------------------------------------------------------------------
   // introduction
   //---------------------------------------------------------------------------

   //-----------------------------------
   // function prototype
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Prototypes:" << std::endl
             << std::endl
             << "  // Form 1: Using type double variables" << std::endl
             << "  bool convertGeod2Ecef("                 << std::endl
             << "       const double lat,                    // IN: Geodetic latitude   [DEG]"   << std::endl
             << "       const double lon,                    // IN: Geodetic longitude  [DEG]"   << std::endl
             << "       const double alt,                    // IN: Geodetic altitude   [M]"     << std::endl
             << "       double* const pX,                    // OUT: ECEF X component   [M]"     << std::endl
             << "       double* const pY,                    // OUT: ECEF Y component   [M]"     << std::endl
             << "       double* const pZ,                    // OUT: ECEF Z component   [M]"     << std::endl
             << "       const EarthModel* const em=nullptr); // IN: Pointer to an optional earth model (default: WGS-84)" << std::endl
             << std::endl
             << "  // Form 2: Using base::Vec3d vectors" << std::endl
             << "  bool convertGeod2Ecef("               << std::endl
             << "       const base::Vec3d& lla,              // IN: Geodetic [ ILAT ILON IALT ]" << std::endl
             << "       base::Vec3d* const ecef,             // OUT: ECEF [ IX IY IZ ]"          << std::endl
             << "       const EarthModel* const em=nullptr); // IN: Pointer to an optional earth model (default: WGS-84)" << std::endl
             << std::endl
             << "  // Form 3: Using array vectors" << std::endl
             << "  bool convertGeod2Ecef(" << std::endl
             << "       const double lla[3],                 // IN: Geodetic [ ILAT ILON IALT ]" << std::endl
             << "       double ecef[3],                      // OUT: ECEF [ IX IY IZ ]"          << std::endl
             << "       const EarthModel* const em=nullptr); // IN: Pointer to an optional earth model (default: WGS-84)" << std::endl
             << std::endl;

   //-----------------------------------
   // function usage
   //-----------------------------------
   std::cout << "-----------------------------------------------------" << std::endl
             << "Nav Function Usage:" << std::endl;

   //-----------------------------------
   // declare function parameters
   //-----------------------------------
   double lat = 40.0;
   double lon = 50.0;
   double alt =  0.0;

   base::Vec3d result;  // expected result (x, y, z)
   result[0] = 3144971.8231;
   result[1] = 3748031.4688;
   result[2] = 4077985.5722;

   //-----------------------------------
   // set output formats
   //-----------------------------------
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);

   //-----------------------------------
   // show test inputs
   //-----------------------------------
   std::cout << "=============================================" << std::endl
             << "test26_convertGeod2Ecef" << std::endl
             << std::endl
             << "Test inputs:" << std::endl
             << "  lat = " << std::setw(12) << lat << ";  // [DEG]" << std::endl
             << "  lon = " << std::setw(12) << lon << ";  // [DEG]" << std::endl
             << "  alt = " << std::setw(12) << alt << ";  // [M]  " << std::endl
             << std::endl;

   //-----------------------------------
   // show expected results
   //-----------------------------------
   std::cout << "Expected Results: " << std::endl
             << "  x   = " << std::setw(12) << result[0] << "  // [M]" << std::endl
             << "  y   = " << std::setw(12) << result[1] << "  // [M]" << std::endl
             << "  z   = " << std::setw(12) << result[2] << "  // [M]" << std::endl
             << std::endl;


   //-----------------------------------
   // calculate test results
   //-----------------------------------
   std::cout << "----------------------------------------------------------------------" << std::endl;
   std::cout << "Form 1:" << std::endl;
   std::cout << "base::nav::convertGeod2Ecef(lat, lon, alt, &x, &y, &z, pEM);" << std::endl;
   std::cout << std::endl;
   {
      double x(0), y(0), z(0);
      base::nav::convertGeod2Ecef(lat, lon, alt, &x, &y, &z, pEM);
      std::cout << "Results:" << std::endl;
      std::cout << "  x      = " << std::setw(12) << x << "; err = " << std::setw(8) << (x-result[0]) << std::endl;
      std::cout << "  y      = " << std::setw(12) << y << "; err = " << std::setw(8) << (y-result[1]) << std::endl;
      std::cout << "  z      = " << std::setw(12) << z << "; err = " << std::setw(8) << (z-result[2]) << std::endl;
      std::cout << std::endl;
   }

   std::cout << "----------------------------------------------------------------------" << std::endl;
   std::cout << "Form 2:" << std::endl;
   std::cout << "base::nav::convertGeod2Ecef(lla, &xyz, pEM);" << std::endl;
   std::cout << std::endl;
   {
      base::Vec3d lla(lat, lon, alt);
      base::Vec3d xyz(0,0,0);
      base::nav::convertGeod2Ecef(lla, &xyz, pEM);
      std::cout << "Results:" << std::endl;
      std::cout << "  xyz[0] = " << std::setw(12) << xyz[0] << "; err = " << std::setw(8) << (xyz[0]-result[0]) << std::endl;
      std::cout << "  xyz[1] = " << std::setw(12) << xyz[1] << "; err = " << std::setw(8) << (xyz[1]-result[1]) << std::endl;
      std::cout << "  xyz[2] = " << std::setw(12) << xyz[2] << "; err = " << std::setw(8) << (xyz[2]-result[2]) << std::endl;
      std::cout << std::endl;
   }

   std::cout << "----------------------------------------------------------------------" << std::endl;
   std::cout << "Form 3:" << std::endl << std::endl;
   std::cout << "base::nav::convertGeod2Ecef(LLA, XYZ, pEM);" << std::endl;
   std::cout << std::endl;
   {
      double lla[3] = {lat, lon, alt};
      double XYZ[3] = {0,0,0};
      base::nav::convertGeod2Ecef(lla, XYZ, pEM);
      std::cout << "Results:" << std::endl
                << "  XYZ[0] = " << std::setw(12) << XYZ[0] << "; err = " << std::setw(8) << (XYZ[0]-result[0]) << std::endl
                << "  XYZ[1] = " << std::setw(12) << XYZ[1] << "; err = " << std::setw(8) << (XYZ[1]-result[1]) << std::endl
                << "  XYZ[2] = " << std::setw(12) << XYZ[2] << "; err = " << std::setw(8) << (XYZ[2]-result[2]) << std::endl
                << std::endl;
   }


   //---------------------------------------------------------------------------
   // calculate results with own data
   //---------------------------------------------------------------------------
   if (testNumber != 99) {
      std::cout << enterYourOwnData; std::cin >> ynCont;
      std::cout << std::endl;

      if (ynCont != 'n') {

         // inputs
         double lat = 0.0;
         double lon = 0.0;
         double alt = 0.0;
         base::Vec3d lla;
         double LLA[3];
         const base::EarthModel* pEM = &base::EarthModel::wgs84;

         // outputs
         double x = 0.0;
         double y = 0.0;
         double z = 0.0;
         base::Vec3d xyz;
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

         base::nav::convertGeod2Ecef(lat, lon, alt, &x, &y, &z, pEM);

         std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
         std::cout << "*** double variables: lat,lon,alt => x,y,z ***" << std::endl;
         std::cout << "x      = " << std::setw(12) << x << " [M]" << std::endl;
         std::cout << "y      = " << std::setw(12) << y << " [M]" << std::endl;
         std::cout << "z      = " << std::setw(12) << z << " [M]" << std::endl;
         std::cout << std::endl;

         base::nav::convertGeod2Ecef(lla, &xyz, pEM);

         // output results
         std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
         std::cout << "*** base::vec3d vector: lla => xyz ***" << std::endl;
         std::cout << "xyz[0] = " << std::setw(12) << xyz[0] << " [M]" << std::endl;
         std::cout << "xyz[1] = " << std::setw(12) << xyz[1] << " [M]" << std::endl;
         std::cout << "xyz[2] = " << std::setw(12) << xyz[2] << " [M]" << std::endl;
         std::cout << std::endl;

         base::nav::convertGeod2Ecef(LLA, XYZ, pEM);

         std::cout << std::setprecision(2) << std::setiosflags(std::ios::fixed);
         std::cout << "*** double array: LLA => XYZ ***" << std::endl;
         std::cout << "XYZ[0] = " << std::setw(12) << XYZ[0] << " [M]" << std::endl;
         std::cout << "XYZ[1] = " << std::setw(12) << XYZ[1] << " [M]" << std::endl;
         std::cout << "XYZ[2] = " << std::setw(12) << XYZ[2] << " [M]" << std::endl;
         std::cout << std::endl;
      }
   }
}


//------------------------------------------------------------------------------
int showVec2(const base::Vec2d V)
{
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << std::setw(12) << V[0] << std::endl
             << std::setw(12) << V[1] << std::endl
             << std::endl;

   return 0;
}

int showVec3(const base::Vec3d V)
{
   std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
   std::cout << std::setw(12) << V[0] << std::endl
             << std::setw(12) << V[1] << std::endl
             << std::setw(12) << V[2] << std::endl
             << std::endl;

   return 0;
}

int displayMatrix(const base::Matrixd M)
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



//--------
// #27
//--------
void test27_convertUtm()
{

   const unsigned int ARRAY_SIZE = 38;
   //double lat[ARRAY_SIZE] = { -90.0, -80.0,  -70.0,  -60.0,  -50.0,  -40.0,  -30.0,  -20.0,  -10.0,   0.0,
   //                            10.0,  20.0,   30.0,   40.0,   50.0,   60.0,   70.0,   80.0,   90.0,
   //                           -90.0, -80.0,  -70.0,  -60.0,  -50.0,  -40.0,  -30.0,  -20.0,  -10.0,   0.0,
   //                            10.0,  20.0,   30.0,   40.0,   50.0,   60.0,   70.0,   80.0,   90.0 };
   //
   //double lon[ARRAY_SIZE] = {  0.0,   10.0,   20.0,   30.0,   40.0,   50.0,   60.0,   70.0,   80.0,  90.0,
   //                          100.0,  110.0,  120.0,  130.0,  140.0,  150.0,  160.0,  170.0,  180.0,
   //                            0.0,  -10.0,  -20.0,  -30.0,  -40.0,  -50.0,  -60.0,  -70.0,  -80.0, -90.0,
   //                         -100.0, -110.0, -120.0, -130.0, -140.0, -150.0, -160.0, -170.0, -180.0 };

   double lat[ARRAY_SIZE] = { -80.0,  -70.0,  -60.0,  -50.0,  -40.0,  -30.0,  -20.0,  -10.0,    0.0,
                               10.0,   20.0,   30.0,   40.0,   50.0,   60.0,   70.0,   80.0,    0.0,
                              -80.0,  -70.0,  -60.0,  -50.0,  -40.0,  -30.0,  -20.0,  -10.0,    0.0,
                               10.0,   20.0,   30.0,   40.0,   50.0,   60.0,   70.0,   80.0,    0.0 };

   double lon[ARRAY_SIZE] = {  10.0,   20.0,   30.0,   40.0,   50.0,   60.0,   70.0,   80.0,   90.0,
                             100.0,  110.0,  120.0,  130.0,  140.0,  150.0,  160.0,  170.0,  180.0,
                              -10.0,  -20.0,  -30.0,  -40.0,  -50.0,  -60.0,  -70.0,  -80.0,  -90.0,
                            -100.0, -110.0, -120.0, -130.0, -140.0, -150.0, -160.0, -170.0, -180.0};

//   char   Zone[6];
//   char*  pZone = Zone;

   //===========================================================================
   double latitude  = 0.0;
   double longitude = 0.0;

   char   latZone   = '*';
   int    lonZone   = 0;
   double N         = 0.0;
   double E         = 0.0;

   const base::EarthModel* pEM = &base::EarthModel::wgs84;


   for (unsigned int i=0; i<ARRAY_SIZE; i++) {

      std::cout << "==============================================" << std::endl;
      std::cout << "lat       = " << std::setw(14) << lat[i] << std::endl;
      std::cout << "lon       = " << std::setw(14) << lon[i] << std::endl << std::endl;


      std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
      base::nav::convertLL2Utm(lat[i], lon[i], &latZone, &lonZone, &N, &E, pEM);
      std::cout << "latZone   = " << std::setw(14) << latZone << std::endl;
      std::cout << "lonZone   = " << std::setw(14) << lonZone << std::endl;
      std::cout << "N         = " << std::setw(14) << N       << std::endl;
      std::cout << "E         = " << std::setw(14) << E       << std::endl << std::endl;

      std::cout << std::setprecision(4) << std::setiosflags(std::ios::fixed);
      base::nav::convertUtm2LL(N, E, latZone, lonZone, &latitude, &longitude, pEM);

      std::cout << "latitude  = " << std::setw(14) << latitude  << std::endl;
      std::cout << "longitude = " << std::setw(14) << longitude << std::endl << std::endl;

      std::cout << "latitude  error = " << std::setw(14) << latitude  - lat[i] << std::endl;
      std::cout << "longitude error = " << std::setw(14) << longitude - lon[i] << std::endl;

   }
}

int main(int argc, char* argv[])
{
   bool runAll = false;
   bool imode = false;

   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-a" ) {
         runAll = true;
      }
      else if ( std::string(argv[i]) == "-i" ) {
         imode = true;
      }
   }

   if (runAll) {
      // Run all tests
      testNumber = 99;
      test99_printAllExamples();
   }
   else if (imode) {
      // Interactive mode
      testNavFns();
   }
   else {
      std::cout                                             << std::endl;
      std::cout << "Test base::nav functions ---"          << std::endl;
      std::cout                                             << std::endl;
      std::cout << "testNav [-i] [-a]"                      << std::endl;
      std::cout << " where:"                                << std::endl;
      std::cout << "    -i    Interactive mode"             << std::endl;
      std::cout << "    -a    Batch mode (Run all tests)"   << std::endl;
      std::cout                                             << std::endl;
   }

   return EXIT_SUCCESS;
}

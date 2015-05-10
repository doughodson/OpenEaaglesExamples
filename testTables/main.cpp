//-----------------------------------------------------------------------------
// LFI Table tester --
//
//   usage:  testTables.exe  [-a] [-r] [-s] [-t] -f <file>
//
//   where:
//       -a          Test all base table classes as well
//                     e.g.,  Table1 and Table2 are tested with Table3
//       -r          Randomly selects the independent values from min to max
//       -s          Use the FStorage object
//       -t          Print timing data
//       -f <file>   defines the input file with the table to be tested
//
//-----------------------------------------------------------------------------

#include "openeaagles/basic/functors/Tables.h"

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"

// class factory
#include "openeaagles/basic/Factory.h"

#include <cstring>

namespace Eaagles {
namespace Test {

static const unsigned int TIMING_LOOPS = 10000;

// table builder
static Basic::Table* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   Basic::Object* obj = Basic::lcParser(filename, Basic::Factory::createObj, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a Basic::Pair, if so, point to object in Pair, not Pair itself
   Basic::Pair* pair = dynamic_cast<Basic::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   Basic::Table* table = dynamic_cast<Basic::Table*>(obj);
   if (table == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return table;
}

//-----------------------------------------------------------------------------
// Test 1D LFI tables
//-----------------------------------------------------------------------------
static unsigned int
testIt(const Basic::Table1* const tbl, const bool tflg, const bool sflg, const bool rflg)
{
   unsigned int cnt = 0;

   Basic::FStorage* s = 0;
   if (sflg) s = tbl->storageFactory();

   LCreal maxX = tbl->getMaxX();
   LCreal minX = tbl->getMinX();
   LCreal dx = (maxX - minX) / static_cast<LCreal>(20);

   if (!tflg) {
      std::cout << std::endl;
      std::cout << "Test 1D LFI";
      if (s != 0) std::cout << "; With Storage";
      std::cout << std::endl;
      std::cout << "x, value" << std::endl;
   }

   LCreal x = minX - 2*dx;
   while ( x <= (maxX + 2*dx) ) {
      LCreal x1 = x;
      if (rflg) x1 = (minX + (maxX - minX) * static_cast<LCreal>(rand()) / static_cast<LCreal>(RAND_MAX));

      LCreal value = tbl->lfi(x1,s);
      cnt++;

      if (!tflg) std::cout << x1 << ", " << value << std::endl;
      x += dx;
   }

   if (sflg && s != 0) { s->unref(); s = 0; }
   return cnt;
}

//-----------------------------------------------------------------------------
// Test 2D LFI tables
//-----------------------------------------------------------------------------
static unsigned int
testIt(const Basic::Table2* const tbl, const bool tflg, const bool sflg, const bool rflg)
{
   unsigned int cnt = 0;

   Basic::FStorage* s = 0;
   if (sflg) s = tbl->storageFactory();

   LCreal maxY = tbl->getMaxY();
   LCreal minY = tbl->getMinY();
   LCreal dy = (maxY - minY) / static_cast<LCreal>(10);

   LCreal maxX = tbl->getMaxX();
   LCreal minX = tbl->getMinX();
   LCreal dx = (maxX - minX) / static_cast<LCreal>(20);

   if (!tflg) {
      std::cout << std::endl;
      std::cout << "Test 2D LFI";
      if (s != 0) std::cout << "; With Storage";
      std::cout << std::endl;
      std::cout << "x, y, value" << std::endl;
   }

   LCreal y = minY - 2*dy;
   while ( y <= (maxY + 2*dy) ) {
      LCreal y1 = y;
      if (rflg) y1 = (minY + (maxY - minY) * static_cast<LCreal>(rand())/static_cast<LCreal>(RAND_MAX));

      LCreal x = minX - 2*dx;
      while ( x <= (maxX + 2*dx) ) {
         LCreal x1 = x;
         if (rflg) x1 = (minX + (maxX - minX) * static_cast<LCreal>(rand())/static_cast<LCreal>(RAND_MAX));

         LCreal value = tbl->lfi(x1,y1,s);
         cnt++;

         if (!tflg) std::cout << x1 << ", " << y1 << ", " << value << std::endl;
         x += dx;
      }
      y += dy;
   }

   if (sflg && s != 0) { s->unref(); s = 0; }
   return cnt;
}

//-----------------------------------------------------------------------------
// Test 3D LFI tables
//-----------------------------------------------------------------------------
static unsigned int
testIt(const Basic::Table3* const tbl, const bool tflg, const bool sflg, const bool rflg)
{
   unsigned int cnt = 0;

   Basic::FStorage* s = 0;
   if (sflg) s = tbl->storageFactory();

   // Setup Z
   LCreal maxZ = tbl->getMaxZ();
   LCreal minZ = tbl->getMinZ();
   LCreal dz = (maxZ - minZ) / static_cast<LCreal>(2*(tbl->getNumZPoints()-1));

   // Setup Y
   LCreal maxY = tbl->getMaxY();
   LCreal minY = tbl->getMinY();
   LCreal dy = (maxY - minY) / static_cast<LCreal>(2*(tbl->getNumYPoints()-1));

   // Setup X
   LCreal maxX = tbl->getMaxX();
   LCreal minX = tbl->getMinX();
   LCreal dx = (maxX - minX) / static_cast<LCreal>(2*(tbl->getNumXPoints()-1));

   if (!tflg) {
      std::cout << std::endl;
      std::cout << "Test 3D LFI";
      if (s != 0) std::cout << "; With Storage";
      std::cout << std::endl;
      std::cout << "x, y, z, value" << std::endl;
   }

   LCreal z = minZ - dz;
   while ( z <= (maxZ + dz) ) {
      LCreal z1 = z;
      if (rflg) z1 = (minZ + (maxZ - minZ) * static_cast<LCreal>(rand())/static_cast<LCreal>(RAND_MAX));

      LCreal y = minY - dy;
      while ( y <= (maxY + dy) ) {
         LCreal y1 = y;
         if (rflg) y1 = (minY + (maxY - minY) * static_cast<LCreal>(rand())/static_cast<LCreal>(RAND_MAX));

         LCreal x = minX - dx;
         while ( x <= (maxX + dx) ) {
            LCreal x1 = x;
            if (rflg) x1 = (minX + (maxX - minX) * static_cast<LCreal>(rand())/static_cast<LCreal>(RAND_MAX));

            LCreal value = tbl->lfi(x1,y1,z1,s);
            cnt++;

            if (!tflg) std::cout << x1 << ", " << y1 << ", " << z1 << ", " << value << std::endl;
            x += dx;
         }
         y += dy;
      }
      z += dz;
   }

   if (sflg && s != 0) { s->unref(); s = 0; }
   return cnt;
}


//-----------------------------------------------------------------------------
// Test 4D LFI tables
//-----------------------------------------------------------------------------
static unsigned int
testIt(const Basic::Table4* const tbl, const bool tflg, const bool sflg, const bool rflg)
{
   unsigned int cnt = 0;

   Basic::FStorage* s = 0;
   if (sflg) s = tbl->storageFactory();

   // Setup W
   const LCreal minW = tbl->getMinW();
   const LCreal maxW = tbl->getMaxW();
   const LCreal dw = (maxW - minW) / static_cast<LCreal>(2 * (tbl->getNumWPoints() - 1));

   const LCreal minZ = tbl->getMinZ();
   const LCreal maxZ = tbl->getMaxZ();
   const LCreal dz = (maxZ - minZ) / static_cast<LCreal>(2 * (tbl->getNumZPoints() - 1));

   const LCreal minY = tbl->getMinY();
   const LCreal maxY = tbl->getMaxY();
   const LCreal dy = (maxY - minY) / static_cast<LCreal>(2 * (tbl->getNumYPoints() - 1));

   const LCreal minX = tbl->getMinX();
   const LCreal maxX = tbl->getMaxX();
   const LCreal dx = (maxX - minX) / static_cast<LCreal>(2 * (tbl->getNumXPoints() - 1));

   if (!tflg) {
      std::cout << std::endl;
      std::cout << "Test 4D LFI";
      if (s != 0) std::cout << "; With Storage";
      std::cout << std::endl;
      std::cout << "x, y, z, w, value" << std::endl;
   }

   LCreal w = minW - dw;
   while (w <= (maxW + dw)) {
      LCreal w1 = w;
      if (rflg) w1 = (minW + (maxW - minW) * static_cast<LCreal>(rand())/static_cast<LCreal>(RAND_MAX));

      LCreal z = minZ - dz;
      while (z <= (maxZ + dz)) {
         LCreal z1 = z;
         if (rflg) z1 = (minZ + (maxZ - minZ) * static_cast<LCreal>(rand())/static_cast<LCreal>(RAND_MAX));

         LCreal y = minY - dy;
         while (y <= (maxY + dy)) {
            LCreal y1 = y;
            if (rflg) y1 = (minY + (maxY - minY) * static_cast<LCreal>(rand())/static_cast<LCreal>(RAND_MAX));

            LCreal x = minX - dx;
            while (x <= (maxX + dx)) {
               LCreal x1 = x;
               if (rflg) x1 = (minX + (maxX - minX) * static_cast<LCreal>(rand())/static_cast<LCreal>(RAND_MAX));

               LCreal value = tbl->lfi(x1, y1, z1, w1, s);
               cnt++;

               if (!tflg) {
                  std::cout << x1 << ", ";
                  std::cout << y1 << ", ";
                  std::cout << z1 << ", ";
                  std::cout << w1 << ", ";
                  std::cout << value << std::endl;
               }

               x += dx;
            }

            if (!tflg) std::cout << std::endl;
            y += dy;
         }

         z += dz;
      }

      w += dw;
   }

   if (sflg && s != 0) { s->unref(); s = 0; }
   return cnt;
}


int main(int argc, char* argv[])
{
   bool aflg = false;   // All base classes flag
   bool rflg = false;   // Random flag
   bool sflg = false;   // TableStoreage flag
   bool tflg = false;   // Timing flag

   // default configuration filename
   const char* configFilename = "test1.edl";

   // Parse arguments
   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i],"-f") == 0) {
         configFilename = argv[++i];
      }
      else if (std::strcmp(argv[i],"-a") == 0) {
         aflg = true;
      }
      else if (std::strcmp(argv[i],"-r") == 0) {
         rflg = true;
      }
      else if (std::strcmp(argv[i],"-s") == 0) {
         sflg = true;
      }
      else if (std::strcmp(argv[i],"-t") == 0) {
         tflg = true;
      }
   }

   // build table
   const Basic::Table* table = builder(configFilename);

   // ---
   // Serialize the table to the output stream
   // ---
   if (!tflg) table->serialize(std::cout);

   // ---
   // Cast table pointers
   // ---
   const Basic::Table1* t1 = dynamic_cast<const Basic::Table1*>(table);
   const Basic::Table2* t2 = dynamic_cast<const Basic::Table2*>(table);
   const Basic::Table3* t3 = dynamic_cast<const Basic::Table3*>(table);
   const Basic::Table4* t4 = dynamic_cast<const Basic::Table4*>(table);

   // ---
   // Call the test function for this LFI table type
   // ---
   double startTime = getComputerTime();
   unsigned int cnt = 0;
   unsigned int n = 1;
   if (tflg) n = TIMING_LOOPS;
   for (unsigned int i = 0; i < n; i++) {
      if (t1 != 0 && (aflg || t2 == 0) ) {
         cnt += testIt(t1, tflg, sflg, rflg);
      }
      if (t2 != 0 && (aflg || t3 == 0) ) {
         cnt += testIt(t2, tflg, sflg, rflg);
      }
      if (t3 != 0 && (aflg || t4 == 0) ) {
         cnt += testIt(t3, tflg, sflg, rflg);
      }
      if (t4 != 0) {
         cnt += testIt(t4, tflg, sflg, rflg);
      }
   }

   // ---
   // Timing data
   // ---
   if (tflg) {
      double endTime = Eaagles::getComputerTime();
      double deltaTime = endTime - startTime;
      double perFrameTime = deltaTime/static_cast<double>(TIMING_LOOPS);
      std::cout << "Total Time = " << deltaTime << " for " << TIMING_LOOPS << " frames." << std::endl;
      std::cout << "Ave time per frame (uS) = " << perFrameTime*1000000.0 << std::endl;
      if (cnt > 0) {
         double perCallTime = deltaTime/static_cast<double>(cnt);
         std::cout << "Ave time per call (uS) = " << perCallTime*1000000.0 << std::endl;
      }
   }

   return EXIT_SUCCESS;
}

}
}

//
int main(int argc, char* argv[])
{
   return Eaagles::Test::main(argc, argv);
}

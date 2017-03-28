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

#include "openeaagles/base/functors/Tables.hpp"

#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/base/util/system_utils.hpp"

// class factory
#include "openeaagles/base/factory.hpp"

#include <string>

const unsigned int TIMING_LOOPS = 10000;

// table builder
oe::base::Table* builder(const std::string& filename)
{
   // read configuration file
   unsigned int num_errors = 0;
   oe::base::Object* obj = oe::base::edl_parser(filename, oe::base::factory, &num_errors);
   if (num_errors > 0) {
      std::cerr << "File: " << filename << ", number of errors: " << num_errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   const auto pair = dynamic_cast<oe::base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   const auto table = dynamic_cast<oe::base::Table*>(obj);
   if (table == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return table;
}

//-----------------------------------------------------------------------------
// Test 1D LFI tables
//-----------------------------------------------------------------------------
unsigned int testIt(const oe::base::Table1* const tbl, const bool tflg, const bool sflg, const bool rflg)
{
   unsigned int cnt = 0;

   oe::base::FStorage* s = nullptr;
   if (sflg) s = tbl->storageFactory();

   const double maxX = tbl->getMaxX();
   const double minX = tbl->getMinX();
   const double dx = (maxX - minX) / static_cast<double>(20);

   if (!tflg) {
      std::cout << std::endl;
      std::cout << "Test 1D LFI";
      if (s != nullptr) std::cout << "; With Storage";
      std::cout << std::endl;
      std::cout << "x, value" << std::endl;
   }

   double x = minX - 2*dx;
   while ( x <= (maxX + 2*dx) ) {
      double x1 = x;
      if (rflg) x1 = (minX + (maxX - minX) * static_cast<double>(rand()) / static_cast<double>(RAND_MAX));

      double value = tbl->lfi(x1,s);
      cnt++;

      if (!tflg) std::cout << x1 << ", " << value << std::endl;
      x += dx;
   }

   if (sflg && s != nullptr) { s->unref(); s = nullptr; }
   return cnt;
}

//-----------------------------------------------------------------------------
// Test 2D LFI tables
//-----------------------------------------------------------------------------
unsigned int testIt(const oe::base::Table2* const tbl, const bool tflg, const bool sflg, const bool rflg)
{
   unsigned int cnt = 0;

   oe::base::FStorage* s = nullptr;
   if (sflg) s = tbl->storageFactory();

   double maxY = tbl->getMaxY();
   double minY = tbl->getMinY();
   double dy = (maxY - minY) / static_cast<double>(10);

   double maxX = tbl->getMaxX();
   double minX = tbl->getMinX();
   double dx = (maxX - minX) / static_cast<double>(20);

   if (!tflg) {
      std::cout << std::endl;
      std::cout << "Test 2D LFI";
      if (s != nullptr) std::cout << "; With Storage";
      std::cout << std::endl;
      std::cout << "x, y, value" << std::endl;
   }

   double y = minY - 2*dy;
   while ( y <= (maxY + 2*dy) ) {
      double y1 = y;
      if (rflg) y1 = (minY + (maxY - minY) * static_cast<double>(rand())/static_cast<double>(RAND_MAX));

      double x = minX - 2*dx;
      while ( x <= (maxX + 2*dx) ) {
         double x1 = x;
         if (rflg) x1 = (minX + (maxX - minX) * static_cast<double>(rand())/static_cast<double>(RAND_MAX));

         double value = tbl->lfi(x1,y1,s);
         cnt++;

         if (!tflg) std::cout << x1 << ", " << y1 << ", " << value << std::endl;
         x += dx;
      }
      y += dy;
   }

   if (sflg && s != nullptr) { s->unref(); s = nullptr; }
   return cnt;
}

//-----------------------------------------------------------------------------
// Test 3D LFI tables
//-----------------------------------------------------------------------------
unsigned int testIt(const oe::base::Table3* const tbl, const bool tflg, const bool sflg, const bool rflg)
{
   unsigned int cnt = 0;

   oe::base::FStorage* s = nullptr;
   if (sflg) s = tbl->storageFactory();

   // Setup Z
   double maxZ = tbl->getMaxZ();
   double minZ = tbl->getMinZ();
   double dz = (maxZ - minZ) / static_cast<double>(2*(tbl->getNumZPoints()-1));

   // Setup Y
   double maxY = tbl->getMaxY();
   double minY = tbl->getMinY();
   double dy = (maxY - minY) / static_cast<double>(2*(tbl->getNumYPoints()-1));

   // Setup X
   double maxX = tbl->getMaxX();
   double minX = tbl->getMinX();
   double dx = (maxX - minX) / static_cast<double>(2*(tbl->getNumXPoints()-1));

   if (!tflg) {
      std::cout << std::endl;
      std::cout << "Test 3D LFI";
      if (s != nullptr) std::cout << "; With Storage";
      std::cout << std::endl;
      std::cout << "x, y, z, value" << std::endl;
   }

   double z = minZ - dz;
   while ( z <= (maxZ + dz) ) {
      double z1 = z;
      if (rflg) z1 = (minZ + (maxZ - minZ) * static_cast<double>(rand())/static_cast<double>(RAND_MAX));

      double y = minY - dy;
      while ( y <= (maxY + dy) ) {
         double y1 = y;
         if (rflg) y1 = (minY + (maxY - minY) * static_cast<double>(rand())/static_cast<double>(RAND_MAX));

         double x = minX - dx;
         while ( x <= (maxX + dx) ) {
            double x1 = x;
            if (rflg) x1 = (minX + (maxX - minX) * static_cast<double>(rand())/static_cast<double>(RAND_MAX));

            double value = tbl->lfi(x1,y1,z1,s);
            cnt++;

            if (!tflg) std::cout << x1 << ", " << y1 << ", " << z1 << ", " << value << std::endl;
            x += dx;
         }
         y += dy;
      }
      z += dz;
   }

   if (sflg && s != nullptr) { s->unref(); s = nullptr; }
   return cnt;
}


//-----------------------------------------------------------------------------
// Test 4D LFI tables
//-----------------------------------------------------------------------------
unsigned int testIt(const oe::base::Table4* const tbl, const bool tflg, const bool sflg, const bool rflg)
{
   unsigned int cnt = 0;

   oe::base::FStorage* s = nullptr;
   if (sflg) s = tbl->storageFactory();

   // Setup W
   const double minW = tbl->getMinW();
   const double maxW = tbl->getMaxW();
   const double dw = (maxW - minW) / static_cast<double>(2 * (tbl->getNumWPoints() - 1));

   const double minZ = tbl->getMinZ();
   const double maxZ = tbl->getMaxZ();
   const double dz = (maxZ - minZ) / static_cast<double>(2 * (tbl->getNumZPoints() - 1));

   const double minY = tbl->getMinY();
   const double maxY = tbl->getMaxY();
   const double dy = (maxY - minY) / static_cast<double>(2 * (tbl->getNumYPoints() - 1));

   const double minX = tbl->getMinX();
   const double maxX = tbl->getMaxX();
   const double dx = (maxX - minX) / static_cast<double>(2 * (tbl->getNumXPoints() - 1));

   if (!tflg) {
      std::cout << std::endl;
      std::cout << "Test 4D LFI";
      if (s != nullptr) std::cout << "; With Storage";
      std::cout << std::endl;
      std::cout << "x, y, z, w, value" << std::endl;
   }

   double w = minW - dw;
   while (w <= (maxW + dw)) {
      double w1 = w;
      if (rflg) w1 = (minW + (maxW - minW) * static_cast<double>(rand())/static_cast<double>(RAND_MAX));

      double z = minZ - dz;
      while (z <= (maxZ + dz)) {
         double z1 = z;
         if (rflg) z1 = (minZ + (maxZ - minZ) * static_cast<double>(rand())/static_cast<double>(RAND_MAX));

         double y = minY - dy;
         while (y <= (maxY + dy)) {
            double y1 = y;
            if (rflg) y1 = (minY + (maxY - minY) * static_cast<double>(rand())/static_cast<double>(RAND_MAX));

            double x = minX - dx;
            while (x <= (maxX + dx)) {
               double x1 = x;
               if (rflg) x1 = (minX + (maxX - minX) * static_cast<double>(rand())/static_cast<double>(RAND_MAX));

               double value = tbl->lfi(x1, y1, z1, w1, s);
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

   if (sflg && s != nullptr) { s->unref(); s = nullptr; }
   return cnt;
}

int main(int argc, char* argv[])
{
   bool aflg = false;   // All base classes flag
   bool rflg = false;   // Random flag
   bool sflg = false;   // TableStoreage flag
   bool tflg = false;   // Timing flag

   // default configuration filename
   std::string configFilename = "test1.edl";

   // Parse arguments
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
      else if ( std::string(argv[i]) == "-a") {
         aflg = true;
      }
      else if ( std::string(argv[i]) == "-r") {
         rflg = true;
      }
      else if ( std::string(argv[i]) == "-s") {
         sflg = true;
      }
      else if ( std::string(argv[i]) == "-t") {
         tflg = true;
      }
   }

   // build table
   const oe::base::Table* table = builder(configFilename);

   // ---
   // Serialize the table to the output stream
   // ---
   if (!tflg) table->serialize(std::cout);

   // ---
   // Cast table pointers
   // ---
   const auto t1 = dynamic_cast<const oe::base::Table1*>(table);
   const auto t2 = dynamic_cast<const oe::base::Table2*>(table);
   const auto t3 = dynamic_cast<const oe::base::Table3*>(table);
   const auto t4 = dynamic_cast<const oe::base::Table4*>(table);

   // ---
   // Call the test function for this LFI table type
   // ---
   double startTime = oe::base::getComputerTime();
   unsigned int cnt = 0;
   unsigned int n = 1;
   if (tflg) n = TIMING_LOOPS;
   for (unsigned int i = 0; i < n; i++) {
      if (t1 != nullptr && (aflg || t2 == nullptr) ) {
         cnt += testIt(t1, tflg, sflg, rflg);
      }
      if (t2 != nullptr && (aflg || t3 == nullptr) ) {
         cnt += testIt(t2, tflg, sflg, rflg);
      }
      if (t3 != nullptr && (aflg || t4 == nullptr) ) {
         cnt += testIt(t3, tflg, sflg, rflg);
      }
      if (t4 != nullptr) {
         cnt += testIt(t4, tflg, sflg, rflg);
      }
   }

   // ---
   // Timing data
   // ---
   if (tflg) {
      double endTime = oe::base::getComputerTime();
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

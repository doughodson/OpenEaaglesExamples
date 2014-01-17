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

#include "openeaagles/basic/Tables.h"

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"

// class factories
#include "openeaagles/basic/Factory.h"

// Parameters
static const char* const DEFAULT_CONFIG_FILE = "test1.edl";
static const unsigned int TIMING_LOOPS = 10000;

//-----------------------------------------------------------------------------
// Read the configuration file
//-----------------------------------------------------------------------------
static const Eaagles::Basic::Table* builder(const char* const fileName)
{
   const Eaagles::Basic::Table* p = 0;

   // Read the description file
   int errors = 0;
   Eaagles::Basic::Object* q1 =
         Eaagles::Basic::lcParser(fileName, Eaagles::Basic::Factory::createObj, &errors);
   if (errors > 0) {
      std::cerr << "File: " << fileName << ", errors: " << errors << std::endl;
      return 0;
   }

   if (q1 != 0) {
      // When we were given a Basic::Pair, get the pointer to its object.
      Eaagles::Basic::Pair* pp = dynamic_cast<Eaagles::Basic::Pair*>(q1);
      if (pp != 0) {
         q1 = pp->object();
      }

      // What we should have here is the Station object
      p = dynamic_cast<const Eaagles::Basic::Table*>(q1);
   }
    
   return p;
}

//-----------------------------------------------------------------------------
// Test 1D LFI tables
//-----------------------------------------------------------------------------
static unsigned int
testIt(const Eaagles::Basic::Table1* const tbl, const bool tflg, const bool sflg, const bool rflg)
{
   unsigned int cnt = 0;

   Eaagles::Basic::FStorage* s = 0;
   if (sflg) s = tbl->storageFactory();

   Eaagles::LCreal maxX = tbl->getMaxX();
   Eaagles::LCreal minX = tbl->getMinX();
   Eaagles::LCreal dx = (maxX - minX) / Eaagles::LCreal(20);

   if (!tflg) {
      std::cout << std::endl;
      std::cout << "Test 1D LFI";
      if (s != 0) std::cout << "; With Storage";
      std::cout << std::endl;
      std::cout << "x, value" << std::endl;
   }

   Eaagles::LCreal x = minX - 2*dx;
   while ( x <= (maxX + 2*dx) ) {
      Eaagles::LCreal x1 = x;
      if (rflg) x1 = (minX + (maxX - minX) * Eaagles::LCreal(rand())/Eaagles::LCreal(RAND_MAX));

      Eaagles::LCreal value = tbl->lfi(x1,s);
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
testIt(const Eaagles::Basic::Table2* const tbl, const bool tflg, const bool sflg, const bool rflg)
{
   unsigned int cnt = 0;

   Eaagles::Basic::FStorage* s = 0;
   if (sflg) s = tbl->storageFactory();

   Eaagles::LCreal maxY = tbl->getMaxY();
   Eaagles::LCreal minY = tbl->getMinY();
   Eaagles::LCreal dy = (maxY - minY) / Eaagles::LCreal(10);

   Eaagles::LCreal maxX = tbl->getMaxX();
   Eaagles::LCreal minX = tbl->getMinX();
   Eaagles::LCreal dx = (maxX - minX) / Eaagles::LCreal(20);

   if (!tflg) {
      std::cout << std::endl;
      std::cout << "Test 2D LFI";
      if (s != 0) std::cout << "; With Storage";
      std::cout << std::endl;
      std::cout << "x, y, value" << std::endl;
   }

   Eaagles::LCreal y = minY - 2*dy;
   while ( y <= (maxY + 2*dy) ) {
      Eaagles::LCreal y1 = y;
      if (rflg) y1 = (minY + (maxY - minY) * Eaagles::LCreal(rand())/Eaagles::LCreal(RAND_MAX));

      Eaagles::LCreal x = minX - 2*dx;
      while ( x <= (maxX + 2*dx) ) {
         Eaagles::LCreal x1 = x;
         if (rflg) x1 = (minX + (maxX - minX) * Eaagles::LCreal(rand())/Eaagles::LCreal(RAND_MAX));

         Eaagles::LCreal value = tbl->lfi(x1,y1,s);
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
testIt(const Eaagles::Basic::Table3* const tbl, const bool tflg, const bool sflg, const bool rflg)
{
   unsigned int cnt = 0;

   Eaagles::Basic::FStorage* s = 0;
   if (sflg) s = tbl->storageFactory();

   // Setup Z
   Eaagles::LCreal maxZ = tbl->getMaxZ();
   Eaagles::LCreal minZ = tbl->getMinZ();
   Eaagles::LCreal dz = (maxZ - minZ) / Eaagles::LCreal(2*(tbl->getNumZPoints()-1));

   // Setup Y
   Eaagles::LCreal maxY = tbl->getMaxY();
   Eaagles::LCreal minY = tbl->getMinY();
   Eaagles::LCreal dy = (maxY - minY) / Eaagles::LCreal(2*(tbl->getNumYPoints()-1));

   // Setup X
   Eaagles::LCreal maxX = tbl->getMaxX();
   Eaagles::LCreal minX = tbl->getMinX();
   Eaagles::LCreal dx = (maxX - minX) / Eaagles::LCreal(2*(tbl->getNumXPoints()-1));

   if (!tflg) {
      std::cout << std::endl;
      std::cout << "Test 3D LFI";
      if (s != 0) std::cout << "; With Storage";
      std::cout << std::endl;
      std::cout << "x, y, z, value" << std::endl;
   }

   Eaagles::LCreal z = minZ - dz;
   while ( z <= (maxZ + dz) ) {
      Eaagles::LCreal z1 = z;
      if (rflg) z1 = (minZ + (maxZ - minZ) * Eaagles::LCreal(rand())/Eaagles::LCreal(RAND_MAX));

      Eaagles::LCreal y = minY - dy;
      while ( y <= (maxY + dy) ) {
         Eaagles::LCreal y1 = y;
         if (rflg) y1 = (minY + (maxY - minY) * Eaagles::LCreal(rand())/Eaagles::LCreal(RAND_MAX));

         Eaagles::LCreal x = minX - dx;
         while ( x <= (maxX + dx) ) {
            Eaagles::LCreal x1 = x;
            if (rflg) x1 = (minX + (maxX - minX) * Eaagles::LCreal(rand())/Eaagles::LCreal(RAND_MAX));

            Eaagles::LCreal value = tbl->lfi(x1,y1,z1,s);
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
testIt(const Eaagles::Basic::Table4* const tbl, const bool tflg, const bool sflg, const bool rflg)
{
   unsigned int cnt = 0;

   Eaagles::Basic::FStorage* s = 0;
   if (sflg) s = tbl->storageFactory();

   // Setup W
   const Eaagles::LCreal minW = tbl->getMinW();
   const Eaagles::LCreal maxW = tbl->getMaxW();
   const Eaagles::LCreal dw = (maxW - minW) / Eaagles::LCreal(2 * (tbl->getNumWPoints() - 1));
        
   const Eaagles::LCreal minZ = tbl->getMinZ();
   const Eaagles::LCreal maxZ = tbl->getMaxZ();
   const Eaagles::LCreal dz = (maxZ - minZ) / Eaagles::LCreal(2 * (tbl->getNumZPoints() - 1));

   const Eaagles::LCreal minY = tbl->getMinY();
   const Eaagles::LCreal maxY = tbl->getMaxY();
   const Eaagles::LCreal dy = (maxY - minY) / Eaagles::LCreal(2 * (tbl->getNumYPoints() - 1));

   const Eaagles::LCreal minX = tbl->getMinX();
   const Eaagles::LCreal maxX = tbl->getMaxX();
   const Eaagles::LCreal dx = (maxX - minX) / Eaagles::LCreal(2 * (tbl->getNumXPoints() - 1));

   if (!tflg) {
      std::cout << std::endl;
      std::cout << "Test 4D LFI";
      if (s != 0) std::cout << "; With Storage";
      std::cout << std::endl;
      std::cout << "x, y, z, w, value" << std::endl;
   }

   Eaagles::LCreal w = minW - dw;
   while (w <= (maxW + dw)) {
      Eaagles::LCreal w1 = w;
      if (rflg) w1 = (minW + (maxW - minW) * Eaagles::LCreal(rand())/Eaagles::LCreal(RAND_MAX));

      Eaagles::LCreal z = minZ - dz;
      while (z <= (maxZ + dz)) {
         Eaagles::LCreal z1 = z;
         if (rflg) z1 = (minZ + (maxZ - minZ) * Eaagles::LCreal(rand())/Eaagles::LCreal(RAND_MAX));

         Eaagles::LCreal y = minY - dy;
         while (y <= (maxY + dy)) {
            Eaagles::LCreal y1 = y;
            if (rflg) y1 = (minY + (maxY - minY) * Eaagles::LCreal(rand())/Eaagles::LCreal(RAND_MAX));

            Eaagles::LCreal x = minX - dx;
            while (x <= (maxX + dx)) {
               Eaagles::LCreal x1 = x;
               if (rflg) x1 = (minX + (maxX - minX) * Eaagles::LCreal(rand())/Eaagles::LCreal(RAND_MAX));

               Eaagles::LCreal value = tbl->lfi(x1, y1, z1, w1, s);
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

   // Config file file
   const char* configFile = DEFAULT_CONFIG_FILE;

   // Parse arguments
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i],"-f") == 0) {
         configFile = argv[++i];
      }
      else if (strcmp(argv[i],"-a") == 0) {
         aflg = true;
      }
      else if (strcmp(argv[i],"-r") == 0) {
         rflg = true;
      }
      else if (strcmp(argv[i],"-s") == 0) {
         sflg = true;
      }
      else if (strcmp(argv[i],"-t") == 0) {
         tflg = true;
      }
   }

   // ---
   // Read in the description files
   // ---
   const Eaagles::Basic::Table* table = builder(configFile);
   if (table == 0) {
      std::cerr << "Invalid configuration file!" << std::endl;
      exit(EXIT_FAILURE);
   }

   // ---
   // Serialize the table to the output stream
   // ---
   if (!tflg) table->serialize(std::cout);

   // ---
   // Cast table pointers
   // ---
   const Eaagles::Basic::Table1* t1 = dynamic_cast<const Eaagles::Basic::Table1*>(table);
   const Eaagles::Basic::Table2* t2 = dynamic_cast<const Eaagles::Basic::Table2*>(table);
   const Eaagles::Basic::Table3* t3 = dynamic_cast<const Eaagles::Basic::Table3*>(table);
   const Eaagles::Basic::Table4* t4 = dynamic_cast<const Eaagles::Basic::Table4*>(table);

   // ---
   // Call the test function for this LFI table type
   // ---
   double startTime = Eaagles::getComputerTime();
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
      double perFrameTime = deltaTime/double(TIMING_LOOPS);
      std::cout << "Total Time = " << deltaTime << " for " << TIMING_LOOPS << " frames." << std::endl;
      std::cout << "Ave time per frame (uS) = " << perFrameTime*1000000.0 << std::endl;
      if (cnt > 0) {
         double perCallTime = deltaTime/double(cnt);
         std::cout << "Ave time per call (uS) = " << perCallTime*1000000.0 << std::endl;
      }
   }

   return EXIT_SUCCESS;
}

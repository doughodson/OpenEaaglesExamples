
#ifndef __AirportTests_H__
#define __AirportTests_H__

//------------------------------------------------
// AirportLoader test subroutines
//------------------------------------------------

namespace oe {
namespace dafif { class AirportLoader; } 
}

class AirportTests
{
public:
   AirportTests(
      const char* country,
      const char* file = "FILE0",
      const char* path = "../shared/data/DAFIF/FULLALL/"
   );

   ~AirportTests();

   void dump();      // dump raw DAFIF records
   void func00();
   void func00I(const double acLat, const double acLon, const double acElev);
   void func00R(const double acLat, const double acLon, const double acElev);

   void func01(const double acLat, const double acLon, const double acElev, const bool printData);
   void func01I(const double acLat, const double acLon, const double acElev, const bool printData);
   void func01R(const double acLat, const double acLon, const double acElev, const bool printData);

   void func02(const double acLat, const double acLon, const double acElev, const bool printData);
   void func02I(const double acLat, const double acLon, const double acElev, const bool printData);
   void func02R(const double acLat, const double acLon, const double acElev, const bool printData);

   void func04(const double acLat, const double acLon, const double acElev, const bool printData);
   void func04I(const double acLat, const double acLon, const double acElev, const bool printData);
   void func04R(const double acLat, const double acLon, const double acElev, const bool printData);

   void func05(const double acLat, const double acLon, const double acElev, const bool printData);
   void func05I(const double acLat, const double acLon, const double acElev, const bool printData);
   void func05R(const double acLat, const double acLon, const double acElev, const bool printData);

   void func06(const double acLat, const double acLon, const double acElev, const bool printData);
   void func06I(const double acLat, const double acLon, const double acElev, const bool printData);
   void func06R(const double acLat, const double acLon, const double acElev, const bool printData);

   void func07(const double acLat, const double acLon, const double acElev, const bool printData);
   void func07R(const double acLat, const double acLon, const double acElev, const bool printData);

   void func08(const double acLat, const double acLon, const double acElev, const bool printData);
   void func08I(const double acLat, const double acLon, const double acElev, const bool printData);
   void func08R(const double acLat, const double acLon, const double acElev, const bool printData);

   void func09(const double acLat, const double acLon, const double acElev, const bool printData);
   void func09I(const double acLat, const double acLon, const double acElev, const bool printData);

   void func0A();

   void func0B(const double acLat, const double acLon, const double acElev, const bool printData);

private:
   oe::dafif::AirportLoader* db {};
};

#endif

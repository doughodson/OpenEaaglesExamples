
#ifndef __NavaidTests_H__
#define __NavaidTests_H__

namespace oe {
namespace dafif { class NavaidLoader; } 
}

class NavaidTests
{
public:
   NavaidTests(
      const char* country,
      const char* file = "FILE2",
      const char* path = "../shared/data/DAFIF/FULLALL/"
   );
   ~NavaidTests();

   void dump();      // dump raw DAFIF records
   void func20();    // print all records
   void func21(const double acLat, const double acLon, const double acElev, const bool printData);    // print selected record
   void func22(const double acLat, const double acLon, const double acElev, const bool printData);    // test queryByIdent()
   void func23();    // print freq list sorting
   void func24(const double acLat, const double acLon, const double acElev, const bool printData);    // test queryByFreq()
   void func25(const double acLat, const double acLon, const double acElev, const bool printData);    // test queryByRange()
   void func26(const double acLat, const double acLon, const double acElev, const bool printData);    // test queryByKey()
   void func27();    // print channel list sorting
   void func28(const double acLat, const double acLon, const double acElev, const bool printData);    // test queryByChannel()
   void func29(const double acLat, const double acLon, const double acElev, const bool printData);    // test queryByType()
   void func2A();    // print ICAO sorted listing
   void func2B(const double acLat, const double acLon, const double acElev, const bool printData);    // test queryByIcao()

private:
   oe::dafif::NavaidLoader* db {};
};

#endif

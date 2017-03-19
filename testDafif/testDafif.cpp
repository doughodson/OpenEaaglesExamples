
#include "AirportTests.hpp"
#include "NavaidTests.hpp"
#include "WaypointTests.hpp"
#include <iostream>

void testAirports(const char* const ccode, const double acLat, const double acLon, const double acElev, const bool printData)
{
   AirportTests tester(ccode);

   int id = 999;
   while (id > 0) {
      std::cout << std::endl;
      std::cout << "1) print all Airport records" << std::endl; 
      std::cout << "2) select a Airport record by index" << std::endl; 
      std::cout << "3) test queryByIdent()" << std::endl; 
      std::cout << "5) test queryByFreq()" << std::endl; 
      std::cout << "6) test queryByRange()" << std::endl; 
      std::cout << "7) test queryByKey()" << std::endl; 
      std::cout << "8) test queryByLength()" << std::endl; 
      std::cout << "9) test queryByChannel()" << std::endl; 
      std::cout << "10) test queryByType()" << std::endl; 
      std::cout << "11) print ICAO sorted listing" << std::endl; 
      std::cout << "12) test queryByIcao()" << std::endl;
      std::cout << "13) test queryRunwayByIdent()" << std::endl;
      std::cout << "15) test queryRunwayByFreq()" << std::endl; 
      std::cout << "16) test queryRunwayByRange()" << std::endl;
      std::cout << "17) test queryRunwayByKey()" << std::endl; 
      std::cout << "18) test queryRunwayByLength()" << std::endl; 
      std::cout << "23) test queryIlsByIdent()" << std::endl;
      std::cout << "25) test queryIlsByFreq()" << std::endl; 
      std::cout << "26) test queryIlsByRange()" << std::endl;
      std::cout << "27) test queryILSByKey()" << std::endl; 
      std::cout << "29) test queryIlsByChannel()" << std::endl; 
      std::cout << "30) test queryIlsByType" << std::endl;
      std::cout << "98) Define Record" << std::endl;
      std::cout << "99) dump raw DAFIF records" << std::endl;
      std::cout << "select test (0 to end):";
      std::cin >> id;

      switch (id) {
         case  1 : tester.func00(); break;
         case  2 : tester.func01(acLat, acLon, acElev, printData); break;
         case  3 : tester.func02(acLat, acLon, acElev, printData); break; // queryByIdent
         case  5 : tester.func04(acLat, acLon, acElev, printData); break; // queryByFreq
         case  6 : tester.func05(acLat, acLon, acElev, printData); break; // queryByRange
         case  7 : tester.func06(acLat, acLon, acElev, printData); break; // queryByKey
         case  8 : tester.func07(acLat, acLon, acElev, printData); break; // queryByLength
         case  9 : tester.func08(acLat, acLon, acElev, printData); break; // queryByChannel
         case 10 : tester.func09(acLat, acLon, acElev, printData); break; // queryByType
         case 11 : tester.func0A(); break; // ICAO sorted listing
         case 12 : tester.func0B(acLat, acLon, acElev, printData); break; // queryByIcao
         case 13 : tester.func02R(acLat, acLon, acElev, printData); break; // queryRunwayByIdent
         case 15 : tester.func04R(acLat, acLon, acElev, printData); break; // queryRunwayByFreq
         case 16 : tester.func05R(acLat, acLon, acElev, printData); break; // queryRunwayByRange
         case 17 : tester.func06R(acLat, acLon, acElev, printData); break; // queryRunwayByKey
         case 18 : tester.func07R(acLat, acLon, acElev, printData); break; // queryRunwayByLength
         case 23 : tester.func02I(acLat, acLon, acElev, printData); break; // queryIlsByIdent
         case 25 : tester.func04I(acLat, acLon, acElev, printData); break; // queryIlsByFreq
         case 26 : tester.func05I(acLat, acLon, acElev, printData); break; // queryIlsByRange
         case 27 : tester.func06I(acLat, acLon, acElev, printData); break; // queryIlsByKey
         case 29 : tester.func08I(acLat, acLon, acElev, printData); break; // queryIlsByChannel
         case 30 : tester.func09I(acLat, acLon, acElev, printData); break; // queryIlsByType
         case 98 :
            std::cout << "  Airport Record" << std::endl;
            std::cout <<  std::endl;
            std::cout << "US71980: DTA-US  D  39.3833, -112.51, 4755, mv-12.425" << std::endl;
            std::cout << "    Key: Id - countryCode airportType" << std::endl;
            std::cout << "                    Latitude Longitude elevation," << std::endl;
            std::cout << "                                            mv- magVariance" << std::endl;
            std::cout <<  std::endl;
            std::cout <<  std::endl;
            std::cout <<  "  Runway Record" << std::endl;
            std::cout << "US2427434R16L: (34R: 40.7746, -111.973, 4221.4, 340.9) 16L: 40.8074, -111.9777, 4226.2, 1609) 12004x15" << std::endl;
            std::cout << "    Key:         Id:                                    ID:" << std::endl;
            std::cout << "                    Latitude, Longitude, elevation,         Latitude, Longitude, elevation," << std::endl;
            std::cout << "                                              magHead,                                magHead," << std::endl;
            std::cout << "                                                                                              length X width" << std::endl;
            std::cout <<  std::endl;
            std::cout <<  std::endl;
            std::cout <<  "  ILS Record" << std::endl;
            std::cout << "US2427434LZ: IUUH: z- : ( 40.8103, -112, 0, 13.5733) 111.9 0 0" << std::endl;
            std::cout << "    Key:      Id   typevalue" << std::endl;
            std::cout << "                        Latitude Longitude elevation," << std::endl;
            std::cout << "                                            magVariance" << std::endl;
            std::cout << "                                                    freq chan glideslope" << std::endl;
            std::cout << std::endl;
            break;
         case 99 : tester.dump(); break;
      };
   }
}


void testNavaids(const char* const ccode, const double acLat, const double acLon, const double acElev, const bool printData)
{
   NavaidTests tester(ccode);

   int id = 999;
   while (id > 0) {
      std::cout << std::endl;
      std::cout << "1) print all Navaid records" << std::endl; 
      std::cout << "2) select a Navaid record by index" << std::endl; 
      std::cout << "3) test queryByIdent()" << std::endl; 
      std::cout << "4) print freq list sorting" << std::endl; 
      std::cout << "5) test queryByFreq()" << std::endl; 
      std::cout << "6) test queryByRange()" << std::endl; 
      std::cout << "7) test queryByKey()" << std::endl; 
      std::cout << "8) print channel list sorting" << std::endl; 
      std::cout << "9) test queryByChannel()" << std::endl; 
      std::cout << "10) test queryByType()" << std::endl; 
      std::cout << "11) print ICAO sorted listing" << std::endl; 
      std::cout << "12) test queryByIcao()" << std::endl;
      std::cout << "98) Define Record" << std::endl;
      std::cout << "99) dump raw DAFIF records" << std::endl;
      std::cout << "select test (0 to end):";
      std::cin >> id;

      switch (id) {
         case  1 : tester.func20(); break;   // DsNavaidLoader; freq list sorting
         case  2 : tester.func21(acLat, acLon, acElev, printData); break; // by index
         case  3 : tester.func22(acLat, acLon, acElev, printData); break; // queryByIdent
         case  4 : tester.func23(); break; // freq list
         case  5 : tester.func24(acLat, acLon, acElev, printData); break; // queryByFreq
         case  6 : tester.func25(acLat, acLon, acElev, printData); break; // queryByRange
         case  7 : tester.func26(acLat, acLon, acElev, printData); break; // queryByKey
         case  8 : tester.func27(); break; // channel list
         case  9 : tester.func28(acLat, acLon, acElev, printData); break; // queryByChannel
         case 10 : tester.func29(acLat, acLon, acElev, printData); break; // queryByType
         case 11 : tester.func2A(); break; // ICAO listing
         case 12 : tester.func2B(acLat, acLon, acElev, printData); break; // queryByIcao
         case 98 :
            std::cout <<  std::endl;
            std::cout << "KZ, \"LWL 1US 1\", LWL-1-US-1:  41.1448, -114.978  114.2-0 ( 14.6417,17) (2000-L-0)" << std::endl;
            std::cout << "icaoCode, \"Key\" ident - navType - countryCode - keyCode " << std::endl;
            std::cout << "                               latitude longitude freg channel" << std::endl;
            std::cout << "                                                            magVar slaveVar" << std::endl;
            std::cout << "                                                                        pwr radioclass range" << std::endl;
            std::cout << std::endl;
            break;
         case 99 : tester.dump(); break;
      };
   }
}

void testWaypoints(const char* const ccode, const double acLat, const double acLon, const double acElev, const bool printData)
{
   WaypointTests tester(ccode);

   int id = 99;
   while (id > 0) {
      std::cout << std::endl;
      std::cout << "1) print Waypoint records" << std::endl; 
      std::cout << "2) select a Waypoint record by index" << std::endl; 
      std::cout << "3) test queryByIdent()" << std::endl; 
      std::cout << std::endl;
      std::cout << "6) test queryByRange()" << std::endl; 
      std::cout << "7) test queryByKey()" << std::endl; 
      std::cout << std::endl;
      std::cout << "11) ICAO sorted listing" << std::endl; 
      std::cout << "12) test queryByIcao()" << std::endl;
      std::cout << "98) Define Record" << std::endl;
      std::cout << "99) dump raw DAFIF records" << std::endl;
      std::cout << "select test (0 to end):";
      std::cin >> id;

      switch (id) {
         case  1 : tester.func30(); break;
         case  2 : tester.func31(acLat, acLon, acElev, printData); break;
         case  3 : tester.func32(acLat, acLon, acElev, printData); break;
         case  6 : tester.func35(acLat, acLon, acElev, printData); break;
         case  7 : tester.func36(acLat, acLon, acElev, printData); break;
         case 11 : tester.func3A(); break;
         case 12 : tester.func3B(acLat, acLon, acElev, printData); break;
         case 98 :
            std::cout <<  std::endl;
            std::cout << "KOGD, \"OGD15   US\", OGD15-US, 41.0615, -112.049" << std::endl;
            std::cout << "icaoCode, \"Key\"    ident - countryCode " << std::endl;
            std::cout << "                               latitude longitude" << std::endl;
            std::cout << std::endl;
            break;
         case 99 : tester.dump(); break;
      };
   }
}

int main(int argc, char* argv[])
{
   char* ccode {};
   if (argc > 1) {
      ccode = argv[1];
   }

   int id {99};

   std::cout << std::endl;
   std::cout << "1) Test Airport records" << std::endl; 
   std::cout << "2) Test Navaid records" << std::endl; 
   std::cout << "3) Test Waypoint records" << std::endl; 
   std::cout << "select test (0 to end): ";
   std::cin >> id;
   std::cout << std::endl;
   double acLat {41.0};
   double acLon {-112.0};
   double acElev {10000.0};
   std::cout << "Use Standard Test Latitude (Salt Lake area): N41.0 deg., Longitude W112.0 deg., Altitude 10000.0 m" << std::endl; 

   char useStandardTest;
   std::cout << "Y / N: " ; 
   std::cin >> useStandardTest;
   
   if (useStandardTest != 'Y' && useStandardTest != 'y') {
      std::cout << "Input aircraft Latitude: " ; 
      std::cin >> acLat;
      std::cout << "Input aircraft Longitude: " ; 
      std::cin >> acLon;
      std::cout << "Input aircraft altitude (meters): " ; 
      std::cin >> acElev;
   }

   char usePrintData {};
   bool printData {false};

   std::cout << std::endl;
   std::cout << "Print extra bearing and range data (Y/N):";
   std::cin >> usePrintData;

   if (usePrintData == 'Y' || usePrintData == 'y')
      printData = true;

   while (id > 0) {
      switch (id) {
         case  1 : testAirports(ccode, acLat, acLon, acElev, printData); break;
         case  2 : testNavaids(ccode, acLat, acLon, acElev, printData); break;
         case  3 : testWaypoints(ccode, acLat, acLon, acElev, printData); break;
      }
      std::cout << std::endl;

      std::cout << "1) Test Airport records" << std::endl; 
      std::cout << "2) Test Navaid records" << std::endl; 
      std::cout << "3) Test Waypoint records" << std::endl; 
      std::cout << "select test (0 to end):";
      std::cin >> id;

      if (id > 0) {
         acLat = 41.0;
         acLon = -112.0;
         acElev = 10000.0;
         std::cout << "Use Standard Test Latitude (Salt Lake area): N41.0 deg., Longitude W112.0 deg., Altitude 10000.0 m" << std::endl; 

         std::cout << "Y / N: " ; 
         std::cin >> useStandardTest;

         if (useStandardTest != 'Y' && useStandardTest != 'y') {
            std::cout << "Input aircraft Latitude: " ; 
            std::cin >> acLat;
            std::cout << "Input aircraft Longitude: " ; 
            std::cin >> acLon;
            std::cout << "Input aircraft altitude (meters): " ; 
            std::cin >> acElev;
         }

         std::cout << std::endl;
         std::cout << "Print extra bearing and range data (Y/N):";
         std::cin >> usePrintData;

         if (usePrintData == 'Y' || usePrintData == 'y')
            printData = true;
         else
            printData = false;
      }

   }

   return EXIT_SUCCESS;
}

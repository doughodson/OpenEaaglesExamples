
#include "WaypointTests.hpp"

#include "openeaagles/dafif/WaypointLoader.hpp"
#include "openeaagles/base/util/str_utils.hpp"

#include <iostream>

WaypointTests::WaypointTests(
               const char* country,
               const char* file,
               const char* path)
{
   char fullname[512];
   oe::base::utStrcpy(fullname,512,path);
   oe::base::utStrcat(fullname,512,"/");
   oe::base::utStrcat(fullname,512,file);
   db = new oe::dafif::WaypointLoader();
   db->setPathname(path);
   db->setFilename(file);
   std::cout << "Loading waypoint file: " << fullname << std::endl;
   db->load(country);
   std::cout << "Completed: number of records = " << db->numberOfRecords() << std::endl;
}

WaypointTests::~WaypointTests()
{
   delete db;
}

void WaypointTests::dump()
{
   for (int i = 0; i < db->numberOfRecords(); i++) {
      std::cout << db->record(i) << std::endl;
   }
}

void WaypointTests::func30()
{
   db->printLoaded(std::cout);
}

void WaypointTests::func31(const double acLat, const double acLon, const double acElev, const bool printData)
{
   std::cout << "Enter index (-1 to end):";
   int idx;
   std::cin >> idx;

   while (idx >= 0) {

      oe::dafif::Waypoint* wp = db->waypoint(idx);
      if (wp != 0) {
         wp->printRecord(std::cout);
		 if (printData)
    		 wp->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		 std::cout << std::endl;
      }
      else {
         std::cout << "test -- Nothing" << std::endl;
      }
      wp->unref();

      std::cout << "Enter index (-1 to end):";
      std::cin >> idx;
   }
}

void WaypointTests::func32(const double acLat, const double acLon, const double acElev, const bool printData)
{
   std::cout << "Enter id ('done' to end): ";
   char id[12];
   std::cin >> id;


   while ( strcmp(id,"done") != 0) {

      int found = db->queryByIdent(id);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Waypoint* wp = db->getWaypoint(i);
         wp->printRecord(std::cout);
		 if (printData)
    		 wp->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         wp->unref();
		 std::cout << std::endl;
      }

      std::cout << "Enter id ('done' to end): ";
      std::cin >> id;

   }
}


void WaypointTests::func35(const double acLat, const double acLon, const double acElev, const bool printData)
{
   std::cout << "Ref point is N" << acLat;
   if (acLon < 0.0)
	   std::cout << " W" << -acLon << std::endl;
   else
	   std::cout << " W" << -acLon << std::endl;

   std::cout << "Enter range (0 to end):";
   float rng;
   std::cin >> rng;

   while ( rng > 0.0f ) {

      db->setArea(41.0f, -112.0f, rng);
      int found = db->queryByRange();
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Waypoint* wp = db->getWaypoint(i);
         wp->printRecord(std::cout);
		 if (printData)
    		 wp->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         wp->unref();
		 std::cout << std::endl;
      }

      std::cout << "Enter range (0 to end):";
      std::cin >> rng;

   }
}


void WaypointTests::func36(const double acLat, const double acLon, const double acElev, const bool printData)
{
   std::cout << "Enter key ('done' to end):";
   char key[16];
   std::cin.getline(key,14,'\n');

   while ( strcmp(key,"done") != 0) {

      int found  = db->queryByKey(key);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Waypoint* wp = db->getWaypoint(i);
         wp->printRecord(std::cout);
		 if (printData)
    		 wp->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         wp->unref();
		 std::cout << std::endl;
      }

      std::cout << "Enter key ('done' to end):";
      std::cin.getline(key,14,'\n');

   }
}

void WaypointTests::func3A()
{
   db->printIcaoList(std::cout);
}

void WaypointTests::func3B(const double acLat, const double acLon, const double acElev, const bool printData)
{
   db->setArea(41.0f, -112.0f);

   char code[8];

   std::cout << "Enter code ('done' to end):";
   std::cin >> code;


   while ( strcmp(code,"done") != 0) {

      int found = db->queryByIcao(code);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Waypoint* wp = db->getWaypoint(i);
         wp->printRecord(std::cout);
		 if (printData)
    		 wp->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         wp->unref();
		 std::cout << std::endl;
      }

      std::cout << "Enter code ('done' to end):";
      std::cin >> code;

   }
}


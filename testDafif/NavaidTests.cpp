
#include "NavaidTests.hpp"

#include "openeaagles/dafif/NavaidLoader.hpp"
#include "openeaagles/base/units/Angles.hpp"
#include "openeaagles/base/units/Distances.hpp"
#include "openeaagles/base/util/str_utils.hpp"

#include <iostream>

NavaidTests::NavaidTests(
               const char* country,
               const char* file,
               const char* path)
{
   char fullname[512];
   oe::base::utStrcpy(fullname,512,path);
   oe::base::utStrcat(fullname,512,"/");
   oe::base::utStrcat(fullname,512,file);
   db = new oe::dafif::NavaidLoader();
   db->setPathname(path);
   db->setFilename(file);
   std::cout << "Loading navaid file: " << fullname << std::endl;
   db->load(country);
   std::cout << "Completed: number of records = " << db->numberOfRecords() << std::endl;
}

NavaidTests::~NavaidTests()
{
   delete db;
}

void NavaidTests::dump()
{
   for (int i = 0; i < db->numberOfRecords(); i++) {
      std::cout << db->record(i) << std::endl;
   }
}

// func20	-- DsNavaidLoader; freq list sorting
void NavaidTests::func20()
{
   db->printLoaded(std::cout);
}

// func21	-- DsNavaidLoader.navaid()
void NavaidTests::func21(const double acLat, const double acLon, const double acElev, const bool printData)
{

   std::cout << "Enter index (-1 to end):";
   int idx;
   std::cin >> idx;

   while (idx >= 0) {

      oe::dafif::Navaid* nav = db->navaid(idx);
      if (nav != 0) {
         nav->printRecord(std::cout);
		 if (printData)
    		 nav->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		 std::cout << std::endl;
      }
      else {
        std::cout << "test -- Nothing" << std::endl;
      }
      nav->unref();

      std::cout << "Enter index (-1 to end):";
      std::cin >> idx;
   }
}

// func22	-- DsNavaidLoader.queryByIdent()
void NavaidTests::func22(const double acLat, const double acLon, const double acElev, const bool printData)
{
   std::cout << "Enter id ('done' to end): ";
   char id[8];
   std::cin >> id;
   db->setArea(acLat, acLon);

   while ( strcmp(id,"done") != 0) {

      int found = db->queryByIdent(id);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Navaid* nav = db->getNavaid(i);
         nav->printRecord(std::cout);
		 if (printData)
    		 nav->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         nav->unref();
		 std::cout << std::endl;
      }

      std::cout << "Enter id ('done' to end): ";
      std::cin >> id;
   }
}

// func23	-- DsNavaidLoader; freq list sorting
void NavaidTests::func23()
{
   db->printFreqList(std::cout);
}

// func24	-- DsNavaidLoader.queryByFreq()
void NavaidTests::func24(const double acLat, const double acLon, const double acElev, const bool printData)
{
   std::cout << std::endl << "Ref point is N41.0 W112.0 (Salt Lake area)" << std::endl;

   float freq;
   std::cout << "Enter freq (0 to end):";
   std::cin >> freq;

   while ( freq > 0 ) {

      float mrng;
      std::cout << "Enter max rng (or zero): ";
      std::cin >> mrng;

      db->setArea(acLat, acLon, mrng);

      int found = db->queryByFreq(freq);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Navaid* nav = db->getNavaid(i);
         nav->printRecord(std::cout);
		 if (printData)
    		 nav->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         nav->unref();
		 std::cout << std::endl;
      }

      std::cout << "Enter freq (0 to end):";
      std::cin >> freq;

   }
}

// func25	-- 
void NavaidTests::func25(const double acLat, const double acLon, const double acElev, const bool printData)
{
   std::cout << std::endl << "Ref point is N41.0 W112.0 (Salt Lake area)" << std::endl;

   std::cout << "Enter range (0 to end):";
   float rng;
   std::cin >> rng;

   while ( rng > 0.0f ) {

      db->setArea(acLat, acLon, rng);
      int found = db->queryByRange();
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Navaid* nav = db->getNavaid(i);
         nav->printRecord(std::cout);
		 if (printData)
    		 nav->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         nav->unref();
		 std::cout << std::endl;
      }

      std::cout << "Enter range (0 to end):";
      std::cin >> rng;

   }
}


// func26	-- DsNavaidLoader.queryByKey()
void NavaidTests::func26(const double acLat, const double acLon, const double acElev, const bool printData)
{
   std::cout << "Enter key ('done' to end):";
   char key[10];
   std::cin.getline(key,10,'\n');

   while ( strcmp(key,"done") != 0) {

      int found  = db->queryByKey(key);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Navaid* nav = db->getNavaid(i);
         nav->printRecord(std::cout);
		 if (printData)
    		 nav->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         nav->unref();
		 std::cout << std::endl;
      }

      std::cout << "Enter key ('done' to end):";
      std::cin.getline(key,10,'\n');

   }
}

// func27	-- DsNavaidLoader; channel list sorting
void NavaidTests::func27()
{
   db->printChannelList(std::cout);
}

// func28	-- DsNavaidLoader.queryByChannel()
void NavaidTests::func28(const double acLat, const double acLon, const double acElev, const bool printData)
{
   std::cout << std::endl << "Ref point is N41.0 W112.0 (Salt Lake area)" << std::endl;

   std::cout << "Enter chan (0 to end):";
   long chan;
   std::cin >> chan;

   while ( chan != 0 ) {
   
      float mrng;
      std::cout << "Enter max rng (or zero): ";
      std::cin >> mrng;

      db->setArea(acLat, acLon, mrng);

      int found = db->queryByChannel(chan);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Navaid* nav = db->getNavaid(i);
         nav->printRecord(std::cout);
		 if (printData)
    		 nav->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         nav->unref();
		 std::cout << std::endl;
      }

      std::cout << "Enter chan (0 to end):";
      std::cin >> chan;

   }
}

// func29	-- DsNavaidLoader.queryByType()
void NavaidTests::func29(const double acLat, const double acLon, const double acElev, const bool printData)
{
   float rng;
   char type;

   std::cout << "Enter range (0 to end):";
   std::cin >> rng;

   while ( rng > 0.0f ) {

	  std::cout << "  Posible types: " << std::endl; 
	  std::cout << "                 Z = ANY" << std::endl; 
	  std::cout << "                 1 = VOR" << std::endl; 
	  std::cout << "                 2 = VORTAC" << std::endl; 
	  std::cout << "                 3 = TACAN" << std::endl; 
	  std::cout << "                 4 = VOR_DME" << std::endl; 
	  std::cout << "                 5 = NDB" << std::endl; 
	  std::cout << "                 7 = NDB_DME" << std::endl; 
	  std::cout << "                 9 = DME" << std::endl; 
      std::cout << "Enter type:";
      std::cin >> type;

      db->setArea(acLat, acLon, rng);

      int found = db->queryByType(oe::dafif::Navaid::NavaidType(type));
      std::cout << "found = " << found;
      if (oe::dafif::Navaid::NavaidType(type) == oe::dafif::Navaid::ANY)
		 std::cout << "  any" << std::endl;
      else if (oe::dafif::Navaid::NavaidType(type) == oe::dafif::Navaid::VOR)
		 std::cout << "  VOR" << std::endl;
      else if (oe::dafif::Navaid::NavaidType(type) == oe::dafif::Navaid::VORTAC)
		 std::cout << "  VORTAC" << std::endl;
      else if (oe::dafif::Navaid::NavaidType(type) == oe::dafif::Navaid::TACAN)
		 std::cout << "  TACAN" << std::endl;
      else if (oe::dafif::Navaid::NavaidType(type) == oe::dafif::Navaid::VOR_DME)
		 std::cout << "  VOR_DME" << std::endl;
      else if (oe::dafif::Navaid::NavaidType(type) == oe::dafif::Navaid::NDB)
		 std::cout << "  NDB" << std::endl;
      else if (oe::dafif::Navaid::NavaidType(type) == oe::dafif::Navaid::NDB_DME)
		 std::cout << "  NDB_DME" << std::endl;
      else if (oe::dafif::Navaid::NavaidType(type) == oe::dafif::Navaid::DME)
		 std::cout << "  DME" << std::endl;
      else
		 std::cout << "  ---" << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Navaid* nav = db->getNavaid(i);
         nav->printRecord(std::cout);
		 if (printData)
    		 nav->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		 nav->unref();
		 std::cout << std::endl;
      }

      std::cout << "Enter range (0 to end):";
      std::cin >> rng;
   }
}

// func2A	-- DsNavaidLoader; ICAO list sorting
void NavaidTests::func2A()
{
   db->printIcaoList(std::cout);
}

// func2B	-- DsNavaidLoader.queryByIcao()
void NavaidTests::func2B(const double acLat, const double acLon, const double acElev, const bool printData)
{
   db->setArea(acLat, acLon);

   char code[8];

   std::cout << "Enter code:";
   std::cin >> code;

   while ( strcmp(code,"done") != 0) {

      int found = db->queryByIcao(code);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Navaid* nav = db->getNavaid(i);
         nav->printRecord(std::cout);
		 if (printData)
    		 nav->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         nav->unref();
		 std::cout << std::endl;
      }

      std::cout << "Enter code:";
      std::cin >> code;

   }
}

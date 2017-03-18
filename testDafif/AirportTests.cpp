
#include "AirportTests.hpp"

#include "openeaagles/dafif/AirportLoader.hpp"
#include "openeaagles/base/util/str_utils.hpp"

#include <iostream>

AirportTests::AirportTests(
               const char* country,
               const char* file,
               const char* path)
{
   char fullname[512];
   oe::base::utStrcpy(fullname, 512, path);
   oe::base::utStrcat(fullname, 512, "/");
   oe::base::utStrcat(fullname, 512, file);
   db = new oe::dafif::AirportLoader();
   db->setPathname(path);
   db->setFilename(file);
   std::cout << "Loading airport file: " << fullname << std::endl;
   db->load(country);
   std::cout << "Completed: number of records = " << db->numberOfRecords() << std::endl;
}

AirportTests::~AirportTests()
{
   delete db;
}

void AirportTests::dump()
{
   for (int i = 0; i < db->numberOfRecords(); i++) {
      std::cout << db->record(i) << std::endl;
   }
}

void AirportTests::func00()
{
   db->printLoaded(std::cout);
}

void AirportTests::func00R(const double acLat, const double acLon, const double acElev)
{
   db->setArea(acLat, acLon, 3000.0);

   char id[12];
   std::cout << "Enter id:";
   std::cin >> id;

   while ( strcmp(id,"done") != 0) {

      int found = db->getNumRunwayRecords(id);
      std::cout << "Runways = " << found << std::endl;

      std::cout << "Enter id:";
      std::cin >> id;

   }
}

void AirportTests::func00I(const double acLat, const double acLon, const double acElev)
{
   db->setArea(acLat, acLon, 3000.0);

   char id[12];
   std::cout << "Enter id:";
   std::cin >> id;

   while ( strcmp(id,"done") != 0) {

      int found = db->getNumIlsRecords(id);
      std::cout << "ILS = " << found << std::endl;

      std::cout << "Enter id:";
      std::cin >> id;
   }
}

void AirportTests::func01(const double acLat, const double acLon, const double acElev, const bool printData)
{
   int num;

   std::cout << "Enter num:";
   std::cin >> num;

   while (num >= 0) {

      oe::dafif::Airport* p = db->airport(num);
      if (p != 0) {
         p->printRecord(std::cout);
		 if (printData)
			 p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         std::cout << std::endl;
      }
      else {
         std::cout << "test -- Nothing" << std::endl;
      }
      p->unref();

      std::cout << "Enter num:";
      std::cin >> num;
   }
}

// func01I	-- oe::dafif::AirportLoader.queryIlsByNumber() and getIls()
void AirportTests::func01I(const double acLat, const double acLon, const double acElev, const bool printData)
{
   db->setArea(acLat, acLon);

   char id[12];
   std::cout << "Enter id:";
   std::cin >> id;

   while ( strcmp(id,"done") != 0) {

      int num;
      std::cout << "Enter num:";
      std::cin >> num;

      while (num >= 0) {

         int found = db->queryIlsByNumber(id,num);
         std::cout << "found = " << found << std::endl;

         for (int i = 0; i < found; i++) {
            oe::dafif::Ils* p = db->getIls(i);
            p->printRecord(std::cout);
			if (printData)
			{
		        p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		        if (p->isIlsType(oe::dafif::Ils::GLIDESLOPE))
			        p->printGlideSlopeData(std::cout, acLat, acLon, acElev);
			}
            std::cout << std::endl;
            p->unref();
         }

         std::cout << "Enter num:";
         std::cin >> num;
      }

      std::cout << "Enter id:";
      std::cin >> id;

   }
}

// func01R	-- oe::dafif::AirportLoader.queryRunwayByNumber() and getRunway()
void AirportTests::func01R(const double acLat, const double acLon, const double acElev, const bool printData)
{
   db->setArea(acLat, acLon);

   char id[12];
   std::cout << "Enter id:";
   std::cin >> id;

   while ( strcmp(id,"done") != 0) {

      int num;
      std::cout << "Enter num:";
      std::cin >> num;

      while (num >= 0) {

         int found = db->queryRunwayByNumber(id,num);
         std::cout << "found = " << found << std::endl;

         for (int i = 0; i < found; i++) {
            oe::dafif::Runway* p = db->getRunway(i);
            p->printRecord(std::cout);
			if (printData)
    		    p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
            std::cout << std::endl;
            p->unref();
         }

         std::cout << "Enter num:";
         std::cin >> num;
      }

      std::cout << "Enter id:";
      std::cin >> id;

   }
}

// func02	-- oe::dafif::AirportLoader.queryByIdent()
void AirportTests::func02(const double acLat, const double acLon, const double acElev, const bool printData)
{
   db->setArea(acLat, acLon);

   char id[12];
   std::cout << "Enter id (done to end):";
   std::cin >> id;

   while ( strcmp(id,"done") != 0) {

      int found = db->queryByIdent(id);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Airport* p = db->getAirport(i);
         p->printRecord(std::cout);
		 if (printData)
    		 p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter id (done to end):";
      std::cin >> id;

   }
}

// func02I	-- oe::dafif::AirportLoader.queryIlsByIdent()
void AirportTests::func02I(const double acLat, const double acLon, const double acElev, const bool printData)
{
   db->setArea(acLat, acLon);

   char id[12];
   std::cout << "Enter id (done to end):";
   std::cin >> id;

   while ( strcmp(id,"done") != 0) {

      int found = db->queryIlsByIdent(id);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Ils* p = db->getIls(i);
         p->printRecord(std::cout);
		 if (printData)
		 {
		     p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		     if (p->isIlsType(oe::dafif::Ils::GLIDESLOPE))
			     p->printGlideSlopeData(std::cout, acLat, acLon, acElev);
		 }
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter id (done to end):";
      std::cin >> id;

   }
}

// func02R	-- oe::dafif::AirportLoader.queryRunwayByIdent()
void AirportTests::func02R(const double acLat, const double acLon, const double acElev, const bool printData)
{
   db->setArea(acLat, acLon);

   char id[12];
   std::cout << "Enter id (done to end):";
   std::cin >> id;

   while ( strcmp(id,"done") != 0) {

      int found = db->queryRunwayByIdent(id);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Runway* p = db->getRunway(i);
         p->printRecord(std::cout);
		 if (printData)
		 {
		     p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		     p->printRunwayMagHeading(std::cout, acLat, acLon, acElev);
		 }
         std::cout << std::endl;
		 p->unref();
      }

      std::cout << "Enter id (done to end):";
      std::cin >> id;

   }
}

// func04	-- DsNavaidLoader.queryByFreq(const double acLat, const double acLon, const double acElev)
void AirportTests::func04(const double acLat, const double acLon, const double acElev, const bool printData)
{
   float freq;
   std::cout << "Enter freq:";
   std::cin >> freq;

   while ( freq > 0 ) {

      float mrng;
      std::cout << "Enter max rng (or zero): ";
      std::cin >> mrng;

      db->setArea(acLat, acLon, mrng);

      int found = db->queryByFreq(freq);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Airport* p = db->getAirport(i);
         p->printRecord(std::cout);
		 if (printData)
    		 p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter freq:";
      std::cin >> freq;

   }
}

// func04I	-- DsNavaidLoader.queryIlsByFreq()
void AirportTests::func04I(const double acLat, const double acLon, const double acElev, const bool printData)
{
   float freq;
   std::cout << "Enter freq:";
   std::cin >> freq;

   while ( freq > 0 ) {

      float mrng;
      std::cout << "Enter max rng (or zero): ";
      std::cin >> mrng;

      db->setArea(acLat, acLon, mrng);

      int found = db->queryIlsByFreq(freq);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Ils* p = db->getIls(i);
         p->printRecord(std::cout);
		 if (printData)
		 {
		     p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		     if (p->isIlsType(oe::dafif::Ils::GLIDESLOPE))
			     p->printGlideSlopeData(std::cout, acLat, acLon, acElev);
		 }
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter freq:";
      std::cin >> freq;

   }
}

// func04R	-- DsNavaidLoader.queryRunwayByFreq()
void AirportTests::func04R(const double acLat, const double acLon, const double acElev, const bool printData)
{
   float freq;
   std::cout << "Enter freq:";
   std::cin >> freq;

   while ( freq > 0 ) {

      float mrng;
      std::cout << "Enter max rng (or zero): ";
      std::cin >> mrng;

      db->setArea(acLat, acLon, mrng);

      int found = db->queryRunwayByFreq(freq);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Runway* p = db->getRunway(i);
         p->printRecord(std::cout);
		 if (printData)
		 {
		     p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		     p->printRunwayMagHeading(std::cout, acLat, acLon, acElev);
		 }
         std::cout << std::endl;
		 p->unref();
      }

      std::cout << "Enter freq:";
      std::cin >> freq;

   }
}

// func05	-- oe::dafif::AirportLoader.queryByRange()
void AirportTests::func05(const double acLat, const double acLon, const double acElev, const bool printData)
{
   float rng;

   std::cout << "Enter range:";
   std::cin >> rng;

   while ( rng > 0.0f ) {

      db->setArea(acLat, acLon, rng);

      int found = db->queryByRange();
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Airport* p = db->getAirport(i);
         p->printRecord(std::cout);
		 if (printData)
    		 p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter range:";
      std::cin >> rng;

   }

}

// func05I	-- oe::dafif::AirportLoader.queryIlsByRange()
void AirportTests::func05I(const double acLat, const double acLon, const double acElev, const bool printData)
{
   float rng;

   std::cout << "Enter range:";
   std::cin >> rng;

   while ( rng > 0.0f ) {

      db->setArea(acLat, acLon, rng);

      int found = db->queryIlsByRange();
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Ils* p = db->getIls(i);
         p->printRecord(std::cout);
		 if (printData)
		 {
    		 p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		     if (p->isIlsType(oe::dafif::Ils::GLIDESLOPE))
			     p->printGlideSlopeData(std::cout, acLat, acLon, acElev);
		 }
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter range:";
      std::cin >> rng;

   }

}

// func05R	-- oe::dafif::AirportLoader.queryRunwayByRange()
void AirportTests::func05R(const double acLat, const double acLon, const double acElev, const bool printData)
{
   float rng;

   std::cout << "Enter range:";
   std::cin >> rng;

   while ( rng > 0.0f ) {

      db->setArea(acLat, acLon, rng);

      int found = db->queryRunwayByRange();
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Runway* p = db->getRunway(i);
         p->printRecord(std::cout);
		 if (printData)
		 {
		     p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		     p->printRunwayMagHeading(std::cout, acLat, acLon, acElev);
		 }
         std::cout << std::endl;
         p->unref();
      }
      std::cout << "Enter range:";
      std::cin >> rng;
   }
}

// func06	-- oe::dafif::AirportLoader.queryByKey()
void AirportTests::func06(const double acLat, const double acLon, const double acElev, const bool printData)
{
   char key[16];

   std::cout << "Enter key (done to end):";
   std::cin.getline(key,14,'\n');

   while ( strcmp(key,"done") != 0) {

      int found  = db->queryByKey(key);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Airport* p = db->getAirport(i);
         p->printRecord(std::cout);
		 if (printData)
    		 p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter key (done to end):";
      std::cin.getline(key,14,'\n');

   }
}

// func06I	-- oe::dafif::AirportLoader.queryIlsBySubkey()
void AirportTests::func06I(const double acLat, const double acLon, const double acElev, const bool printData)
{
   char key[34];

   std::cout << "Enter key (done to end):";
   std::cin.getline(key,32,'\n');

   while ( strcmp(key,"done") != 0) {

      int found  = db->queryIlsBySubkey(key);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Ils* p = db->getIls(i);
         p->printRecord(std::cout);
		 if (printData)
		 {
		     p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		     if (p->isIlsType(oe::dafif::Ils::GLIDESLOPE))
			     p->printGlideSlopeData(std::cout, acLat, acLon, acElev);
		 }
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter key (done to end):";
      std::cin.getline(key,32,'\n');

   }
}

// func06R	-- oe::dafif::AirportLoader.queryRunwayBySubkey()
void AirportTests::func06R(const double acLat, const double acLon, const double acElev, const bool printData)
{
   char key[34];

   std::cout << "Enter key (done to end):";
   std::cin.getline(key,32,'\n');

   while ( strcmp(key,"done") != 0) {

      int found  = db->queryRunwayBySubkey(key);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Runway* p = db->getRunway(i);
         p->printRecord(std::cout);
		 if (printData)
		 {
    		 p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		     p->printRunwayMagHeading(std::cout, acLat, acLon, acElev);
		 }
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter key (done to end):";
      std::cin.getline(key,32,'\n');

   }
}

// func07	-- oe::dafif::AirportLoader.queryByLength()
void AirportTests::func07(const double acLat, const double acLon, const double acElev, const bool printData)
{
   float rng;

   std::cout << "Enter range:";
   std::cin >> rng;

   while ( rng > 0.0f ) {

      float rwlen;
      std::cout << "Enter min runway length:";
      std::cin >> rwlen;

      db->setArea(acLat, acLon, rng);

      int found = db->queryByLength(rwlen);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Airport* p = db->getAirport(i);
         p->printRecord(std::cout);
		 if (printData)
    		 p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter range:";
      std::cin >> rng;

   }

}

// func07R	-- oe::dafif::AirportLoader.queryRunwayByLength()
void AirportTests::func07R(const double acLat, const double acLon, const double acElev, const bool printData)
{
   float rng;

   std::cout << "Enter range:";
   std::cin >> rng;

   while ( rng > 0.0f ) {

      float rwlen;
      std::cout << "Enter min runway length:";
      std::cin >> rwlen;

      db->setArea(acLat, acLon, rng);

      int found = db->queryRunwayByLength(rwlen);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Runway* p = db->getRunway(i);
         p->printRecord(std::cout);
		 if (printData)
		 {
		     p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		     p->printRunwayMagHeading(std::cout, acLat, acLon, acElev);
		 }
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter range:";
      std::cin >> rng;
   }
}

// func08	-- DsNavaidLoader.queryByChannel()
void AirportTests::func08(const double acLat, const double acLon, const double acElev, const bool printData)
{
   int chan;
   std::cout << "Enter channel:";
   std::cin >> chan;

   while ( chan > 0 ) {

      float mrng;
      std::cout << "Enter max rng (or zero): ";
      std::cin >> mrng;

      db->setArea(acLat, acLon, mrng);

      int found = db->queryByChannel(chan);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Airport* p = db->getAirport(i);
         p->printRecord(std::cout);
		 if (printData)
    		 p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter channel:";
      std::cin >> chan;

   }
}

// func08I	-- DsNavaidLoader.queryIlsByChannel()
void AirportTests::func08I(const double acLat, const double acLon, const double acElev, const bool printData)
{
   int chan;
   std::cout << "Enter channel:";
   std::cin >> chan;

   while ( chan > 0 ) {

      float mrng;
      std::cout << "Enter max rng (or zero): ";
      std::cin >> mrng;

      db->setArea(acLat, acLon, mrng);

      int found = db->queryIlsByChannel(chan);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Ils* p = db->getIls(i);
         p->printRecord(std::cout);
		 if (printData)
		 {
		     p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
		     if (p->isIlsType(oe::dafif::Ils::GLIDESLOPE))
			     p->printGlideSlopeData(std::cout, acLat, acLon, acElev);
		 }
         std::cout << std::endl;
		 p->unref();
      }
      std::cout << "Enter channel:";
      std::cin >> chan;
   }
}

// func08R	-- DsNavaidLoader.queryRunwayByChannel()
void AirportTests::func08R(const double acLat, const double acLon, const double acElev, const bool printData)
{
   int chan;
   std::cout << "Enter channel:";
   std::cin >> chan;

   while ( chan > 0 ) {

      float mrng;
      std::cout << "Enter max rng (or zero): ";
      std::cin >> mrng;

      db->setArea(acLat, acLon, mrng);

      int found = db->queryRunwayByChannel(chan);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Runway* p = db->getRunway(i);
         p->printRecord(std::cout);
		 if (printData)
    		 p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         std::cout << std::endl;
         p->unref();
      }
      std::cout << "Enter channel:";
      std::cin >> chan;
   }
}


// func09	-- oe::dafif::AirportLoader.queryByType()
void AirportTests::func09(const double acLat, const double acLon, const double acElev, const bool printData)
{
   float rng;
   unsigned char type;

   std::cout << "Enter range:";
   std::cin >> rng;

   while ( rng > 0.0f ) {

	  std::cout << "  Possible types:" << std::endl; 
	  std::cout << "                  Z = ANY" << std::endl; 
	  std::cout << "                  A = CIVIL" << std::endl; 
	  std::cout << "                  B = JOINT" << std::endl; 
	  std::cout << "                  C = MILITARY" << std::endl; 
	  std::cout << "                  D = INACTIVE" << std::endl; 
      std::cout << "Enter type:";
      std::cin >> type;

      db->setArea(acLat, acLon, rng);


      int found = db->queryByType(oe::dafif::Airport::AirportType(type));
      std::cout << "found = " << found;
	  
	  if (oe::dafif::Airport::AirportType(type) == oe::dafif::Airport::ANY)
		  std::cout << "  ANY Airports" << std::endl;
	  else if (oe::dafif::Airport::AirportType(type) == oe::dafif::Airport::CIVIL)
		  std::cout << "  CIVIL Airports" << std::endl;
	  else if (oe::dafif::Airport::AirportType(type) == oe::dafif::Airport::JOINT)
		  std::cout << "  JOINT Airports" << std::endl;
	  else if (oe::dafif::Airport::AirportType(type) == oe::dafif::Airport::MILITARY)
		  std::cout << "  MILITARY Airports" << std::endl;
	  else if (oe::dafif::Airport::AirportType(type) == oe::dafif::Airport::INACTIVE)
		  std::cout << "  INACTIVE Airports" << std::endl;
	  else
		  std::cout << "  UNDEFINED" << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Airport* p = db->getAirport(i);
         p->printRecord(std::cout);
		 if (printData)
    		 p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         std::cout << std::endl;
         p->unref();
      }
      std::cout << "Enter range:";
      std::cin >> rng;
   }
}

// func09I	-- oe::dafif::AirportLoader.queryIlsByType()
void AirportTests::func09I(const double acLat, const double acLon, const double acElev, const bool printData)
{
   float rng(0.0);
   unsigned char type;

   std::cout << "Enter range:";
   std::cin >> rng;

   while ( rng > 0.0f ) {

	  std::cout << "  Posible types:" << std::endl; 
	  std::cout << "                 Y  = ANY" << std::endl; 
	  std::cout << "                 L  = LOCATOR" << std::endl; 
	  std::cout << "                 D  = DME" << std::endl; 
	  std::cout << "                 Z  = LOCALIZER" << std::endl; 
	  std::cout << "                 B  = BACKCOURSE_MARKER" << std::endl; 
	  std::cout << "                 G  = GLIDESLOPE" << std::endl; 
	  std::cout << "                 I  = INNER_MARKER" << std::endl; 
	  std::cout << "                 M  = MIDDLE_MARKER" << std::endl; 
	  std::cout << "                 O  = OUTER_MARKER" << std::endl; 
	  std::cout << "                 U  = UNKNOWN" << std::endl; 
      std::cout << "Enter type:";
      std::cin >> type;

      db->setArea(acLat, acLon, rng);

      int found = db->queryIlsByType(oe::dafif::Ils::IlsType(type));
      std::cout << "found = " << found;
	  if (oe::dafif::Ils::IlsType(type) == oe::dafif::Ils::ANY)
		  std::cout << "  ANY ILS Aids" << std::endl;
	  else if (oe::dafif::Ils::IlsType(type) == oe::dafif::Ils::LOCATOR)
		  std::cout << "  LOCATOR ILS Aids" << std::endl;
	  else if (oe::dafif::Ils::IlsType(type) == oe::dafif::Ils::DME)
		  std::cout << "  DME ILS Aids" << std::endl;
	  else if (oe::dafif::Ils::IlsType(type) == oe::dafif::Ils::LOCALIZER)
		  std::cout << "  LOCALIZER ILS Aids" << std::endl;
	  else if (oe::dafif::Ils::IlsType(type) == oe::dafif::Ils::GLIDESLOPE)
		  std::cout << "  GLIDESLOPE ILS Aids" << std::endl;
	  else if (oe::dafif::Ils::IlsType(type) == oe::dafif::Ils::BACKCOURSE_MARKER)
		  std::cout << "  BACKCOURSE_MARKER ILS Aids" << std::endl;
	  else if (oe::dafif::Ils::IlsType(type) == oe::dafif::Ils::INNER_MARKER)
		  std::cout << "  INNER_MARKER ILS Aids" << std::endl;
	  else if (oe::dafif::Ils::IlsType(type) == oe::dafif::Ils::MIDDLE_MARKER)
		  std::cout << "  MIDDLE_MARKER ILS Aids" << std::endl;
	  else if (oe::dafif::Ils::IlsType(type) == oe::dafif::Ils::OUTER_MARKER)
		  std::cout << "  OUTER_MARKER ILS Aids" << std::endl;
	  else if (oe::dafif::Ils::IlsType(type) == oe::dafif::Ils::UNKNOWN)
		  std::cout << "  UNKNOWN ILS Aids" << std::endl;
	  else
		  std::cout << "  UNDEFINE" << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Ils* p = db->getIls(i);
         p->printRecord(std::cout);
		 if (printData)
		 {
    		 p->printTrueBearingRange(std::cout, acLat, acLon, acElev);
	    	 if (p->isIlsType(oe::dafif::Ils::GLIDESLOPE))
				 p->printGlideSlopeData(std::cout, acLat, acLon, acElev);
		 }
         std::cout << std::endl;
         p->unref();
      }

      std::cout << "Enter range:";
      std::cin >> rng;

   }

}

// func0A	-- oe::dafif::AirportLoader; ICAO list sorting
void AirportTests::func0A()
{
   db->printIcaoList(std::cout);
}

// func0B	-- oe::dafif::AirportLoader.queryByIcao()
void AirportTests::func0B(const double acLat, const double acLon, const double acElev, const bool printData)
{
   db->setArea(acLat, acLon);

   char code[8];

   std::cout << "Enter code:";
   std::cin >> code;

   while ( strcmp(code, "done") != 0) {

      int found = db->queryByIcao(code);
      std::cout << "found = " << found << std::endl;

      for (int i = 0; i < found; i++) {
         oe::dafif::Airport* ap = db->getAirport(i);
         ap->printRecord(std::cout);
		 if (printData)
    		 ap->printTrueBearingRange(std::cout, acLat, acLon, acElev);
         std::cout << std::endl;
         ap->unref();
      }
      std::cout << "Enter code:";
      std::cin >> code;
   }
}



#include <QApplication>

#include "MainWindow.h"
#include "Station.h"

#include "openeaagles/base/parser.h"
#include "openeaagles/base/factory.h"
#include "openeaagles/base/Pair.h"
#include "openeaagles/simulation/factory.h"

#include <cstdlib>
#include <cstring>

namespace example {

// The main station
Station* station = nullptr;

// our class factory
oe::base::Object* factory(const char* name)
{
    oe::base::Object* obj = nullptr;

    // This test ...
    if ( std::strcmp(name, Station::getFactoryName()) == 0 ) {
        obj = new Station;
    }

    else {
        if (obj == nullptr) obj = oe::simulation::factory(name);
        if (obj == nullptr) obj = oe::base::factory(name);
    }
    return obj;
}

// build a display
void builder(const char* const testFileName)
{
    // Read the description file
    int errors = 0;
    oe::base::Object* q1 = oe::base::edlParser(testFileName, factory, &errors);
    if (errors > 0) {
        std::cerr << "Errors in reading file: " << errors << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // Set 'station' to our basic description object.
    station = nullptr;
    if (q1 != nullptr) {

        // When we were given a Pair, get the pointer to its object.
        oe::base::Pair* pp = dynamic_cast<oe::base::Pair*>(q1);
        if (pp != nullptr) {
           std::cout << "Factory: " << *pp->slot() << std::endl;
           q1 = pp->object();
        }

        // What we should have here is the description object and
        // it should be of type 'Station'.
        station = dynamic_cast<Station*>(q1);
    }

    // Make sure we did get a valid object (we must have one!)
    if (station == nullptr) {
        std::cout << "Invalid description file!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    //station->serialize(std::cout);
}

int main(int argc, char* argv[])
{
   const char* fileName = "test.edl";

   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i], "-f") == 0) {
         fileName = argv[++i];
      }
   }

   char fileNames[80];

#if !defined(WIN32)
   const char* funcCall = "cpp ";
   std::strcpy(fileNames, funcCall);
   std::strcat(fileNames, "configs/");
   if (std::strlen(fileName) < 60){
      std::strcat(fileNames, fileName);
      std::strcpy(fileNames + strlen(fileNames)-2, "pp");
   }
   std::strcat(fileNames, ">");
   std::strcat(fileNames, fileName);
   funcCall = fileNames;
   std::cout << "Precompiling: " << fileName << std::endl;
   std::cout << funcCall << std::endl;
   system(funcCall);
#endif

   builder(fileName);

   // prime the station
   station->event(oe::base::Component::RESET_EVENT);

   // create the time critical process
   station->createTimeCriticalProcess();
   station->createWindow(argc, argv);

   return 0;
}

}

int main(int argc, char* argv[])
{
   return example::main(argc, argv);
}

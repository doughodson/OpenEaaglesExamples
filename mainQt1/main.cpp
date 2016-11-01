
#include <QApplication>

#include "MainWindow.hpp"
#include "Station.hpp"

#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/base/factory.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/simulation/factory.hpp"

#include <cstdlib>
#include <string>

// class factory
oe::base::Object* factory(const std::string& name)
{
   oe::base::Object* obj = nullptr;

   if ( name == Station::getFactoryName() ) {
      obj = new Station;
   }

   if (obj == nullptr)  { obj = oe::simulation::factory(name);  }
   if (obj == nullptr)  { obj = oe::base::factory(name);        }
   return obj;
}

// Station builder
Station* builder(const std::string& filename)
{
   // Read the description file
   unsigned int num_errors = 0;
   oe::base::Object* obj = oe::base::edl_parser(filename, factory, &num_errors);
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
   oe::base::Pair* pair = dynamic_cast<oe::base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   Station* station = dynamic_cast<Station*>(obj);
   if (station == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return station;
}

void compile_edl(const std::string& filename)
{
#if !defined(WIN32)
   std::string func_call = "cpp configs/" + filename;        // cpp configs/test.edl
   func_call = func_call.substr(0, func_call.length() - 2);  // cpp configs/test.e
   func_call = func_call + "pp > " + filename;               // cpp configs/test.epp > test.edl
   std::cout << "Compiling: " << filename << std::endl;
   system(func_call.c_str());
#endif

   return;
}

int main(int argc, char* argv[])
{
   // default configuration filename
   std::string configFilename = "test.edl";
   // parse arguments
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   compile_edl(configFilename);

   Station* station = builder(configFilename);

   // prime the station
   station->event(oe::base::Component::RESET_EVENT);

   // create the time critical process
   station->createTimeCriticalProcess();
   station->createWindow(argc, argv);

   return 0;
}

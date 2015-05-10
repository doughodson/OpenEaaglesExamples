
//
#include "Application.h"
#include "MainWindow.h"
#include "FoxStation.h"
#include "FoxDisplay.h"
#include "Worm.h"

#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"

// class factories
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/basic/Factory.h"

#include <cstring>
#include <cstdlib>

namespace Eaagles {
namespace Example {

static FoxStation* foxStation = nullptr;

// our class factory
static Basic::Object* factory(const char* name)
{
   Basic::Object* obj = nullptr;

   if ( std::strcmp(name, FoxDisplay::getFactoryName()) == 0 ) {
      obj = new FoxDisplay();
   }
   else if ( std::strcmp(name, FoxStation::getFactoryName()) == 0 ) {
      obj = new FoxStation();
   }
   else if ( std::strcmp(name, Worm::getFactoryName()) == 0 ) {
      obj = new Worm();
   }

   if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
   if (obj == nullptr) obj = Basic::Factory::createObj(name);

   return obj;
}

// FOX station builder
static FoxStation* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   Basic::Object* obj = Basic::lcParser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a Basic::Pair, if so, point to object in Pair, not Pair itself
   Basic::Pair* pair = dynamic_cast<Basic::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   FoxStation* foxStation = dynamic_cast<FoxStation*>(obj);
   if (foxStation == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return foxStation;
}

//
int main(int argc, char* argv[])
{
   // default configuration filename
   const char* configFilename = "testfox.edl";
   // set optional input file
   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i],"-f") == 0) {
         configFilename = argv[++i];
      }
   }
   // build a station
   foxStation = builder(configFilename);

   // send a reset pulse to station
   foxStation->event(Basic::Component::RESET_EVENT);
   // start real-time thread
   foxStation->createTimeCriticalProcess();

   // create Fox application object
   // this will be our non-real-time main loop
   Application application("Application", "FoxDefault");

   // it needs a station pointer to call updateData()
   application.setStation(foxStation);

   // initialize Fox and setup non-real-time timer
   application.init(argc,argv);

   // create our main window (a Fox FXMainWindow) which
   // handles GUI events
   MainWindow* mainWindow = new MainWindow(&application);

   // create the application's windows
   application.create();

   // enter main loop
   return application.run();

   // cleanup
   delete mainWindow;
}

} // end Example namespace
} // end Eaagles namespace


//
int main(int argc, char* argv[])
{
  Eaagles::Example::main(argc, argv);
}

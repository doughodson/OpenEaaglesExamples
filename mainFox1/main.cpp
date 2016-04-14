
//
#include "Application.h"
#include "MainWindow.h"
#include "FoxStation.h"
#include "FoxDisplay.h"
#include "Worm.h"

#include "openeaagles/base/edl_parser.h"
#include "openeaagles/base/Pair.h"

// factories
#include "openeaagles/graphics/factory.h"
#include "openeaagles/base/factory.h"

#include <string>
#include <cstdlib>

namespace oe {
namespace example {

FoxStation* foxStation = nullptr;

// our class factory
base::Object* factory(const std::string& name)
{
   base::Object* obj = nullptr;

   if ( name == FoxDisplay::getFactoryName() ) {
      obj = new FoxDisplay();
   }
   else if ( name == FoxStation::getFactoryName() ) {
      obj = new FoxStation();
   }
   else if ( name == Worm::getFactoryName() ) {
      obj = new Worm();
   }

   if (obj == nullptr) obj = graphics::factory(name);
   if (obj == nullptr) obj = base::factory(name);

   return obj;
}

// FOX station builder
FoxStation* builder(const std::string& filename)
{
   // read configuration file
   unsigned int errors = 0;
   base::Object* obj = base::edl_parser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   base::Pair* pair = dynamic_cast<base::Pair*>(obj);
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
   std::string configFilename = "testfox.edl";
   // set optional input file
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }
   // build a station
   foxStation = builder(configFilename);

   // send a reset pulse to station
   foxStation->event(base::Component::RESET_EVENT);
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

} // end example namespace
} // end oe namespace

//
int main(int argc, char* argv[])
{
  oe::example::main(argc, argv);
}

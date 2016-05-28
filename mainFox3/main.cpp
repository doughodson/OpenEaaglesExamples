
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

oe::base::Object* factory(const std::string& name)
{
   oe::base::Object* obj = nullptr;

   if ( name == FoxDisplay::getFactoryName() ) {
      obj = new FoxDisplay();
   }
   else if ( name == FoxStation::getFactoryName() ) {
      obj = new FoxStation();
   }
   else if ( name == Worm::getFactoryName() ) {
      obj = new Worm();
   }

   if (obj == nullptr) obj = oe::graphics::factory(name);
   if (obj == nullptr) obj = oe::base::factory(name);

   return obj;
}

FoxStation* builder(const std::string& filename)
{
   // read configuration file
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
   FoxStation* station = dynamic_cast<FoxStation*>(obj);
   if (station == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return station;
}

int main(int argc, char* argv[])
{
   // default configuration filename
   std::string configFilename = "foxstation.edl";
   // set optional input file
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   // build a station
   FoxStation* foxStation = builder(configFilename);

   // send a reset pulse to station
   foxStation->event(oe::base::Component::RESET_EVENT);
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

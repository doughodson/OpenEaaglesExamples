
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

namespace Eaagles {
namespace Example {

// default configuration file
static const char* const DEFAULT_CONFIG_FILE = "testfox.edl";
static const char* fileName = DEFAULT_CONFIG_FILE;

static FoxStation* station = 0;

// our class factory
static Basic::Object* factory(const char* name)
{
  Basic::Object* obj = 0;

  if ( strcmp(name, FoxDisplay::getFactoryName()) == 0 ) {
    obj = new FoxDisplay();
  }
  else if ( strcmp(name, FoxStation::getFactoryName()) == 0 ) {
    obj = new FoxStation();
  }
  else if ( strcmp(name, Worm::getFactoryName()) == 0 ) {
    obj = new Worm();
  }

  if (obj == 0) obj = BasicGL::Factory::createObj(name);
  if (obj == 0) obj = Basic::Factory::createObj(name);

  return obj;
}

// build a station
static void builder(const char* const name)
{
   // Read the description file
   int errors = 0;
   Basic::Object* q1 = Basic::lcParser(name, factory, &errors);
   if (errors > 0) {
      std::cerr << "Errors in reading file: " << errors << std::endl;
      q1 = 0;
   }

   if (q1 != 0) {
      // When we were given a Pair, get the pointer to its object.
      Basic::Pair* pp = dynamic_cast<Basic::Pair*>(q1);
      if (pp != 0) {
         q1 = pp->object();
      }
      // What we should have here is the description object and
      // it should be of type 'Station'.
      station = dynamic_cast<FoxStation*>(q1);
   }

   // Make sure we did get a valid Station object (we must have one!)
   if (station == 0) {
      std::cout << "Invalid description file!" << std::endl;
      exit(EXIT_FAILURE);
   }
}

int exec(int argc, char* argv[])
{
   // set optional input file
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i],"-f") == 0) {
         fileName = argv[++i];
      }
   }

   // build a station
   builder(fileName);

   // send a reset pulse to station
   station->event(Basic::Component::RESET_EVENT);
   // start real-time thread
   station->createTimeCriticalProcess();

   // create Fox application object
   // this will be our non-real-time main loop
   Application application("Application", "FoxDefault");

   // it needs a station pointer to call updateData()
   application.setStation(station);

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


//-----------------------------------------------------------------------------
// main()
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  Eaagles::Example::exec(argc, argv);
}

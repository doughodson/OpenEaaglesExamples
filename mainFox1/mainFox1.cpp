
//
#include "Application.h"
#include "MainWindow.h"
#include "FoxStation.h"
#include "FoxDisplay.h"
#include "Worm.h"

#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"

#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/basic/basicFF.h"

namespace Eaagles {
namespace mainFox {

// default configuration file
static const char* const DEFAULT_CONFIG_FILE = "testfox.edl";
static const char* fileName = DEFAULT_CONFIG_FILE;

static FoxStation* station = 0;	

static Basic::Object* formFunc(const char* formname)
{
  Basic::Object* newform = 0;

  if ( strcmp(formname, FoxDisplay::getFormName()) == 0 ) {
    newform = new FoxDisplay();
  }
  else if ( strcmp(formname, FoxStation::getFormName()) == 0 ) {
    newform = new FoxStation();
  }
  else if ( strcmp(formname, Worm::getFormName()) == 0 ) {
    newform = new Worm();
  }

  if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
  if (newform == 0) newform = Basic::basicFormFunc(formname);

  return newform;
}

static void readConfigFile(const char* const name)
{
   // Read the description file
   int errors = 0;
   Basic::Object* q1 = Basic::lcParser(name, formFunc, &errors);
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

   // read input file to define the station
   readConfigFile(fileName);

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

} // end mainFox namespace
} // end Eaagles namespace


//-----------------------------------------------------------------------------
// main()
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  Eaagles::mainFox::exec(argc, argv);
}

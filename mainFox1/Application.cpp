
#include "Application.h"
#include "Display.h"
#include "Station.h"

#include "formFunc.h"

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace mainFox {

// Display refresh rate (hz)
const FXuint DRAW_FRAME_RATE = 50;
const char* fileName = "testfox.edl";

// Message Map 
FXDEFMAP(Application) AppMap[] = {
  //_Message_Type__________ID______________________________________Message_Handler__________________
  FXMAPFUNC(SEL_TIMEOUT,   Application::ID_TIMEOUT,                Application::onTimeout),
};

// Macro for the Application class hierarchy implementation
FXIMPLEMENT(Application,FXApp,AppMap,ARRAYNUMBER(AppMap))

Application::Application(const FXString& name, const FXString& vendor) : FXApp(name, vendor)
{
  station = 0;
}

// Destructor
Application::~Application()
{
  //removeTimeout(this,ID_TIMEOUT);
  //if (station != 0) {
  //  station->unref();
  //}
  //station = 0;
}

void Application::init(int& argc, char** argv, bool connect)
{
  FXApp::init(argc, argv, connect);

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i],"-f") == 0) {
      fileName = argv[++i];
    }
  }

  station = readConfigFile(fileName);

  if (station != 0) {
//    station->setApplication(this);
    station->event(Basic::Component::RESET_EVENT);
    station->createTimeCriticalProcess();
  }

  // Schedule for display refresh
  double dt0 = 1.0/double(DRAW_FRAME_RATE);
  unsigned int millis = (unsigned int)(dt0 * 1000);
  addTimeout(this,ID_TIMEOUT,millis);
}

// readConfigFile() -- function to the read configutation description file
Station* Application::readConfigFile(const char* const name)
{
  Station* sys = 0;	

  // Read the description file
  int errors = 0;
  Basic::Object* q1 = Basic::lcParser(name, mainFoxFormFunc, &errors);
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
    sys = dynamic_cast<Station*>(q1);
  }

  // Make sure we did get a valid object (we must have one!)
  if (sys == 0) {
    std::cerr << "Invalid description file!" << std::endl;
  }

  return sys;
}

// when we timeout
long Application::onTimeout(FXObject*,FXSelector,void*)
{
  // ---
  // Reschedule the display refresh timer
  // ---
  double dt0 = 1.0/double(DRAW_FRAME_RATE);
  unsigned int millis = (unsigned int)(dt0 * 1000);
  addTimeout(this,ID_TIMEOUT,millis);

  // ---
  // Compute delta time
  // ---

  double time = getComputerTime(); // Current time
  static double time0 = time;      // N-1 time
  double dt = time - time0;
  if (dt < 0) {
    dt = 0;
  }
  time0 = time;
   
  // ---
  // Update station data (background thread)
  // and get the current status display data.
  // ---
  if (station != 0) {
    station->updateData((LCreal)dt);
  }

  // ---
  // Draw the FOX displays
  // ---
  if (station != 0) {
    if (station->getMainDisplay() != 0) {
      station->getMainDisplay()->drawIt();
    }
  }
  return 1;
}

} // end mainFox namespace
} // end Eaagles namespace


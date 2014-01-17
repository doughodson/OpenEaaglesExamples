
#include "Application.h"
#include "FoxDisplay.h"
#include "FoxStation.h"

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace Example {

// display refresh rate (hz)
static const FXuint DRAW_FRAME_RATE = 50;

// Message Map 
FXDEFMAP(Application) AppMap[] = {
  //_Message_Type__________ID______________________________________Message_Handler__________________
  FXMAPFUNC(SEL_TIMEOUT,   Application::ID_TIMEOUT,                Application::onTimeout),
};

// Macro for the Application class hierarchy implementation
FXIMPLEMENT(Application,FXApp,AppMap,ARRAYNUMBER(AppMap))

Application::Application(const FXString& name, const FXString& vendor) : FXApp(name, vendor)
{
}

Application::~Application()
{
   if (station!=0) { station->unref(); station = 0; }
}

void Application::init(int& argc, char** argv, bool connect)
{
   FXApp::init(argc, argv, connect);

   // schedule a timer for display refresh
   double dt0 = 1.0/double(DRAW_FRAME_RATE);
   unsigned int millis = (unsigned int)(dt0 * 1000);
   addTimeout(this,ID_TIMEOUT,millis);
}

// when we timeout
long Application::onTimeout(FXObject*,FXSelector,void*)
{
   // ---
   // reschedule the display refresh timer
   // ---
   double dt0 = 1.0/double(DRAW_FRAME_RATE);
   unsigned int millis = (unsigned int)(dt0 * 1000);
   addTimeout(this,ID_TIMEOUT,millis);

   // ---
   // compute delta time
   // ---
   double time = getComputerTime(); // Current time
   static double time0 = time;      // N-1 time
   double dt = time - time0;
   if (dt < 0) {
      dt = 0;
   }
   time0 = time;
   
   // ---
   // update station data (background thread)
   // and get the current status display data.
   // ---
   station->updateData((LCreal)dt);

   // ---
   // draw the FOX displays
   // ---
   if (station->getMainDisplay() != 0) {
      station->getMainDisplay()->drawIt();
   }
   return 1;
}

} // end Example namespace
} // end Eaagles namespace


#include "Application.h"
#include "FoxDisplay.h"
#include "FoxStation.h"

#include "openeaagles/base/Pair.h"
#include "openeaagles/graphics/Graphic.h"
#include "openeaagles/base/util/system.h"

// message map
FXDEFMAP(Application) AppMap[] = {
   //________Message_Type_____ID______________________________Message_Handler_______
   FXMAPFUNC(SEL_CHORE,       Application::ID_CHORE,          Application::onChore)
};

// Macro for the Application class hierarchy implementation
FXIMPLEMENT(Application, FXApp, AppMap, ARRAYNUMBER(AppMap))

Application::Application(const FXString& name, const FXString& vendor) : FXApp(name, vendor)
{
   station = nullptr;
}

Application::~Application()
{
   if (station!=nullptr) {
      station->unref();
      station = nullptr;
   }
}

void Application::init(int& argc, char** argv, bool connect)
{
   FXApp::init(argc, argv, connect);

   // schedule a timer for display refresh
//   const double dt0 = 1.0 / static_cast<double>(DRAW_FRAME_RATE);
//   const unsigned int millis = static_cast<unsigned int>(dt0 * 1000);
   //addTimeout(this, ID_TIMEOUT, millis);
   addChore(this, ID_CHORE);
}

// when we timeout
long Application::onChore(FXObject*, FXSelector, void*)
{
   std::cout << "onChore called!!\n";

   static FXTime lt_nsecs(FXThread::time());     // last time in nanoseconds
   const FXTime ct_nsecs = FXThread::time();     // current  time nanoseconds since Epoch (Jan 1, 1970)
   const FXTime dt_nsecs = ct_nsecs - lt_nsecs;  // delta time difference from last time
   lt_nsecs = FXThread::time();

   const double dt_msecs = static_cast<double>(dt_nsecs) / 1000000.0;
   const double dt_secs = dt_msecs / 1000.0;

   std::cout << "dt_nsecs: " << dt_nsecs << std::endl;
   std::cout << "dt_msecs: " << dt_msecs << std::endl;
   std::cout << "dt_secs: " << dt_secs << std::endl;

   // ---
   // reschedule the display refresh timer
   // ---
//   const double dt0 = 1.0/static_cast<double>(DRAW_FRAME_RATE);
//   const unsigned int millis = static_cast<unsigned int>(dt0 * 1000);
   //addTimeout(this, ID_TIMEOUT, millis);

   addChore(this, ID_CHORE);

   // ---
   // compute delta time
   // ---
//   const double time = oe::base::getComputerTime(); // Current time
//   static double time0 = time;      // N-1 time
//   double dt = time - time0;
//   if (dt < 0) {
//      dt = 0;
//   }
//   time0 = time;

   // ---
   // update station data (background thread)
   // and get the current status display data.
   // ---
//   station->updateData(static_cast<double>(dt));
   station->updateData(dt_secs);

   // ---
   // draw the FOX displays
   // ---
//   if (station->getMainDisplay() != nullptr) {
//      station->getMainDisplay()->drawIt();
//   }

   if (station->getMainDisplay() != nullptr) {
      station->getMainDisplay()->drawIt();
   }

   return 1;
}

void Application::setStation(FoxStation* x)
{
   if (station != nullptr) {
      station->unref();
   }
   station = x;
   station->ref();
}

FoxStation* Application::getStation()
{
   return station;
}

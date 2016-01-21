//------------------------------------------------------------------------------
// Class: Application
//
// Description: Application class which processes GUI events
//------------------------------------------------------------------------------
#ifndef __oe_example_Application_H__
#define __oe_example_Application_H__

#include "fx.h"

#include "FoxStation.h"

namespace oe {

namespace example {

class Station;

class Application : public FX::FXApp {

   FXDECLARE(Application)

public:

   // We define additional ID's, starting from the last one used by the base class+1.
   // This way, we know the ID's are all unique for this particular target.
   enum {
      ID_TIMEOUT=FX::FXApp::ID_LAST,      // Timer ID
      ID_LAST,
   };

public:

   Application(const FXString& name, const FXString& vendor);
   virtual ~Application();

   // FXApp interface
   virtual void init(int& argc, char** argv, bool connect=true);

   // Message handlers
   long onTimeout(FXObject*, FXSelector, void*);

   void setStation(FoxStation* s);
   FoxStation* getStation();

protected:

   Application() {}

private:

  FoxStation* station;
};

} // end example namespace
} // end oe namespace

#endif

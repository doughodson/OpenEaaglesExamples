//------------------------------------------------------------------------------
// Class: Application
//
// Description: Application class which processes GUI events
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_Application_H__
#define __Eaagles_Example_Application_H__

#include "fx.h"

#include "FoxStation.h"

namespace Eaagles {

namespace Example {

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
   long onTimeout(FXObject*,FXSelector,void*);

   void setStation(FoxStation* s);
   FoxStation* getStation();

protected:

   Application() {}

private:

  FoxStation* station;
};

} // end Example namespace
} // end Eaagles namespace

#endif

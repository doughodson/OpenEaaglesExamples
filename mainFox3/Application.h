
#ifndef __Application_H__
#define __Application_H__

#include "FoxStation.h"

#include "fx.h"

namespace oe {
namespace simulation {
   class Station;
}
}

//------------------------------------------------------------------------------
// Class: Application
//
// Description: Application class which manages an oe Station and processes
//              GUI events
//------------------------------------------------------------------------------
class Application : public FX::FXApp
{
   FXDECLARE(Application)

public:

   // We define additional ID's, starting from the last one used by the base class+1.
   // This way, we know the ID's are all unique for this particular target.
   enum {
      ID_CHORE=FX::FXApp::ID_LAST,
      ID_LAST,
   };

public:

   Application(const FXString& name, const FXString& vendor);
   virtual ~Application();

   // FXApp interface
   virtual void init(int& argc, char** argv, bool connect=true);

   // message handlers
   long onChore(FXObject*, FXSelector, void*);

   void setStation(FoxStation* s);
   FoxStation* getStation();

protected:

   Application() {}

private:

  FoxStation* station;
};

#endif

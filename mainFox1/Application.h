
// Application class, which handles the data events between Fox and Eaagles displays

#include "fx.h"

namespace Eaagles {

namespace Basic {
  class Object;
}

namespace mainFox {

class Station;

class Application : public FX::FXApp {

  FXDECLARE(Application)

public: 
  // We define additional ID's, starting from the last one used by the base class+1.
  // This way, we know the ID's are all unique for this particular target.
  enum{
    ID_TIMEOUT=FX::FXApp::ID_LAST,      // Timer ID
    ID_LAST,
  };

public:
  Application(const FXString& name, const FXString& vendor);
  virtual ~Application();
   
  // Message handlers
  long onTimeout(FXObject*,FXSelector,void*);
    
  // FXApp interface
  virtual void init(int& argc, char** argv, bool connect=true);
    
  Station* getStation() { return station; }
	    
protected:

  Application() {}

private:

  // read configuration file
  Station* readConfigFile(const char* const fileName = "testfox.eil");
    
  Station* station;        // holds our station

};

} // end mainFox namespace
} // end Eaagles namespace


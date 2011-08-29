
//
#include "Application.h"
#include "MainWindow.h"

namespace Eaagles {
namespace mainFox {

int exec(int argc, char* argv[])
{
    // create a Fox application object
    Application application("Application","FoxDefault");

    // initialize Fox and read in OpenEaagles EIL input file which will create
    // a FoxStation object, which creates a FoxDisplay.
    application.init(argc,argv);
 
    // create our main window (a Fox FXMainWindow) which serves
    // as an event handler between Fox GUI events and OpenEaagles   
    new MainWindow(&application);

    // create the application's windows
    application.create();

    // Run the application
    return application.run();
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


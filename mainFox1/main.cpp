
#include "fx.h"

#include "TestWindow.h"

int main(int argc, char* argv[])
{
   // application object
   FXApp application("GLTest", "FoxTest");

   // init application and open display (no actual window will open)
   application.init(argc, argv);

   // create main/central window for the application
   // associate it with application
   new TestWindow(&application);

   // create application's windows
   application.create();

   // start event loop
   return application.run();
}

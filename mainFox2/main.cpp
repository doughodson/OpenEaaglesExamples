

#include "fx.h"
#include "fx3d.h"

#include "GLSettingsDialog.h"
#include "GLTestWindow.h"

int main(int argc,char *argv[]){
  
  // Make application
  FXApp application("GLTest","FoxTest");

  // Open the display
  application.init(argc,argv);

  // Make window
  new GLTestWindow(&application);

  // Create the application's windows
  application.create();

  // Run the application
  return application.run();
}


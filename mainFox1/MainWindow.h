//------------------------------------------------------------------
// Class:  FX::FXMainWindow -> Eaagles::Fox::MainWindow
//
// Description: Eaagles version of a Fox MainWindow, understands
// Eaagles::mainFox::Application and Eaagles::mainFox::Display
//
//------------------------------------------------------------------

#include "fx.h"

namespace Eaagles {
namespace mainFox {

class Application;
class Display;  
class Station;

//
// maps events between Fox and OpenEaagles
//
class MainWindow : public FX::FXMainWindow {

  FXDECLARE(MainWindow)

public:

  MainWindow(Application* a);
  virtual ~MainWindow();

  // initialize
  void create();

public:

  // We define additional ID's, starting from the last one used by the base class+1.
  // This way, we know the ID's are all unique for this particular target.
  enum {
    ID_CANVAS=FX::FXMainWindow::ID_LAST,         // Canvas ID for the OpenGL window
    ID_START_STOP_ROTATE,                        // Start and stop rotating our graphic 
    ID_START_STOP_TRANSLATE,                     // Start and stop translating our graphic
    ID_MY_BUTTON,                                // Button 
    ID_LAST,
  };

  // Message handlers
  long onUpdateCanvas(FXObject*,FXSelector,void*);
  long onPaintCanvas(FXObject*,FXSelector,void*);
  long onLeftBtnRelease(FXObject*, FXSelector, void*);
  long onStartStopRotate(FXObject*, FXSelector, void*);
  long onStartStopTranslate(FXObject*, FXSelector, void*);
  
  virtual void setupGUI();
  
protected:

  MainWindow(){}
  
private:

   // application, station and displays
   Application* app;
   Display* display; 
   Station* station;

   // menu stuff
   FXMenuBar*   menuBar;
   
   // left frame - to get width and height
   FXComposite* leftFrame; 
   FXComposite* rightFrame;

};

} // end mainFox namespace
} // end Eaagles namespace

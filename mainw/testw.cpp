//*****************************************************************************
// Example routine for the basicGL and basic framework
//*****************************************************************************

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Timers.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Tables.h"
#include "openeaagles/basic/Nav.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/basicFF.h"

#include "openeaagles/basicGL/Graphic.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/basicGL/Image.h"

#include "openeaagles/gui/glut/GlutDisplay.h"
#include "openeaagles/gui/glut/glutFF.h"

#include <GL/glut.h>

#include "openeaagles/basic/osg/Matrixd"


#include "MfdPage.h"
#include "TestOne.h"
#include "TestTwo.h"
#include "TdAzPtr.h"
#include "TdElevPtr.h"
#include "TestRotator.h"

namespace Eaagles {
namespace MainW {

// Frame Rate
const int frameRate = 20;

// System descriptions
static class TestDisplay* sys = 0;	

//=============================================================================
// TestDisplay
//=============================================================================
class TestDisplay : public Glut::GlutDisplay
{
    DECLARE_SUBCLASS(TestDisplay, Glut::GlutDisplay)

public:
    TestDisplay();
    
    virtual void drawIt();
    virtual void mouseEvent(const int button, const int state, const int x, const int y);
    virtual bool event(const int event, Basic::Object* const obj = 0);
    bool onFrameBufferKey();

private:
    // Select/Pick test
    BasicGL::Graphic* selected;
};

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestDisplay,"TestDisplay")
EMPTY_SERIALIZER(TestDisplay)

TestDisplay::TestDisplay()
{
    STANDARD_CONSTRUCTOR()
    selected = 0;
}

EMPTY_COPYDATA(TestDisplay)
EMPTY_DELETEDATA(TestDisplay)

// Event() map
BEGIN_EVENT_HANDLER(TestDisplay)
   ON_EVENT('f',onFrameBufferKey)
   ON_EVENT('F',onFrameBufferKey)
END_EVENT_HANDLER()


// drawIt() -- function to display the test
void TestDisplay::drawIt()
{
    BaseClass::drawIt();
    //clear();
    //draw();
    //swapBuffers();
}

// mouseEvent() -- Handle mouse inputs
void TestDisplay::mouseEvent(const int button, const int state, const int x, const int y)
{
    setMouse(x,y);
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if (selected != 0) selected->setFlashRate(0.0);
        selected = pick(0);
        if (selected != 0) selected->setFlashRate(2.0f);
    }
}

// reset simulation
bool TestDisplay::onFrameBufferKey()
{
   BasicGL::Image* image = readFrameBuffer();
   image->writeFileBMP("./test.bmp");
   return true;
}

//=============================================================================
// Main test functions
//=============================================================================

// timerFunc() -- Time critical stuff)
static void timerFunc(int)
{
    double dt = 1.0/double(frameRate);

    unsigned int millis = (unsigned int)(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

    Basic::Timer::updateTimers((LCreal)dt);
    BasicGL::Graphic::flashTimer((LCreal)dt);
    sys->tcFrame((LCreal)dt);
}

// Test Form Function
static Basic::Object* testFormFunc(const char* formname)
{
    Basic::Object* newform = 0;

    // This test ...
    if ( strcmp(formname, TestDisplay::getFormName()) == 0 ) {
        newform = new TestDisplay;
    }
    else if ( strcmp(formname, MfdPage::getFormName()) == 0 ) {
        newform = new MfdPage;
    }

    // TestX
    else if ( strcmp(formname, TestOne::getFormName()) == 0 ) {
        newform = new TestOne;
    }
    
    // TestY
    else if ( strcmp(formname, TestTwo::getFormName()) == 0 ) {
        newform = new TestTwo;
    }
    else if ( strcmp(formname, TdAzPtr::getFormName()) == 0 ) {
        newform = new TdAzPtr;
    }
    else if ( strcmp(formname, TdElevPtr::getFormName()) == 0 ) {
        newform = new TdElevPtr;
    }
    else if ( strcmp(formname, TestRotator::getFormName()) == 0 ) {
        newform = new TestRotator;
    }
    
    else {
        //if (newform == 0) newform = Instruments::formFunc(formname);
        if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
        if (newform == 0) newform = Glut::glutFormFunc(formname);
        if (newform == 0) newform = Basic::basicFormFunc(formname);
    }
    return newform;
}

// readTest() -- function to the read description files
static void readTest(const char* const testFileName)
{
    // Read the description file
    int errors = 0;
    Basic::Object* q1 = Basic::lcParser(testFileName, testFormFunc, &errors);
    if (errors > 0) {
        std::cerr << "Errors in reading file: " << errors << std::endl;
        exit(1);
    }

    // Set 'sys' to our basic description object.
    sys = 0;
    if (q1 != 0) {

        // When we were given a Pair, get the pointer to its object.
        Basic::Pair* pp = dynamic_cast<Basic::Pair*>(q1);
        if (pp != 0) {
           std::cout << "Form: " << *pp->slot() << std::endl;
            q1 = pp->object();
        }

        // What we should have here is the description object and
        // it should be of type 'TestDisplay'.
        sys = dynamic_cast<TestDisplay*>(q1);
    }

    // Make sure we did get a valid object (we must have one!)
    if (sys == 0) {
        std::cout << "Invalid description file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //sys->serialize(std::cout);
}

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);

   // Config file file
   const char* configFile = "test.edl";

   // Parse arguments
   for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i],"-f") == 0) {
         configFile = argv[++i];
      }
   }

// ---
// Read in the description files
// ---
    readTest(configFile);

// ---
// Create a display window
// ---
    sys->createWindow();

// ---
// Set timer
// ---
    double dt = 1.0/double(frameRate);
    unsigned int millis = (unsigned int)(dt * 1000);
    glutTimerFunc(millis, timerFunc, 1);

// ---
// Main loop
// ---
    glutMainLoop();

    return 0;
}

} // End MainW namespace
} // End Eaagles namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::MainW::main(argc,argv);
}

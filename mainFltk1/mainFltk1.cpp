
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/PairStream.h"

#include "openeaagles/basic/basicFF.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/instruments/instrumentsFF.h"
#include "openeaagles/simulation/simulationFF.h"

#include <FL/Fl.H>

#include "FltkStation.h"
#include "FltkDisplay.h"


// ----------------------------------------------------------------------------
// update() - static call from mainline that will call our update date
// ----------------------------------------------------------------------------
static void update(void* pData)
{
    if (pData != NULL) {
        Eaagles::mainFltk1::FltkStation* stn = reinterpret_cast<Eaagles::mainFltk1::FltkStation*>(pData);
        if (stn != 0) {
            double dt = 1 / 20.0f;
            stn->updateData((Eaagles::LCreal)dt);
            Fl::repeat_timeout(dt, update, pData);
        }
    }
}

namespace Eaagles {
namespace mainFltk1 {

static FltkStation* sys = 0;
static const char* testFileName = "test.edl";

// Test Form Function
static Basic::Object* testFormFunc(const char* formname)
{
    Basic::Object* newform = 0;

    // This test ...
    if ( strcmp(formname, FltkStation::getFormName()) == 0 ) {
        newform = new FltkStation;
    }
    else if ( strcmp(formname, FltkDisplay::getFormName()) == 0 ) {
        newform = new FltkDisplay;
    }
    else {
        if (newform == 0) newform = Simulation::simulationFormFunc(formname);
        if (newform == 0) newform = Instruments::instrumentsFormFunc(formname);
        if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
        if (newform == 0) newform = Basic::basicFormFunc(formname);
    }
    
    return newform;
}


// readTest() -- function to the read description files
static void readTest()
{
    // Read the description file
    int errors = 0;
    Eaagles::Basic::Object* q1 = Eaagles::Basic::lcParser(testFileName, testFormFunc, &errors);
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

        // we should have a FltkStation
        sys = dynamic_cast<FltkStation*>(q1);

    }

    // Make sure we did get a valid object
    if (sys == 0) {
        std::cout << "Invalid description file!" << std::endl;
        exit(EXIT_FAILURE);
    }
        
}

int main(int, char* [])
{

    // read our description file
    readTest();

    // now do a reset
    sys->reset();
    sys->updateData(0.025f);

    // test our real time process (not needed here)
    //sys->createRealTimeProcess();

    // run at 20 HZ roughly, backround thread
    double dt = 1 / 20.f;
    // create our update data timer
    Fl::add_timeout(dt, update, sys);

    return Fl::run();
}

};
};

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::mainFltk1::main(argc,argv);
}

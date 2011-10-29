
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/PairStream.h"

#include "openeaagles/basic/basicFF.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/instruments/instrumentsFF.h"
#include "openeaagles/simulation/simulationFF.h"

// include our fltk library
#include <FL/Fl.H>

#include "Station.h"
#include "Display.h"


// ----------------------------------------------------------------------------
// update() - static call from mainline that will call our update date
// ----------------------------------------------------------------------------
static void update(void* pData)
{
    if (pData != NULL) {
        Eaagles::Fltk1::Station* stn = reinterpret_cast<Eaagles::Fltk1::Station*>(pData);
        if (stn != 0) {
            double dt = 1 / 20.0f;
            stn->updateData((Eaagles::LCreal)dt);
            Fl::repeat_timeout(dt, update, pData);
        }
    }
}

namespace Eaagles {
namespace Fltk1 {

static Station* sys = 0;
const char* testFileName = "test.edl";

// Test Form Function
static Basic::Object* testFormFunc(const char* formname)
{
    Basic::Object* newform = 0;

    // This test ...
    if ( strcmp(formname, Station::getFormName()) == 0 ) {
        newform = new Station;
    }
    else if ( strcmp(formname, Display::getFormName()) == 0 ) {
        newform = new Display;
    }
    else {
        //if (newform == 0) newform = Eaagles::Fltk1::fltkFormFunc(formname);
        if (newform == 0) newform = Eaagles::Simulation::simulationFormFunc(formname);
        if (newform == 0) newform = Eaagles::Instruments::instrumentsFormFunc(formname);
        if (newform == 0) newform = Eaagles::BasicGL::basicGLFormFunc(formname);
        if (newform == 0) newform = Eaagles::Basic::basicFormFunc(formname);
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

        // When we were given a LcPair, get the pointer to its object.
        Eaagles::Basic::Pair* pp = dynamic_cast<Eaagles::Basic::Pair*>(q1);
        if (pp != 0) {
        std::cout << "Form: " << *pp->slot() << std::endl;
            q1 = pp->object();
        }

        // What we should have here is the description object and
        // it should be of type 'Station'.
        sys = dynamic_cast<Station*>(q1);

    }

    // Make sure we did get a valid object (we must have one!)
    if (sys == 0) {
        std::cout << "Invalid description file!" << std::endl;
        exit(EXIT_FAILURE);
    }
        
}

int main(int, char* []) {
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
   return Eaagles::Fltk1::main(argc,argv);
}

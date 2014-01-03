
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/PairStream.h"

// class factories
#include "openeaagles/basic/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/simulation/Factory.h"

#include <FL/Fl.H>

#include "FltkStation.h"
#include "FltkDisplay.h"

// ----------------------------------------------------------------------------
// update() - static call from mainline that will call our update date
// ----------------------------------------------------------------------------
static void update(void* pData)
{
    if (pData != NULL) {
        Eaagles::Example::FltkStation* stn = reinterpret_cast<Eaagles::Example::FltkStation*>(pData);
        if (stn != 0) {
            double dt = 1 / 20.0f;
            stn->updateData((Eaagles::LCreal)dt);
            Fl::repeat_timeout(dt, update, pData);
        }
    }
}

namespace Eaagles {
namespace Example {

static FltkStation* sys = 0;
static const char* testFileName = "test.edl";

// our class factory
static Basic::Object* factory(const char* name)
{
    Basic::Object* obj = 0;

    // This test ...
    if ( strcmp(name, FltkStation::getFactoryName()) == 0 ) {
        obj = new FltkStation;
    }
    else if ( strcmp(name, FltkDisplay::getFactoryName()) == 0 ) {
        obj = new FltkDisplay;
    }
    else {
        if (obj == 0) obj = Simulation::Factory::createObj(name);
        if (obj == 0) obj = Instruments::Factory::createObj(name);
        if (obj == 0) obj = BasicGL::Factory::createObj(name);
        if (obj == 0) obj = Basic::Factory::createObj(name);
    }

    return obj;
}


// build a station
static void builder()
{
    // Read the description file
    int errors = 0;
    Eaagles::Basic::Object* q1 = Eaagles::Basic::lcParser(testFileName, factory, &errors);
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

    // build a station
    builder();

    // now do a reset
    sys->reset();
    sys->updateData(0.025f);

    // test our real time process (not needed here)
    //sys->createRealTimeProcess();

    // run at 20 HZ roughly, background thread
    double dt = 1 / 20.f;
    // create our update data timer
    Fl::add_timeout(dt, update, sys);

    return Fl::run();
}

}
}

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   return Eaagles::Example::main(argc,argv);
}

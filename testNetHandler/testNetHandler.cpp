//-----------------------------------------------------------------------------
// Description: application to test NetHandler functionality
//-----------------------------------------------------------------------------

#include "Endpoint.h"
#include "Sender.h"
#include "Echo.h"

#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"

// class factories
#include "openeaagles/basic/Factory.h"
#include "../shared/xZeroMQHandlers/Factory.h"

namespace Eaagles {
namespace Test {

const float UPDATE_RATE = 10.0; // Main loop update rate

// our class factory
static Basic::Object* factory(const char* name)
{
    Basic::Object* obj = 0;

    if ( strcmp(name, Sender::getFactoryName()) == 0 ) {
        obj = new Sender();
    }
    else if ( strcmp(name, Echo::getFactoryName()) == 0 ) {
        obj = new Echo();
    }

    // Example libraries
    if (obj == 0) obj = xZeroMQHandlers::Factory::createObj(name);
    // Framework libraries
    if (obj == 0) obj = Basic::Factory::createObj(name);

    return obj;
}

// build an endpoint as specified by configuration file
static Endpoint* builder(const char* const testFile)
{
  if (testFile == 0) return 0;

  std::cout << "Reading file : " << testFile << std::endl;

  // Read the description file
  int errors = 0;
  Basic::Object* q1 = lcParser(testFile, factory, &errors);
  if (errors > 0) {
    std::cerr << "File: " << testFile << ", errors: " << errors << std::endl;
    exit(1);
  }

  // Set 'sys' to our basic description object.
  Endpoint* sys = 0;
  if (q1 != 0) {

    // When we were given a Pair, get the pointer to its object.
    Basic::Pair* pp = dynamic_cast<Basic::Pair*>(q1);
    if (pp != 0) {
      q1 = pp->object();
    }

    // What we should have here is the description object and
    // it should be of type 'Station'.
    sys = dynamic_cast<Endpoint*>(q1);

  }

  return sys;
}

int exec(int argc, char* argv[])
{
    const char* testFile = "configs/senderUdpBroadcast.edl";

    // Get the command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i],"-f") == 0) {
            testFile = argv[++i];
        }
    }

    // Must have a test file name
    if (testFile == 0) {
        std::cerr << "usage: testNetHandler -f testFile" << std::endl;
        return EXIT_FAILURE;
    }

    // build an endpoint
    Endpoint* sys = builder(testFile);

    // Must have a valid system of type Endpoint (e.g., Sender or Echo)
    if (sys == 0) {
        std::cerr << "Invalid test file -- requires a Sender or Echo component." << std::endl;
        return EXIT_FAILURE;
    }

    // Send a reset event
    std::cout << "Reset event: which will establish the networks." << std::endl;
    sys->event(Basic::Component::RESET_EVENT);

    // System Time of Day
    double dt = 1.0/double(UPDATE_RATE);             // Delta time
    double simTime = 0.0;                            // Simulator time reference
    double startTime = Eaagles::getComputerTime();   // Time of day (sec) run started

    // Main loop !!!!
    std::cout << "Starting main loop ..." << std::endl;
    for(;;) {

        sys->updateTC( LCreal(dt) );
        sys->updateData( LCreal(dt) );

        simTime += dt;                       // time of next frame
        double timeNow = Eaagles::getComputerTime();  // time now

        double elapsedTime = timeNow - startTime;
        double nextFrameStart = simTime - elapsedTime;
        int sleepTime = int(nextFrameStart*1000.0);

        // wait for the next frame
        if (sleepTime > 0)
            lcSleep(sleepTime);
    }

    return EXIT_SUCCESS;
}

}
}

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    Eaagles::Test::exec(argc, argv);
}


//-----------------------------------------------------------------------------
// Description: application to test NetHandler functionality
//-----------------------------------------------------------------------------

#include "Endpoint.h"
#include "Sender.h"
#include "Echo.h"

#include "openeaagles/basic/basicFF.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"

#include "../shared-libs/xZeroMQ/formFunc.h"

namespace Test {

const float UPDATE_RATE = 10.0; // Main loop update rate

//-----------------------------------------------------------------------------
// testFormFunc() -- our form function used by the parser
//-----------------------------------------------------------------------------
static Eaagles::Basic::Object* testFormFunc(const char* formname)
{
    Eaagles::Basic::Object* newform = 0;

    if ( strcmp(formname, Sender::getFormName()) == 0 ) {
        newform = new Sender();
    }
    else if ( strcmp(formname, Echo::getFormName()) == 0 ) {
        newform = new Echo();
    }

    if (newform == 0) newform = Eaagles::Basic::basicFormFunc(formname);
    if (newform == 0) newform = Eaagles::xZeroMQ::formFunc(formname);
    return newform;
}

//-----------------------------------------------------------------------------
// readTest() -- function to the read description files
//-----------------------------------------------------------------------------
static Endpoint* readTest(const char* const testFile)
{
  if (testFile == 0) return 0;

  std::cout << "Reading file : " << testFile << std::endl;

  // Read the description file
  int errors = 0;
  Eaagles::Basic::Object* q1 = lcParser(testFile, testFormFunc, &errors);
  if (errors > 0) {
    std::cerr << "File: " << testFile << ", errors: " << errors << std::endl;
    exit(1);
  }

  // Set 'sys' to our basic description object.
  Endpoint* sys = 0;
  if (q1 != 0) {

    // When we were given a Pair, get the pointer to its object.
    Eaagles::Basic::Pair* pp = dynamic_cast<Eaagles::Basic::Pair*>(q1);
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
    const char* testFile = "inputs/senderUdpBroadcast.edl";

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

    // Read in the description files
    Endpoint* sys = readTest(testFile);

    // Must have a valid system of type Endpoint (e.g., Sender or Echo)
    if (sys == 0) {
        std::cerr << "Invalid test file -- requires a Sender or Echo component." << std::endl;
        return EXIT_FAILURE;
    }

    // Send a reset event
    std::cout << "Reset event: which will establish the networks." << std::endl;
    sys->event(Eaagles::Basic::Component::RESET_EVENT);

    // System Time of Day
    double dt = 1.0/double(UPDATE_RATE);             // Delta time
    double simTime = 0.0;                            // Simulator time reference
    double startTime = Eaagles::getComputerTime();   // Time of day (sec) run started

    // Main loop !!!!
    std::cout << "Starting main loop ..." << std::endl;
    for(;;) {

        sys->updateTC( Eaagles::LCreal(dt) );
        sys->updateData( Eaagles::LCreal(dt) );

        simTime += dt;                       // time of next frame
        double timeNow = Eaagles::getComputerTime();  // time now

        double elapsedTime = timeNow - startTime;
        double nextFrameStart = simTime - elapsedTime;
        int sleepTime = int(nextFrameStart*1000.0);

        // wait for the next frame
        if (sleepTime > 0)
            Eaagles::lcSleep(sleepTime);
    }

    return EXIT_SUCCESS;
}

} // namespace

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    Test::exec(argc, argv);
}


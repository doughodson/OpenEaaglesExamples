
#include "openeaagles/simulation/Station.h"
#include "openeaagles/simulation/simulationFF.h"
#include "openeaagles/vehicles/vehiclesFF.h"
#include "openeaagles/sensors/sensorsFF.h"
#include "openeaagles/dis/disFF.h"
#include "openeaagles/otw/otwFF.h"
#include "openeaagles/basic/basicFF.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Integer.h"
#include "openeaagles/basic/units/Angles.h"
#include "openeaagles/basic/osg/Vec3"
#include "openeaagles/otw/OtwPC.h"         // for OTW


namespace Eaagles {
namespace Sim2 {

// Test file
const char* testFile = "test1.edl";

// Background frame rate
const int bgRate = 10;

static Simulation::Station* sys = 0;

//-----------------------------------------------------------------------------
// testFormFunc() -- our form function used by the parser
//-----------------------------------------------------------------------------
static Basic::Object* testFormFunc(const char* formname)
{
  Basic::Object* newform = 0;

  if (newform == 0) newform = Simulation::simulationFormFunc(formname);
  if (newform == 0) newform = Vehicle::vehiclesFormFunc(formname);
  if (newform == 0) newform = Sensor::sensorsFormFunc(formname);
  if (newform == 0) newform = Network::Dis::disFormFunc(formname);
  if (newform == 0) newform = Basic::basicFormFunc(formname);
  return newform;
}

//-----------------------------------------------------------------------------
// readTest() -- function to the read description files
//-----------------------------------------------------------------------------
static void readTest()
{
  std::cout << "Reading file : " << testFile << std::endl;

  // Read the description file
  int errors = 0;
  Basic::Object* q1 = lcParser(testFile, testFormFunc, &errors);
  if (errors > 0) {
    std::cerr << "File: " << testFile << ", errors: " << errors << std::endl;
    exit(1);
  }

  // Set 'sys' to our basic description object.
  sys = 0;
  if (q1 != 0) {

    // When we were given a Pair, get the pointer to its object.
    Basic::Pair* pp = dynamic_cast<Basic::Pair*>(q1);
    if (pp != 0) {
      q1 = pp->object();
    }

    // What we should have here is the description object and
    // it should be of type 'Station'.
    sys = dynamic_cast<Simulation::Station*>(q1);
  }

  // Make sure we did get a valid Station object (we must have one!)
  if (sys == 0) {
    std::cout << "Invalid description file!" << std::endl;
    exit(EXIT_FAILURE);
  }
}

int exec(int argc, char* argv[])
{
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i],"-f") == 0) {
      testFile = argv[++i];
    }
  }

  // Read in the description files
  readTest();
  // send a reset event and frame sim once
  sys->event(Basic::Component::RESET_EVENT);
  sys->tcFrame( (LCreal) (1.0/double(sys->getTimeCriticalRate())) );

  // Create Time Critical Thread
  sys->createTimeCriticalProcess();
  // short pause to allow os to startup thread
  lcSleep(2000);

  // Calc delta time for background thread
  double dt = 1.0/double(bgRate);

  // System Time of Day 
  double simTime = 0.0;                    // Simulator time reference
  double startTime = getComputerTime();    // Time of day (sec) run started

  int k = 0;
  std::cout << "Starting background main loop ..." << std::endl;
  for(;;) {

    // Update background thread
    sys->updateData( LCreal(dt) );

    simTime += dt;                       // time of next frame
    double timeNow = getComputerTime();  // time now

    double elapsedTime = timeNow - startTime;
    double nextFrameStart = simTime - elapsedTime;
    int sleepTime = int(nextFrameStart*1000.0);

    // wait for the next frame
    if (sleepTime > 0)
      lcSleep(sleepTime);

/*
    std::cout << ".";
    k += 1;
    if ( k == 40 ) {
      std::cout << "\n";
      k = 0;
    }
*/

  }
  return 0;
}

} // namespace Sim2
} // namespace Eaagles

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  return Eaagles::Sim2::exec(argc, argv);
}

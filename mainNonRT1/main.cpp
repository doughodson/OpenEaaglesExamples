
#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/Pair.h"

// class factories
#include "openeaagles/simulation/Factory.h"
#include "openeaagles/vehicles/Factory.h"
#include "openeaagles/sensors/Factory.h"
#include "openeaagles/basic/Factory.h"

namespace Eaagles {
namespace Example {

// Test file
const char* testFile = "test1.edl";

// frame rate (50 Hz)
const unsigned int frameRate = 50;

static Simulation::Simulation* sys = 0;

// our class factory
static Basic::Object* factory(const char* name)
{
  Basic::Object* obj = 0;

  if (obj == 0) obj = Simulation::Factory::createObj(name);
  if (obj == 0) obj = Vehicle::Factory::createObj(name);
  if (obj == 0) obj = Sensor::Factory::createObj(name);
  if (obj == 0) obj = Basic::Factory::createObj(name);

  return obj;
}

// build simulation
static void builder()
{
  std::cout << "Reading file : " << testFile << std::endl;

  // Read the description file
  int errors = 0;
  Basic::Object* q1 = lcParser(testFile, factory, &errors);
  if (errors > 0) {
    std::cerr << "File: " << testFile << ", errors: " << errors << std::endl;
    exit(1);
  }

  // Set 'sys' to our basic description object.
  sys = 0;
  if (q1 != 0) {

    // if we are given a Pair, get the pointer to its object
    Basic::Pair* pp = dynamic_cast<Basic::Pair*>(q1);
    if (pp != 0) {
      q1 = pp->object();
    }

    // What we should have here is the description object and
    // it should be of type 'Simulation'
    sys = dynamic_cast<Simulation::Simulation*>(q1);
  }

  // Make sure we did get a valid Simulation object (we must have one!)
  if (sys == 0) {
    std::cout << "Invalid description file!" << std::endl;
    exit(EXIT_FAILURE);
  }
}

int exec(int argc, char* argv[])
{
  // delta time (20ms)
  LCreal dt = (LCreal)1.0/LCreal(frameRate);

  // read filename from command line if provided
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i],"-f") == 0) {
      testFile = argv[++i];
    }
  }

  // build simulation
  builder();

  // reset component tree
  sys->reset();

  // execute simulation as fast as possible
  for(; sys->getExecTimeSec() < 50.0; ) {
    // print out simulation time
    std::cout << sys->getExecTimeSec() << std::endl;
    // execute timestep
    sys->tcFrame( dt );
    sys->updateData( dt );
  }
  return 0;
}

} // namespace Example
} // namespace Eaagles

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  Eaagles::Example::exec(argc, argv);
}

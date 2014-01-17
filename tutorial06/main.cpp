
#include <iostream>
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/String.h"

// class factories
#include "openeaagles/basic/Factory.h"

#include "MyComp.h"

namespace Eaagles {
namespace Tutorial {

// Description (input) File
// After being processed by the C preprocessor
const char* inputFileName = "file0.edl";

// Frame Rate
const int frameRate = 20;

static class MyComp* sys = 0;

// our class factory
static Basic::Object* factory(const char* const name)
{
  Basic::Object* obj = 0;

  // look in application's classes
  if ( strcmp(name, MyComp::getFactoryName()) == 0 ) {
    obj = new MyComp;
  }
  // look in basic classes
  if (obj == 0) obj = Basic::Factory::createObj(name);

  return obj;
}

// build my component
static void builder()
{
  // Read the description file
  int errors = 0;
  Basic::Object* q1 = lcParser(inputFileName, factory, &errors);
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
      q1 = pp->object();
    }
    sys = dynamic_cast<MyComp*>(q1);
  }

  // Make sure we did get a valid object (we must have one!)
  if (sys == 0) {
    std::cout << "example: invalid description file!" << std::endl;
    exit(1);
  }
}

int main(int argc, char *argv[])
{
  // allow user to specify input file
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i],"-f") == 0) {
      inputFileName = argv[++i];
    }
  }

  // build my component
  builder();

  // compute a delta time
  LCreal dt = (LCreal)(1.0/double(frameRate));
  // process component tree
  sys->tcFrame(dt);     // time critical
  sys->updateData(dt);  // non-time critical

  // reset component tree
  sys->reset();

  // process component tree again
  sys->tcFrame(dt);     // time critical
  sys->updateData(dt);  // non-time critical

  sys->unref();

  return 0;
}

} // namespace Tutorial
} // namespace Eaagles

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  Eaagles::Tutorial::main(argc, argv);
}

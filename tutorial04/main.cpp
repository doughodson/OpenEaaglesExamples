
#include <iostream>
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"

// class factories
#include "openeaagles/basic/Factory.h"

#include "Uniform.h"
#include "Exp.h"

namespace Eaagles {
namespace Tutorial {

// Description (input) File
// After being processed by the C preprocessor
const char* inputFileName = "file0.edl";

static class Random* sys = 0;

// our class factory
static Basic::Object* factory(const char* const name)
{
  Basic::Object* obj = 0;

  // look in application's classes
  if ( strcmp(name, Uniform::getFactoryName()) == 0 ) {
    obj = new Uniform();
  }
  else if ( strcmp(name, Exp::getFactoryName()) == 0 ) {
    obj = new Exp();
  }

  // look in base classes
  if (obj == 0) obj = Basic::Factory::createObj(name);

  return obj;
}

// build random
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
    sys = dynamic_cast<Random*>(q1);
  }

  // Make sure we did get a valid object (we must have one!)
  if (sys == 0) {
    std::cout << "example: invalid description file!" << std::endl;
    exit(1);
  }
}

int main(int argc, char* argv[])
{
  // build random
  builder();

  for( int i=0; i<10; i++)
    std::cout << sys->getNum() << std::endl;

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


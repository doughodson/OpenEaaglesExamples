
#include <iostream>
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/basicFF.h"
#include "Uniform.h"
#include "Exp.h"

namespace Eaagles {
namespace Example04 {

// Description (input) File
// After being processed by the C preprocessor
const char* inputFileName = "file0.edl";

static class Random* sys = 0;

static Basic::Object* exampleFormFunc(const char* const formname)
{
  Basic::Object* newform = 0;

  // look in application's classes
  if ( strcmp(formname, Uniform::getFormName()) == 0 ) {
    newform = new Uniform();
  }
  else if ( strcmp(formname, Exp::getFormName()) == 0 ) {
    newform = new Exp();
  }

  // look in base classes
  if (newform == 0) newform = Basic::basicFormFunc(formname);

  return newform;
}

// read and parse input file
static void readInput()
{
  // Read the description file
  int errors = 0;
  Basic::Object* q1 = lcParser(inputFileName, exampleFormFunc, &errors);
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

int exec(int, char **)
{
  // parse and read input file
  readInput();

  for( int i=0; i<10; i++)
    std::cout << sys->getNum() << std::endl;

  sys->unref();

  return 0;
}

} // namespace Example04
} // namespace Eaagles

//-----------------------------------------------------------------------------
// main() -- Main routine
//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  Eaagles::Example04::exec(argc, argv);
}


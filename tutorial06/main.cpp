
#include <iostream>
#include <cstring>
#include <cstdlib>

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/String.h"

// class factories
#include "openeaagles/basic/Factory.h"

#include "MyComp.h"

namespace Eaagles {
namespace Tutorial {

// frame rate
const int frameRate = 20;

static class MyComp* myComp = nullptr;

// our class factory
static Basic::Object* factory(const char* const name)
{
  Basic::Object* obj = nullptr;

  // look in application's classes
  if ( std::strcmp(name, MyComp::getFactoryName()) == 0 ) {
    obj = new MyComp;
  }
  // look in basic classes
  if (obj == nullptr) obj = Basic::Factory::createObj(name);

  return obj;
}

// MyComp builder
static MyComp* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   Basic::Object* obj = Basic::lcParser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a Basic::Pair, if so, point to object in Pair, not Pair itself
   Basic::Pair* pair = dynamic_cast<Basic::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   MyComp* myComp = dynamic_cast<MyComp*>(obj);
   if (myComp == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return myComp;
}

int main(int argc, char *argv[])
{
   // default configuration filename
   const char* configFilename = "file0.edl";

   // allow user to specify input file
   for (int i = 1; i < argc; i++) {
      if (std::strcmp(argv[i],"-f") == 0) {
         configFilename = argv[++i];
      }
   }

   // build my component
   myComp = builder(configFilename);

   // compute a delta time
   double dt = 1.0 / static_cast<double>(frameRate);
   // process component tree
   myComp->tcFrame(dt);     // time critical
   myComp->updateData(dt);  // non-time critical

   // reset component tree
   myComp->reset();

   // process component tree again
   myComp->tcFrame(dt);     // time critical
   myComp->updateData(dt);  // non-time critical

   myComp->unref();

  return 0;
}

} // namespace Tutorial
} // namespace Eaagles

//
int main(int argc, char* argv[])
{
   Eaagles::Tutorial::main(argc, argv);
}

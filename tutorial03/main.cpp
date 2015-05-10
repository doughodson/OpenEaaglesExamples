
#include <iostream>
#include <cstring>
#include <cstdlib>

#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"

// class factories
#include "openeaagles/basic/Factory.h"

#include "Random.h"

namespace Eaagles {
namespace Tutorial {

static class Random* random = nullptr;

// our class factory
static Basic::Object* factory(const char* const name)
{
   Basic::Object* obj = nullptr;

   // look in application's classes
   if ( std::strcmp(name, Random::getFactoryName()) == 0 ) {
      obj = new Random;
   }

   // look in base classes
   if (obj == nullptr) obj = Basic::Factory::createObj(name);
   return obj;
}

// random builder
static Random* builder(const char* const filename)
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
   Random* random = dynamic_cast<Random*>(obj);
   if (random == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return random;
}

int main(int argc, char* argv[])
{
   // default configuration filename
   const char* configFilename = "file0.edl";

   // build random
   random = builder(configFilename);

   for (unsigned int i=0; i<10; i++) {
      std::cout << random->getNum() << std::endl;
   }

   random->unref();

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

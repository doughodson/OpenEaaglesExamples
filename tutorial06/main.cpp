
#include <iostream>
#include <string>
#include <cstdlib>

#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/edl_parser.hpp"

// factories
#include "openeaagles/base/factory.hpp"

#include "MyComp.hpp"

// frame rate
const int frameRate = 20;

// class factory
oe::base::Object* factory(const std::string& name)
{
  oe::base::Object* obj = nullptr;

  // look in application's classes
  if ( name == MyComp::getFactoryName() ) {
    obj = new MyComp;
  }
  // look in base classes
  if (obj == nullptr) obj = oe::base::factory(name);

  return obj;
}

// MyComp builder
MyComp* builder(const std::string& filename)
{
   // read configuration file
   unsigned int num_errors = 0;
   oe::base::Object* obj = oe::base::edl_parser(filename, factory, &num_errors);
   if (num_errors > 0) {
      std::cerr << "File: " << filename << ", number of errors: " << num_errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   const auto pair = dynamic_cast<oe::base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   const auto myComp = dynamic_cast<MyComp*>(obj);
   if (myComp == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return myComp;
}

int main(int argc, char *argv[])
{
   // default configuration filename
   std::string configFilename = "file0.edl";

   // allow user to specify input file
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   // build my component
   MyComp* myComp = builder(configFilename);

   // compute a delta time
   const double dt = 1.0 / static_cast<double>(frameRate);
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

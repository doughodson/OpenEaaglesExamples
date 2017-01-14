
#include <iostream>
#include <string>
#include <cstdlib>

#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/edl_parser.hpp"

// factories
#include "openeaagles/base/factory.hpp"

#include "Uniform.hpp"
#include "Exp.hpp"

// class factory
oe::base::Object* factory(const std::string& name)
{
   oe::base::Object* obj = nullptr;

   // look in application's classes
   if ( name == Uniform::getFactoryName() ) {
      obj = new Uniform();
   }
   else if ( name == Exp::getFactoryName() ) {
      obj = new Exp();
   }

   // look in base classes
   if (obj == nullptr) obj = oe::base::factory(name);

   return obj;
}

// random builder
Random* builder(const std::string& filename)
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
   const auto random = dynamic_cast<Random*>(obj);
   if (random == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return random;
}

int main(int argc, char* argv[])
{
   // default configuration filename
   std::string configFilename = "file0.edl";

   // build random
   Random* random = builder(configFilename);

   for (unsigned int i=0; i<10; i++) {
      std::cout << random->getNum() << std::endl;
   }

   random->unref();

   return 0;
}

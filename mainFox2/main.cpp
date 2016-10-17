
#include "fx.h"

#include "MainWindow.hpp"

#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/graphics/Display.hpp"

// factories
#include "openeaagles/graphics/factory.hpp"
#include "openeaagles/base/factory.hpp"
#include "Worm.hpp"

#include "openeaagles/base/safe_ptr.hpp"

#include <string>

// class factory
oe::base::Object* factory(const std::string& name)
{
   oe::base::Object* obj = nullptr;

   if ( name == Worm::getFactoryName() ) {
      obj = new Worm;
   }

   if (obj == nullptr) obj = oe::graphics::factory(name);
   if (obj == nullptr) obj = oe::base::factory(name);

   return obj;
}

// assemble a Display from configuration
oe::graphics::Display* builder(const std::string& filename)
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
   oe::base::Pair* pair = dynamic_cast<oe::base::Pair*>(obj);
   if (pair != nullptr) {
      obj = pair->object();
      obj->ref();
      pair->unref();
   }

   // try to cast to proper object, and check
   oe::graphics::Display* display = dynamic_cast<oe::graphics::Display*>(obj);
   if (display == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return display;
}

int main(int argc, char* argv[])
{
   // default configuration filename
   std::string configFilename = "wormdisplay.edl";
   // set optional input file
   for (int i = 1; i < argc; i++) {
      if ( std::string(argv[i]) == "-f" ) {
         configFilename = argv[++i];
      }
   }

   // build a display
   oe::base::safe_ptr<oe::graphics::Display> display(builder(configFilename), false);

   // application object
   FXApp application("example", "openeaagles");

   // init application and open display (no actual window will open)
   application.init(argc, argv);

   // create main/central window for the application
   // associate it with application
   new MainWindow(&application, display);

   // create application's windows
   application.create();

   // start event loop
   return application.run();
}


#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/edl_parser.hpp"
#include "openeaagles/base/PairStream.hpp"

// factories
#include "openeaagles/base/factory.hpp"
#include "openeaagles/graphics/factory.hpp"
#include "openeaagles/instruments/factory.hpp"
#include "openeaagles/simulation/factory.hpp"

#include <FL/Fl.H>

#include "FltkStation.hpp"
#include "FltkDisplay.hpp"

#include <string>
#include <cstdlib>

// ----------------------------------------------------------------------------
// update() - static call from mainline that will call our update date
// ----------------------------------------------------------------------------
static void update(void* pData)
{
   if (pData != nullptr) {
      FltkStation* stn = reinterpret_cast<FltkStation*>(pData);
      if (stn != nullptr) {
         const double dt = 1 / 20.0;
         stn->updateData(dt);
         Fl::repeat_timeout(dt, update, pData);
      }
   }
}

// our class factory
oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

    // This test ...
    if ( name == FltkStation::getFactoryName() ) {
        obj = new FltkStation;
    }
    else if ( name == FltkDisplay::getFactoryName() ) {
        obj = new FltkDisplay;
    }
    else {
        if (obj == nullptr) obj = oe::simulation::factory(name);
        if (obj == nullptr) obj = oe::instruments::factory(name);
        if (obj == nullptr) obj = oe::graphics::factory(name);
        if (obj == nullptr) obj = oe::base::factory(name);
    }

    return obj;
}

// FLTK station builder
FltkStation* builder(const std::string& filename)
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
   FltkStation* fltkStation = dynamic_cast<FltkStation*>(obj);
   if (fltkStation == nullptr) {
      std::cerr << "Invalid configuration file!" << std::endl;
      std::exit(EXIT_FAILURE);
   }
   return fltkStation;
}

int main(int, char* [])
{
   // default configuration filename
   std::string configFilename = "test.edl";

   FltkStation* fltkStation = builder(configFilename);

   // now do a reset
   fltkStation->reset();
   fltkStation->updateData(0.025);

   // run at 20 HZ roughly, background thread
   const double dt = 1 / 20.0;
   // create our update data timer
   Fl::add_timeout(dt, update, fltkStation);

   return Fl::run();
}

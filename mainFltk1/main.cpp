
#include "openeaagles/base/Pair.h"
#include "openeaagles/base/parser.h"
#include "openeaagles/base/PairStream.h"

// factories
#include "openeaagles/base/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/instruments/factory.h"
#include "openeaagles/simulation/factory.h"

#include <FL/Fl.H>

#include "FltkStation.h"
#include "FltkDisplay.h"

#include <cstring>
#include <cstdlib>

// ----------------------------------------------------------------------------
// update() - static call from mainline that will call our update date
// ----------------------------------------------------------------------------
static void update(void* pData)
{
   if (pData != nullptr) {
      oe::example::FltkStation* stn = reinterpret_cast<oe::example::FltkStation*>(pData);
      if (stn != nullptr) {
         const double dt = 1 / 20.0;
         stn->updateData(dt);
         Fl::repeat_timeout(dt, update, pData);
      }
   }
}

namespace oe {
namespace example {

static FltkStation* fltkStation = nullptr;

// our class factory
static base::Object* factory(const char* name)
{
    base::Object* obj = nullptr;

    // This test ...
    if ( std::strcmp(name, FltkStation::getFactoryName()) == 0 ) {
        obj = new FltkStation;
    }
    else if ( std::strcmp(name, FltkDisplay::getFactoryName()) == 0 ) {
        obj = new FltkDisplay;
    }
    else {
        if (obj == nullptr) obj = simulation::factory(name);
        if (obj == nullptr) obj = instruments::factory(name);
        if (obj == nullptr) obj = graphics::factory(name);
        if (obj == nullptr) obj = base::factory(name);
    }

    return obj;
}

// FLTK station builder
static FltkStation* builder(const char* const filename)
{
   // read configuration file
   int errors = 0;
   base::Object* obj = base::edlParser(filename, factory, &errors);
   if (errors > 0) {
      std::cerr << "File: " << filename << ", errors: " << errors << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // test to see if an object was created
   if (obj == nullptr) {
      std::cerr << "Invalid configuration file, no objects defined!" << std::endl;
      std::exit(EXIT_FAILURE);
   }

   // do we have a base::Pair, if so, point to object in Pair, not Pair itself
   base::Pair* pair = dynamic_cast<base::Pair*>(obj);
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
   const char* configFilename = "test.edl";
   fltkStation = builder(configFilename);

   // now do a reset
   fltkStation->reset();
   fltkStation->updateData(0.025);

   // run at 20 HZ roughly, background thread
   const double dt = 1 / 20.0;
   // create our update data timer
   Fl::add_timeout(dt, update, fltkStation);

   return Fl::run();
}

}
}

//
int main(int argc, char* argv[])
{
   return oe::example::main(argc,argv);
}

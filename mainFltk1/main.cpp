
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/Parser.h"
#include "openeaagles/basic/PairStream.h"

// class factories
#include "openeaagles/basic/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/simulation/Factory.h"

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
   if (pData != NULL) {
      Eaagles::Example::FltkStation* stn = reinterpret_cast<Eaagles::Example::FltkStation*>(pData);
      if (stn != nullptr) {
         double dt = 1 / 20.0;
         stn->updateData(static_cast<Eaagles::LCreal>(dt));
         Fl::repeat_timeout(dt, update, pData);
      }
   }
}

namespace Eaagles {
namespace Example {

static FltkStation* fltkStation = nullptr;

// our class factory
static Basic::Object* factory(const char* name)
{
    Basic::Object* obj = nullptr;

    // This test ...
    if ( std::strcmp(name, FltkStation::getFactoryName()) == 0 ) {
        obj = new FltkStation;
    }
    else if ( std::strcmp(name, FltkDisplay::getFactoryName()) == 0 ) {
        obj = new FltkDisplay;
    }
    else {
        if (obj == nullptr) obj = Simulation::Factory::createObj(name);
        if (obj == nullptr) obj = Instruments::Factory::createObj(name);
        if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
        if (obj == nullptr) obj = Basic::Factory::createObj(name);
    }

    return obj;
}

// FLTK station builder
static FltkStation* builder(const char* const filename)
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
   double dt = 1 / 20.0;
   // create our update data timer
   Fl::add_timeout(dt, update, fltkStation);

   return Fl::run();
}

}
}

//
int main(int argc, char* argv[])
{
   return Eaagles::Example::main(argc,argv);
}

//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "TestDisplay.h"
#include "TestStation.h"
#include "TestComputer.h"

// class factories
#include "openeaagles/basic/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/simulation/Factory.h"
#include "openeaagles/sensors/Factory.h"
#include "openeaagles/dis/Factory.h"
#include "openeaagles/otw/Factory.h"

#include <cstring>

namespace oe {
namespace example {

Factory::Factory()
{}

basic::Object* Factory::createObj(const char* name)
{
    basic::Object* obj = nullptr;

   if ( std::strcmp(name, TestStation::getFactoryName()) == 0 ) {
      obj = new TestStation;
   }
   else if ( std::strcmp(name, TestDisplay::getFactoryName()) == 0 ) {
      obj = new TestDisplay;
   }
   else if ( std::strcmp(name, TestComputer::getFactoryName()) == 0 ) {
      obj = new TestComputer;
   }

   if (obj == nullptr) obj = Otw::Factory::createObj(name);
   if (obj == nullptr) obj = Simulation::Factory::createObj(name);
   if (obj == nullptr) obj = Sensor::Factory::createObj(name);
   if (obj == nullptr) obj = network::dis::Factory::createObj(name);
   if (obj == nullptr) obj = instruments::Factory::createObj(name);
   if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
   if (obj == nullptr) obj = glut::Factory::createObj(name);
   if (obj == nullptr) obj = basic::Factory::createObj(name);

    return obj;
}

}  // end namespace example
}  // end namespace oe


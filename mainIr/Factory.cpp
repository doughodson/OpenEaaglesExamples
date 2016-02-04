//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "TestDisplay.h"
#include "TestStation.h"
#include "TestComputer.h"

// factories
#include "openeaagles/basic/Factory.h"
#include "openeaagles/graphics/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/simulation/Factory.h"
#include "openeaagles/models/factory.h"
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

   if (obj == nullptr) obj = otw::factory(name);
   if (obj == nullptr) obj = simulation::factory(name);
   if (obj == nullptr) obj = models::factory(name);
   if (obj == nullptr) obj = network::dis::factory(name);
   if (obj == nullptr) obj = instruments::factory(name);
   if (obj == nullptr) obj = graphics::factory(name);
   if (obj == nullptr) obj = glut::factory(name);
   if (obj == nullptr) obj = basic::factory(name);

    return obj;
}

}  // end namespace example
}  // end namespace oe


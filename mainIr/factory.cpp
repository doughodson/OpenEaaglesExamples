
#include "factory.h"

#include "openeaagles/basic/Object.h"

#include "TestDisplay.h"
#include "TestStation.h"
#include "TestComputer.h"

// factories
#include "openeaagles/basic/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/instruments/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/simulation/factory.h"
#include "openeaagles/models/factory.h"
#include "openeaagles/dis/factory.h"
#include "openeaagles/otw/factory.h"

#include <cstring>

namespace oe {
namespace example {

basic::Object* factory(const char* name)
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

}
}


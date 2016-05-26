
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "TestDisplay.h"
#include "TestStation.h"
#include "TestComputer.h"

// factories
#include "openeaagles/base/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/instruments/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/simulation/factory.h"
#include "openeaagles/models/factory.h"
#include "openeaagles/networks/dis/factory.h"
#include "openeaagles/otw/factory.h"

#include <string>

oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

   if ( name == TestStation::getFactoryName() ) {
      obj = new TestStation;
   }
   else if ( name == TestDisplay::getFactoryName() ) {
      obj = new TestDisplay;
   }
   else if ( name == TestComputer::getFactoryName() ) {
      obj = new TestComputer;
   }

   if (obj == nullptr) obj = oe::otw::factory(name);
   if (obj == nullptr) obj = oe::simulation::factory(name);
   if (obj == nullptr) obj = oe::models::factory(name);
   if (obj == nullptr) obj = oe::dis::factory(name);
   if (obj == nullptr) obj = oe::instruments::factory(name);
   if (obj == nullptr) obj = oe::graphics::factory(name);
   if (obj == nullptr) obj = oe::glut::factory(name);
   if (obj == nullptr) obj = oe::base::factory(name);

   return obj;
}

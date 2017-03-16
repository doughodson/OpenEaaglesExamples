
#include "factory.hpp"

#include "openeaagles/base/Object.hpp"

#include "TestDisplay.hpp"
#include "TestStation.hpp"
#include "TestComputer.hpp"

// factories
#include "openeaagles/base/factory.hpp"
#include "openeaagles/graphics/factory.hpp"
#include "openeaagles/instruments/factory.hpp"
#include "openeaagles/gui/glut/factory.hpp"
#include "openeaagles/simulation/factory.hpp"
#include "openeaagles/models/factory.hpp"
#include "openeaagles/terrain/factory.hpp"
#include "openeaagles/interop/dis/factory.hpp"
#include "openeaagles/otw/factory.hpp"

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
   if (obj == nullptr) obj = oe::terrain::factory(name);
   if (obj == nullptr) obj = oe::dis::factory(name);
   if (obj == nullptr) obj = oe::instruments::factory(name);
   if (obj == nullptr) obj = oe::graphics::factory(name);
   if (obj == nullptr) obj = oe::glut::factory(name);
   if (obj == nullptr) obj = oe::base::factory(name);

   return obj;
}

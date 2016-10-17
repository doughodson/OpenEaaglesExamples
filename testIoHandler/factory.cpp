
#include "factory.hpp"

#include "openeaagles/base/Object.hpp"

#include "Display.hpp"
#include "Table.hpp"

// factories
#include "openeaagles/iodevice/factory.hpp"
#include "openeaagles/gui/glut/factory.hpp"
#include "openeaagles/graphics/factory.hpp"
#include "openeaagles/base/factory.hpp"

#include <string>

oe::base::Object* factory(const std::string& name)
{
   oe::base::Object* obj = nullptr;

   if ( name == Display::getFactoryName() ) {
      obj = new Display();
   }
   else if ( name == Table::getFactoryName() ) {
      obj = new Table();
   }

   if (obj == nullptr) obj = oe::iodevice::factory(name);
   if (obj == nullptr) obj = oe::glut::factory(name);
   if (obj == nullptr) obj = oe::graphics::factory(name);
   if (obj == nullptr) obj = oe::base::factory(name);

    return obj;
}

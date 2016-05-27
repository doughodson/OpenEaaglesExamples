
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "Display.h"
#include "Table.h"

// factories
#include "openeaagles/iodevice/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/base/factory.h"

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

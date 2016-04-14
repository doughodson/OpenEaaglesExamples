
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

namespace oe {
namespace test {

base::Object* factory(const std::string& name)
{
    base::Object* obj = nullptr;

   if ( name == Display::getFactoryName() ) {
      obj = new Display();
   }
   else if ( name == Table::getFactoryName() ) {
      obj = new Table();
   }

   if (obj == nullptr) obj = iodevice::factory(name);
   if (obj == nullptr) obj = glut::factory(name);
   if (obj == nullptr) obj = graphics::factory(name);
   if (obj == nullptr) obj = base::factory(name);

    return obj;
}

}
}

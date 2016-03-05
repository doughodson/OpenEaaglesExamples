//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/base/Object.h"

#include "Display.h"
#include "Table.h"

// factories
#include "openeaagles/iodevice/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/base/factory.h"

#include <cstring>

namespace oe {
namespace test {

Factory::Factory()
{}

base::Object* Factory::createObj(const char* name)
{
    base::Object* obj = nullptr;

   if ( std::strcmp(name, Display::getFactoryName()) == 0 ) {
      obj = new Display();
   }
   else if ( std::strcmp(name, Table::getFactoryName()) == 0 ) {
      obj = new Table();
   }

   if (obj == nullptr) obj = iodevice::factory(name);
   if (obj == nullptr) obj = glut::factory(name);
   if (obj == nullptr) obj = graphics::factory(name);
   if (obj == nullptr) obj = base::factory(name);

    return obj;
}

} // End of test namespace
} // End of oe namespace

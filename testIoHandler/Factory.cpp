//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "Display.h"
#include "Table.h"

// factories
#include "openeaagles/iodevice/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/basic/factory.h"

#include <cstring>

namespace oe {
namespace test {

Factory::Factory()
{}

basic::Object* Factory::createObj(const char* name)
{
    basic::Object* obj = nullptr;

   if ( std::strcmp(name, Display::getFactoryName()) == 0 ) {
      obj = new Display();
   }
   else if ( std::strcmp(name, Table::getFactoryName()) == 0 ) {
      obj = new Table();
   }

   if (obj == nullptr) obj = iodevice::factory(name);
   if (obj == nullptr) obj = glut::factory(name);
   if (obj == nullptr) obj = graphics::factory(name);
   if (obj == nullptr) obj = basic::factory(name);

    return obj;
}

} // End of test namespace
} // End of oe namespace

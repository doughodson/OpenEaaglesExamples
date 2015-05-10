//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "Display.h"
#include "Table.h"

// class factories
#include "openeaagles/ioDevice/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/basic/Factory.h"

#include <cstring>

namespace Eaagles {
namespace Test {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = nullptr;

   if ( std::strcmp(name, Display::getFactoryName()) == 0 ) {
      obj = new Display();
   }
   else if ( std::strcmp(name, Table::getFactoryName()) == 0 ) {
      obj = new Table();
   }

   if (obj == nullptr) obj = IoDevice::Factory::createObj(name);
   if (obj == nullptr) obj = Glut::Factory::createObj(name);
   if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
   if (obj == nullptr) obj = Basic::Factory::createObj(name);

    return obj;
}

} // End of Test namespace
} // End of Eaagles namespace

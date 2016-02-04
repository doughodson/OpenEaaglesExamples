//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "Display.h"

#include "openeaagles/terrain/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/basic/factory.h"

#include <cstring>

namespace oe {
namespace example {

Factory::Factory()
{}

basic::Object* Factory::createObj(const char* name)
{
    basic::Object* obj = nullptr;

    if (std::strcmp(name, Display::getFactoryName()) == 0)
        obj = new Display();

    if (obj == nullptr) obj = terrain::factory(name);
    if (obj == nullptr) obj = graphics::factory(name);
    if (obj == nullptr) obj = glut::factory(name);
    if (obj == nullptr) obj = basic::factory(name);

    return obj;
}

}  // end namespace example
}  // end namespace oe

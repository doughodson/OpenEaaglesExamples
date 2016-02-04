//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "Display.h"

#include "openeaagles/terrain/Factory.h"
#include "openeaagles/graphics/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/basic/Factory.h"

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

    if (obj == nullptr) obj = terrain::Factory::createObj(name);
    if (obj == nullptr) obj = BasicGL::Factory::createObj(name);
    if (obj == nullptr) obj = glut::Factory::createObj(name);
    if (obj == nullptr) obj = basic::Factory::createObj(name);

    return obj;
}

}  // end namespace example
}  // end namespace oe

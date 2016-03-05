
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "Display.h"

#include "openeaagles/terrain/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/base/factory.h"

#include <cstring>

namespace oe {
namespace example {

base::Object* factory(const char* name)
{
    base::Object* obj = nullptr;

    if (std::strcmp(name, Display::getFactoryName()) == 0)
        obj = new Display();

    if (obj == nullptr) obj = terrain::factory(name);
    if (obj == nullptr) obj = graphics::factory(name);
    if (obj == nullptr) obj = glut::factory(name);
    if (obj == nullptr) obj = base::factory(name);

    return obj;
}

}
}


#include "factory.hpp"

#include "openeaagles/base/Object.hpp"

#include "Display.hpp"

#include "openeaagles/terrain/factory.hpp"
#include "openeaagles/graphics/factory.hpp"
#include "openeaagles/gui/glut/factory.hpp"
#include "openeaagles/base/factory.hpp"

#include <string>

oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

    if ( name == Display::getFactoryName() ) {
        obj = new Display();
    }

    if (obj == nullptr) obj = oe::terrain::factory(name);
    if (obj == nullptr) obj = oe::graphics::factory(name);
    if (obj == nullptr) obj = oe::glut::factory(name);
    if (obj == nullptr) obj = oe::base::factory(name);

    return obj;
}

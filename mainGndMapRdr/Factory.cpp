//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "Display.h"
#include "RealBeamRadar.h"
#include "Station.h"

// class factories
#include "openeaagles/simulation/Factory.h"
#include "openeaagles/terrain/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/basic/Factory.h"

namespace Eaagles {
namespace Example {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = 0;

    if ( strcmp(name, Display::getFactoryName()) == 0 ) {
        obj = new Display();
    }
    else if ( strcmp(name, RealBeamRadar::getFactoryName()) == 0 ) {
        obj = new RealBeamRadar();
    }
    else if ( strcmp(name, TestStation::getFactoryName()) == 0 ) {
        obj = new TestStation();
    }
   
    if (obj == 0) obj = Simulation::Factory::createObj(name);
    if (obj == 0) obj = Terrain::Factory::createObj(name);
    if (obj == 0) obj = BasicGL::Factory::createObj(name);
    if (obj == 0) obj = Glut::Factory::createObj(name);
    if (obj == 0) obj = Basic::Factory::createObj(name);

    return obj;
}

}  // end namespace Example
}  // end namespace Eaagles

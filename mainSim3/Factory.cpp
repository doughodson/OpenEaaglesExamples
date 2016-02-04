//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "SimIoHandler.h"
#include "SimPlayer.h"
#include "SimStation.h"
#include "InstrumentPanel.h"

// factories
#include "../shared/xZeroMQHandlers/Factory.h"
#include "openeaagles/basic/Factory.h"
#include "openeaagles/graphics/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/dis/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/iodevice/Factory.h"
#include "openeaagles/otw/Factory.h"
#include "openeaagles/models/factory.h"
#include "openeaagles/simulation/Factory.h"

#include <cstring>

namespace oe {
namespace example {

Factory::Factory()
{}

basic::Object* Factory::createObj(const char* name)
{
    basic::Object* obj = nullptr;

    // Sim3 Station & IoHandler
    if ( std::strcmp(name, SimStation::getFactoryName()) == 0 ) {
        obj = new SimStation();
    }
     else if ( std::strcmp(name, SimIoHandler::getFactoryName()) == 0 ) {
        obj = new SimIoHandler();
    }

    // Sim3 Player
    else if ( std::strcmp(name, SimPlayer::getFactoryName()) == 0 ) {
        obj = new SimPlayer();
    }

    // InstrumentPanel
    else if ( std::strcmp(name, InstrumentPanel::getFactoryName()) == 0 ) {
        obj = new InstrumentPanel();
    }

   if (obj == nullptr) obj = xZeroMQHandlers::factory(name);

   if (obj == nullptr) obj = otw::factory(name);
   if (obj == nullptr) obj = models::factory(name);
   if (obj == nullptr) obj = simulation::factory(name);
   if (obj == nullptr) obj = network::dis::factory(name);
   if (obj == nullptr) obj = iodevice::factory(name);
   if (obj == nullptr) obj = instruments::factory(name);
   if (obj == nullptr) obj = graphics::factory(name);
   if (obj == nullptr) obj = glut::factory(name);
   if (obj == nullptr) obj = basic::factory(name);

    return obj;
}

}  // end namespace example
}  // end namespace oe

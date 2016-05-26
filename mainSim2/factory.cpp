
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "SimIoHandler.h"
#include "SimPlayer.h"
#include "SimStation.h"
#include "InstrumentPanel.h"

// factories
#include "../shared/xzmq/factory.h"
#include "openeaagles/base/factory.h"
#include "openeaagles/graphics/factory.h"
#include "openeaagles/gui/glut/factory.h"
#include "openeaagles/networks/dis/factory.h"
#include "openeaagles/instruments/factory.h"
#include "openeaagles/iodevice/factory.h"
#include "openeaagles/otw/factory.h"
#include "openeaagles/models/factory.h"
#include "openeaagles/simulation/factory.h"

#include <string>

namespace oe {
namespace example {

base::Object* factory(const std::string& name)
{
    base::Object* obj = nullptr;

    // Sim3 Station & IoHandler
    if ( name == SimStation::getFactoryName() ) {
        obj = new SimStation();
    }
     else if ( name == SimIoHandler::getFactoryName() ) {
        obj = new SimIoHandler();
    }

    // Sim3 Player
    else if ( name == SimPlayer::getFactoryName() ) {
        obj = new SimPlayer();
    }

    // InstrumentPanel
    else if ( name == InstrumentPanel::getFactoryName() ) {
        obj = new InstrumentPanel();
    }

   if (obj == nullptr) obj = xzmq::factory(name);

   if (obj == nullptr) obj = otw::factory(name);
   if (obj == nullptr) obj = models::factory(name);
   if (obj == nullptr) obj = simulation::factory(name);
   if (obj == nullptr) obj = dis::factory(name);
   if (obj == nullptr) obj = iodevice::factory(name);
   if (obj == nullptr) obj = instruments::factory(name);
   if (obj == nullptr) obj = graphics::factory(name);
   if (obj == nullptr) obj = glut::factory(name);
   if (obj == nullptr) obj = base::factory(name);

    return obj;
}

}
}

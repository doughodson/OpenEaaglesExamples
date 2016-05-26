
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

oe::base::Object* factory(const std::string& name)
{
    oe::base::Object* obj = nullptr;

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

   if (obj == nullptr) obj = oe::xzmq::factory(name);

   if (obj == nullptr) obj = oe::otw::factory(name);
   if (obj == nullptr) obj = oe::models::factory(name);
   if (obj == nullptr) obj = oe::simulation::factory(name);
   if (obj == nullptr) obj = oe::dis::factory(name);
   if (obj == nullptr) obj = oe::iodevice::factory(name);
   if (obj == nullptr) obj = oe::instruments::factory(name);
   if (obj == nullptr) obj = oe::graphics::factory(name);
   if (obj == nullptr) obj = oe::glut::factory(name);
   if (obj == nullptr) obj = oe::base::factory(name);

    return obj;
}

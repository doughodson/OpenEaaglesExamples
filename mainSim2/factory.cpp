
#include "factory.hpp"

#include "openeaagles/base/Object.hpp"

#include "SimIoHandler.hpp"
#include "SimPlayer.hpp"
#include "SimStation.hpp"
#include "InstrumentPanel.hpp"

// factories
#include "../shared/xzmq/factory.hpp"
#include "openeaagles/base/factory.hpp"
#include "openeaagles/graphics/factory.hpp"
#include "openeaagles/gui/glut/factory.hpp"
#include "openeaagles/interop/dis/factory.hpp"
#include "openeaagles/instruments/factory.hpp"
#include "openeaagles/iodevice/factory.hpp"
#include "openeaagles/otw/factory.hpp"
#include "openeaagles/models/factory.hpp"
#include "openeaagles/simulation/factory.hpp"
#include "openeaagles/terrain/factory.hpp"

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
   if (obj == nullptr) obj = oe::terrain::factory(name);
   if (obj == nullptr) obj = oe::dis::factory(name);
   if (obj == nullptr) obj = oe::iodevice::factory(name);
   if (obj == nullptr) obj = oe::instruments::factory(name);
   if (obj == nullptr) obj = oe::graphics::factory(name);
   if (obj == nullptr) obj = oe::glut::factory(name);
   if (obj == nullptr) obj = oe::base::factory(name);

    return obj;
}

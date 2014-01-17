//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "SimIoHandler.h"
#include "SimPlayer.h"
#include "SimStation.h"
#include "InstrumentPanel.h"

// class factories
#include "../shared/xZeroMQHandlers/Factory.h"
#include "openeaagles/basic/Factory.h"
#include "openeaagles/basicGL/Factory.h"
#include "openeaagles/gui/glut/Factory.h"
#include "openeaagles/dis/Factory.h"
#include "openeaagles/instruments/Factory.h"
#include "openeaagles/ioDevice/Factory.h"
#include "openeaagles/otw/Factory.h"
#include "openeaagles/sensors/Factory.h"
#include "openeaagles/simulation/Factory.h"
#include "openeaagles/vehicles/Factory.h"

namespace Eaagles {
namespace Example {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = 0;

    // Sim3 Station & IoHandler
    if ( strcmp(name, SimStation::getFactoryName()) == 0 ) {
        obj = new SimStation();
    }
     else if ( strcmp(name, SimIoHandler::getFactoryName()) == 0 ) {
        obj = new SimIoHandler();
    }
   
    // Sim3 Player
    else if ( strcmp(name, SimPlayer::getFactoryName()) == 0 ) {
        obj = new SimPlayer();
    }
    
    // InstrumentPanel
    else if ( strcmp(name, InstrumentPanel::getFactoryName()) == 0 ) {
        obj = new InstrumentPanel();
    }

   if (obj == 0) obj = xZeroMQHandlers::Factory::createObj(name);

   if (obj == 0) obj = Otw::Factory::createObj(name);
   if (obj == 0) obj = Vehicle::Factory::createObj(name);
   if (obj == 0) obj = Sensor::Factory::createObj(name);
   if (obj == 0) obj = Simulation::Factory::createObj(name);
   if (obj == 0) obj = Network::Dis::Factory::createObj(name);
   if (obj == 0) obj = IoDevice::Factory::createObj(name);
   if (obj == 0) obj = Instruments::Factory::createObj(name);
   if (obj == 0) obj = BasicGL::Factory::createObj(name);
   if (obj == 0) obj = Glut::Factory::createObj(name);
   if (obj == 0) obj = Basic::Factory::createObj(name);

    return obj;
}

}  // end namespace Example
}  // end namespace Eaagles

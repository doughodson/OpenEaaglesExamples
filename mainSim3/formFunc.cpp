//------------------------------------------------------------------------------
// f16FormFunc() -- parser form function for Sim simulation & PVI components
//
// See parser/Parser.y
//------------------------------------------------------------------------------

#include "formFunc.h"

#include "SimIoHandler.h"
#include "SimPlayer.h"
#include "SimStation.h"
#include "InstrumentPanel.h"

#include "openeaagles/basic/basicFF.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/gui/glut/glutFF.h"
#include "openeaagles/dis/disFF.h"
#include "openeaagles/instruments/instrumentsFF.h"
#include "openeaagles/ioDevice/ioDeviceFF.h"
#include "openeaagles/otw/otwFF.h"
#include "openeaagles/sensors/sensorsFF.h"
#include "openeaagles/simulation/simulationFF.h"
#include "openeaagles/vehicles/vehiclesFF.h"

namespace Eaagles {
namespace Sim3 {

Basic::Object* sim3FormFunc(const char* formname)
{
    Basic::Object* newform = 0;
    
    // Sim3 Station & IoHandler
    if ( strcmp(formname, SimStation::getFormName()) == 0 ) {
        newform = new SimStation();
    }
     else if ( strcmp(formname, SimIoHandler::getFormName()) == 0 ) {
        newform = new SimIoHandler();
    }
   
    // Sim3 Player   
    else if ( strcmp(formname, SimPlayer::getFormName()) == 0 ) {
        newform = new SimPlayer();
    }
    
    // InstrumentPanel  
    else if ( strcmp(formname, InstrumentPanel::getFormName()) == 0 ) {
        newform = new InstrumentPanel();
    }

   if (newform == 0) newform = Otw::otwFormFunc(formname);
   if (newform == 0) newform = Vehicle::vehiclesFormFunc(formname);
   if (newform == 0) newform = Sensor::sensorsFormFunc(formname);
   if (newform == 0) newform = Simulation::simulationFormFunc(formname);
   if (newform == 0) newform = Network::Dis::disFormFunc(formname);
   if (newform == 0) newform = IoDevice::ioDeviceFormFunc(formname);
   if (newform == 0) newform = Instruments::instrumentsFormFunc(formname);
   if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
   if (newform == 0) newform = Glut::glutFormFunc(formname);
   if (newform == 0) newform = Basic::basicFormFunc(formname);

   return newform;
}

}  //end Sim3 namespace
} // End Eaagles namespace

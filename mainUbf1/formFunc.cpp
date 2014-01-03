
#include "formFunc.h"

#include "TestDisplay.h"
#include "TestIoHandler.h"
#include "SimStation.h"

// class factories
#include "xBehaviors/Factory.h"
#include "xPanel/formFunc.h"

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
namespace MainUbf1 {

Basic::Object* formFunc(const char* name)
{
   Basic::Object* obj = 0;

   if ( strcmp(name, SimStation::getFormName()) == 0 ) {
     obj = new SimStation();
   }
   else if ( strcmp(name, TestDisplay::getFormName()) == 0 ) {
     obj = new TestDisplay();
   }
   else if ( strcmp(name, TestIoHandler::getFormName()) == 0 ) {
     obj = new TestIoHandler();
   }

   // Example library packages
   if (obj == 0) obj = xBehaviors::Factory::createObj(name);
   if (obj == 0) obj = xPanel::formFunc(name);

   // OpenEaagles packages
   if (obj == 0) obj = Simulation::simulationFormFunc(name);
   if (obj == 0) obj = Instruments::instrumentsFormFunc(name);
   if (obj == 0) obj = IoDevice::ioDeviceFormFunc(name);
   if (obj == 0) obj = Instruments::instrumentsFormFunc(name);
   if (obj == 0) obj = Vehicle::vehiclesFormFunc(name);
   if (obj == 0) obj = Sensor::sensorsFormFunc(name);
   if (obj == 0) obj = Otw::otwFormFunc(name);
   if (obj == 0) obj = Network::Dis::disFormFunc(name);
   if (obj == 0) obj = BasicGL::basicGLFormFunc(name);
   if (obj == 0) obj = Glut::glutFormFunc(name);
   if (obj == 0) obj = Basic::basicFormFunc(name);
   return obj;
}

} // End MainUbf1 namespace
} // End Eaagles namespace



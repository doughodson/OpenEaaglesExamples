
#include "formFunc.h"

#include "TestDisplay.h"
#include "TestStation.h"
#include "TestComputer.h"

//
#include "openeaagles/basic/basicFF.h"
// graphics
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/instruments/instrumentsFF.h"
#include "openeaagles/gui/glut/glutFF.h"
// simulation
#include "openeaagles/simulation/simulationFF.h"
#include "openeaagles/sensors/sensorsFF.h"
// interoperability and visual
#include "openeaagles/dis/disFF.h"

namespace Eaagles {
namespace MainIR {

Basic::Object* formFunc(const char* formname)
{
   Basic::Object* newform = 0;

   // Test display classes
   if ( strcmp(formname, TestStation::getFormName()) == 0 ) {
      newform = new TestStation;
   }
   else if ( strcmp(formname, TestDisplay::getFormName()) == 0 ) {
      newform = new TestDisplay;
   }
   else if ( strcmp(formname, TestComputer::getFormName()) == 0 ) {
      newform = new TestComputer;
   }

   //if (newform == 0) newform = Vehicle::vehiclesFormFunc(formname);
   if (newform == 0) newform = Simulation::simulationFormFunc(formname);
   if (newform == 0) newform = Sensor::sensorsFormFunc(formname);
   if (newform == 0) newform = Network::Dis::disFormFunc(formname);
   if (newform == 0) newform = Instruments::instrumentsFormFunc(formname);
   if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
   if (newform == 0) newform = Glut::glutFormFunc(formname);
   if (newform == 0) newform = Basic::basicFormFunc(formname);

   return newform;
}

} // End MainIR namespace
} // End Eaagles namespace

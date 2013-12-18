//------------------------------------------------------------------------------
// Form function for mainLaero example
//------------------------------------------------------------------------------

#include "formFunc.h"
#include "TestStation.h"
#include "AdiDisplay.h"
#include "MapDisplay.h"
#include "MapPage.h"

#include "openeaagles/simulation/simulationFF.h"
#include "openeaagles/vehicles/vehiclesFF.h"
#include "openeaagles/sensors/sensorsFF.h"
#include "openeaagles/dis/disFF.h"
#include "openeaagles/instruments/instrumentsFF.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/gui/glut/glutFF.h"
#include "openeaagles/basic/basicFF.h"

#include "../shared-libs/xZeroMQHandlers/formFunc.h"

namespace Eaagles {
namespace MainLaero {

Basic::Object* formFunc(const char* formname)
{
    Basic::Object* newform = 0;

    // Test classes
    if ( strcmp(formname, TestStation::getFormName()) == 0 ) {
        newform = new TestStation();
    }
    else if ( strcmp(formname, AdiDisplay::getFormName()) == 0 ) {
        newform = new AdiDisplay();
    }
    else if ( strcmp(formname, MapDisplay::getFormName()) == 0 ) {
        newform = new MapDisplay();
    }
    else if ( strcmp(formname, MapPage::getFormName()) == 0 ) {
        newform = new MapPage();
    }

    // Example libraries
    if (newform == 0) newform = xZeroMQHandlers::formFunc(formname);

    // Framework libraries
    if (newform == 0) newform = Simulation::simulationFormFunc(formname);
    if (newform == 0) newform = Sensor::sensorsFormFunc(formname);
    if (newform == 0) newform = Instruments::instrumentsFormFunc(formname);
    if (newform == 0) newform = Network::Dis::disFormFunc(formname);
    if (newform == 0) newform = Vehicle::vehiclesFormFunc(formname);
    if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
    if (newform == 0) newform = Glut::glutFormFunc(formname);
    if (newform == 0) newform = Basic::basicFormFunc(formname);
    return newform;
}

} 
} 

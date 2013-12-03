//------------------------------------------------------------------------------
// form function
//------------------------------------------------------------------------------
#include "formFunc.h"

#include "TestDisplay.h"
#include "TestStation.h"
#include "DspRadar.h"
#include "DspRwr.h"
#include "TdAzPtr.h"
#include "TdElevPtr.h"

#include "openeaagles/simulation/simulationFF.h"
#include "openeaagles/sensors/sensorsFF.h"
#include "openeaagles/dis/disFF.h"
#include "openeaagles/instruments/instrumentsFF.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/gui/glut/glutFF.h"
#include "openeaagles/basic/basicFF.h"

namespace Eaagles {
namespace Test {

Basic::Object* formFunc(const char* formname)
{
    Basic::Object* newform = 0;

    // Test classes
    if ( strcmp(formname, TestStation::getFormName()) == 0 ) {
        newform = new TestStation();
    }
    else if ( strcmp(formname, TestDisplay::getFormName()) == 0 ) {
        newform = new TestDisplay();
    }
    else if ( strcmp(formname, DspRadar::getFormName()) == 0 ) {
        newform = new DspRadar();
    }
    else if ( strcmp(formname, DspRwr::getFormName()) == 0 ) {
        newform = new DspRwr();
    }
    else if ( strcmp(formname, TdAzPtr::getFormName()) == 0 ) {
        newform = new TdAzPtr();
    }
    else if ( strcmp(formname, TdElevPtr::getFormName()) == 0 ) {
        newform = new TdElevPtr();
    }

    if (newform == 0) newform = Simulation::simulationFormFunc(formname);
    if (newform == 0) newform = Sensor::sensorsFormFunc(formname);
    if (newform == 0) newform = Instruments::instrumentsFormFunc(formname);
    if (newform == 0) newform = Network::Dis::disFormFunc(formname);
    if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
    if (newform == 0) newform = Glut::glutFormFunc(formname);
    if (newform == 0) newform = Basic::basicFormFunc(formname);
    return newform;
}

} // End Test namespace
} // End Eaagles namespace

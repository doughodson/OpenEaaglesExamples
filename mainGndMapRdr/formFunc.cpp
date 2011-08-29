
#include "Display.h"
#include "RealBeamRadar.h"
#include "Station.h"
#include "openeaagles/simulation/simulationFF.h"
#include "openeaagles/terrain/terrainFF.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/gui/glut/glutFF.h"
#include "openeaagles/basic/basicFF.h"

namespace Eaagles {
namespace MainGndMapRdr {

Basic::Object* formFunc(const char* formname)
{
    Basic::Object* newform = 0;

   if ( strcmp(formname, Display::getFormName()) == 0 ) {
      newform = new Display();
   }
   else if ( strcmp(formname, RealBeamRadar::getFormName()) == 0 ) {
      newform = new RealBeamRadar();
   }
   else if ( strcmp(formname, TestStation::getFormName()) == 0 ) {
      newform = new TestStation();
   }
   
   if (newform == 0) newform = Simulation::simulationFormFunc(formname);
   if (newform == 0) newform = Terrain::terrainFormFunc(formname);
   if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
   if (newform == 0) newform = Glut::glutFormFunc(formname);
   if (newform == 0) newform = Basic::basicFormFunc(formname);
   return newform;
}

}; // end MainGndMapRdr namespace
}; // end Eaagles namespace


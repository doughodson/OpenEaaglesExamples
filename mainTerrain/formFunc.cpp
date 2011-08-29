
#include "Display.h"
#include "openeaagles/terrain/terrainFF.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/gui/glut/glutFF.h"
#include "openeaagles/basic/basicFF.h"

namespace Eaagles {

namespace MainTerrain {

Basic::Object* formFunc(const char* formname)
{
   Basic::Object* newform = 0;

   if (strcmp(formname, Display::getFormName()) == 0) newform = new Display();

   if (newform == 0) newform = Terrain::terrainFormFunc(formname);
   if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
   if (newform == 0) newform = Glut::glutFormFunc(formname);
   if (newform == 0) newform = Basic::basicFormFunc(formname);
   return newform;
}

}; // end MainTerrain namespace
}; // end Eaagles namespace


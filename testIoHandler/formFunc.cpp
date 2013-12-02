//------------------------------------------------------------------------------
// Eaagles::TestIo::mainFormFunc() -- parser form function
//------------------------------------------------------------------------------

#include "formFunc.h"

#include "Display.h"
#include "Table.h"

#include "openeaagles/ioDevice/ioDeviceFF.h"
#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/gui/glut/glutFF.h"
#include "openeaagles/basic/basicFF.h"

namespace Eaagles {
namespace TestIo {

Basic::Object* mainFormFunc(const char* formname)
{
   Basic::Object* newform = 0;

   if ( strcmp(formname, Display::getFormName()) == 0 ) {
      newform = new Display();
   }    
   else if ( strcmp(formname, Table::getFormName()) == 0 ) {
      newform = new Table();
   }    

   if (newform == 0) newform = IoDevice::ioDeviceFormFunc(formname);
   if (newform == 0) newform = BasicGL::basicGLFormFunc(formname);
   if (newform == 0) newform = Glut::glutFormFunc(formname);
   if (newform == 0) newform = Basic::basicFormFunc(formname);
   return newform;
}

} // End of TestIo namespace
} // End of Eaagles namespace


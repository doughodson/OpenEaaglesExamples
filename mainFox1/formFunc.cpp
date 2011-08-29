
#include "formFunc.h"

#include "Station.h"
#include "Display.h"
#include "Worm.h"

#include "openeaagles/basicGL/basicGLFF.h"
#include "openeaagles/basic/basicFF.h"

namespace Eaagles {
namespace mainFox {

Basic::Object* mainFoxFormFunc(const char* formname)
{
  Basic::Object* newform = 0;

  if ( strcmp(formname, Display::getFormName()) == 0 ) {
    newform = new Display();
  }
  else if ( strcmp(formname, Station::getFormName()) == 0 ) {
    newform = new Station();
  }
  else if ( strcmp(formname, Worm::getFormName()) == 0 ) {
    newform = new Worm();
  }

  if (newform == 0) newform = Eaagles::BasicGL::basicGLFormFunc(formname);
  if (newform == 0) newform = Eaagles::Basic::basicFormFunc(formname);

  return newform;
}

} // end mainFox namespace
} // end Eaagles namespace


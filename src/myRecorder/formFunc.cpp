//------------------------------------------------------------------------------
// Form function for the example extended data record library
//------------------------------------------------------------------------------

#include "myRecorder/formFunc.h"

#include "myRecorder/DataRecorder.h"

namespace Eaagles {
namespace MyRecorder {

Basic::Object* formFunc(const char* formname)
{
   Basic::Object* newform = 0;

   if ( strcmp(formname, DataRecorder::getFormName()) == 0 ) {
      newform = new DataRecorder();
   }

   return newform;
}

}
}



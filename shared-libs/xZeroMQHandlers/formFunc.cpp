//------------------------------------------------------------------------------
// Form function for common code for several examples
//------------------------------------------------------------------------------

#include "formFunc.h"
#include "ZeroMQContext.h"
#include "ZeroMQHandler.h"

namespace Eaagles {
namespace xZeroMQHandlers {

Basic::Object* formFunc (const char* const formname)
{
   Basic::Object* newform = 0;

   if (strcmp (formname, ZeroMQContext::getFormName ()) == 0) {
      newform = new ZeroMQContext;
   }
   else if (strcmp (formname, ZeroMQHandler::getFormName ()) == 0) {
      newform = new ZeroMQHandler;
   }

   return newform;
}

} // End xZeroMQHandlers namespace
} // End Eaagles namespace


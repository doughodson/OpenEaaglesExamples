//------------------------------------------------------------------------------
// Form function for common code for several examples
//------------------------------------------------------------------------------

#include "y1panel/formFunc.h"

#include "y1panel/DspRadar.h"
#include "y1panel/DspRwr.h"
#include "y1panel/Hsi.h"
#include "y1panel/TdAzPtr.h"
#include "y1panel/TdElevPtr.h"
#include "y1panel/Pfd.h"
#include "y1panel/SpdLines.h"

namespace Eaagles {
namespace Y1 {

Basic::Object* formFunc(const char* formname)
{
    Basic::Object* newform = 0;

    if ( strcmp(formname, DspRadar::getFormName()) == 0 ) {
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

    // Pfd/Hsi
    else if ( strcmp(formname, Pfd::getFormName()) == 0 ) {
        newform = new Pfd();
    }
    else if ( strcmp(formname, Hsi::getFormName()) == 0 ) {
        newform = new Hsi();
    }
    else if ( strcmp(formname, SpdLines::getFormName()) == 0 ) {
        newform = new SpdLines();
    }

    return newform;
}

} // End Y1 namespace
} // End Eaagles namespace

//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "DspRadar.h"
#include "DspRwr.h"
#include "Hsi.h"
#include "TdAzPtr.h"
#include "TdElevPtr.h"
#include "Pfd.h"
#include "SpdLines.h"

namespace Eaagles {
namespace xPanel {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = 0;

    if ( strcmp(name, DspRadar::getFactoryName()) == 0 ) {
        obj = new DspRadar();
    }
    else if ( strcmp(name, DspRwr::getFactoryName()) == 0 ) {
        obj = new DspRwr();
    }
    else if ( strcmp(name, TdAzPtr::getFactoryName()) == 0 ) {
        obj = new TdAzPtr();
    }
    else if ( strcmp(name, TdElevPtr::getFactoryName()) == 0 ) {
        obj = new TdElevPtr();
    }

    // Pfd/Hsi
    else if ( strcmp(name, Pfd::getFactoryName()) == 0 ) {
        obj = new Pfd();
    }
    else if ( strcmp(name, Hsi::getFactoryName()) == 0 ) {
        obj = new Hsi();
    }
    else if ( strcmp(name, SpdLines::getFactoryName()) == 0 ) {
        obj = new SpdLines();
    }

    return obj;
}

}  // end namespace xPanel
}  // end namespace Eaagles

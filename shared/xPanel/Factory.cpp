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
#include <cstring>

namespace Eaagles {
namespace xPanel {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = nullptr;

    if ( std::strcmp(name, DspRadar::getFactoryName()) == 0 ) {
        obj = new DspRadar();
    }
    else if ( std::strcmp(name, DspRwr::getFactoryName()) == 0 ) {
        obj = new DspRwr();
    }
    else if ( std::strcmp(name, TdAzPtr::getFactoryName()) == 0 ) {
        obj = new TdAzPtr();
    }
    else if ( std::strcmp(name, TdElevPtr::getFactoryName()) == 0 ) {
        obj = new TdElevPtr();
    }

    // Pfd/Hsi
    else if ( std::strcmp(name, Pfd::getFactoryName()) == 0 ) {
        obj = new Pfd();
    }
    else if ( std::strcmp(name, Hsi::getFactoryName()) == 0 ) {
        obj = new Hsi();
    }
    else if ( std::strcmp(name, SpdLines::getFactoryName()) == 0 ) {
        obj = new SpdLines();
    }

    return obj;
}

}  // end namespace xPanel
}  // end namespace Eaagles

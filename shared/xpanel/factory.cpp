
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "DspRadar.h"
#include "DspRwr.h"
#include "Hsi.h"
#include "TdAzPtr.h"
#include "TdElevPtr.h"
#include "Pfd.h"
#include "SpdLines.h"
#include <cstring>

namespace oe {
namespace xpanel {

base::Object* factory(const char* name)
{
    base::Object* obj = nullptr;

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

}
}

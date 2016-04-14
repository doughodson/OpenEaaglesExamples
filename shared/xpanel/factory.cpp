
#include "factory.h"

#include "openeaagles/base/Object.h"

#include "DspRadar.h"
#include "DspRwr.h"
#include "Hsi.h"
#include "TdAzPtr.h"
#include "TdElevPtr.h"
#include "Pfd.h"
#include "SpdLines.h"
#include <string>

namespace oe {
namespace xpanel {

base::Object* factory(const std::string& name)
{
    base::Object* obj = nullptr;

    if ( name == DspRadar::getFactoryName() ) {
        obj = new DspRadar();
    }
    else if ( name == DspRwr::getFactoryName() ) {
        obj = new DspRwr();
    }
    else if ( name == TdAzPtr::getFactoryName() ) {
        obj = new TdAzPtr();
    }
    else if ( name == TdElevPtr::getFactoryName() ) {
        obj = new TdElevPtr();
    }

    // Pfd/Hsi
    else if ( name == Pfd::getFactoryName() ) {
        obj = new Pfd();
    }
    else if ( name == Hsi::getFactoryName() ) {
        obj = new Hsi();
    }
    else if ( name == SpdLines::getFactoryName() ) {
        obj = new SpdLines();
    }

    return obj;
}

}
}


#include "factory.hpp"

#include "openeaagles/base/Object.hpp"

#include "DspRadar.hpp"
#include "DspRwr.hpp"
#include "Hsi.hpp"
#include "TdAzPtr.hpp"
#include "TdElevPtr.hpp"
#include "Pfd.hpp"
#include "SpdLines.hpp"
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

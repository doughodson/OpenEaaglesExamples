//------------------------------------------------------------------------------
// Class: TestStation
//
// Description: Test station for the Ground mapping radar demo
//------------------------------------------------------------------------------
#ifndef __oe_example_TestStation_H__
#define __oe_example_TestStation_H__

#include "openeaagles/simulation/Station.h"

namespace oe {
namespace graphics { class GlutDisplay; }

namespace example {
class Display;

class TestStation : public simulation::Station
{
    DECLARE_SUBCLASS(TestStation, simulation::Station)

public:
    TestStation();

    virtual void updateTC(const double dt = 0.0) override;
    virtual void reset() override;

private:
    bool setDisplay(Display* const d);

    base::safe_ptr<Display> display;
    bool displayInit;
};

}
}

#endif

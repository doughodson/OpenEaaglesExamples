//------------------------------------------------------------------------------
// Class: TestStation
//
// Description: Test station for the Ground mapping radar demo
//------------------------------------------------------------------------------
#ifndef __oe_example_TestStation_H__
#define __oe_example_TestStation_H__

#include "openeaagles/simulation/Station.h"

namespace oe {
namespace BasicGL { class GlutDisplay; }

namespace example {
class Display;

class TestStation : public Simulation::Station
{
    DECLARE_SUBCLASS(TestStation, Simulation::Station)

public:
    TestStation();

    void updateTC(const LCreal dt = 0.0) override;
    void reset() override;

private:
    bool setDisplay(Display* const d);

    basic::safe_ptr<Display> display;
    bool displayInit;
};

} // end example namespace
} // end oe namespace

#endif

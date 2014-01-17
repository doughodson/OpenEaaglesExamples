//------------------------------------------------------------------------------
// Class: TestStation
//
// Description: Test station for the Ground mapping radar demo
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_TestStation_H__
#define __Eaagles_Example_TestStation_H__

#include "openeaagles/simulation/Station.h"

namespace Eaagles {
namespace BasicGL { class GlutDisplay; }

namespace Example {
class Display;

class TestStation : public Simulation::Station
{
    DECLARE_SUBCLASS(TestStation,Simulation::Station)

public:
    TestStation();

    // Component Interface
    virtual void updateTC(const LCreal dt = 0.0f);
    virtual void reset();

private:
    bool setDisplay(Display* const d);

    SPtr<Display> display;
    bool displayInit;
};

} // end Example namespace
} // end Eaagles namespace

#endif

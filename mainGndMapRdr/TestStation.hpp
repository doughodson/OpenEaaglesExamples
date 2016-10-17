
#ifndef __TestStation_H__
#define __TestStation_H__

#include "openeaagles/simulation/Station.hpp"

namespace oe {
   namespace graphics { class GlutDisplay; }
}

class Display;

//------------------------------------------------------------------------------
// Class: TestStation
//
// Description: Test station for the Ground mapping radar demo
//------------------------------------------------------------------------------
class TestStation : public oe::simulation::Station
{
    DECLARE_SUBCLASS(TestStation, oe::simulation::Station)

public:
    TestStation();

    virtual void updateTC(const double dt = 0.0) override;
    virtual void reset() override;

private:
    bool setDisplay(Display* const d);

    oe::base::safe_ptr<Display> display;
    bool displayInit;
};

#endif

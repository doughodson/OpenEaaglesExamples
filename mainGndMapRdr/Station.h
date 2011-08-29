//------------------------------------------------------------------------------
// Class:	TestStation
// Base class:	Basic::Object -> Basic::Component -> Simulation::Station ->
//                            -> MainGndMapRdr::TestStation
//
// Description: Test station for the Ground mapping radar demo
//------------------------------------------------------------------------------
#ifndef EAAGLES_MAINGNDMAPRDR_TESTSTATION_H
#define EAAGLES_MAINGNDMAPRDR_TESTSTATION_H

#include "openeaagles/simulation/Station.h"

namespace Eaagles {
namespace BasicGL { class GlutDisplay; }

namespace MainGndMapRdr {
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

} // end MainGndMapRdr namespace
} // end Eaagles namespace

#endif // EAAGLES_MAINGNDMAPRDR_TESTSTATION_H


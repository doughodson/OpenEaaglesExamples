
#ifndef __TestAdi_H__
#define __TestAdi_H__

#include "openeaagles/graphics/Page.hpp"

//------------------------------------------------------------------------------
// Class: TestAdi
//
// Description: Tests our core ADI graphic
//------------------------------------------------------------------------------
class TestAdi : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestAdi, oe::graphics::Page)

public:
    TestAdi();

    virtual void updateData(const double dt = 0) override;

private:
    double pitch {};           // our pitch (90 to -90)
    SendData pitchSD;
    double  pitchRate {10.0};

    double roll {};            // our roll (3.14 to -3.14)
    SendData rollSD;
    double rollRate {25.0};

    double slip {};            // our side slip (20 to -20)
    SendData slipSD;
    double slipRate {5.0};
};

#endif

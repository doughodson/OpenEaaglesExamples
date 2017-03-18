
#ifndef __TestFtitDial_H__
#define __TestFtitDial_H__

#include "openeaagles/graphics/Page.hpp"

//------------------------------------------------------------------------------
// Class: TestFtitDial
//
// Description: Example Analog Dial Page
// This page will supply test data to the fuel temperature internal dial
//
//------------------------------------------------------------------------------
class TestFtitDial : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestFtitDial, oe::graphics::Page)

public:
    TestFtitDial();

    virtual void updateData(const double dt = 0) override;

private:
    double ftitRotation {};     // our ftit position (0 - 1000)
    double ftitRate {100.0};    // rate which are going (up or down)
    SendData ftitRotationSD;
    SendData ftitRotationROSD;  // for our readout
};

#endif

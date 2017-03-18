
#ifndef __TestHsi_H__
#define __TestHsi_H__

#include "openeaagles/graphics/Page.hpp"

//------------------------------------------------------------------------------
// Class: TestHsi
//
// Description: Tests our core HSI graphic
//------------------------------------------------------------------------------
class TestHsi : public oe::graphics::Page
{
   DECLARE_SUBCLASS(TestHsi, oe::graphics::Page)

public:
    TestHsi();

    virtual void updateData(const double dt = 0) override;

private:
    double heading {};          // our heading
    double headingRate {20.0};  // rate which are going (up or down)
    SendData headingSD;
    SendData headingROSD;

    double dme {};
    SendData dmeROSD;           // dme
};

#endif


#ifndef __TestRotator_H__
#define __TestRotator_H__

#include "openeaagles/graphics/Graphic.hpp"

//------------------------------------------------------------------------------
// Class: TestRotator
//
// Description: Example MFD page
//------------------------------------------------------------------------------
class TestRotator : public oe::graphics::Graphic
{
   DECLARE_SUBCLASS(TestRotator, oe::graphics::Graphic)

public:
    TestRotator();

    virtual void drawFunc() override;
    virtual void updateData(const double dt = 0.0) override;

private:
    double t1Pos {};
    double t1Rate {0.5};
    double t2Pos {};
    double t2Rate {0.7};
    double t3Pos {};
    double t3Rate {0.3};
    double rotate {};
    double rotateRate {20};
    GLfloat light_position[4] {};
    int count {};
};

#endif

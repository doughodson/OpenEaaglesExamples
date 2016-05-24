//------------------------------------------------------------------------------
// Class: TestRotator
//
// Description: Example MFD page
//------------------------------------------------------------------------------
#ifndef __oe_example_TestRotator_H__
#define __oe_example_TestRotator_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
namespace example {

class TestRotator : public graphics::Graphic
{
   DECLARE_SUBCLASS(TestRotator, graphics::Graphic)

public:
    TestRotator();

    virtual void drawFunc() override;
    virtual void updateData(const double dt = 0.0) override;

private:
    double t1Pos;
    double t1Rate;
    double t2Pos;
    double t2Rate;
    double t3Pos;
    double t3Rate;
    double rotate;
    double rotateRate;
    GLfloat light_position[4];
    int count;
};

}
}

#endif

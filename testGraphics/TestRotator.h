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

class TestRotator : public BasicGL::Graphic
{
   DECLARE_SUBCLASS(TestRotator, BasicGL::Graphic)

public:
    TestRotator();

    void drawFunc() override;
    void updateData(const LCreal dt = 0.0) override;

private:
    LCreal t1Pos;
    LCreal t1Rate;
    LCreal t2Pos;
    LCreal t2Rate;
    LCreal t3Pos;
    LCreal t3Rate;
    LCreal rotate;
    LCreal rotateRate;
    GLfloat light_position[4];
    int count;
};

} // End example namespace
} // End oe namespace

#endif

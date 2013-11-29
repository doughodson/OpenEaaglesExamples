//------------------------------------------------------------------------------
// Class: TestRotator
//
// Description: Example MFD page
//------------------------------------------------------------------------------
#ifndef __TestRotator_H__
#define __TestRotator_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace MainW {

class TestRotator : public BasicGL::Graphic
{
   DECLARE_SUBCLASS(TestRotator,BasicGL::Graphic)

public:
    TestRotator();

    virtual void drawFunc();
    virtual void updateData(const LCreal dt = 0.000000);
    
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

} // End MainW namespace
} // End Eaagles namespace

#endif

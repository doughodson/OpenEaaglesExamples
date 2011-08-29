//------------------------------------------------------------------------------
// Class:	TestRotator
// Base class:	Object > BasicGL::Graphic > Page -> TestRotator
//
// Description:	Example MFD page
//
//------------------------------------------------------------------------------
#ifndef	__TestRotator_H__B9FF76F9_DCBA_4add_BA8A_294721C9D2BB
#define __TestRotator_H__B9FF76F9_DCBA_4add_BA8A_294721C9D2BB

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace MainW {

class TestRotator : public BasicGL::Graphic {
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

#endif	/* __TestRotator_H__B9FF76F9_DCBA_4add_BA8A_294721C9D2BB */

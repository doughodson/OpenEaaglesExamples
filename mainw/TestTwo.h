//------------------------------------------------------------------------------
// Class: TestTwo
//
// Description: Control and Send values 'v1' and 'v2' to components 
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_TestTwo_H__
#define __Eaagles_Example_TestTwo_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace Example {

class TestTwo : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(TestTwo,BasicGL::Graphic)

public:
    TestTwo();

    virtual bool event(const int event, Basic::Object* const obj = 0);
    virtual void updateTC(const LCreal dt = 0.0);
    virtual void updateData(const LCreal dt = 0.0);
    virtual void reset();

    //macro functions for slot table mapping
    virtual bool setV1(const Basic::Number* const sv1obj);
    virtual bool setV1Rate(const Basic::Number* const sv1robj);
    virtual bool setV1Max(const Basic::Number* const sv1mobj);
    virtual bool setV1Min(const Basic::Number* const sv1miobj);
    virtual bool setV2(const Basic::Number* const sv2obj);
    virtual bool setV2Rate(const Basic::Number* const sv2robj);
    virtual bool setV2Max(const Basic::Number* const sv2mobj);
    virtual bool setV2Min(const Basic::Number* const sv2miobj);

private:
    
    LCreal v1, v1Rate;
    LCreal v1Max, v1Min;
    
    LCreal v2, v2Rate;
    LCreal v2Max, v2Min;
    
    LCreal iv1, iv1Rate;
    LCreal iv2, iv2Rate;

    SendData v1SD;
    SendData v2SD;
    SendData v1TitleSD;
    SendData v2TitleSD;
};

} // End Example namespace
} // End Eaagles namespace

#endif

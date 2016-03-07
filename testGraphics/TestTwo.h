//------------------------------------------------------------------------------
// Class: TestTwo
//
// Description: Control and Send values 'v1' and 'v2' to components
//------------------------------------------------------------------------------
#ifndef __oe_example_TestTwo_H__
#define __oe_example_TestTwo_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
namespace example {

class TestTwo : public graphics::Graphic
{
    DECLARE_SUBCLASS(TestTwo,graphics::Graphic)

public:
    TestTwo();

    bool event(const int event, base::Object* const obj = nullptr) override;
    void updateTC(const double dt = 0.0) override;
    void updateData(const double dt = 0.0) override;
    void reset() override;

    //macro functions for slot table mapping
    virtual bool setV1(const base::Number* const sv1obj);
    virtual bool setV1Rate(const base::Number* const sv1robj);
    virtual bool setV1Max(const base::Number* const sv1mobj);
    virtual bool setV1Min(const base::Number* const sv1miobj);
    virtual bool setV2(const base::Number* const sv2obj);
    virtual bool setV2Rate(const base::Number* const sv2robj);
    virtual bool setV2Max(const base::Number* const sv2mobj);
    virtual bool setV2Min(const base::Number* const sv2miobj);

private:

    double v1, v1Rate;
    double v1Max, v1Min;

    double v2, v2Rate;
    double v2Max, v2Min;

    double iv1, iv1Rate;
    double iv2, iv2Rate;

    SendData v1SD;
    SendData v2SD;
    SendData v1TitleSD;
    SendData v2TitleSD;
};

} // End example namespace
} // End oe namespace

#endif

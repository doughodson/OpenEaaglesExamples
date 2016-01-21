//------------------------------------------------------------------------------
// Class: TdElevPtr
//
// Description: Test Display Elevation Pointer
//------------------------------------------------------------------------------
#ifndef __oe_example_TdElevPtr_H__
#define __oe_example_TdElevPtr_H__

#include "openeaagles/basicGL/Graphic.h"

namespace oe {
namespace example {

class TdElevPtr : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(TdElevPtr, BasicGL::Graphic)

public:
    TdElevPtr();

    bool event(const int event, Basic::Object* const obj = nullptr) override;
    void draw() override;

    //event handler macro functions
    virtual bool onUpdateValue(const Basic::Number* const ouvobj);

private:
    LCreal  elev;
};

} // End example namespace
} // End oe namespace

#endif

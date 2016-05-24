//------------------------------------------------------------------------------
// Class: TdElevPtr
//
// Description: Test Display Elevation Pointer
//------------------------------------------------------------------------------
#ifndef __oe_example_TdElevPtr_H__
#define __oe_example_TdElevPtr_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
namespace example {

class TdElevPtr : public graphics::Graphic
{
    DECLARE_SUBCLASS(TdElevPtr, graphics::Graphic)

public:
    TdElevPtr();

    virtual bool event(const int event, base::Object* const obj = nullptr) override;
    virtual void draw() override;

    //event handler macro functions
    virtual bool onUpdateValue(const base::Number* const ouvobj);

private:
    double  elev;
};

}
}

#endif

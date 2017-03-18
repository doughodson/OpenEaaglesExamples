
#ifndef __TdElevPtr_H__
#define __TdElevPtr_H__

#include "openeaagles/graphics/Graphic.hpp"

namespace oe {
   namespace base { class Number; }
}

//------------------------------------------------------------------------------
// Class: TdElevPtr
//
// Description: Test Display Elevation Pointer
//------------------------------------------------------------------------------
class TdElevPtr : public oe::graphics::Graphic
{
    DECLARE_SUBCLASS(TdElevPtr, oe::graphics::Graphic)

public:
    TdElevPtr();

    virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;
    virtual void draw() override;

    //event handler macro functions
    virtual bool onUpdateValue(const oe::base::Number* const ouvobj);

private:
    double elev {};
};

#endif

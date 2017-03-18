
#ifndef __TdAzPtr_H__
#define __TdAzPtr_H__

#include "openeaagles/graphics/Graphic.hpp"

//------------------------------------------------------------------------------
// Class: TdAzPtr
//
// Description: Test Display Azimuth Pointer
//------------------------------------------------------------------------------
class TdAzPtr : public oe::graphics::Graphic
{
    DECLARE_SUBCLASS(TdAzPtr, oe::graphics::Graphic)

public:
    TdAzPtr();

    virtual bool event(const int event, oe::base::Object* const obj = nullptr) override;
    virtual void draw() override;

private:
    double azimuth {};
};

#endif

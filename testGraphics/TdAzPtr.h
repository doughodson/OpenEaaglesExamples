//------------------------------------------------------------------------------
// Class: TdAzPtr
//
// Description: Test Display Azimuth Pointer
//------------------------------------------------------------------------------
#ifndef __oe_example_TdAzPtr_H__
#define __oe_example_TdAzPtr_H__

#include "openeaagles/graphics/Graphic.h"

namespace oe {
namespace example {

class TdAzPtr : public graphics::Graphic
{
    DECLARE_SUBCLASS(TdAzPtr,graphics::Graphic)

public:
    TdAzPtr();

    bool event(const int event, base::Object* const obj = nullptr) override;
    void draw() override;

private:
    double azimuth;
};

} // End example namespace
} // End oe namespace

#endif

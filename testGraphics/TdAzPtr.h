//------------------------------------------------------------------------------
// Class: TdAzPtr
//
// Description: Test Display Azimuth Pointer
//------------------------------------------------------------------------------
#ifndef __oe_example_TdAzPtr_H__
#define __oe_example_TdAzPtr_H__

#include "openeaagles/basicGL/Graphic.h"

namespace oe {
namespace example {

class TdAzPtr : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(TdAzPtr,BasicGL::Graphic)

public:
    TdAzPtr();

    bool event(const int event, basic::Object* const obj = nullptr) override;
    void draw() override;

private:
    LCreal azimuth;
};

} // End example namespace
} // End oe namespace

#endif

//------------------------------------------------------------------------------
// Class: TdAzPtr
//
// Description: Test Display Azimuth Pointer
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_TdAzPtr_H__
#define __Eaagles_Example_TdAzPtr_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace Example {

class TdAzPtr : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(TdAzPtr,BasicGL::Graphic)

public:
    TdAzPtr();

    bool event(const int event, Basic::Object* const obj = nullptr) override;
    void draw() override;

private:
    LCreal azimuth;
};

} // End Example namespace
} // End Eaagles namespace

#endif

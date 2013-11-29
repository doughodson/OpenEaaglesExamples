//------------------------------------------------------------------------------
// Class: TdAzPtr
//
// Description: TEST Display Azimuth Pointer
//------------------------------------------------------------------------------
#ifndef __TdAzPtr_H__
#define __TdAzPtr_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace MainW {

class TdAzPtr : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(TdAzPtr,BasicGL::Graphic)

public:
    TdAzPtr();

    virtual bool event(const int event, Basic::Object* const obj = 0);
    virtual void draw();

private:
    LCreal      azimuth;
};

} // End MainW namespace
} // End Eaagles namespace

#endif

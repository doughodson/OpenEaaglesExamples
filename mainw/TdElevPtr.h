//------------------------------------------------------------------------------
// Class: TdElevPtr
//
// Description: Test Display Elevation Pointer
//------------------------------------------------------------------------------
#ifndef __Eaagles_Example_TdElevPtr_H__
#define __Eaagles_Example_TdElevPtr_H__

#include "openeaagles/basicGL/Graphic.h"

namespace Eaagles {
namespace Example {

class TdElevPtr : public BasicGL::Graphic
{
    DECLARE_SUBCLASS(TdElevPtr, BasicGL::Graphic)

public:
    TdElevPtr();

    virtual bool event(const int event, Basic::Object* const obj = 0);
    virtual void draw();

    //event handler macro functions
    virtual bool onUpdateValue(const Basic::Number* const ouvobj);

private:
    LCreal  elev;
};

} // End Example namespace
} // End Eaagles namespace

#endif

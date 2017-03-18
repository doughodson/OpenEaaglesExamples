
#include "TdElevPtr.hpp"
#include "openeaagles/base/Number.hpp"
#include <iostream>

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TdElevPtr, "TdElevPtr")
EMPTY_SERIALIZER(TdElevPtr)
EMPTY_DELETEDATA(TdElevPtr)

TdElevPtr::TdElevPtr()
{
    STANDARD_CONSTRUCTOR()
}

void TdElevPtr::copyData(const TdElevPtr& org, const bool)
{
    BaseClass::copyData(org);
    elev = 0.0;
}

BEGIN_EVENT_HANDLER(TdElevPtr)
    ON_EVENT_OBJ(UPDATE_VALUE, onUpdateValue, base::Number)
END_EVENT_HANDLER()

void TdElevPtr::draw()
{
   if (isVisible())  {
       lcSaveMatrix();
       lcTranslate( 0.0, elev );
       BaseClass::draw();
       lcRestoreMatrix();
   }
}

//------------------------------------------------------------------------------
// onUpdateValue()-- event handler for an updated value
//------------------------------------------------------------------------------
bool TdElevPtr::onUpdateValue(const base::Number* const ouvobj)
{
    if (ouvobj != nullptr) elev = ouvobj->getReal();
    return true;
}

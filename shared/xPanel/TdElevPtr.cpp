//------------------------------------------------------------------------------
// Class: TdElevPtr
//------------------------------------------------------------------------------
#include "TdElevPtr.h"
#include "openeaagles/basic/Number.h"
#include "openeaagles/basic/units/Angles.h"

namespace Eaagles {
namespace xPanel {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TdElevPtr,"TdElevPtr")
EMPTY_SERIALIZER(TdElevPtr)
EMPTY_DELETEDATA(TdElevPtr)

BEGIN_EVENT_HANDLER(TdElevPtr)
    ON_EVENT_OBJ(UPDATE_VALUE, onUpdateValue, Basic::Number)   
END_EVENT_HANDLER()


//------------------------------------------------------------------------------
// Class support functions
//------------------------------------------------------------------------------

// Constructor(s)
TdElevPtr::TdElevPtr()
{
    STANDARD_CONSTRUCTOR()
    elev = 0.0;
}

// copy member data
void TdElevPtr::copyData(const TdElevPtr& org, const bool)
{
    BaseClass::copyData(org);
    elev = org.elev;
}

//------------------------------------------------------------------------------
// Get & Set functions
//------------------------------------------------------------------------------
LCreal TdElevPtr::getElevation() const
{
   return elev;
}

bool TdElevPtr::setElevation(const LCreal v)
{
   elev = lcAepcDeg(v);
   return true;
}

//------------------------------------------------------------------------------
// Event handlers
//------------------------------------------------------------------------------
bool TdElevPtr::onUpdateValue(const Basic::Number* const msg)
{
    bool ok = false;
    if (msg != nullptr) {
      ok = setElevation(msg->getReal());
    }
    return ok;
}

//------------------------------------------------------------------------------
// Translate in Y by the elevation angle and draw.
//------------------------------------------------------------------------------
void TdElevPtr::draw()
{
   if (isVisible())  {
       lcSaveMatrix();
       lcTranslate( 0.0, elev/30.0f );
       BasicGL::Graphic::draw();
       lcRestoreMatrix();
   }
}

} // End xPanel namespace
} // End Eaagles namespace


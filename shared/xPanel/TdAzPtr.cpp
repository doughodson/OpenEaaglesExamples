//------------------------------------------------------------------------------
// Class: TdAzPtr
//------------------------------------------------------------------------------
#include "TdAzPtr.h"
#include "openeaagles/basic/Number.h"
#include "openeaagles/basic/units/Angles.h"

namespace Eaagles {
namespace xPanel {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TdAzPtr,"TdAzPtr")
EMPTY_SERIALIZER(TdAzPtr)
EMPTY_DELETEDATA(TdAzPtr)

BEGIN_EVENT_HANDLER(TdAzPtr)
    ON_EVENT_OBJ(UPDATE_VALUE, onUpdateValue, Basic::Number)   
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// Class support functions
//------------------------------------------------------------------------------

// Constructor(s)
TdAzPtr::TdAzPtr()
{
    STANDARD_CONSTRUCTOR()
    azimuth = 0.0;
}

// copy member data
void TdAzPtr::copyData(const TdAzPtr& org, const bool)
{
    BaseClass::copyData(org);
    azimuth = org.azimuth;
}

//------------------------------------------------------------------------------
// Get & Set functions
//------------------------------------------------------------------------------
LCreal TdAzPtr::getAzimuth() const
{
   return azimuth;
}

bool TdAzPtr::setAzimuth(const LCreal v)
{
   azimuth = lcAepcDeg(v);
   return true;
}

//------------------------------------------------------------------------------
// Event handlers
//------------------------------------------------------------------------------
bool TdAzPtr::onUpdateValue(const Basic::Number* const msg)
{
    bool ok = false;
    if (msg != nullptr) {
      ok = setAzimuth(msg->getReal());
    }
    return ok;
}

//------------------------------------------------------------------------------
// Translate in X by the azimuth angle and draw.
//------------------------------------------------------------------------------
void TdAzPtr::draw()
{
   if (isVisible())  {
       lcSaveMatrix();
       lcTranslate( azimuth/30.0f, 0.0 );
       BasicGL::Graphic::draw();
       lcRestoreMatrix();
   }
}

} // End xPanel namespace
} // End Eaagles namespace


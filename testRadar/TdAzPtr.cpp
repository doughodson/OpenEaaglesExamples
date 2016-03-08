//------------------------------------------------------------------------------
// Class: TdAzPtr
//------------------------------------------------------------------------------
#include "TdAzPtr.h"
#include "openeaagles/base/Number.h"
#include "openeaagles/base/units/Angles.h"

namespace oe {
namespace test {

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TdAzPtr,"TdAzPtr")
EMPTY_SERIALIZER(TdAzPtr)
EMPTY_DELETEDATA(TdAzPtr)

BEGIN_EVENT_HANDLER(TdAzPtr)
    ON_EVENT_OBJ(UPDATE_VALUE, onUpdateValue, base::Number)
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// Class support functions
//------------------------------------------------------------------------------

// Constructor
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
double TdAzPtr::getAzimuth() const
{
   return azimuth;
}

bool TdAzPtr::setAzimuth(const double v)
{
   azimuth = base::Angle::aepcdDeg(v);
   return true;
}

//------------------------------------------------------------------------------
// Event handlers
//------------------------------------------------------------------------------
bool TdAzPtr::onUpdateValue(const base::Number* const msg)
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
       graphics::Graphic::draw();
       lcRestoreMatrix();
   }
}

} // End test namespace
} // End oe namespace

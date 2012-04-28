//
// PlaneAction
//

#include "PlaneAction.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(PlaneAction, "PlaneAction")
EMPTY_SLOTTABLE(PlaneAction)
EMPTY_DELETEDATA(PlaneAction)
EMPTY_COPYDATA(PlaneAction)
EMPTY_SERIALIZER(PlaneAction)

PlaneAction::PlaneAction()
{
   STANDARD_CONSTRUCTOR()

   heading = 0;
   headingChanged = false;

   pitch = 0;
   pitchChanged = false;

   roll = 0;
   rollChanged = false;

   fireMissile = false;
   fireMissileChanged = false;

   throttle = 0;
   throttleChanged = false;

   pitchTrim = 0;
   pitchTrimChanged = false;
}

void PlaneAction::setPitch(const double x)
{
   pitch = x;
   pitchChanged = true;
}

void PlaneAction::setRoll(const double x)
{
   roll = x;
   rollChanged = true;
}

void PlaneAction::setHeading(const double x)
{
   heading = x;
   headingChanged = true;
}

void PlaneAction::setThrottle(const double x)
{
   throttle = x;
   throttleChanged = true;
}
	
void PlaneAction::setFireMissile(const bool x)
{
   fireMissile = x;
   fireMissileChanged = true;
}

void PlaneAction::setPitchTrim(const double x)
{
   pitchTrim = x;
   pitchTrimChanged = true;
}

}
}



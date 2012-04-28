//
// PlaneFlyStraight
//

#include "PlaneFlyStraight.h"

#include "PlaneClimb.h"
#include "PlaneAction.h"
#include "PlaneState.h"

#include "openeaagles/ubf/Action.h"
#include "openeaagles/ubf/State.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(PlaneFlyStraight, "PlaneFlyStraight")
EMPTY_SLOTTABLE(PlaneFlyStraight)
EMPTY_COPYDATA(PlaneFlyStraight)
EMPTY_SERIALIZER(PlaneFlyStraight)
EMPTY_DELETEDATA(PlaneFlyStraight)

PlaneFlyStraight::PlaneFlyStraight()
{
   STANDARD_CONSTRUCTOR()

   holdingAltitude = 4500;
}

Ubf::Action* PlaneFlyStraight::genAction(const Ubf::State* const state, const LCreal dt)
{
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state);

   PlaneAction* action = new PlaneAction();
		
   //Reverse pitch to get level with the horizon
   double pitch = -1 * pState->getPitch();	
   //For positive pitch values, multiply to counteract effects of the negative pitch rate
   //of the dynamics model
   if (pitch > 0) {
      pitch *= 100;
   }
   //If below the threshold, add an amount to the pitch based on the distance below the threshold
   if (pState->getAltitude() < holdingAltitude) {
      pitch += ((holdingAltitude - pState->getAltitude()) / (200));
   }
   action->setPitch(pitch);

   double roll = -1 * pState->getRoll();
   roll *= 100;
   action->setRoll(roll);

   if (pState->getRoll() > 1.57 || pState->getRoll() < -1.57) {
      action->setPitch(action->getPitch() * -1);	//change pitch in the opposite direction if upside-down
   }

   double heading = 1;
   action->setHeading(heading);
   double pitchTrim = 0;
   action->setThrottle(2.0);

   if (pState->getAltitude() < 3500) {
      action->setVote(100);
   } else {
      action->setVote(10);
   }
   return action;
}

}
}

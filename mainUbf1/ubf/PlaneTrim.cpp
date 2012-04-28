//
// PlaneTrim
//

#include "PlaneTrim.h"

#include "PlaneAction.h"
#include "PlaneState.h"

#include "openeaagles/ubf/Action.h"
#include "openeaagles/ubf/State.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(PlaneTrim, "PlaneTrim")
EMPTY_SLOTTABLE(PlaneTrim)
EMPTY_COPYDATA(PlaneTrim)
EMPTY_SERIALIZER(PlaneTrim)
EMPTY_DELETEDATA(PlaneTrim)

PlaneTrim::PlaneTrim()
{
   STANDARD_CONSTRUCTOR()

   holdingAltitude = 4500;
   count = 0;
}

Ubf::Action* PlaneTrim::genAction(const Ubf::State* const state, const LCreal dt)
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
   //action->setPitch(pitch);
		
   double roll = -1 * pState->getRoll();
   roll *= 100;
   //action->setRoll(1);

   if (pState->getRoll() > 1.57 || pState->getRoll() < -1.57) {
      action->setPitch(action->getPitch() * -1); //change pitch in the opposite direction if upside-down
   }

   double heading = 1;
   //action->setHeading(heading);
		
   double pitchTrim = 0;
   if(pState->getPitch() >.00) {
      //if(pState->getPitch() > -.1)
      //{
      //  pitchTrim = pState->getPitch();
      //}else{
      pitchTrim = -.1;
      //}
   } else if(pState->getPitch() < .00) {
      //if(pState->getPitch() < .1)
      //{
      // pitchTrim = pState->getPitch();
      //}else{
      pitchTrim = .1;
      //}
   }
   count++;
   if(count>2) {
      count = 0;
   }
   action->setThrottle(2.0);
   action->setPitchTrim(pitchTrim);

   if (pState->getAltitude() < 3500) {
      action->setVote(100);
   } else {
      action->setVote(11);
   }
   return action;
}

}
}

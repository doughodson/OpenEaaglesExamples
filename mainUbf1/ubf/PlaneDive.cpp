//
// PlaneDive
//

#include "PlaneDive.h"

#include "PlaneClimb.h"
#include "PlaneAction.h"
#include "PlaneState.h"

#include "openeaagles/ubf/Action.h"
#include "openeaagles/ubf/State.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(PlaneDive, "PlaneDive")
EMPTY_SLOTTABLE(PlaneDive)
EMPTY_COPYDATA(PlaneDive)
EMPTY_SERIALIZER(PlaneDive)
EMPTY_DELETEDATA(PlaneDive)

PlaneDive::PlaneDive()
{
   STANDARD_CONSTRUCTOR()
}

Ubf::Action* PlaneDive::genAction(const Ubf::State* const state, const LCreal dt)
{
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state);
		
   PlaneAction* action = new PlaneAction();

   double pitch;
   if(pState->getPitch() > -Eaagles::PI/2) {
      pitch=-1;
   } else {
      pitch = 1;
   }
   action->setPitch(pitch);

   if(!pState->isIncomingMissile()) {
      action->setVote(5);
   } else {
      action->setVote(100);
   }
   return action;
}

}
}

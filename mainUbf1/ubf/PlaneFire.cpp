//
// PlaneFire
//

#include "PlaneFire.h"

#include "PlaneClimb.h"
#include "PlaneAction.h"
#include "PlaneState.h"

#include "openeaagles/ubf/Action.h"
#include "openeaagles/ubf/State.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(PlaneFire, "PlaneFire")
EMPTY_SLOTTABLE(PlaneFire)
EMPTY_COPYDATA(PlaneFire)
EMPTY_SERIALIZER(PlaneFire)
EMPTY_DELETEDATA(PlaneFire)

PlaneFire::PlaneFire()
{
   STANDARD_CONSTRUCTOR()
}

// FAB - cleaned up plane state
// actions do not modify state, no need to cast away const

Ubf::Action* PlaneFire::genAction(const Ubf::State* const state, const LCreal dt)
{
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state);
   
   PlaneAction* action = new PlaneAction();
   action->setVote(0);

   if (pState->isTracking()) {
      if (pState->getDistanceToTracked(pState->getTargetTrack()) < 15000 && !pState->isMissileFired()) {
         action->setFireMissile(true);
         action->setVote(50);
      }
   }
   return action;
}

}
}


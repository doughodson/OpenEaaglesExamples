//
// PlaneFollowEnemy
//

#include "PlaneFollowEnemy.h"

#include "PlaneClimb.h"
#include "PlaneAction.h"
#include "PlaneState.h"

#include "openeaagles/ubf/Action.h"
#include "openeaagles/ubf/State.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(PlaneFollowEnemy, "PlaneFollowEnemy")
EMPTY_SLOTTABLE(PlaneFollowEnemy)
EMPTY_COPYDATA(PlaneFollowEnemy)
EMPTY_SERIALIZER(PlaneFollowEnemy)
EMPTY_DELETEDATA(PlaneFollowEnemy)

PlaneFollowEnemy::PlaneFollowEnemy()
{
   STANDARD_CONSTRUCTOR()
}

// FAB - cleaned up plane state
// actions do not modify state, no need to cast away const

Ubf::Action* PlaneFollowEnemy::genAction(const Ubf::State* const state, const LCreal dt)
{
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state);

   PlaneAction* action = new PlaneAction();
   action->setVote(0);

   if (pState->isTracking()) {
      double pitch = -1 * pState->getPitch()+ .02;// pState->getPitchToEnemy() * 10;	
      //For positive pitch values, multiply to counteract effects of the negative pitch rate
      //of the dynamics model
      if (pitch > 0) {
         // pitch *= 100;
      }
      action->setPitch(pitch);

      double roll = -1 * pState->getRoll();
      unsigned int targetTrack = pState->getTargetTrack();
      roll += pState->getHeadingToTracked(targetTrack) * 10;

      if (pState->getRoll() < -1.57079) {
         roll = -1 * pState->getRoll() - 1.57079;
      } else if (pState->getRoll() > 1.57079) {
         roll = -1 * pState->getRoll() + 1.57079;
      }
      if(roll > 1.0) {
         roll = 1.0;
      }
      if(roll < -1.0) {
         roll = -1.0;
      }
      action->setRoll(roll);
	
      action->setVote(50);
   }
   return action;
}

}
}

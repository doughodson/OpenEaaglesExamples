//
// PlaneBarrelRoll
//

#include "PlaneBarrelRoll.h"

#include "PlaneAction.h"
#include "PlaneState.h"

#include "openeaagles/ubf/Action.h"
#include "openeaagles/ubf/State.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(PlaneBarrelRoll, "PlaneBarrelRoll")
EMPTY_SLOTTABLE(PlaneBarrelRoll)
EMPTY_COPYDATA(PlaneBarrelRoll)
EMPTY_SERIALIZER(PlaneBarrelRoll)
EMPTY_DELETEDATA(PlaneBarrelRoll)

PlaneBarrelRoll::PlaneBarrelRoll()
{
   STANDARD_CONSTRUCTOR()
}

Ubf::Action* PlaneBarrelRoll::genAction(const Ubf::State* const state, const LCreal dt)
{
   const PlaneState *pState = dynamic_cast<const PlaneState*>(state);

   PlaneAction* action = new PlaneAction();

   action->setRoll(1);
   action->setPitch(1);
   action->setThrottle(2);
		
   if(pState->isIncomingMissile()) {
      action->setVote(100);
   } else {
      action->setVote(5);
   }
   return action;
}

}
}

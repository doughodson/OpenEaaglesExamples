//
// PlaneLoop
//
//

#include "PlaneLoop.h"

#include "PlaneClimb.h"
#include "PlaneAction.h"
#include "PlaneState.h"

#include "openeaagles/ubf/Action.h"
#include "openeaagles/ubf/State.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(PlaneLoop, "PlaneLoop")
EMPTY_SLOTTABLE(PlaneLoop)
EMPTY_COPYDATA(PlaneLoop)
EMPTY_SERIALIZER(PlaneLoop)
EMPTY_DELETEDATA(PlaneLoop)

PlaneLoop::PlaneLoop()
{
   STANDARD_CONSTRUCTOR()

   keepGoing = false;
}

Ubf::Action* PlaneLoop::genAction(const Ubf::State* const state, const LCreal dt)
{
   const PlaneState *pState = dynamic_cast<const PlaneState*>(state);

   PlaneAction* action = new PlaneAction();

   action->setRoll(0);
   if(pState->getSpeed() < 600 && !keepGoing) {
      action->setPitch(0);
   } else {
      keepGoing = true;
      action->setPitch(1);
   }
   if(pState->isIncomingMissile()) {
      action->setVote(75);
   } else {
      action->setVote(5);
   }
   return action;
}

}
}


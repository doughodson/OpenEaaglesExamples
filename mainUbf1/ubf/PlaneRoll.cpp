//
// PlaneRoll
//

#include "PlaneRoll.h"

#include "PlaneClimb.h"
#include "PlaneAction.h"
#include "PlaneState.h"

#include "openeaagles/ubf/Action.h"
#include "openeaagles/ubf/State.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(PlaneRoll, "PlaneRoll")
EMPTY_SLOTTABLE(PlaneRoll)
EMPTY_COPYDATA(PlaneRoll)
EMPTY_SERIALIZER(PlaneRoll)
EMPTY_DELETEDATA(PlaneRoll)

PlaneRoll::PlaneRoll()
{
   STANDARD_CONSTRUCTOR()
}

Ubf::Action* PlaneRoll::genAction(const Ubf::State* const state, const LCreal dt)
{
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state);
		
   PlaneAction* action = new PlaneAction();

   double roll=1;
		
   action->setRoll(roll);

   if(!pState->isIncomingMissile()) {
      action->setVote(5);
   } else {
      action->setVote(100);
   }
   return action;
}

}
}

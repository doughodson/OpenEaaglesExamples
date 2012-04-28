//
// PlaneClimb
//
//

#include "PlaneClimb.h"
#include "PlaneAction.h"
#include "PlaneState.h"

#include "openeaagles/simulation/Player.h"
#include "openeaagles/ubf/Action.h"
#include "openeaagles/ubf/State.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(PlaneClimb, "PlaneClimb")
EMPTY_SLOTTABLE(PlaneClimb)
EMPTY_COPYDATA(PlaneClimb)
EMPTY_SERIALIZER(PlaneClimb)
EMPTY_DELETEDATA(PlaneClimb)

PlaneClimb::PlaneClimb()
{
   STANDARD_CONSTRUCTOR()
}

Ubf::Action* PlaneClimb::genAction(const Ubf::State* const state, const LCreal dt)
{
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state);

   PlaneAction* action = new PlaneAction();

   double pitch = -1;
   if(pState->getPitch() < PI/2) {
      pitch=1;
   }
   action->setPitch(pitch);

   if( !pState->isIncomingMissile() ) {
      action->setVote(5);
   } else {
      action->setVote(100);
   }

   return action;
}

}
}

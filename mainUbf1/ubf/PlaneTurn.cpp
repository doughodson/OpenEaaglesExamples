//
// PlaneTurn
//

#include "PlaneTurn.h"

#include "PlaneClimb.h"
#include "PlaneAction.h"
#include "PlaneState.h"

#include "openeaagles/ubf/Action.h"
#include "openeaagles/ubf/State.h"

namespace Eaagles {
namespace MainUbf1 {

IMPLEMENT_SUBCLASS(PlaneTurn, "PlaneTurn")
EMPTY_SLOTTABLE(PlaneTurn)
EMPTY_COPYDATA(PlaneTurn)
EMPTY_SERIALIZER(PlaneTurn)
EMPTY_DELETEDATA(PlaneTurn)

PlaneTurn::PlaneTurn()
{
   STANDARD_CONSTRUCTOR()
}

Ubf::Action* PlaneTurn::genAction(const Ubf::State* const state, const LCreal dt)
{
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state);

   PlaneAction* action = new PlaneAction();

   //std::cout<<pState->getRoll()<<" "<<pState->getPitch()<<" "<<pState->getHeading()<<std::endl;
   double currentAlt = pState->getAltitude();
   double changeInAlt = currentAlt - prevAlt;

   double pitch = 1;//.5;

   action->setPitch(pitch);

   double roll;
   //if(pState->getPitch() >.015)
   //{
		//roll = -1 * pState->getRoll() - 1.25;
   //}else if(pState->getPitch()< 0){
		//roll = -1 * pState->getRoll() - 1.0;
  // }else{
		roll = -1 * pState->getRoll() - 1.047;//1.25
   //}
   //roll *= 100;
   //if(roll > 1)
   //  roll = 1;
   action->setRoll(roll);

   action->setVote(15);

   return action;
}

}
}

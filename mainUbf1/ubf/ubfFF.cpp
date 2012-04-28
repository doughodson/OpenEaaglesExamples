//------------------------------------------------------------------------------
// Form function for the 'ubf' library
//------------------------------------------------------------------------------

#include "ubfFF.h"

// behaviors/arbiters
#include "PlaneBarrelRoll.h"
#include "PlaneClimb.h"
#include "PlaneDive.h"
#include "PlaneFire.h"
#include "PlaneFlyStraight.h"
#include "PlaneFollowEnemy.h"
#include "PlaneLoop.h"
#include "PlaneRoll.h"
#include "PlaneTrim.h"
#include "PlaneTurn.h"
#include "DumbArbiter.h"
#include "PriorityArbiter.h"

// plane agent
#include "PlaneAgent.h"

namespace Eaagles {
namespace MainUbf1 {

Basic::Object* ubfFormFunc(const char* formname)
{
   Basic::Object* newform = 0;

   // agents
   if ( strcmp(formname, PlaneAgent::getFormName()) == 0 ) {
      newform = new PlaneAgent();
   }

   // behaviors
   else if ( strcmp(formname, PlaneBarrelRoll::getFormName()) == 0 ) {
      newform = new PlaneBarrelRoll();
   }
   else if ( strcmp(formname, PlaneClimb::getFormName()) == 0 ) {
      newform = new PlaneClimb();
   }
   else if ( strcmp(formname, PlaneDive::getFormName()) == 0 ) {
      newform = new PlaneDive();
   }
   else if ( strcmp(formname, PlaneFire::getFormName()) == 0 ) {
      newform = new PlaneFire();
   }
   else if ( strcmp(formname, PlaneFlyStraight::getFormName()) == 0 ) {
      newform = new PlaneFlyStraight();
   }
   else if ( strcmp(formname, PlaneFollowEnemy::getFormName()) == 0 ) {
      newform = new PlaneFollowEnemy();
   }
   else if ( strcmp(formname, PlaneLoop::getFormName()) == 0 ) {
      newform = new PlaneLoop();
   }
   else if ( strcmp(formname, PlaneRoll::getFormName()) == 0 ) {
      newform = new PlaneRoll();
   }
   else if ( strcmp(formname, PlaneTrim::getFormName()) == 0 ) {
      newform = new PlaneTrim();
   }
   else if ( strcmp(formname, PlaneTurn::getFormName()) == 0 ) {
      newform = new PlaneTurn();
   }
   // arbiters
   else if ( strcmp(formname, DumbArbiter::getFormName()) == 0 ) {
      newform = new DumbArbiter();
   }
   else if ( strcmp(formname, PriorityArbiter::getFormName()) == 0 ) {
      newform = new PriorityArbiter();
   }

   return newform;
}

}
}


//------------------------------------------------------------------------------
// Class:    formFunc
//
// Base class:    
//
// Description: formFunc for  program
//------------------------------------------------------------------------------

#include "planeAgentFF.h"

#include "PlaneState.h"
#include "PlaneBehaviors.h"
#include "PriorityArbiter.h"

namespace Eaagles {
namespace PlaneAgent {

Basic::Object* planeAgentFormFunc(const char* formname)
{
   Basic::Object* newform = 0;

   if ( strcmp(formname, PlaneState::getFormName()) == 0 ) {
      newform = new PlaneState();
   }

   else if ( strcmp(formname, PriorityArbiter::getFormName()) == 0 ) {
      newform = new PriorityArbiter();
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

   else if ( strcmp(formname, PlaneTurn::getFormName()) == 0 ) {
      newform = new PlaneTurn();
   }
   else if ( strcmp(formname, PlaneSlowTurn::getFormName()) == 0 ) {
      newform = new PlaneSlowTurn();
   }
   else if ( strcmp(formname, PlaneClimb::getFormName()) == 0 ) {
      newform = new PlaneClimb();
   }
   else if ( strcmp(formname, PlaneDive::getFormName()) == 0 ) {
      newform = new PlaneDive();
   }

   else if ( strcmp(formname, PlaneTrim::getFormName()) == 0 ) {
      newform = new PlaneTrim();
   }
   else if ( strcmp(formname, PlaneRoll::getFormName()) == 0 ) {
      newform = new PlaneRoll();
   }
   else if ( strcmp(formname, PlaneBarrelRoll::getFormName()) == 0 ) {
      newform = new PlaneBarrelRoll();
   }
   else if ( strcmp(formname, PlaneLoop::getFormName()) == 0 ) {
      newform = new PlaneLoop();
   }
   return newform;
}

} // End Fox namespace
} // End Eaagles namespace

//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "PlaneState.h"
#include "PlaneBehaviors.h"
#include "PriorityArbiter.h"

namespace Eaagles {
namespace xBehaviors {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = 0;

    if ( strcmp(name, PlaneState::getFactoryName()) == 0 ) {
        obj = new PlaneState();
    }

    else if ( strcmp(name, PriorityArbiter::getFactoryName()) == 0 ) {
        obj = new PriorityArbiter();
    }

    else if ( strcmp(name, PlaneFire::getFactoryName()) == 0 ) {
        obj = new PlaneFire();
    }
    else if ( strcmp(name, PlaneFlyStraight::getFactoryName()) == 0 ) {
        obj = new PlaneFlyStraight();
    }
    else if ( strcmp(name, PlaneFollowEnemy::getFactoryName()) == 0 ) {
        obj = new PlaneFollowEnemy();
    }

    else if ( strcmp(name, PlaneTurn::getFactoryName()) == 0 ) {
        obj = new PlaneTurn();
    }
    else if ( strcmp(name, PlaneSlowTurn::getFactoryName()) == 0 ) {
        obj = new PlaneSlowTurn();
    }
    else if ( strcmp(name, PlaneClimb::getFactoryName()) == 0 ) {
        obj = new PlaneClimb();
    }
    else if ( strcmp(name, PlaneDive::getFactoryName()) == 0 ) {
        obj = new PlaneDive();
    }

    else if ( strcmp(name, PlaneTrim::getFactoryName()) == 0 ) {
        obj = new PlaneTrim();
    }
    else if ( strcmp(name, PlaneRoll::getFactoryName()) == 0 ) {
        obj = new PlaneRoll();
    }
    else if ( strcmp(name, PlaneBarrelRoll::getFactoryName()) == 0 ) {
        obj = new PlaneBarrelRoll();
    }
    else if ( strcmp(name, PlaneLoop::getFactoryName()) == 0 ) {
        obj = new PlaneLoop();
    }

    return obj;
}

}  // end namespace xBehaviors
}  // end namespace Eaagles


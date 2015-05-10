//------------------------------------------------------------------------------
// Class: Factory
//------------------------------------------------------------------------------
#include "Factory.h"

#include "openeaagles/basic/Object.h"

#include "PlaneState.h"
#include "PlaneBehaviors.h"
#include "PriorityArbiter.h"

#include <cstring>

namespace Eaagles {
namespace xBehaviors {

Factory::Factory()
{}

Basic::Object* Factory::createObj(const char* name)
{
    Basic::Object* obj = nullptr;

    if ( std::strcmp(name, PlaneState::getFactoryName()) == 0 ) {
        obj = new PlaneState();
    }

    else if ( std::strcmp(name, PriorityArbiter::getFactoryName()) == 0 ) {
        obj = new PriorityArbiter();
    }

    else if ( std::strcmp(name, PlaneFire::getFactoryName()) == 0 ) {
        obj = new PlaneFire();
    }
    else if ( std::strcmp(name, PlaneFlyStraight::getFactoryName()) == 0 ) {
        obj = new PlaneFlyStraight();
    }
    else if ( std::strcmp(name, PlaneFollowEnemy::getFactoryName()) == 0 ) {
        obj = new PlaneFollowEnemy();
    }

    else if ( std::strcmp(name, PlaneTurn::getFactoryName()) == 0 ) {
        obj = new PlaneTurn();
    }
    else if ( std::strcmp(name, PlaneSlowTurn::getFactoryName()) == 0 ) {
        obj = new PlaneSlowTurn();
    }
    else if ( std::strcmp(name, PlaneClimb::getFactoryName()) == 0 ) {
        obj = new PlaneClimb();
    }
    else if ( std::strcmp(name, PlaneDive::getFactoryName()) == 0 ) {
        obj = new PlaneDive();
    }

    else if ( std::strcmp(name, PlaneTrim::getFactoryName()) == 0 ) {
        obj = new PlaneTrim();
    }
    else if ( std::strcmp(name, PlaneRoll::getFactoryName()) == 0 ) {
        obj = new PlaneRoll();
    }
    else if ( std::strcmp(name, PlaneBarrelRoll::getFactoryName()) == 0 ) {
        obj = new PlaneBarrelRoll();
    }
    else if ( std::strcmp(name, PlaneLoop::getFactoryName()) == 0 ) {
        obj = new PlaneLoop();
    }

    return obj;
}

}  // end namespace xBehaviors
}  // end namespace Eaagles


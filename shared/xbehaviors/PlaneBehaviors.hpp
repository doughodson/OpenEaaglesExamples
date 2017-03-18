//------------------------------------------------------------------------------
// Classes: PlaneBehaviorBase
//          PlaneBehaviorBase -> PlaneFire
//          PlaneBehaviorBase -> PlaneFlyStraight
//          PlaneBehaviorBase -> PlaneFollowEnemy
//          PlaneBehaviorBase -> PlaneTurn
//          PlaneBehaviorBase -> PlaneSlowTurn
//          PlaneBehaviorBase -> PlaneClimb
//          PlaneBehaviorBase -> PlaneDive
//          PlaneBehaviorBase -> PlaneTrim
//          PlaneBehaviorBase -> PlaneRoll
//          PlaneBehaviorBase -> PlaneBarrelRoll
//          PlaneBehaviorBase -> PlaneLoop
//------------------------------------------------------------------------------
#ifndef __oe_xbehaviors_PlaneBehaviors_H__
#define __oe_xbehaviors_PlaneBehaviors_H__

#include "openeaagles/base/ubf/AbstractBehavior.hpp"

namespace oe {
namespace base { class Distance; class State; }
namespace base {
namespace ubf { class AbstractState; class AbstractAction; }
}
namespace xbehaviors {

//------------------------------------------------------------------------------
// test code for a base class for PlaneBehaviors, implements some common slots
//------------------------------------------------------------------------------
class PlaneBehaviorBase : public base::ubf::AbstractBehavior
{
  DECLARE_SUBCLASS(PlaneBehaviorBase, base::ubf::AbstractBehavior)
public:
   PlaneBehaviorBase();

protected:
   bool setSlotCriticalAltitude(const base::Distance* const msg);
   bool setSlotVoteOnCriticalAltitude(const base::Number* const num);
   bool setSlotVoteOnIncomingMissile(const base::Number* const num);

   unsigned int voteOnIncomingMissile {};
   unsigned int voteOnCriticalAltitude {};
   double criticalAltitude {3500.0};
};


//------------------------------------------------------------------------------
// Class: PlaneFire
//
// Description: Behavior class that shoots missiles at enemy planes
//------------------------------------------------------------------------------
class PlaneFire : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneFire, PlaneBehaviorBase)
public:
   PlaneFire();
   virtual base::ubf::AbstractAction* genAction(const base::ubf::AbstractState* const state, const double dt) override;
protected:
   bool setSlotMaxDistance(const base::Distance* const msg);
private:
   double maxDistance {15500.0};
};

class PlaneFlyStraight : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneFlyStraight, PlaneBehaviorBase)
public:
   PlaneFlyStraight();
   virtual base::ubf::AbstractAction* genAction(const base::ubf::AbstractState* const state, const double dt) override;
private:
   double holdingAltitude {4500.0};
};

class PlaneFollowEnemy : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneFollowEnemy, PlaneBehaviorBase)
public:
   PlaneFollowEnemy();
   virtual base::ubf::AbstractAction* genAction(const base::ubf::AbstractState* const state, const double dt) override;
};

class PlaneTurn : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneTurn, PlaneBehaviorBase)
public:
   PlaneTurn();
   virtual base::ubf::AbstractAction* genAction(const base::ubf::AbstractState* const state, const double dt) override;
};

class PlaneSlowTurn : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneSlowTurn, PlaneBehaviorBase)
public:
   PlaneSlowTurn();
   virtual base::ubf::AbstractAction* genAction(const base::ubf::AbstractState* const state, const double dt) override;
};

class PlaneClimb : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneClimb, PlaneBehaviorBase)
public:
   PlaneClimb();
   virtual base::ubf::AbstractAction* genAction(const base::ubf::AbstractState* const state, const double dt) override;
};

class PlaneDive : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneDive, PlaneBehaviorBase)
public:
   PlaneDive();
   virtual base::ubf::AbstractAction* genAction(const base::ubf::AbstractState* const state, const double dt) override;
};

class PlaneTrim : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneTrim, PlaneBehaviorBase)
public:
   PlaneTrim();
   virtual base::ubf::AbstractAction* genAction(const base::ubf::AbstractState* const state, const double dt) override;
private:
   double holdingAltitude {4500.0};
   int count {};
};

class PlaneRoll : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneRoll, PlaneBehaviorBase)
public:
   PlaneRoll();
   virtual base::ubf::AbstractAction* genAction(const base::ubf::AbstractState* const state, const double dt) override;
};

class PlaneBarrelRoll : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneBarrelRoll, PlaneBehaviorBase)
public:
   PlaneBarrelRoll();
   virtual base::ubf::AbstractAction* genAction(const base::ubf::AbstractState* const state, const double dt) override;
};

class PlaneLoop : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneLoop, PlaneBehaviorBase)
public:
   PlaneLoop();
   virtual base::ubf::AbstractAction* genAction(const base::ubf::AbstractState* const state, const double dt) override;
private:
   bool keepGoing {};
};

}
}

#endif


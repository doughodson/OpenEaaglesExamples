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

#include "openeaagles/base/ubf/Behavior.h"

namespace oe {

namespace base { class Distance; class State; }

namespace xbehaviors {

//------------------------------------------------------------------------------
// test code for a base class for PlaneBehaviors, implements some common slots
//------------------------------------------------------------------------------
class PlaneBehaviorBase : public base::ubf::Behavior
{
  DECLARE_SUBCLASS(PlaneBehaviorBase, base::ubf::Behavior)
public:
   PlaneBehaviorBase();

protected:
   bool setSlotCriticalAltitude(const base::Distance* const msg);
   bool setSlotVoteOnCriticalAltitude(const base::Number* const num);
   bool setSlotVoteOnIncomingMissile(const base::Number* const num);

   unsigned int voteOnIncomingMissile;
   unsigned int voteOnCriticalAltitude;
   LCreal criticalAltitude;
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
   base::ubf::Action* genAction(const base::ubf::State* const state, const LCreal dt) override;
protected:
   bool setSlotMaxDistance(const base::Distance* const msg);
private:
   LCreal maxDistance;
};

class PlaneFlyStraight : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneFlyStraight, PlaneBehaviorBase)
public:
   PlaneFlyStraight();
   base::ubf::Action* genAction(const base::ubf::State* const state, const LCreal dt) override;
private:
   double holdingAltitude;
};

class PlaneFollowEnemy : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneFollowEnemy, PlaneBehaviorBase)
public:
   PlaneFollowEnemy();
   base::ubf::Action* genAction(const base::ubf::State* const state, const LCreal dt) override;
};

class PlaneTurn : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneTurn, PlaneBehaviorBase)
public:
   PlaneTurn();
   base::ubf::Action* genAction(const base::ubf::State* const state, const LCreal dt) override;
private:
   //double prevAlt;
};

class PlaneSlowTurn : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneSlowTurn, PlaneBehaviorBase)
public:
   PlaneSlowTurn();
   base::ubf::Action* genAction(const base::ubf::State* const state, const LCreal dt) override;
private:
   //double prevAlt;
};

class PlaneClimb : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneClimb, PlaneBehaviorBase)
public:
   PlaneClimb();
   base::ubf::Action* genAction(const base::ubf::State* const state, const LCreal dt) override;
private:
};

class PlaneDive : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneDive, PlaneBehaviorBase)
public:
   PlaneDive();
   base::ubf::Action* genAction(const base::ubf::State* const state, const LCreal dt) override;
private:
};

class PlaneTrim : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneTrim, PlaneBehaviorBase)
public:
   PlaneTrim();
   base::ubf::Action* genAction(const base::ubf::State* const state, const LCreal dt) override;
private:
   double holdingAltitude;
   int count;
};

class PlaneRoll : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneRoll, PlaneBehaviorBase)
public:
   PlaneRoll();
   base::ubf::Action* genAction(const base::ubf::State* const state, const LCreal dt) override;
private:
};

class PlaneBarrelRoll : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneBarrelRoll, PlaneBehaviorBase)
public:
   PlaneBarrelRoll();
   base::ubf::Action* genAction(const base::ubf::State* const state, const LCreal dt) override;
private:
};


class PlaneLoop : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneLoop, PlaneBehaviorBase)
public:
   PlaneLoop();
   base::ubf::Action* genAction(const base::ubf::State* const state, const LCreal dt) override;
private:
   bool keepGoing;
};

}
}

#endif


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
#ifndef __Eaagles_xBehaviors_PlaneBehaviors_H__
#define __Eaagles_xBehaviors_PlaneBehaviors_H__

#include "openeaagles/basic/ubf/Behavior.h"

namespace Eaagles {

namespace Basic { class Distance; class State; }

namespace xBehaviors {

//------------------------------------------------------------------------------
// test code for a base class for PlaneBehaviors, implements some common slots
//------------------------------------------------------------------------------
class PlaneBehaviorBase : public Basic::Ubf::Behavior
{
  DECLARE_SUBCLASS(PlaneBehaviorBase, Basic::Ubf::Behavior)
public:
   PlaneBehaviorBase();

protected:
   bool setSlotCriticalAltitude(const Basic::Distance* const msg);
   bool setSlotVoteOnCriticalAltitude(const Basic::Number* const num);
   bool setSlotVoteOnIncomingMissile(const Basic::Number* const num);

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
   Basic::Ubf::Action* genAction(const Basic::Ubf::State* const state, const LCreal dt) override;
protected:
   bool setSlotMaxDistance(const Basic::Distance* const msg);
private:
   LCreal maxDistance;
};

class PlaneFlyStraight : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneFlyStraight, PlaneBehaviorBase)
public:
   PlaneFlyStraight();
   Basic::Ubf::Action* genAction(const Basic::Ubf::State* const state, const LCreal dt) override;
private:
   double holdingAltitude;
};

class PlaneFollowEnemy : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneFollowEnemy, PlaneBehaviorBase)
public:
   PlaneFollowEnemy();
   Basic::Ubf::Action* genAction(const Basic::Ubf::State* const state, const LCreal dt) override;
};

class PlaneTurn : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneTurn, PlaneBehaviorBase)
public:
   PlaneTurn();
   Basic::Ubf::Action* genAction(const Basic::Ubf::State* const state, const LCreal dt) override;
private:
   //double prevAlt;
};

class PlaneSlowTurn : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneSlowTurn, PlaneBehaviorBase)
public:
   PlaneSlowTurn();
   Basic::Ubf::Action* genAction(const Basic::Ubf::State* const state, const LCreal dt) override;
private:
   //double prevAlt;
};

class PlaneClimb : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneClimb, PlaneBehaviorBase)
public:
   PlaneClimb();
   Basic::Ubf::Action* genAction(const Basic::Ubf::State* const state, const LCreal dt) override;
private:
};

class PlaneDive : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneDive, PlaneBehaviorBase)
public:
   PlaneDive();
   Basic::Ubf::Action* genAction(const Basic::Ubf::State* const state, const LCreal dt) override;
private:
};

class PlaneTrim : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneTrim, PlaneBehaviorBase)
public:
   PlaneTrim();
   Basic::Ubf::Action* genAction(const Basic::Ubf::State* const state, const LCreal dt) override;
private:
   double holdingAltitude;
   int count;
};

class PlaneRoll : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneRoll, PlaneBehaviorBase)
public:
   PlaneRoll();
   Basic::Ubf::Action* genAction(const Basic::Ubf::State* const state, const LCreal dt) override;
private:
};

class PlaneBarrelRoll : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneBarrelRoll, PlaneBehaviorBase)
public:
   PlaneBarrelRoll();
   Basic::Ubf::Action* genAction(const Basic::Ubf::State* const state, const LCreal dt) override;
private:
};


class PlaneLoop : public PlaneBehaviorBase
{
   DECLARE_SUBCLASS(PlaneLoop, PlaneBehaviorBase)
public:
   PlaneLoop();
   Basic::Ubf::Action* genAction(const Basic::Ubf::State* const state, const LCreal dt) override;
private:
   bool keepGoing;
};

}
}

#endif


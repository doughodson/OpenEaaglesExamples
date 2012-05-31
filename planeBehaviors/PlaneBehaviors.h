//------------------------------------------------------------------------------
// Class: PlaneFire, PlaneTurn, PlaneClimb
//------------------------------------------------------------------------------

#ifndef __Eaagles_PlaneBehaviors_PlaneBehaviors_H__
#define __Eaagles_PlaneBehaviors_PlaneBehaviors_H__

#include "openeaagles/basic/ubf/Behavior.h"

namespace Eaagles {

namespace Basic { class Distance; class State; }

namespace PlaneBehaviors {

// test code for a base class for PlaneBehaviors, implements some common slots
class PlaneBehaviorBase : public Basic::Behavior
{
  DECLARE_SUBCLASS(PlaneBehaviorBase, Basic::Behavior)
public:
   PlaneBehaviorBase();
   Basic::Action* genAction(const Basic::State* const state, const LCreal dt)=0;
protected:
   bool setSlotCriticalAltitude(const Basic::Distance* const msg);
   bool setSlotVoteOnCriticalAltitude(const Basic::Number* const num);
   bool setSlotVoteOnIncomingMissile(const Basic::Number* const num);

   unsigned int voteOnIncomingMissile;
   unsigned int voteOnCriticalAltitude;
   LCreal criticalAltitude;
};


// Class: PlaneFire
//
// Description: Behavior class that shoots missiles at enemy planes
//
class PlaneFire : public PlaneBehaviorBase   //Basic::Behavior
{
   DECLARE_SUBCLASS(PlaneFire, PlaneBehaviorBase)   //Basic::Behavior)
public:
   PlaneFire();
   Basic::Action* genAction(const Basic::State* const state, const LCreal dt);
protected:
   bool setSlotMaxDistance(const Basic::Distance* const msg);
private:
   LCreal maxDistance;
};


class PlaneFlyStraight : public PlaneBehaviorBase   //Basic::Behavior
{
   DECLARE_SUBCLASS(PlaneFlyStraight, PlaneBehaviorBase)   //Basic::Behavior)
public:
   PlaneFlyStraight();
   Basic::Action* genAction(const Basic::State* const state, const LCreal dt);
private:
   double holdingAltitude;
};


class PlaneFollowEnemy : public PlaneBehaviorBase   //Basic::Behavior
{
   DECLARE_SUBCLASS(PlaneFollowEnemy, PlaneBehaviorBase)   //Basic::Behavior)
public:
   PlaneFollowEnemy();
   Basic::Action* genAction(const Basic::State* const state, const LCreal dt);
};


class PlaneTurn : public PlaneBehaviorBase   //Basic::Behavior
{
   DECLARE_SUBCLASS(PlaneTurn, PlaneBehaviorBase)   //Basic::Behavior)
public:
   PlaneTurn();
   Basic::Action* genAction(const Basic::State* const state, const LCreal dt);
private:
   //double prevAlt;
};

class PlaneSlowTurn : public PlaneBehaviorBase   //Basic::Behavior
{
   DECLARE_SUBCLASS(PlaneSlowTurn, PlaneBehaviorBase)   //Basic::Behavior)
public:
   PlaneSlowTurn();
   Basic::Action* genAction(const Basic::State* const state, const LCreal dt);
private:
   //double prevAlt;
};

class PlaneClimb : public PlaneBehaviorBase   //Basic::Behavior
{
   DECLARE_SUBCLASS(PlaneClimb, PlaneBehaviorBase)   //Basic::Behavior)
public:
   PlaneClimb();
   Basic::Action* genAction(const Basic::State* const state, const LCreal dt);
private:
};

class PlaneDive : public PlaneBehaviorBase   //Basic::Behavior
{
   DECLARE_SUBCLASS(PlaneDive, PlaneBehaviorBase)   //Basic::Behavior)
public:
   PlaneDive();
   Basic::Action* genAction(const Basic::State* const state, const LCreal dt);
private:
};

class PlaneTrim : public PlaneBehaviorBase   //Basic::Behavior
{
   DECLARE_SUBCLASS(PlaneTrim, PlaneBehaviorBase)   //Basic::Behavior)
public:
   PlaneTrim();
   Basic::Action* genAction(const Basic::State* const state, const LCreal dt);
private:
   double holdingAltitude;
   int count;
};


class PlaneRoll : public PlaneBehaviorBase   //Basic::Behavior
{
   DECLARE_SUBCLASS(PlaneRoll, PlaneBehaviorBase)   //Basic::Behavior)
public:
   PlaneRoll();
   Basic::Action* genAction(const Basic::State* const state, const LCreal dt);
private:
};


class PlaneBarrelRoll : public PlaneBehaviorBase   //Basic::Behavior
{
   DECLARE_SUBCLASS(PlaneBarrelRoll, PlaneBehaviorBase)   //Basic::Behavior)
public:
   PlaneBarrelRoll();
   Basic::Action* genAction(const Basic::State* const state, const LCreal dt);
private:
};


class PlaneLoop : public PlaneBehaviorBase   //Basic::Behavior
{
   DECLARE_SUBCLASS(PlaneLoop, PlaneBehaviorBase)   //Basic::Behavior)
public:
   PlaneLoop();
   Basic::Action* genAction(const Basic::State* const state, const LCreal dt);
private:
   bool keepGoing;
};

}
}

#endif


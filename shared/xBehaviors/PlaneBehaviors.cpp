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
#include "PlaneBehaviors.h"
#include "PlaneAction.h"
#include "PlaneState.h"

#include "openeaagles/basic/units/Distances.h"
#include "openeaagles/basic/ubf/State.h"

namespace Eaagles {
namespace xBehaviors {

IMPLEMENT_ABSTRACT_SUBCLASS(PlaneBehaviorBase, "PlaneBehaviorBase")
EMPTY_COPYDATA(PlaneBehaviorBase)
EMPTY_SERIALIZER(PlaneBehaviorBase)
EMPTY_DELETEDATA(PlaneBehaviorBase)

// slot table for this class type
BEGIN_SLOTTABLE(PlaneBehaviorBase)
    "criticalAltitude",
    "voteOnCriticalAltitude",
    "voteOnIncomingMissile"
END_SLOTTABLE(PlaneBehaviorBase)

// map slot table to handles
BEGIN_SLOT_MAP(PlaneBehaviorBase)
   ON_SLOT( 1, setSlotCriticalAltitude, Basic::Distance )
   ON_SLOT( 2, setSlotVoteOnCriticalAltitude, Basic::Number)
   ON_SLOT( 3, setSlotVoteOnIncomingMissile, Basic::Number)
END_SLOT_MAP()


PlaneBehaviorBase::PlaneBehaviorBase()
{
   STANDARD_CONSTRUCTOR()
   criticalAltitude = 3500.0f;
   voteOnCriticalAltitude = 0;
   voteOnIncomingMissile = 0;
}

bool PlaneBehaviorBase::setSlotCriticalAltitude(const Basic::Distance* const msg)
{
    bool ok = false;
    if (msg != nullptr) {
       double value = Basic::Meters::convertStatic( *msg );
       criticalAltitude = value;
       ok = true;
    }
    return ok;
}

// [ 1 .. 65535 ]
bool PlaneBehaviorBase::setSlotVoteOnCriticalAltitude(const Basic::Number* const num)
{
   bool ok = false;
   int vote = num->getInt();
   if (vote > 0 && vote <= 65535) {
      voteOnCriticalAltitude = static_cast<unsigned int>(vote);
      ok = true;
   }
   return ok;
}

// [ 1 .. 65535 ]
bool PlaneBehaviorBase::setSlotVoteOnIncomingMissile(const Basic::Number* const num)
{
   bool ok = false;
   int vote = num->getInt();
   if (vote > 0 && vote <= 65535) {
      voteOnIncomingMissile = static_cast<unsigned int>(vote);
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex() for Graphic
//------------------------------------------------------------------------------
Basic::Object* PlaneBehaviorBase::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}


IMPLEMENT_SUBCLASS(PlaneFire, "PlaneFire")
EMPTY_COPYDATA(PlaneFire)
EMPTY_SERIALIZER(PlaneFire)
EMPTY_DELETEDATA(PlaneFire)

// slot table for this class type
BEGIN_SLOTTABLE(PlaneFire)
    "maxDistance"
END_SLOTTABLE(PlaneFire)

// map slot table to handles
BEGIN_SLOT_MAP(PlaneFire)
   ON_SLOT( 1, setSlotMaxDistance, Basic::Distance )
END_SLOT_MAP()

PlaneFire::PlaneFire()
{
   STANDARD_CONSTRUCTOR()
   maxDistance = 15500.0f;

}
Basic::Ubf::Action* PlaneFire::genAction(const Basic::Ubf::State* const state, const LCreal dt)
{
   PlaneAction* action = nullptr;
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state->getUbfStateByType(typeid(PlaneState)));
   
   //if (pState!=0 && pState->isAlive() && pState->isTracking() && pState->getTargetTrack()>=0) {
   if (pState!=nullptr && pState->isAlive() && pState->isTracking() && pState->getTargetTrack()<PlaneState::MAX_TRACKS) {
      if (!pState->isMissileFired() && pState->getDistanceToTracked(pState->getTargetTrack()) < maxDistance) {
         action = new PlaneAction();
         action->setFireMissile(true);

         action->setVote(getVote());
      }
   }
   return action;
}

bool PlaneFire::setSlotMaxDistance(const Basic::Distance* const msg)
{
    bool ok = false;
    if (msg != nullptr) {
       double value = Basic::Meters::convertStatic( *msg );
       maxDistance = value;
       ok = true;
    }
    return ok;
}

//------------------------------------------------------------------------------
// getSlotByIndex() for Graphic
//------------------------------------------------------------------------------
Basic::Object* PlaneFire::getSlotByIndex(const int si)
{
    return BaseClass::getSlotByIndex(si);
}


IMPLEMENT_SUBCLASS(PlaneFlyStraight, "PlaneFlyStraight")
EMPTY_SLOTTABLE(PlaneFlyStraight)
EMPTY_COPYDATA(PlaneFlyStraight)
EMPTY_SERIALIZER(PlaneFlyStraight)
EMPTY_DELETEDATA(PlaneFlyStraight)

PlaneFlyStraight::PlaneFlyStraight()
{
   STANDARD_CONSTRUCTOR()
   holdingAltitude = 4500;
}

Basic::Ubf::Action* PlaneFlyStraight::genAction(const Basic::Ubf::State* const state, const LCreal dt)
{
   PlaneAction* action = nullptr;
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state->getUbfStateByType(typeid(PlaneState)));

   if (pState!=nullptr && pState->isAlive()) {
      action = new PlaneAction();
      
      //Reverse pitch to get level with the horizon
      double pitch = -1 * pState->getPitch();
      //For positive pitch values, multiply to counteract effects of the negative pitch rate
      //of the dynamics model
      if (pitch > 0) {
         pitch *= 100;
      }
      //If below the threshold, add an amount to the pitch based on the distance below the threshold
      if (pState->getAltitude() < holdingAltitude) {
         pitch += ((holdingAltitude - pState->getAltitude()) / (200));
      }
      action->setPitch(pitch);

      double roll = -1 * pState->getRoll();
      roll *= 100;
      action->setRoll(roll);

      if (pState->getRoll() > 1.57 || pState->getRoll() < -1.57) {
         action->setPitch(action->getPitch() * -1);                //change pitch in the opposite direction if upside-down
      }

      double heading = 1;
      action->setHeading(heading);
      //double pitchTrim = 0;
      action->setThrottle(2.0);

      if (voteOnCriticalAltitude!=0 && pState->getAltitude() < criticalAltitude)
         action->setVote(voteOnCriticalAltitude);  // was 100
      else
         action->setVote(getVote());
   }
   return action;
}


IMPLEMENT_SUBCLASS(PlaneFollowEnemy, "PlaneFollowEnemy")
EMPTY_SLOTTABLE(PlaneFollowEnemy)
EMPTY_CONSTRUCTOR(PlaneFollowEnemy)
EMPTY_COPYDATA(PlaneFollowEnemy)
EMPTY_SERIALIZER(PlaneFollowEnemy)
EMPTY_DELETEDATA(PlaneFollowEnemy)

Basic::Ubf::Action* PlaneFollowEnemy::genAction(const Basic::Ubf::State* const state, const LCreal dt)
{
   PlaneAction* action = nullptr;
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state->getUbfStateByType(typeid(PlaneState)));

   if (pState!=nullptr && pState->isAlive() && pState->isTracking() && pState->getTargetTrack()<PlaneState::MAX_TRACKS) {
      action = new PlaneAction();

      double pitch = -1 * pState->getPitch()+ .02;// pState->getPitchToEnemy() * 10;
      //For positive pitch values, multiply to counteract effects of the negative pitch rate
      //of the dynamics model
      if (pitch > 0) {
         // pitch *= 100;
      }
      action->setPitch(pitch);

      double roll = -1 * pState->getRoll();
      unsigned int targetTrack = pState->getTargetTrack();
      roll += pState->getHeadingToTracked(targetTrack) * 10;

      if (pState->getRoll() < -1.57079) {
         roll = -1 * pState->getRoll() - 1.57079;
      } else if (pState->getRoll() > 1.57079) {
         roll = -1 * pState->getRoll() + 1.57079;
      }
      if(roll > 1.0) {
         roll = 1.0;
      }
      if(roll < -1.0) {
         roll = -1.0;
      }
      action->setRoll(roll);

      action->setVote(getVote());
   }
   return action;
}


IMPLEMENT_SUBCLASS(PlaneTurn, "PlaneTurn")
EMPTY_SLOTTABLE(PlaneTurn)
EMPTY_CONSTRUCTOR(PlaneTurn)
EMPTY_COPYDATA(PlaneTurn)
EMPTY_SERIALIZER(PlaneTurn)
EMPTY_DELETEDATA(PlaneTurn)

Basic::Ubf::Action* PlaneTurn::genAction(const Basic::Ubf::State* const state, const LCreal dt)
{
   PlaneAction* action = nullptr;
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state->getUbfStateByType(typeid(PlaneState)));

   if (pState!=nullptr && pState->isAlive()) {
      action = new PlaneAction();
      //std::cout<<pState->getRoll()<<" "<<pState->getPitch()<<" "<<pState->getHeading()<<std::endl;
      //double currentAlt = pState->getAltitude();
      //double changeInAlt = currentAlt - prevAlt;

      double pitch = 1;//.5;
      action->setPitch(pitch);

      double roll;
      //if(pState->getPitch() >.015)
      //{
      //  roll = -1 * pState->getRoll() - 1.25;
      //}else if(pState->getPitch()< 0){
      //roll = -1 * pState->getRoll() - 1.0;
      //}else{
      roll = -1 * pState->getRoll() - 1.047;//1.25
      //}
      //roll *= 100;
      //if(roll > 1)
      //  roll = 1;
      action->setRoll(roll);

      action->setVote(getVote());
   }
   return action;
}


IMPLEMENT_SUBCLASS(PlaneSlowTurn, "PlaneSlowTurn")
EMPTY_SLOTTABLE(PlaneSlowTurn)
EMPTY_CONSTRUCTOR(PlaneSlowTurn)
EMPTY_COPYDATA(PlaneSlowTurn)
EMPTY_SERIALIZER(PlaneSlowTurn)
EMPTY_DELETEDATA(PlaneSlowTurn)

Basic::Ubf::Action* PlaneSlowTurn::genAction(const Basic::Ubf::State* const state, const LCreal dt)
{
   PlaneAction* action = nullptr;
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state->getUbfStateByType(typeid(PlaneState)));

   if (pState!=nullptr && pState->isAlive()) {
      action = new PlaneAction();
      //std::cout<<pState->getRoll()<<" "<<pState->getPitch()<<" "<<pState->getHeading()<<std::endl;
      //double currentAlt = pState->getAltitude();
      //double changeInAlt = currentAlt - prevAlt;

      //double pitch = 1;//.5;
      //action->setPitch(pitch);

      double roll;
      //if(pState->getPitch() >.015)
      //{
      //  roll = -1 * pState->getRoll() - 1.25;
      //}else if(pState->getPitch()< 0){
      //roll = -1 * pState->getRoll() - 1.0;
      //}else{
      roll = -1 * pState->getRoll() - 1.047;//1.25
      //}
      roll *= 100;
      //if(roll > 1)
      //  roll = 1;
      action->setRoll(roll);
      action->setThrottle(1.5);

      action->setVote(getVote());
   }
   return action;
}


IMPLEMENT_SUBCLASS(PlaneClimb, "PlaneClimb")
EMPTY_SLOTTABLE(PlaneClimb)
EMPTY_CONSTRUCTOR(PlaneClimb)
EMPTY_COPYDATA(PlaneClimb)
EMPTY_SERIALIZER(PlaneClimb)
EMPTY_DELETEDATA(PlaneClimb)

Basic::Ubf::Action* PlaneClimb::genAction(const Basic::Ubf::State* const state, const LCreal dt)
{
   PlaneAction* action = nullptr;
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state->getUbfStateByType(typeid(PlaneState)));

   if (pState!=nullptr && pState->isAlive()) {
      double pitch = -1;
      action = new PlaneAction();

      if(pState->getPitch() < PI/2) {
         pitch=1;
      }
      action->setPitch(pitch);

      if (voteOnIncomingMissile!=0 && pState->isIncomingMissile() )
         action->setVote(voteOnIncomingMissile); // was 100
      else
         action->setVote(getVote());
   }
   return action;
}


IMPLEMENT_SUBCLASS(PlaneDive, "PlaneDive")
EMPTY_SLOTTABLE(PlaneDive)
EMPTY_CONSTRUCTOR(PlaneDive)
EMPTY_COPYDATA(PlaneDive)
EMPTY_SERIALIZER(PlaneDive)
EMPTY_DELETEDATA(PlaneDive)

Basic::Ubf::Action* PlaneDive::genAction(const Basic::Ubf::State* const state, const LCreal dt)
{
   PlaneAction* action = nullptr;
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state->getUbfStateByType(typeid(PlaneState)));

   if (pState!=nullptr && pState->isAlive()) {
      double pitch;
      action = new PlaneAction();

      if(pState->getPitch() > -Eaagles::PI/2) {
         pitch=-1;
      } else {
         pitch = 1;
      }
      action->setPitch(pitch);

      if (voteOnIncomingMissile!=0 && pState->isIncomingMissile() )
         action->setVote(voteOnIncomingMissile);   // was 100
      else
         action->setVote(getVote());
   }
   return action;
}


IMPLEMENT_SUBCLASS(PlaneTrim, "PlaneTrim")
EMPTY_SLOTTABLE(PlaneTrim)
EMPTY_COPYDATA(PlaneTrim)
EMPTY_SERIALIZER(PlaneTrim)
EMPTY_DELETEDATA(PlaneTrim)

PlaneTrim::PlaneTrim()
{
   STANDARD_CONSTRUCTOR()
   holdingAltitude = 4500;
   count = 0;
}

Basic::Ubf::Action* PlaneTrim::genAction(const Basic::Ubf::State* const state, const LCreal dt)
{
   PlaneAction* action = nullptr;
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state->getUbfStateByType(typeid(PlaneState)));

   if (pState!=nullptr && pState->isAlive()) {
      double pitchTrim = 0;
      action = new PlaneAction();

      if(pState->getPitch() >0.0) {
         pitchTrim = -.1;
      }else{
         pitchTrim = .1;
      }
      action->setPitchTrim(pitchTrim);

      if (voteOnCriticalAltitude!=0 && pState->getAltitude() < criticalAltitude)
         action->setVote(voteOnCriticalAltitude);   // was 100
      else
         action->setVote(getVote());
   }
   return action;
}


IMPLEMENT_SUBCLASS(PlaneRoll, "PlaneRoll")
EMPTY_SLOTTABLE(PlaneRoll)
EMPTY_CONSTRUCTOR(PlaneRoll)
EMPTY_COPYDATA(PlaneRoll)
EMPTY_SERIALIZER(PlaneRoll)
EMPTY_DELETEDATA(PlaneRoll)

Basic::Ubf::Action* PlaneRoll::genAction(const Basic::Ubf::State* const state, const LCreal dt)
{
   PlaneAction* action = nullptr;
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state->getUbfStateByType(typeid(PlaneState)));

   if (pState!=nullptr && pState->isAlive()) {
      double roll=1;
      action = new PlaneAction();

      action->setRoll(roll);

      if (voteOnIncomingMissile!=0 && pState->isIncomingMissile() )
         action->setVote(voteOnIncomingMissile);   // was 100
      else
         action->setVote(getVote());
   }
   return action;
}


IMPLEMENT_SUBCLASS(PlaneBarrelRoll, "PlaneBarrelRoll")
EMPTY_SLOTTABLE(PlaneBarrelRoll)
EMPTY_CONSTRUCTOR(PlaneBarrelRoll)
EMPTY_COPYDATA(PlaneBarrelRoll)
EMPTY_SERIALIZER(PlaneBarrelRoll)
EMPTY_DELETEDATA(PlaneBarrelRoll)

Basic::Ubf::Action* PlaneBarrelRoll::genAction(const Basic::Ubf::State* const state, const LCreal dt)
{
   PlaneAction* action = nullptr;
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state->getUbfStateByType(typeid(PlaneState)));

   if (pState!=nullptr && pState->isAlive()) {
      action = new PlaneAction();

      action->setRoll(1);
      action->setPitch(1);
      action->setThrottle(2);

      if (voteOnIncomingMissile!=0 && pState->isIncomingMissile() )
         action->setVote(voteOnIncomingMissile);                     // was 100
      else
         action->setVote(getVote());
   }
   return action;
}


IMPLEMENT_SUBCLASS(PlaneLoop, "PlaneLoop")
EMPTY_SLOTTABLE(PlaneLoop)
EMPTY_COPYDATA(PlaneLoop)
EMPTY_SERIALIZER(PlaneLoop)
EMPTY_DELETEDATA(PlaneLoop)

PlaneLoop::PlaneLoop()
{
   STANDARD_CONSTRUCTOR()
   keepGoing = false;
}

Basic::Ubf::Action* PlaneLoop::genAction(const Basic::Ubf::State* const state, const LCreal dt)
{
   PlaneAction* action = nullptr;
   const PlaneState* pState = dynamic_cast<const PlaneState*>(state->getUbfStateByType(typeid(PlaneState)));

   if (pState!=nullptr && pState->isAlive()) {
      action = new PlaneAction();
      action->setRoll(0.0);
      if(pState->getSpeed() < 600 && !keepGoing) {
         action->setPitch(0);
      } else {
         keepGoing = true;
         action->setPitch(1);
      }

      if (voteOnIncomingMissile!=0 && pState->isIncomingMissile() )
         action->setVote(voteOnIncomingMissile); // was 75
      else
         action->setVote(getVote());
   }
   return action;
}

}
}



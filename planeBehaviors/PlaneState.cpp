//
// PlaneState
//

// this implementation of PlaneState:
// assumes that player using this state has only one missile (or is ok with firing all missiles at first target)
//

#include "PlaneState.h"

#include "openeaagles/basic/List.h"
#include "openeaagles/basic/PairStream.h"

#include "openeaagles/simulation/Radar.h"
#include "openeaagles/simulation/TrackManager.h"
#include "openeaagles/simulation/Track.h"
#include "openeaagles/simulation/OnboardComputer.h"
#include "openeaagles/simulation/StoresMgr.h"
#include "openeaagles/simulation/Missile.h"
#include "openeaagles/simulation/AirVehicle.h"
#include "openeaagles/simulation/Simulation.h"

namespace Eaagles {
namespace PlaneBehaviors {

IMPLEMENT_SUBCLASS(PlaneState, "PlaneState")
EMPTY_SLOTTABLE(PlaneState)
EMPTY_DELETEDATA(PlaneState)
EMPTY_COPYDATA(PlaneState)
EMPTY_SERIALIZER(PlaneState)

PlaneState::PlaneState()
{
   STANDARD_CONSTRUCTOR()

   alive          = false;
   roll           = 0;
   pitch          = 0;
   heading        = 0;
   rollRate       = 0;
   pitchRate      = 0;
   yawRate        = 0;
   altitude       = 0;
   throttle       = 0;
   speed          = 0;
   pitchTrim      = 0;
   numTracks      = 0;
   tracking       = false;
   missileFired   = false;
   targetTrack    = MAX_TRACKS;  // 0 is a valid target track, use MAX_TRACKS to signal "no tgt track"
   numEngines     = 0;
}

void PlaneState::reset()
{
   alive          = false;
   roll           = 0;
   pitch          = 0;
   heading        = 0;
   rollRate       = 0;
   pitchRate      = 0;
   yawRate        = 0;
   altitude       = 0;
   throttle       = 0;
   speed          = 0;
   pitchTrim      = 0;
   numTracks      = 0;
   tracking       = false;
   missileFired   = false;
   targetTrack    = MAX_TRACKS;  // 0 is a valid target track, use MAX_TRACKS to signal "no tgt track"
   numEngines     = 0;

   BaseClass::reset();
}

void PlaneState::updateState(const Basic::Component* const actor)
{
   const Simulation::AirVehicle* airVehicle = dynamic_cast<const Simulation::AirVehicle*>(actor);
   setAlive(false);
   if (airVehicle != 0 && airVehicle->isActive()) {
      setAltitude(airVehicle->getAltitude());
      setAlive(airVehicle->getMode() == Simulation::Player::ACTIVE);
      setHeading(airVehicle->getHeading());
      setPitch(airVehicle->getPitch());
      setRoll(airVehicle->getRoll());
      osg::Vec3d angularVels = airVehicle->getAngularVelocities();
      setRollRate(angularVels.x());
      setPitchRate(angularVels.y());
      setYawRate(angularVels.z());      
      setTracking(false);
      setTargetTrack(MAX_TRACKS);  // 0 is a valid target track, use MAX_TRACKS to signal "no tgt track"
      setSpeed(airVehicle->getCalibratedAirspeed());
      setNumEngines(airVehicle->getNumberOfEngines());
      setIncomingMissile(false);
      setMissileFired(false);

      // determine if we have a missile to fire 
      // this state class has no way to determine whether we've fired a missile other than checking to see if sms is out of missiles to fire.
      // which means, it will fire all its missiles at first target.
      const Simulation::StoresMgr* stores = airVehicle->getStoresManagement();
      if (stores != 0) {
         const Simulation::Missile* wpn = stores->getNextMissile();
         if (!wpn)
		      setMissileFired(true);
      }
      else {
         // we have no SMS, we can't fire a missile;
         setMissileFired(true);
      }

      const Basic::String* playerName = airVehicle->getName();
      // DH - DOES NOT COMPILE WITH CONST -- ????
      Simulation::AirVehicle* airVehicleX = const_cast<Simulation::AirVehicle*>(airVehicle);
      const Basic::Pair* sensorPair = airVehicleX->getSensorByType(typeid(Simulation::Radar));

      if (sensorPair != 0) {
         const Simulation::Radar* radar = (const Simulation::Radar*)sensorPair->object();
         if (radar != 0) {
            const Simulation::TrackManager* trackManager = radar->getTrackManager();
            SPtr<Simulation::Track> trackList[50];
            unsigned int nTracks = trackManager->getTrackList(trackList, 50);

            for (int trackIndex = nTracks -1; trackIndex >= 0; trackIndex--) {
               setHeadingToTracked(trackIndex, trackList[trackIndex]->getRelAzimuth());
               setPitchToTracked(trackIndex, trackList[trackIndex]->getElevation());
               setDistanceToTracked(trackIndex, trackList[trackIndex]->getRange());
               
               // do we have a "target track"? (shootlist is 1-based)
               if (getTargetTrack()==MAX_TRACKS && trackList[trackIndex]->getShootListIndex() == 1) {
                  setTargetTrack(trackIndex);
               }
               setTracking(true);
               setNumTracks(nTracks);

               // hack to implement "missile warning"
               if (isIncomingMissile() == false) {
                  // is this track a weapon, and if so, is it targeting me?
                  Simulation::Player* target = trackList[trackIndex]->getTarget();
                  Simulation::Weapon* weapon = dynamic_cast<Simulation::Weapon*> (target);
                  if (weapon!=0 && !weapon->isDead()) {
                     Simulation::Player* wpntgt = weapon->getTargetPlayer();
                     if (wpntgt == airVehicle) {
                        setIncomingMissile(true);
                     }
                  }
               }

            }
         }
      }

      const Simulation::OnboardComputer* oc = airVehicle->getOnboardComputer();
      if (oc != 0) {
         const Simulation::TrackManager* rtm = oc->getTrackManagerByType(typeid(Simulation::RwrTrkMgr));
         if(rtm !=0) {
            SPtr<Simulation::Track> trackList[50];
            unsigned int nTracks = rtm->getTrackList(trackList, 50);
            int newTracks = 0;
            for (unsigned int trackIndex = 0; trackIndex < nTracks; trackIndex++) {
               Simulation::Player* target = trackList[trackIndex]->getTarget();
               bool alreadyTracked = false;
               for (int currTracks = 0; currTracks>getNumTracks(); currTracks++) {
                  // tracks are the same if the associated players are the same
                  if(trackList[currTracks]->getTarget()==target) {
                     alreadyTracked = true;
                     break;
                  }
               }

               if (!alreadyTracked && (getNumTracks() + newTracks) < MAX_TRACKS) {
                  int newTrackIndex = getNumTracks() + newTracks;
                  newTracks++;
                  setHeadingToTracked(newTrackIndex, trackList[trackIndex]->getRelAzimuth());
                  setPitchToTracked(newTrackIndex, trackList[trackIndex]->getElevation());
                  setDistanceToTracked(newTrackIndex, trackList[trackIndex]->getRange());
                  setTracking(true);

                  // update numTracks to new sum of radar + rwr tracks
                  setNumTracks(getNumTracks()+newTracks);
               }

               // do we have a "target track"? (shootlist is 1-based)
               if (getTargetTrack()==MAX_TRACKS && trackList[trackIndex]->getShootListIndex() == 1) {
                  setTargetTrack(trackIndex);
               }
               else if (getTargetTrack() == MAX_TRACKS) {
                  setTargetTrack(trackIndex); // in absence of any target, make the first rwr track the target?
               }

               // hack to implement "missile warning"
               if (isIncomingMissile() == false) {
                  // is this track a weapon, and if so, is it targeting me?
                  Simulation::Weapon* weapon = dynamic_cast<Simulation::Weapon*> (target);
                  if (weapon!=0 && !weapon->isDead()) {
                     Simulation::Player* wpntgt = weapon->getTargetPlayer();
                     if (wpntgt == airVehicle) {
                        setIncomingMissile(true);
                     }
                  }
               }

            }
         }
      }
   }
   BaseClass::updateState(actor);
}

void PlaneState::setPitchToTracked(const unsigned int trackNumber, const double angle)
{
   if ( trackNumber<numTracks ) {
      pitchToTracked[trackNumber] = angle;
   }
}

double PlaneState::getPitchToTracked(const unsigned int trackNumber) const
{
   if ( trackNumber<numTracks ) {
      return pitchToTracked[trackNumber];
   }
   std::cout << trackNumber << " is out of bounds of the tracking array of PlaneState! Error!\n";
   return trackNumber;
}

void PlaneState::setHeadingToTracked(const unsigned int trackNumber, const double angle)
{
   if (trackNumber < numTracks) {
      headingToTracked[trackNumber] = angle;
   }
}

double PlaneState::getHeadingToTracked(const unsigned int trackNumber) const
{
   if (trackNumber < numTracks) {
      return headingToTracked[trackNumber];
   }
   std::cout << trackNumber << " is out of bounds of the tracking array of PlaneState! Error!\n";
   return trackNumber;
}

void PlaneState::setDistanceToTracked(const unsigned int trackNumber, const double distance)
{
   if (trackNumber < numTracks) {
      distanceToTracked[trackNumber] = distance;
   }
}

double PlaneState::getDistanceToTracked(const unsigned int trackNumber) const
{
   if (trackNumber < numTracks) {
      return distanceToTracked[trackNumber];
   }
   std::cout << trackNumber << " is out of bounds of the tracking array of PlaneState! Error!\n";
   return trackNumber;
}

}
}


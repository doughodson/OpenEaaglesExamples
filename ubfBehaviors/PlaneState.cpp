//
// PlaneState
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
namespace PlaneAgent {


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
   targetTrack    = -1;  // 0 is a valid target track
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
   targetTrack    = -1;  // 0 is a valid target track
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
      setTargetTrack(-1);  // 0 is a valid target track
      setSpeed(airVehicle->getCalibratedAirspeed());
      setNumEngines(airVehicle->getNumberOfEngines());
      setIncomingMissile(false);
      setMissileFired(false);

      // determine if we have a missile to fire 
      // -some parts of PlaneState assume that this a/c has only one missile
      const Simulation::StoresMgr* stores = airVehicle->getStoresManagement();
      if (stores != 0) {
         // whether i fired is a matter of fact, not perception
         // (whether a missile is incoming is a matter of perception)
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
            unsigned int numTracks = trackManager->getTrackList(trackList, 50);

            for (int trackIndex = numTracks -1; trackIndex >= 0; trackIndex--) {
               setHeadingToTracked(trackIndex, trackList[trackIndex]->getRelAzimuth());
               setPitchToTracked(trackIndex, trackList[trackIndex]->getElevation());
               setDistanceToTracked(trackIndex, trackList[trackIndex]->getRange());
               // track's shootlist is 1-based?
               if (trackList[trackIndex]->getShootListIndex() == 1) {
                  setTargetTrack(trackIndex);
               }
               setTracking(true);
               setNumTracks(numTracks);


			      //temporary hack to replace OE's lack of missile warning
               Simulation::Player* target = trackList[trackIndex]->getTarget();
               char* targetName = target->getName()->getCopyString();
               //DRAC-FAB - if there is a third player, it is the  missile.
			   // determine if i am the launcher or the target, and update state accordingly.
			   if(strncmp(targetName,"duck",4)!=0 && strncmp(targetName,"p",1)!=0 ) {
                  if(strncmp(playerName->getCopyString(),"duck",4)!=0)
					   setIncomingMissile(true);
			      else
					   setMissileFired(true);
               } //end hack
            }
         }
      }

      const Simulation::OnboardComputer* oc = airVehicle->getOnboardComputer();
      if (oc != 0) {
         const Simulation::TrackManager* rtm = oc->getTrackManagerByType(typeid(Simulation::RwrTrkMgr));
         if(rtm !=0) {
            SPtr<Simulation::Track> trackList[50];
            unsigned int numTracks = rtm->getTrackList(trackList, 50);
            int newTracks = 0;
            for (unsigned int trackIndex = 0; trackIndex < numTracks; trackIndex++) {
               //Simulation::Track* trk = trackList[trackIndex];
               Simulation::Player* target = trackList[trackIndex]->getTarget();
               bool alreadyTracked = false;
               for(int currTracks = 0; currTracks>getNumTracks();currTracks++) {
                  //tracks are the same if the associated players are the same
                  if(trackList[currTracks]->getTarget()==target) {
                     alreadyTracked = true;
                     break;
                  }
               }
               if(alreadyTracked) {
                  continue;
               }
               newTracks++;
      			
               int newTrackIndex= getNumTracks()-1 + newTracks;
               setHeadingToTracked(newTrackIndex, trackList[trackIndex]->getRelAzimuth());
               setPitchToTracked(newTrackIndex, trackList[trackIndex]->getElevation());
               setDistanceToTracked(newTrackIndex, trackList[trackIndex]->getRange());
               // track's shootlist is 1-based?
               if (trackList[trackIndex]->getShootListIndex() == 1) {
                  setTargetTrack(trackIndex);
               }
               setTracking(true);
               setNumTracks(numTracks);


		       //temporary hack to replace OE's lack of missile warning
               char *targetName = target->getName()->getCopyString();
                  //DRAC-FAB - if there is a third player, it is the  missile.
			      // determine if i am the launcher or the target, and update state accordingly.
			      if(strncmp(targetName,"duck",4)!=0 && strncmp(targetName,"p",1)!=0 ) {
                     if(strncmp(playerName->getCopyString(),"duck",4)!=0)
					      setIncomingMissile(true);
		         else
				      setMissileFired(true);
               } //end hack
            }
         }
      }

      // DRAC-FAB this does nothing currently, but is possibly supposed to be a different implementation of missile warning ?
      const Basic::PairStream* players = airVehicle->getSimulation()->getPlayers(); 
      const Basic::List::Item* p = players->getFirstItem();
      while(p != 0) {
         Basic::Pair* pair = (Basic::Pair*)(p->getValue());
         Simulation::Player* playa = (Simulation::Player*)(pair->object());
         Simulation::OnboardComputer* obc = playa->getOnboardComputer();
         Simulation::Player* tgt = 0;
         if ( obc!=0 ) {
            Simulation::Track* tgttrk = obc->getNextTarget();
            if( tgttrk!=0 ) {
               tgt = tgttrk->getTarget();
            }
         } 
         else if (playa->isMajorType(Simulation::Player::WEAPON)) {
            Simulation::Weapon* missile = (Simulation::Weapon*)playa;
            tgt = missile->getTargetPlayer();
            //if its not the player we're updating, they're not dead and they're targetting the player in question
            if( (airVehicle->getName()!=missile->getName()) && !missile->isDead() && (tgt==airVehicle) ) {
            }
         }
         if ( tgt!=0 ) {   //numShootList>0)
            //std::cout<<tgt->getName()->getCopyString()<<std::endl;//shootlist[0]->getTarget()->getName()->getCopyString()<<std::endl;
         }
         if( (airVehicle->getName()!=playa->getName()) && !playa->isDead() ) {
            //playa->get
         }
         p = p->getNext();
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
} // end Eaagles namespace

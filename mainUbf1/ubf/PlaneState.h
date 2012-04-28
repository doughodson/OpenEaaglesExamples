//
// Class: PlaneState
//
// Base class: Basic::Object -> Ubf::State -> PlaneState
//
// Description: State of aircraft
//

#ifndef __Eaagles_MainUbf1_PlaneState_H__
#define __Eaagles_MainUbf1_PlaneState_H__

#include "openeaagles/ubf/State.h"

namespace Eaagles {

namespace Simulation { class Player; }

namespace MainUbf1 {

class PlaneState : public Ubf::State
{
   DECLARE_SUBCLASS(PlaneState, Ubf::State)

public:

   PlaneState();

   virtual void updateState(const Eaagles::Simulation::Player* const ownship);

   // set/get
   void setAlive(const bool x)                 { alive = x; return; }
   bool isAlive() const                        { return alive; }

   void setRoll(const double x)                { roll = x; return; }
   double getRoll() const                      { return roll; }

   void setPitch(const double x)               { pitch = x; return; }
   double getPitch() const                     { return pitch; }

   void setHeading(const double x)             { heading = x; return; }
   double getHeading() const                   { return heading; }

   void setAltitude(const double x)            { altitude = x; return; }
   double getAltitude() const                  { return altitude; }

   void setThrottle(const double x)            { throttle = x; return; }
   double getThrottle() const                  { return throttle; }

   void setSpeed(const double x)               { speed = x; return; }
   double getSpeed() const                     { return speed; }

   void setPitchTrim(const double x)           { pitchTrim = x; return; }
   double getPitchTrim() const                 { return pitchTrim; }

   void setNumTracks(const unsigned int x)     { numTracks = x; return; }
   int getNumTracks() const                    { return numTracks; }

   //tracking setter
   void setTracking(const bool x)              { tracking = x; return; }
   //returns true if plane is currently tracking
   bool isTracking() const                     { return tracking; }

   void setMissileFired(const bool x)          { missileFired = x; return; }
   bool isMissileFired() const                 { return missileFired; }

   void setTargetTrack(const unsigned int x)   { targetTrack = x; return; }
   unsigned int getTargetTrack() const         { return targetTrack; }

   void setNumEngines(const unsigned int x)    { numEngines = x; return; }
   int getNumEngines() const                   { return numEngines; }

   void setIncomingMissile(const bool x)       { incomingMissile = x; return; }
   bool isIncomingMissile() const              { return incomingMissile; }

   //sets the pitch to current object being tracked
   void setPitchToTracked(const unsigned int track, const double angle);
   double getPitchToTracked(const unsigned int track) const;

   void setHeadingToTracked(const unsigned int track, const double angle);
   double getHeadingToTracked(const unsigned int track) const;

   void setDistanceToTracked(const unsigned int track, const double distance);
   double getDistanceToTracked(const unsigned int track) const;

private:

   bool alive;
   double roll;
   double pitch;
   double heading;
   double altitude;
   double throttle;
   double speed;
   double pitchTrim;
   static const int MAX_TRACKS = 50;
   double pitchToTracked[MAX_TRACKS];
   double headingToTracked[MAX_TRACKS];
   double distanceToTracked[MAX_TRACKS];
   unsigned int targetTrack;
   unsigned int numTracks;
   bool tracking;
   bool missileFired;
   bool incomingMissile;
   int numEngines;

};

}
}

#endif

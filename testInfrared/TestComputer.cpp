
#include "TestComputer.hpp"

#include "openeaagles/models/Track.hpp"
#include "openeaagles/models/system/AngleOnlyTrackManager.hpp"
#include "openeaagles/models/player/AbstractWeapon.hpp"
#include "openeaagles/models/system/IrSeeker.hpp"
#include "openeaagles/models/system/IrSensor.hpp"

#include "openeaagles/models/WorldModel.hpp"

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestComputer, "TestComputer")
EMPTY_SERIALIZER(TestComputer)
EMPTY_DELETEDATA(TestComputer)

TestComputer::TestComputer()
{
   STANDARD_CONSTRUCTOR()
}

void TestComputer::reset()
{
   BaseClass::reset();
   uncaged=false;
   haveTarget=false;
}

void TestComputer::copyData(const TestComputer& org, const bool cc)
{
   BaseClass::copyData(org);
   uncaged=false;
   haveTarget=false;
}

//------------------------------------------------------------------------------
// updateTC() -- override the System:: version so that we can get process call to our
//               components (our TM) before we do our own processing
//------------------------------------------------------------------------------
void TestComputer::updateTC(const double dt0)
{
#if 0
   // easy one-step way to test overriding the override
   BaseClass::updateTC(dt0);
#else
   // We're nothing without an ownship ...
   if (getOwnship() == nullptr) return;

   // ---
   // Delta time
   // ---

   // real or frozen?
   double dt = dt0;
   if (isFrozen()) dt = 0.0;

   // Delta time for methods that are running every fourth phase
   const double dt4 = dt * 4.0;

   // ---
   // Four phases per frame
   // ---
   oe::simulation::Simulation* sim = getOwnship()->getWorldModel();
   if (sim == nullptr) return;

   // ---
   // bypass System:: version, forward call to Component directly,
   // and use 'dt' because if we're frozen then so are our subcomponents.
   // ---
   oe::base::Component::updateTC(dt);

   switch (sim->phase()) {

      case 0 : // Frame0 --- Dynamics method
         dynamics(dt4);
         break;

      case 1 : // Frame1 --- Transmit method
         transmit(dt4);
         break;

      case 2 : // Frame2 --- Receive method
         receive(dt4);
         break;

      case 3 : // Frame3 --- Process method
         process(dt4);
         break;
   }
#endif
}

//------------------------------------------------------------------------------
// process() -- Process phase
//------------------------------------------------------------------------------
void TestComputer::process(const double dt)
{
   BaseClass::process(dt);

   const auto irSeeker = dynamic_cast<oe::models::IrSeeker*>(getOwnship()->getGimbal());
   if (irSeeker) {
      haveTarget = processIr();
   }
}

//------------------------------------------------------------------------------
// Update gimbal for latest trackmanager track information/prediction,
// Update targetPlayer for dynamics model if change of target/track
// Return true if we have a target
//------------------------------------------------------------------------------
bool TestComputer::processIr()
{
   // set the seeker/gimbal free to track target if just launched
   if (uncaged==false && getOwnship()->isMode(oe::models::Player::ACTIVE))
      uncaged = true;

   // waiting on getnexttarget may mean missing one or two updates
   // because we have to wait for obc::updateShootList which is an updateData task
   oe::models::Track* irTrk = getNextTarget();
   if (irTrk && uncaged) {
      // we have a target and our gimbal must be updated
      double pt_az = irTrk->getPredictedAzimuth();
      double pt_el = irTrk->getPredictedElevation();

      const auto irSeeker = dynamic_cast<oe::models::IrSeeker*>(getOwnship()->getGimbal());

      // reposition seeker/gimbal to follow IR target
      if (irSeeker) {
         irSeeker->setCmdPos(pt_az, pt_el);

         if (isMessageEnabled(MSG_DEBUG))
            std::cout << "TestComputer::processIr : cmdpos " << irSeeker->getCmdAz() << " " << irSeeker->getCmdElev() << std::endl;
      }
   }

   const auto ourWeapon = dynamic_cast<oe::models::AbstractWeapon*>(getOwnship());

   // update the weapon's tracking if the target changed (includes loss of target)
   // weapon::targetPlayer tells the dynamics model where the target is -
   // if the seeker has no track, then the targetPlayer must be cleared

   oe::models::Player* irTarget = nullptr;
   if (irTrk)
      irTarget = irTrk->getTarget();
   // tell the missile what to track
   if (irTarget!= ourWeapon->getTargetPlayer()) {
      std::cout << "TestComputer::processIr : changed target: old " << ourWeapon->getTargetPlayer() << " new: " << irTarget << std::endl;
      ourWeapon->setTargetPlayer(irTarget, true);
   }
   return (irTarget != nullptr);
}

//------------------------------------------------------------------------------
// updateShootList() -- Update the shoot list.  When the step flag is true,
//                      force step to the next target.
//------------------------------------------------------------------------------
void TestComputer::updateShootList(const bool step)
{
   // Temporary next to shoot indexes
   int cNTS = -1;  // Current
   int nNTS = -1;  // New

   // First, let's get the active track list
   const unsigned int MAX_TRKS = 20;
   oe::base::safe_ptr<oe::models::Track> trackList[MAX_TRKS];

   int n = 0;
   oe::models::TrackManager* tm = getTrackManagerByType(typeid(oe::models::AngleOnlyTrackManager));
   if (tm != nullptr) n = tm->getTrackList(trackList, MAX_TRKS);

   if (isMessageEnabled(MSG_DEBUG)) {
      for (int i = 0; i < n; i++) {
         oe::models::Track* trk = trackList[i];
         const auto irTrk = dynamic_cast<oe::models::IrTrack*>(trk);
         std::cout << irTrk->getTarget()->getID() << " avg " << irTrk->getAvgSignal() << " max " << irTrk->getMaxSignal() << std::endl;
      }
   }

   if (n > 0) {
      // ---
      // Update the next to shoot?
      // ---
      if (cNTS < 0) {
         // 1) When we don't have or couldn't find our NTS, pick the track w/ strongest signal
         int i = 0;
         do {
            //if (trackList[i]->getGroundSpeed() >= 1.0f) {
               if (nNTS >= 0) {
                  // is this one closer?
                  oe::models::Track* trk = trackList[i];
                  const auto irTrk = dynamic_cast<oe::models::IrTrack*>(trk);

                  trk = trackList[nNTS];
                  const auto irTrknNTS = dynamic_cast<oe::models::IrTrack*>(trk);

                  if (irTrk->getAvgSignal() > irTrknNTS->getAvgSignal()) {
                     nNTS = i;
                  }
               }
               else {
                  // only one so far
                  nNTS = i;
               }
            //}
            i = i + 1;
            if (i >= n) i = 0;
         } while (i != 0);
      }
      //else if (step) {
      //   // 2) When a target step has been requested ...
      //   int i = cNTS + 1;
      //   if (i >= n) i = 0;
      //   do {
      //      //if (trackList[i]->getGroundSpeed() >= 50.0f) {
      //         nNTS = i;
      //      //}
      //      i = i + 1;
      //      if (i >= n) i = 0;
      //   } while (nNTS < 0 && i != cNTS);
      //}
      //else {
      //   // 3) Keep the same next-to-shoot track
      //   nNTS = cNTS;
      //}

      // ---
      // update the shoot list index values in the tracks
      // ---
      if (nNTS >= 0) {
         // Start at the next-to-shoot
         int idx = nNTS;
         for (int i = 0; i < n; i++) {
            trackList[idx++]->setShootListIndex(i+1);
            if (idx >= n) idx = 0;
         }
      }
      else {
         // When there isn't a next to shoot, clear all
         for (int i = 0; i < n; i++) trackList[i]->setShootListIndex(0);
      }
   }

   // Update the next to shoot
   if (nNTS >= 0) setNextToShoot( trackList[nNTS] );
   else setNextToShoot(nullptr);
}

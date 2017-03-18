
#include "TestDisplay.hpp"
#include "TestStation.hpp"

#include "openeaagles/models/player/Aam.hpp"
#include "openeaagles/models/player/AirVehicle.hpp"
#include "openeaagles/models/system/StoresMgr.hpp"

#include "openeaagles/simulation/Simulation.hpp"

#include "openeaagles/graphics/SymbolLoader.hpp"

#include "openeaagles/base/Boolean.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/PairStream.hpp"

IMPLEMENT_SUBCLASS(TestDisplay, "TestDisplay")
EMPTY_SLOTTABLE(TestDisplay)
EMPTY_SERIALIZER(TestDisplay)
EMPTY_DELETEDATA(TestDisplay)

BEGIN_EVENT_HANDLER(TestDisplay)
   ON_EVENT('r',onResetKey)        // Station Reset
   ON_EVENT('R',onResetKey)        // Station Reset
   ON_EVENT('f',onFreezeKey)       // Simulation Freeze
   ON_EVENT('F',onFreezeKey)       // Simulation Freeze
   ON_EVENT('l',onWpnRelKey)       // Launch
   ON_EVENT('L',onWpnRelKey)       // Launch
   ON_EVENT('p',onPreRelKey)       // Pre-launch
   ON_EVENT('P',onPreRelKey)       // Pre-launch
   ON_EVENT('i',onIncRngKey)       // Increase range
   ON_EVENT('I',onIncRngKey)       // Increase range
   ON_EVENT('d',onDecRngKey)       // Decrease range
   ON_EVENT('D',onDecRngKey)       // Decrease range
   ON_EVENT('s',onStepOwnshipKey)  // Step ownship
   ON_EVENT('S',onStepOwnshipKey)  // Step ownship
END_EVENT_HANDLER()

TestDisplay::TestDisplay() : myStation(nullptr)
{
   STANDARD_CONSTRUCTOR()
}

void TestDisplay::copyData(const TestDisplay& org, const bool)
{
   BaseClass::copyData(org);

   myStation = nullptr;
   for (unsigned int i = 0; i < MAX_TRACKS; i++) {
      tracks[i] = nullptr;
      trkIdx[i] = 0;
   }

   range = org.range;
}


//------------------------------------------------------------------------------
// Event handlers
//------------------------------------------------------------------------------

// reset simulation
bool TestDisplay::onResetKey()
{
   if ( getSimulation() != nullptr ) {
      getSimulation()->event(RESET_EVENT);
   }
   return true;
}

// freeze simulation
bool TestDisplay::onFreezeKey()
{
   if ( getSimulation() != nullptr ) {
      oe::base::Boolean newFrz( !getSimulation()->isFrozen() );
      getSimulation()->event(FREEZE_EVENT, &newFrz);
   }
   return true;
}


// Weapon Release Switch
bool TestDisplay::onWpnRelKey()
{
   if (getOwnship() != nullptr) {
      oe::models::StoresMgr* sms = getOwnship()->getStoresManagement();
      if (sms != nullptr) {
         sms->setWeaponDeliveryMode(oe::models::StoresMgr::A2A);
         getOwnship()->event(WPN_REL_EVENT);
      }
   }
   return true;
}

// Pre-Release Switch
bool TestDisplay::onPreRelKey()
{
    if (getOwnship() != nullptr) {
       oe::models::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            sms->setWeaponDeliveryMode(oe::models::StoresMgr::A2A);
            oe::models::AbstractWeapon* wpn = sms->getCurrentWeapon();
            if (wpn != nullptr) {
               wpn->prerelease();
               std::cout << "Prelaunched wpn = " << wpn << std::endl;
            }
        }
    }
    return true;
}

// Increase range key
bool TestDisplay::onIncRngKey()
{
   double rng = range * 2.0;
   if (rng < 200) range =  rng;
   return true;
}

// Decrease range key
bool TestDisplay::onDecRngKey()
{
   double rng = range / 2.0;
   if (rng >= 2.0) range = rng;
   return true;
}

// Step ownship key
bool TestDisplay::onStepOwnshipKey()
{
   const auto ts = dynamic_cast<TestStation*>(getStation());
   if ( ts != nullptr ) {
      ts->stepOwnshipPlayer();
   }
   return true;
}

//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void TestDisplay::updateData(const double dt)
{
    // Send flight data to readouts
    if (getOwnship() != nullptr) {

       send("hsi", UPDATE_VALUE5, getOwnship()->getHeadingR(), headingSD);
       send("rangeRO", UPDATE_VALUE, range, rangeSD);

       // Maintain Air Tracks
       oe::base::Pair* pair = findByName("airTracks");
       if (pair != nullptr) {
          const auto myLoader = dynamic_cast<oe::graphics::SymbolLoader*>(pair->object());
          if (myLoader != nullptr) {
             myLoader->setRange(range);
             myLoader->setHeadingDeg(getOwnship()->getHeadingD());
             myLoader->setNorthUp(false);

             maintainAirTrackSymbols(myLoader, range);
          }
       }
    }

    // Update base classes stuff
    BaseClass::updateData(dt);
}

//------------------------------------------------------------------------------
// maintainAirTrackSymbols() -- maintain the air track symbology
//------------------------------------------------------------------------------
void TestDisplay::maintainAirTrackSymbols(oe::graphics::SymbolLoader* loader, const double rng)
{
   int codes[MAX_TRACKS] {};              // Work codes: empty(0), matched(1), unmatched(-1)
   const double rng2 = (rng * rng);       // Range squared (KM * KM)

   oe::models::Player* newTracks[MAX_TRACKS] {};   // New tracks to add
   int nNewTracks {};                              // Number of new tracks
   oe::models::Player* target = nullptr;

   // The real maximum number of tracks is the smaller of MAX_TRACKS and the loader's maximum
   int maxTracks = loader->getMaxSymbols();
   if (MAX_TRACKS < static_cast<unsigned int>(maxTracks)) maxTracks = MAX_TRACKS;

   // Set the initial codes
   for (int i = 0; i < maxTracks; i++) {
      if (tracks[i] != nullptr) codes[i] = -1;  // needs to be matched
      else codes[i] = 0;                        // empty slot
   }

   // find all air vehicles within range
   {
      // get the player list
      oe::simulation::Simulation* sim = getSimulation();
      oe::base::PairStream* plist = sim->getPlayers();

      // search for air vehicles or missiles within range
      oe::base::List::Item* item = plist->getFirstItem();
      while (item != nullptr && nNewTracks < maxTracks) {
         const auto pair = static_cast<oe::base::Pair*>(item->getValue());
         const auto p = static_cast<oe::models::Player*>(pair->object());
         oe::base::Vec3d rpos = p->getPosition() - getOwnship()->getPosition();
         const double x = rpos[0] * oe::base::distance::M2NM;
         const double y = rpos[1] * oe::base::distance::M2NM;

         const auto weapon = dynamic_cast<oe::models::AbstractWeapon*>(p);
         if (weapon && (weapon->isMode(oe::models::Player::PRE_RELEASE) || weapon->isActive())) {
            target = weapon->getTargetPlayer();
         }

         if (
            p != getOwnship() &&
            p->isActive() &&
            ((x*x + y*y) < rng2) &&
            (p->isClassType(typeid(oe::models::AirVehicle)) || p->isClassType(typeid(oe::models::Missile))) ) {
               // Ok, it's an active air vehicle or missile that's within range, and it's not us.

               // Are we already in the track list?
               bool found = false;
               for (unsigned int i = 0; !found && i < static_cast<unsigned int>(maxTracks); i++) {
                  if (p == tracks[i]) {
                     // Yes it is.  So mark the slot as matched!
                     codes[i] = 1;
                     found = true;
                  }
               }

               // If not found then add it to the new tracks list
               if (!found) {
                  p->ref();
                  newTracks[nNewTracks++] = p;
               }

         }
         item = item->getNext();
      }

      plist->unref();
   }


   // Now remove any unmatched tracks
   for (int i = 0; i < maxTracks; i++) {
      if (codes[i] == -1) {
         // This is an old symbol that wasn't matched with a valid player
         loader->removeSymbol( trkIdx[i] );
         tracks[i]->unref();       // unref the player
         tracks[i] = nullptr;      // clear the player pointer
         trkIdx[i] = 0;            // clear the index
         codes[i]  = 0;            // slot is now empty
      }
   }

   // Now add any new tracks
   {
      int islot = 0;      // slot index
      int inew = 0;       // new track index

      while (inew < nNewTracks && islot < maxTracks) {
         if (codes[islot] == 0) {
            // We have an empty slot, so add the symbol

            int type = 4;                                                            // unknown
            if (newTracks[inew]->isClassType(typeid(oe::models::AirVehicle))) {
               if (newTracks[inew]->isSide(oe::models::Player::BLUE)) type = 1;      // friend
               else if (newTracks[inew]->isSide(oe::models::Player::RED)) type = 2;  // foe
               else type = 3; // neutral/commercial
            }
            else if (newTracks[inew]->isClassType(typeid(oe::models::Missile))) {
               type = 5;                                                             // missile
            }

            tracks[islot] = newTracks[inew];
            trkIdx[islot] = loader->addSymbol( type, nullptr);
            if (trkIdx[islot] == 0) {
               // it didn't make it in for some unknown reason
               tracks[islot]->unref();
               tracks[islot] = nullptr;
            }
            inew++;

         }
         islot++;
      }

      // unref any air vehicles that didn't make it
      while (inew < nNewTracks) {
         newTracks[inew++]->unref();
      }
   }

   // now update the active tracks
   const auto os = dynamic_cast<oe::models::Player*>(getOwnship());
   for (int i = 0; i < maxTracks; i++) {
      const double osX = os->getXPosition();
      const double osY = os->getYPosition();
      if (tracks[i] != nullptr && trkIdx[i] != 0) {
         double xp = tracks[i]->getXPosition() - osX;
         double yp = tracks[i]->getYPosition() - osY;
         loader->updateSymbolPositionXY( trkIdx[i], (xp * oe::base::distance::M2NM), (yp * oe::base::distance::M2NM) );
         loader->updateSymbolHeading( trkIdx[i], tracks[i]->getHeadingD() );
         if (tracks[i]==target) {
            //const auto temp = new base::Identifier("green");
            //loader->changeSymbolColor(trkIdx[i], 0, temp);
            loader->setSymbolFlashRate(trkIdx[i], nullptr, 2);
         }
      }
   }
}

//------------------------------------------------------------------------------
// Simulation access functions
//------------------------------------------------------------------------------
oe::models::Player* TestDisplay::getOwnship()
{
   oe::models::Player* p = nullptr;
   oe::simulation::Station* sta = getStation();
   if (sta != nullptr) {
      p = dynamic_cast<oe::models::Player*>(sta->getOwnship());
   }
   return p;
}

oe::simulation::Simulation* TestDisplay::getSimulation()
{
   oe::simulation::Simulation* s = nullptr;
   oe::simulation::Station* sta = getStation();
   if (sta != nullptr) s = sta->getSimulation();
   return s;
}

oe::simulation::Station* TestDisplay::getStation()
{
   if (myStation == nullptr) {
      const auto s = dynamic_cast<oe::simulation::Station*>( findContainerByType(typeid(oe::simulation::Station)) );
      if (s != nullptr) myStation = s;
   }
   return myStation;
}

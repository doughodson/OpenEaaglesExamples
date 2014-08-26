
#include "TestDisplay.h"
#include "TestStation.h"

#include "openeaagles/simulation/AirVehicle.h"
#include "openeaagles/simulation/Aam.h"
#include "openeaagles/simulation/Simulation.h"
#include "openeaagles/simulation/StoresMgr.h"
#include "openeaagles/basicGL/SymbolLoader.h"
#include "openeaagles/basic/Boolean.h"
#include "openeaagles/basic/Pair.h"
#include "openeaagles/basic/PairStream.h"
#include "openeaagles/basic/units/Distances.h"

namespace Eaagles {
namespace Example {

IMPLEMENT_SUBCLASS(TestDisplay,"TestDisplay")
EMPTY_SLOTTABLE(TestDisplay)
EMPTY_SERIALIZER(TestDisplay)
EMPTY_DELETEDATA(TestDisplay)

// Event() map
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

//------------------------------------------------------------------------------
// Class support functions
//------------------------------------------------------------------------------

// constructor
TestDisplay::TestDisplay() : myStation(0)
{
   STANDARD_CONSTRUCTOR()

   for (unsigned int i = 0; i < MAX_TRACKS; i++) {
      tracks[i] = 0;
      trkIdx[i] = 0;
   }
   range = 40.0;
}

// copy member data
void TestDisplay::copyData(const TestDisplay& org, const bool)
{
   BaseClass::copyData(org);

   myStation = 0;
   for (int i = 0; i < MAX_TRACKS; i++) {
      tracks[i] = 0;
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
   if ( getSimulation() != 0 ) {
      getSimulation()->event(RESET_EVENT);
   }
   return true;
}

// freeze simulation
bool TestDisplay::onFreezeKey()
{
   if ( getSimulation() != 0 ) {
      Basic::Boolean newFrz( !getSimulation()->isFrozen() );
      getSimulation()->event(FREEZE_EVENT, &newFrz);
   }
   return true;
}


// Weapon Release Switch
bool TestDisplay::onWpnRelKey()
{
   if (getOwnship() != 0) {
      Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
      if (sms != 0) {
         sms->setWeaponDeliveryMode(Simulation::StoresMgr::A2A);
         getOwnship()->event(WPN_REL_EVENT);
      }
   }
   return true;
}

// Pre-Release Switch
bool TestDisplay::onPreRelKey()
{
    if (getOwnship() != 0) {
       Simulation::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != 0) {
            sms->setWeaponDeliveryMode(Simulation::StoresMgr::A2A);
            Simulation::Weapon* wpn = sms->getCurrentWeapon();
            if (wpn != 0) {
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
   LCreal rng = range * 2.0f;
   if (rng < 200) range =  rng;
   return true;
}

// Decrease range key
bool TestDisplay::onDecRngKey()
{
   LCreal rng = range / 2.0f;
   if (rng >= 2.0) range = rng;
   return true;
}

// Step ownship key
bool TestDisplay::onStepOwnshipKey()
{
   TestStation* ts = dynamic_cast<TestStation*>(getStation());
   if ( ts != 0 ) {
      ts->stepOwnshipPlayer();
   }
   return true;
}

//------------------------------------------------------------------------------
// updateData() -- update non-time critical stuff here
//------------------------------------------------------------------------------
void TestDisplay::updateData(const LCreal dt)
{
    // Send flight data to readouts
    if (getOwnship() != 0) {

       send("hsi", UPDATE_VALUE5, getOwnship()->getHeadingR(), headingSD);
       send("rangeRO", UPDATE_VALUE, range, rangeSD);


       // Maintain Air Tracks
       Basic::Pair* pair = findByName("airTracks");
       if (pair != 0) {
          BasicGL::SymbolLoader* myLoader = dynamic_cast<BasicGL::SymbolLoader*>(pair->object());
          if (myLoader != 0) {
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
void TestDisplay::maintainAirTrackSymbols(BasicGL::SymbolLoader* loader, const LCreal rng)
{
   int codes[MAX_TRACKS];              // Work codes: empty(0), matched(1), unmatched(-1)
   LCreal rng2 = (rng * rng);          // Range squared (KM * KM)

   Simulation::Player* newTracks[MAX_TRACKS];  // New tracks to add
   int nNewTracks = 0;                         // Number of new tracks
   Simulation::Player* target = 0;

   // The real maximum number of tracks is the smaller of MAX_TRACKS and the loader's maximum
   int maxTracks = loader->getMaxSymbols();
   if (MAX_TRACKS < maxTracks) maxTracks = MAX_TRACKS;

   // Set the initial codes
   for (int i = 0; i < maxTracks; i++) {
      if (tracks[i] != 0) codes[i] = -1;  // needs to be matched
      else codes[i] = 0;                  // empty slot
   }

   // find all air vehicles within range
   {
      // get the player list
      Simulation::Simulation* sim = getSimulation();
      Basic::PairStream* plist = sim->getPlayers();

      // search for air vehicles or missiles within range
      Basic::List::Item* item = plist->getFirstItem();
      while (item != 0 && nNewTracks < maxTracks) {
         Basic::Pair* pair = static_cast<Basic::Pair*>(item->getValue());
         Simulation::Player* p = static_cast<Simulation::Player*>(pair->object());
         osg::Vec3 rpos = p->getPosition() - getOwnship()->getPosition();
         LCreal x = rpos[0] * Basic::Distance::M2NM;
         LCreal y = rpos[1] * Basic::Distance::M2NM;

         Simulation::Weapon* weapon = dynamic_cast<Simulation::Weapon*>(p);
         if (weapon && (weapon->isMode(Simulation::Player::PRE_RELEASE) || weapon->isActive())) {
            target = weapon->getTargetPlayer();
         }

         if (
            p != getOwnship() && 
            p->isActive() &&
            ((x*x + y*y) < rng2) &&
            (p->isClassType(typeid(Simulation::AirVehicle)) || p->isClassType(typeid(Simulation::Missile))) ) {
               // Ok, it's an active air vehicle or missile that's within range, and it's not us.

               // Are we already in the track list?
               bool found = false;
               for (int i = 0; !found && i < maxTracks; i++) {
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
         tracks[i]->unref(); // unref the player
         tracks[i] = 0;      // clear the player pointer
         trkIdx[i] = 0;      // clear the index
         codes[i]  = 0;      // slot is now empty
      }
   }

   // Now add any new tracks
   {
      int islot = 0;      // slot index
      int inew = 0;       // new track index

      while (inew < nNewTracks && islot < maxTracks) {
         if (codes[islot] == 0) {
            // We have an empty slot, so add the symbol

            int type = 4;                                       // unknown
            if (newTracks[inew]->isClassType(typeid(Simulation::AirVehicle))) {
               if (newTracks[inew]->isSide(Simulation::Player::BLUE)) type = 1;      // friend
               else if (newTracks[inew]->isSide(Simulation::Player::RED)) type = 2; // foe  
               else type = 3; // neutral/commercial
            }
            else if (newTracks[inew]->isClassType(typeid(Simulation::Missile))) {
               type = 5; // Missile
            }


            tracks[islot] = newTracks[inew];
            trkIdx[islot] = loader->addSymbol( type, 0);
            if (trkIdx[islot] == 0) {
               // it didn't make it in for some unknown reason
               tracks[islot]->unref();
               tracks[islot] = 0;
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
   for (int i = 0; i < maxTracks; i++) {
      double osX = getOwnship()->getXPosition();
      double osY = getOwnship()->getYPosition();
      if (tracks[i] != 0 && trkIdx[i] != 0) {
         double xp = tracks[i]->getXPosition() - osX;
         double yp = tracks[i]->getYPosition() - osY;
         loader->updateSymbolPositionXY( trkIdx[i], (xp * Basic::Distance::M2NM), (yp * Basic::Distance::M2NM) );
         loader->updateSymbolHeading( trkIdx[i], tracks[i]->getHeadingD() );
         if (tracks[i]==target) {
            //Basic::Identifier* temp = new Basic::Identifier("green");
            //loader->changeSymbolColor(trkIdx[i], 0, temp);
            loader->setSymbolFlashRate(trkIdx[i], 0, 2);
         }
      }
   }
}


//------------------------------------------------------------------------------
// Simulation access functions
//------------------------------------------------------------------------------
Simulation::Player* TestDisplay::getOwnship()
{
   Simulation::Player* p = 0;
   Simulation::Station* sta = getStation();
   if (sta != 0) p = sta->getOwnship();
   return p;
}

Simulation::Simulation* TestDisplay::getSimulation()
{
   Simulation::Simulation* s = 0;
   Simulation::Station* sta = getStation();
   if (sta != 0) s = sta->getSimulation();
   return s;
}

Simulation::Station* TestDisplay::getStation()
{
   if (myStation == 0) {
      Simulation::Station* s = dynamic_cast<Simulation::Station*>( findContainerByType(typeid(Simulation::Station)) );
      if (s != 0) myStation = s;
   }
   return myStation;
}

} // End Example namespace
} // End Eaagles namespace

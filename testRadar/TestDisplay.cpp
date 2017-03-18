
#include "TestDisplay.hpp"
#include "TestStation.hpp"
#include "DspRadar.hpp"
#include "DspRwr.hpp"

#include "openeaagles/models/player/AirVehicle.hpp"
#include "openeaagles/models/player/Missile.hpp"
#include "openeaagles/models/player/AbstractWeapon.hpp"

#include "openeaagles/models/system/Jammer.hpp"
#include "openeaagles/models/system/Radar.hpp"
#include "openeaagles/models/system/Rwr.hpp"
#include "openeaagles/models/system/StoresMgr.hpp"
#include "openeaagles/models/sensor/Gmti.hpp"
#include "openeaagles/models/sensor/Tws.hpp"

#include "openeaagles/simulation/Simulation.hpp"

#include "openeaagles/base/Boolean.hpp"
#include "openeaagles/base/Pair.hpp"
#include "openeaagles/base/PairStream.hpp"
#include "openeaagles/graphics/SymbolLoader.hpp"
#include <GL/glut.h>

using namespace oe;

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(TestDisplay, "TestDisplay")
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
   ON_EVENT('s',onTgtStepKey)      // Step target
   ON_EVENT('S',onTgtStepKey)      // Step target
   ON_EVENT('2',onRtn2SearchKey)   // Return to search
   ON_EVENT('a',onAir2AirKey)      // A/A mode toggle
   ON_EVENT('A',onAir2AirKey)      // A/A mode toggle
   ON_EVENT('g',onAir2GndKey)      // A/G mode toggle
   ON_EVENT('G',onAir2GndKey)      // A/G mode toggle
   ON_EVENT('i',onIncRngKey)       // Increase range
   ON_EVENT('I',onIncRngKey)       // Increase range
   ON_EVENT('d',onDecRngKey)       // Decrease range
   ON_EVENT('D',onDecRngKey)       // Decrease range
   ON_EVENT('+',onStepOwnshipKey)  // Step ownship
END_EVENT_HANDLER()

TestDisplay::TestDisplay() : myStation(nullptr)
{
   STANDARD_CONSTRUCTOR()
}

void TestDisplay::copyData(const TestDisplay& org, const bool)
{
   BaseClass::copyData(org);

   myStation = nullptr;
   tracks.fill(nullptr);
   trkIdx.fill(0);
   rdrDisplay = nullptr;
   rwrDisplay = nullptr;
   range = org.range;

   rangeSD.empty();
   headingSD.empty();
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
        base::Boolean newFrz( !getSimulation()->isFrozen() );
        getSimulation()->event(FREEZE_EVENT, &newFrz);
    }
    return true;
}

// Weapon Release Switch
bool TestDisplay::onWpnRelKey()
{
    if (getOwnship() != nullptr) {
        getOwnship()->event(WPN_REL_EVENT);
    }
    return true;
}

// Pre-Release Switch
bool TestDisplay::onPreRelKey()
{
    if (getOwnship() != nullptr) {
       models::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            models::AbstractWeapon* wpn = sms->getCurrentWeapon();
            if (wpn != nullptr) {
               wpn->prerelease();
               std::cout << "Prelaunched wpn = " << wpn << std::endl;
            }
        }
    }
    return true;
}

// Target Step Switch
bool TestDisplay::onTgtStepKey()
{
    if (getOwnship() != nullptr) {
        getOwnship()->event(TGT_STEP_EVENT);
    }
    return true;
}

// Target Step Switch
bool TestDisplay::onRtn2SearchKey()
{
    if (getOwnship() != nullptr) {
        getOwnship()->event(SENSOR_RTS);
    }
    return true;
}

// Air to Air mode key
bool TestDisplay::onAir2AirKey()
{
    if (getOwnship() != nullptr) {
       models::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            sms->setWeaponDeliveryMode(models::StoresMgr::A2A);
            std::cout << "Set A/A Weapon Mode!" << std::endl;
        }
    }
    return true;
}

// Air to Ground mode key
bool TestDisplay::onAir2GndKey()
{
    if (getOwnship() != nullptr) {
        models::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            sms->setWeaponDeliveryMode(models::StoresMgr::A2G);
            std::cout << "Set A/G Weapon Mode!" << std::endl;
        }
    }
    return true;
}

// Increase range key
bool TestDisplay::onIncRngKey()
{
    if (getOwnship() != nullptr) {
        models::Radar* rdr = nullptr;
        {
           base::Pair* pair = getOwnship()->getSensorByType(typeid(models::Tws));
           if (pair != nullptr) rdr = static_cast<models::Radar*>(pair->object());
        }
        models::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            // But could be GMTI ...
            if (sms->isWeaponDeliveryMode(models::StoresMgr::A2G)) {
                base::Pair* pair = getOwnship()->getSensorByType(typeid(models::Gmti));
                if (pair != nullptr) rdr = static_cast<models::Radar*>(pair->object());
            }
        }
        if (rdr != nullptr) {
            rdr->incRange();
        }
        else {
            range = range * 2.0f;
        }
    }
    return true;
}

// Decrease range key
bool TestDisplay::onDecRngKey()
{
    if (getOwnship() != nullptr) {
        models::Radar* rdr = nullptr;
        {
           base::Pair* pair = getOwnship()->getSensorByType(typeid(models::Tws));
           if (pair != nullptr) rdr = static_cast<models::Radar*>(pair->object());
        }
        models::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            // But could be GMTI
            if (sms->isWeaponDeliveryMode(models::StoresMgr::A2G)) {
                base::Pair* pair = getOwnship()->getSensorByType(typeid(models::Gmti));
                if (pair != nullptr) rdr = static_cast<models::Radar*>(pair->object());
            }
        }
        if (rdr != nullptr) {
            rdr->decRange();
        }
        else {
            range = range / 2.0f;
        }
    }
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

void TestDisplay::updateData(const double dt)
{
    // Find and update the test RADAR display
    {
        rdrDisplay = nullptr;
        base::Pair* p = findByType(typeid(DspRadar));
        if (p != nullptr) rdrDisplay = dynamic_cast<DspRadar*>( p->object() );
    }
    if (rdrDisplay != nullptr && getOwnship() != nullptr) {
        // Default is TWS
        models::Radar* rdr = nullptr;
        {
           base::Pair* pair = getOwnship()->getSensorByType(typeid(models::Tws));
           if (pair != nullptr) rdr = static_cast<models::Radar*>(pair->object());
        }
        models::StoresMgr* sms = getOwnship()->getStoresManagement();
        if (sms != nullptr) {
            // But could be GMTI ...
            if (sms->isWeaponDeliveryMode(models::StoresMgr::A2G)) {
                base::Pair* pair = getOwnship()->getSensorByType(typeid(models::Gmti));
                if (pair != nullptr) rdr = static_cast<models::Radar*>(pair->object());
            }
        }
        rdrDisplay->setRadar(rdr);
    }


    // Find and update the test RWR display
    {
        rwrDisplay = nullptr;
        base::Pair* p = findByType(typeid(DspRwr));
        if (p != nullptr) rwrDisplay = dynamic_cast<DspRwr*>( p->object() );
    }
    if (rwrDisplay != nullptr && getOwnship() != nullptr) {
        models::Rwr* rwr = nullptr;
        base::Pair* pair = getOwnship()->getSensorByType(typeid(models::Rwr));
        if (pair != nullptr) rwr = static_cast<models::Rwr*>(pair->object());
        rwrDisplay->setRwr(rwr);
    }

   // Send flight data to readouts
   if (getOwnship() != nullptr) {

      {
         models::Radar* rdr = nullptr;
         {
            base::Pair* pair = getOwnship()->getSensorByType(typeid(models::Tws));
            if (pair != nullptr) rdr = static_cast<models::Radar*>(pair->object());
         }
         models::StoresMgr* sms = getOwnship()->getStoresManagement();
         if (sms != nullptr) {
               // But could be GMTI ...
               if (sms->isWeaponDeliveryMode(models::StoresMgr::A2G)) {
                  base::Pair* pair = getOwnship()->getSensorByType(typeid(models::Gmti));
                  if (pair != nullptr) rdr = static_cast<models::Radar*>(pair->object());
               }
         }
         if (rdr != nullptr) range = rdr->getRange();
      }

      send("hsi", UPDATE_VALUE5, getOwnship()->getHeadingR(), headingSD);
      send("rangeRO", UPDATE_VALUE, range, rangeSD);


      // Maintain Air Tracks
      base::Pair* pair = findByName("airTracks");
      if (pair != nullptr) {
         const auto myLoader = dynamic_cast<graphics::SymbolLoader*>(pair->object());
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
// mouseEvent() -- Handle mouse inputs
//------------------------------------------------------------------------------
void TestDisplay::mouseEvent(const int button, const int state, const int x, const int y)
{
    setMouse(x,y);

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
      base::Pair* pair = findByName("airTracks");
      if (pair != nullptr) {
         const auto myLoader = dynamic_cast<graphics::SymbolLoader*>(pair->object());
         if (myLoader != nullptr) {
            graphics::Graphic* selected = pick(0);
            if (selected != nullptr) {
               int idx = myLoader->getSymbolIndex(selected);
               if (idx > 0) {
                  int found = -1;
                  for (unsigned int i = 0; found < 0 && i < MAX_TRACKS; i++) {
                     if (idx == trkIdx[i]) found = i;
                  }
                  if (found >= 0) {
                     getStation()->setOwnshipPlayer(tracks[found]);
                  }
               }
            }
         }
      }
    }
}

//------------------------------------------------------------------------------
// maintainAirTrackSymbols() -- maintain the air track symbology
//------------------------------------------------------------------------------
void TestDisplay::maintainAirTrackSymbols(graphics::SymbolLoader* loader, const double rng)
{
    int codes[MAX_TRACKS];              // Work codes: empty(0), matched(1), unmatched(-1)
    double rng2 = (rng * rng);          // Range squared (KM * KM)

    models::Player* newTracks[MAX_TRACKS];      // New tracks to add
    int nNewTracks = 0;                         // Number of new tracks

    // The real maximum number of tracks is the smaller of MAX_TRACKS and the loader's maximum
    int maxTracks = loader->getMaxSymbols();
    if (MAX_TRACKS < static_cast<unsigned int>(maxTracks)) maxTracks = MAX_TRACKS;

    // Set the initial codes
    for (int i = 0; i < maxTracks; i++) {
        if (tracks[i] != nullptr) codes[i] = -1;  // needs to be matched
        else codes[i] = 0;                  // empty slot
    }

    // find all air vehicles within range
    {
        // get the player list
        simulation::Simulation* sim = getSimulation();
        base::PairStream* plist = sim->getPlayers();

        // search for air vehicles or missiles within range
        base::List::Item* item = plist->getFirstItem();
        while (item != nullptr && nNewTracks < maxTracks) {

            const auto pair = static_cast<base::Pair*>(item->getValue());
            const auto p = static_cast<models::Player*>(pair->object());
            base::Vec3d rpos = p->getPosition() - getOwnship()->getPosition();
            double x = rpos[0] * base::distance::M2NM;
            double y = rpos[1] * base::distance::M2NM;

            if (
               p != getOwnship() &&
               p->isActive() &&
               ((x*x + y*y) < rng2) &&
               (p->isClassType(typeid(models::AirVehicle)) || p->isClassType(typeid(models::Missile))) ) {
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
            tracks[i] = nullptr;      // clear the player pointer
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
                if (newTracks[inew]->isClassType(typeid(models::AirVehicle))) {
                  if (newTracks[inew]->getSensorByType(typeid(models::Jammer)) == nullptr) {
                     // non-jammers
                     if (newTracks[inew]->isSide(models::Player::BLUE)) type = 1;      // friend
                     else if (newTracks[inew]->isSide(models::Player::RED)) type = 2; // foe
                     else type = 3; // neutral/commercial
                  }
                }
                else if (newTracks[inew]->isClassType(typeid(models::Missile))) {
                   type = 5; // Missile
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
    for (int i = 0; i < maxTracks; i++) {
        double osX = getOwnship()->getXPosition();
        double osY = getOwnship()->getYPosition();
        if (tracks[i] != nullptr && trkIdx[i] != 0) {
            double xp = tracks[i]->getXPosition() - osX;
            double yp = tracks[i]->getYPosition() - osY;
            loader->updateSymbolPositionXY( trkIdx[i], (xp * base::distance::M2NM), (yp * base::distance::M2NM) );
            loader->updateSymbolHeading( trkIdx[i], tracks[i]->getHeadingD() );
        }
    }

}

//------------------------------------------------------------------------------
// Simulation access functions
//------------------------------------------------------------------------------
models::Player* TestDisplay::getOwnship()
{
    models::Player* p = nullptr;
    simulation::Station* sta = getStation();
    if (sta != nullptr) {
       p = dynamic_cast<models::Player*>(sta->getOwnship());
    }
    return p;
}

simulation::Simulation* TestDisplay::getSimulation()
{
    simulation::Simulation* s = nullptr;
    simulation::Station* sta = getStation();
    if (sta != nullptr) s = sta->getSimulation();
    return s;
}

simulation::Station* TestDisplay::getStation()
{
    if (myStation == nullptr) {
        const auto s = dynamic_cast<simulation::Station*>( findContainerByType(typeid(simulation::Station)) );
        if (s != nullptr) myStation = s;
    }
    return myStation;
}
